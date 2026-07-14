#include "Application.h"
#include "Utility/VoxelGridLoader.h"
#include "Utility/BMPSaver.h"
#include "Core/CpuRenderer.h"

Main::Application::Application()
//	: renderer{ APPLICATION_NAME.data() }
{

}

Main::Application::~Application()
{

}

void Main::Application::Run()
{
	Core::GridInfo gridInfo{};
	std::vector<Core::Cell> grid;

	Utility::VoxelGridLoader::LoadGrid(MODEL_PATH, gridInfo, grid);

	std::vector<uint8_t> resultImage;

	Core::CpuRenderer cpuRenderer{};
	cpuRenderer.RenderVoxels(resultImage);

	Utility::BMPSaver::Save(CPU_IMAGE_PATH, resultImage);
}
