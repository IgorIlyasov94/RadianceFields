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
		Graphics::VkRenderer renderer;
	};
}
