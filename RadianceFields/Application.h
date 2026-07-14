#pragma once

#include "Includes.h"
#include "Graphics/VkRenderer.h"

namespace Main
{
	class Application
	{
	public:
		Application();
		~Application();

		void Run();

		static constexpr std::string_view APPLICATION_NAME = "Radiance Fields";

	private:
		Application(const Application&) = delete;
		Application(Application&&) = delete;
		Application& operator=(const Application&) = delete;
		Application& operator=(Application&&) = delete;

		static constexpr std::string_view MODEL_PATH = "Resources/VoxelGrid.bin";
		static constexpr std::string_view CPU_IMAGE_PATH = "CpuRenderResult.bmp";
		static constexpr std::string_view GPU_IMAGE_PATH = "GpuRenderResult.bmp";

		//Graphics::VkRenderer renderer;
	};
}
