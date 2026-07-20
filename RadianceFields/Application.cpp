#include "Application.h"
#include "Utility/VoxelGridLoader.h"
#include "Utility/BMPSaver.h"
#include "Core/Math.h"
#include "Core/CpuRenderer.h"
#include "Core/RegularRadianceFieldGrid.h"

Main::Application::Application()
	: cpuRenderer{}
//	: renderer{ APPLICATION_NAME.data() }
{

}

Main::Application::~Application()
{

}

void Main::Application::Run()
{
	Core::GridInfo gridInfo{};
	std::vector<Core::Cell> rawGrid;

	Utility::VoxelGridLoader::LoadGrid(MODEL_PATH, gridInfo, rawGrid);
	Core::RegularRadianceFieldGrid regularGrid(rawGrid, gridInfo);

	float3 volumeSize = float3(
		gridInfo.GridSize.x * gridInfo.VoxelSize.x,
		gridInfo.GridSize.y * gridInfo.VoxelSize.y,
		gridInfo.GridSize.z * gridInfo.VoxelSize.z);
	float3 testCameraPosition = gridInfo.Origin + volumeSize * 2.0f;
	float3 cameraDirection = Core::Math::Normalize(gridInfo.Origin - testCameraPosition);
	float testCameraFovY = Core::Camera::DEFAULT_FIELD_OF_VIEW_Y;

	Core::Viewport viewport(IMAGE_SIZE, 0.01f, 1000.0f);
	Core::Camera camera(testCameraPosition, cameraDirection, testCameraFovY, viewport);

	std::vector<float> resultImage;
	resultImage.resize(static_cast<size_t>(IMAGE_SIZE.x) * IMAGE_SIZE.y);

	cpuRenderer.SetGrid(&regularGrid);
	cpuRenderer.SetViewport(viewport);
	cpuRenderer.SetCamera(camera);
	cpuRenderer.SetTargetImage(resultImage);

	cpuRenderer.DispatchRays(Core::GridSampleMethod::SAMPLE_DENSITY, false);

	Utility::BMPSaver::Save(CPU_IMAGE_PATH, resultImage);
}
