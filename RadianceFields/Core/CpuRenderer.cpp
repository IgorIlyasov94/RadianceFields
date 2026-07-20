#include "CpuRenderer.h"
#include "../Utility/RadianceFieldsUtility.h"

using namespace Utility;

Core::CpuRenderer::CpuRenderer()
	: _camera{}, _viewport{}, _grid{}, targetImageAddress{}
{

}

Core::CpuRenderer::~CpuRenderer()
{

}

void Core::CpuRenderer::SetCamera(const Camera& camera)
{
	_camera = camera;
}

void Core::CpuRenderer::SetViewport(const Viewport& viewport)
{
	ValidateViewport(viewport);

	_viewport = viewport;
}

void Core::CpuRenderer::SetTargetImage(std::vector<float>& target)
{
	uint32_t totalSize = _viewport.Size.x * _viewport.Size.y;

	if (totalSize != target.size())
	{
		throw std::runtime_error("The Target Image must be the same size as the Viewport!");
	}

	if (totalSize == 0)
	{
		throw std::runtime_error("The Target Image must have size greater than zero!");
	}

	targetImageAddress = target.data();
}

void Core::CpuRenderer::SetGrid(IRadianceFieldGrid* grid) noexcept
{
	_grid = grid;
}

void Core::CpuRenderer::DispatchRays(GridSampleMethod sampleMethod, bool useMultithreading)
{
	if (_grid == nullptr)
	{
		throw std::runtime_error("The Grid is not set!");
	}

	if (targetImageAddress == nullptr)
	{
		throw std::runtime_error("The Target Image is not set!");
	}

	ValidateViewport(_viewport);

	uint32_t threadNumber = useMultithreading ? std::thread::hardware_concurrency() : 1u;
	threadNumber = std::max(threadNumber, MIN_THREAD_NUMBER);

	uint32_t totalRayNumber = _viewport.Size.x * _viewport.Size.y;
	uint32_t raysPerThread = totalRayNumber / threadNumber;
	uint32_t raysPerLastThread = raysPerThread + totalRayNumber % threadNumber;

	float3 cameraPosition = _camera.Position();
	float4x4 invViewProjectionMatrix = _camera.GetInvViewProjectionMatrix();

	std::vector<std::thread> threads;

	auto rayTracer = [&](uint32_t startRayIndex, uint32_t endRayIndex)
		{
			if (sampleMethod == GridSampleMethod::SAMPLE_DENSITY)
			{
				for (uint32_t rayIndex = startRayIndex; rayIndex < endRayIndex; rayIndex++)
				{
					uint32_t targetIndex = rayIndex;
					Ray ray = Ray::Build(rayIndex, cameraPosition, _viewport, invViewProjectionMatrix);
					float density = _grid->SampleDensity(ray);

					targetImageAddress[targetIndex] = std::max(density, 0.0f);
				}
			}
			else
			{
				for (uint32_t rayIndex = startRayIndex; rayIndex < endRayIndex; rayIndex++)
				{
					uint32_t targetIndex = rayIndex * 3u;
					Ray ray = Ray::Build(rayIndex, cameraPosition, _viewport, invViewProjectionMatrix);
					float3 color = _grid->SampleColor(ray);

					targetImageAddress[targetIndex + 0u] = color.x;
					targetImageAddress[targetIndex + 1u] = color.y;
					targetImageAddress[targetIndex + 2u] = color.z;
				}
			}
		};

	uint32_t startRayIndex = 0;
	uint32_t endRayIndex = threadNumber == 1u ? raysPerThread : raysPerLastThread;

	for (uint32_t threadIndex = 0; threadIndex < threadNumber;)
	{
		threads.emplace_back(rayTracer, startRayIndex, endRayIndex);

		threadIndex++;
		startRayIndex += threadIndex == (threadNumber - 1) ? raysPerThread : raysPerLastThread;
		endRayIndex += threadIndex == (threadNumber - 1) ? raysPerThread : raysPerLastThread;
	}

	for (std::thread& thread : threads)
	{
		if (thread.joinable())
		{
			thread.join();
		}
	}
}

inline void Core::CpuRenderer::ValidateViewport(const Viewport& viewport) const
{
	if (viewport.Size.x == 0 ||
		viewport.Size.y == 0 ||
		std::abs(viewport.ZNear - viewport.ZFar) < std::numeric_limits<float>::epsilon())
	{
		throw std::runtime_error("The Viewport is invalid!");
	}
}
