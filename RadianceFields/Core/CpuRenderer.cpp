#include "CpuRenderer.h"

Core::CpuRenderer::CpuRenderer()
	: _viewport{}, _grid{}, targetImageAddress{}
{

}

Core::CpuRenderer::~CpuRenderer()
{

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

void Core::CpuRenderer::DispatchRays(uint2 groupNumber, uint2 groupInnerLoopSize)
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

	uint32_t threadSimultaneousNumber = std::thread::hardware_concurrency();
	uint32_t totalRayNumber = _viewport.Size.x * _viewport.Size.y;
	uint32_t totalThreadNumber = CalculateTotalThreadNumber(_viewport, groupNumber);

	//std::vector<std::thread> threads;

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

inline uint32_t Core::CpuRenderer::CalculateTotalThreadNumber(const Viewport& viewport, uint2 groupNumber) const
{
	uint32_t totalThreadNumber = static_cast<uint32_t>(std::ceil(viewport.Size.x / static_cast<float>(groupNumber.x)));
	totalThreadNumber *= static_cast<uint32_t>(std::ceil(viewport.Size.y / static_cast<float>(groupNumber.y)));

	return totalThreadNumber;
}
