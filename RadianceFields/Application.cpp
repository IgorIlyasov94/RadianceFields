#include "Application.h"
#include "Utility/VoxelGridLoader.h"
#include "Utility/BMPSaver.h"
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

	std::vector<uint8_t> resultImage;

	//cpuRenderer.RenderVoxels(resultImage);

	Utility::BMPSaver::Save(CPU_IMAGE_PATH, resultImage);
}
