#pragma once

#include "../Includes.h"
#include <vulkan/vulkan.h>

namespace Graphics
{
	class VkRenderer
	{
	public:
		VkRenderer(const std::string_view& applicationName);
		~VkRenderer();

	private:
		VkRenderer() = delete;

		using DebugReportCallbackFuncType = VkBool32(VKAPI_PTR*)(VkDebugReportFlagsEXT flags,
			VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode,
			const char* layerPrefix, const char* message, void* userData);

		std::vector<const char*> CreateEnabledLayersData(bool enableValidationLayer) const;
		std::vector<const char*> CreateEnabledExtensionsData(bool enableValidationLayer) const;

		VkInstance CreateVulkanInstance(const std::string_view& applicationName,
			const std::vector<const char*>& enabledLayers,
			const std::vector<const char*>& enabledExtensions) const;

		void CreateDebugReportCallback(VkInstance instance, DebugReportCallbackFuncType callback,
			VkDebugReportCallbackEXT* reportCallback) const;

		inline void VkAssert(VkResult result,
			const std::source_location location = std::source_location::current()) const;

		static VKAPI_ATTR VkBool32 VKAPI_CALL DebugReportCallbackFunc(VkDebugReportFlagsEXT flags,
			VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode,
			const char* layerPrefix, const char* message, void* userData);

		static constexpr std::string_view KHRONOS_VALIDATION_LAYER_NAME = "VK_LAYER_KHRONOS_validation";
		static constexpr std::string_view LUNARG_VALIDATION_LAYER_NAME = "VK_LAYER_LUNARG_standard_validation";
		static constexpr std::string_view DEBUG_REPORT_EXTENSION_NAME = VK_EXT_DEBUG_REPORT_EXTENSION_NAME;

#ifdef NDEBUG
		static constexpr bool ENABLE_VALIDATION_LAYER = false;
#else
		static constexpr bool ENABLE_VALIDATION_LAYER = true;
#endif

		VkInstance vulkanInstance;
		VkDevice device;
		VkCommandBuffer commandBuffer;
		VkCommandPool commandPool;
		VkQueue commandQueue;
		VkFence fence;

		VkDebugReportCallbackEXT debugReportCallback;
	};
}
