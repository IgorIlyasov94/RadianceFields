#pragma once

#include "../Includes.h"
#include <vulkan/vulkan.h>

namespace Graphics
{
	class VkRenderer
	{
	public:
		VkRenderer(const std::string& applicationName);
		~VkRenderer();

	private:
		VkRenderer() = delete;

		std::vector<const char*> CreateEnabledLayersData(bool enableValidationLayer) const;
		std::vector<const char*> CreateEnabledExtensionsData() const;

		VkInstance CreateVulkanInstance(const std::string& applicationName,
			const std::vector<const char*>& enabledLayers,
			const std::vector<const char*>& enabledExtensions) const;

		inline void VkAssert(VkResult result,
			const std::source_location location = std::source_location::current()) const;

		static constexpr std::string_view KHRONOS_VALIDATION_LAYER_NAME = "VK_LAYER_KHRONOS_validation";
		static constexpr std::string_view LUNARG_VALIDATION_LAYER_NAME = "VK_LAYER_LUNARG_standard_validation";
		static constexpr std::string_view DEBUG_REPORT_EXTENSION_NAME = VK_EXT_DEBUG_REPORT_EXTENSION_NAME;

		VkInstance vulkanInstance;
		VkDevice device;
		VkCommandBuffer commandBuffer;
		VkCommandPool commandPool;
		VkQueue commandQueue;
		VkFence fence;
	};
}
