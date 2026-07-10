#include "VkRenderer.h"
#include "../Utility/RadianceFieldsUtility.h"

using namespace Utility;

Graphics::VkRenderer::VkRenderer(const std::string& applicationName)
{
    std::vector<const char*> enabledLayers = CreateEnabledLayersData(ENABLE_VALIDATION_LAYER);
    std::vector<const char*> enabledExtensions = CreateEnabledExtensionsData(ENABLE_VALIDATION_LAYER);

    vulkanInstance = CreateVulkanInstance(applicationName, enabledLayers, enabledExtensions);

    if constexpr (ENABLE_VALIDATION_LAYER)
    {
        CreateDebugReportCallback(vulkanInstance, DebugReportCallbackFunc, &debugReportCallback);
    }


}

Graphics::VkRenderer::~VkRenderer()
{
    vkDestroyFence(device, fence, nullptr);
    vkDestroyCommandPool(device, commandPool, nullptr);
    vkDestroyDevice(device, nullptr);
    vkDestroyInstance(vulkanInstance, nullptr);
}

std::vector<const char*> Graphics::VkRenderer::CreateEnabledLayersData(bool enableValidationLayer) const
{
    std::vector<const char*> enabledLayers;

    if (enableValidationLayer)
    {
        uint32_t layerNumber;
        vkEnumerateInstanceLayerProperties(&layerNumber, nullptr);

        std::vector<VkLayerProperties> layerProperties(layerNumber);
        vkEnumerateInstanceLayerProperties(&layerNumber, layerProperties.data());

        bool layerFound = false;

        for (const VkLayerProperties& properties : layerProperties)
        {
            if (std::string_view(properties.layerName) == KHRONOS_VALIDATION_LAYER_NAME)
            {
                enabledLayers.push_back(KHRONOS_VALIDATION_LAYER_NAME.data());

                layerFound = true;
                break;
            }

            if (std::string_view(properties.layerName) == LUNARG_VALIDATION_LAYER_NAME)
            {
                enabledLayers.push_back(LUNARG_VALIDATION_LAYER_NAME.data());

                layerFound = true;
                break;
            }
        }

        if (!layerFound)
        {
            RadianceFieldsUtility::ThrowRunTimeError("Standard validation layer isn't supported\n");
        }
    }

    return enabledLayers;
}

std::vector<const char*> Graphics::VkRenderer::CreateEnabledExtensionsData(bool enableValidationLayer) const
{
    std::vector<const char*> enabledExtensions;

    if (enableValidationLayer)
    {
        uint32_t extensionNumber;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionNumber, nullptr);

        std::vector<VkExtensionProperties> extensionProperties(extensionNumber);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionNumber, extensionProperties.data());

        bool extensionFound = false;

        for (const VkExtensionProperties& properties : extensionProperties)
        {
            if (std::string_view(properties.extensionName) == std::string_view("VK_EXT_DEBUG_REPORT_EXTENSION_NAME"))
            {
                enabledExtensions.push_back(DEBUG_REPORT_EXTENSION_NAME.data());

                extensionFound = true;
                break;
            }
        }

        if (!extensionFound)
        {
            RadianceFieldsUtility::ThrowRunTimeError("Extension VK_EXT_DEBUG_REPORT_EXTENSION_NAME isn't supported\n");
        }
    }

    return enabledExtensions;
}

VkInstance Graphics::VkRenderer::CreateVulkanInstance(const std::string& applicationName,
    const std::vector<const char*>& enabledLayers, const std::vector<const char*>& enabledExtensions) const
{
    VkApplicationInfo applicationInfo{};
    applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    applicationInfo.pApplicationName = applicationName.c_str();
    applicationInfo.pEngineName = "EngineName";
    applicationInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &applicationInfo;
    createInfo.enabledLayerCount = static_cast<uint32_t>(enabledLayers.size());
    createInfo.ppEnabledLayerNames = enabledLayers.data();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(enabledExtensions.size());
    createInfo.ppEnabledExtensionNames = enabledExtensions.data();

    VkInstance instance;
    VkAssert(vkCreateInstance(&createInfo, nullptr, &instance));

	return instance;
}

void Graphics::VkRenderer::CreateDebugReportCallback(VkInstance instance, DebugReportCallbackFuncType callback,
    VkDebugReportCallbackEXT* reportCallback) const
{
    VkDebugReportCallbackCreateInfoEXT createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;
    createInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT |
        VK_DEBUG_REPORT_WARNING_BIT_EXT |
        VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT;

    createInfo.pfnCallback = callback;

    auto vkCreateDebugReportCallbackEXT = reinterpret_cast<PFN_vkCreateDebugReportCallbackEXT>(vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT"));

    if (vkCreateDebugReportCallbackEXT == nullptr)
    {
        RadianceFieldsUtility::ThrowRunTimeError("Couldn't load vkCreateDebugReportCallbackEXT");
    }
    else
    {
        VkAssert(vkCreateDebugReportCallbackEXT(instance, &createInfo, nullptr, reportCallback));
    }
}

inline void Graphics::VkRenderer::VkAssert(VkResult result, const std::source_location location) const
{
    if (result != VK_SUCCESS)
    {
        std::printf("Error: VkResult is %d in file %s, method %s at line %d\n", result,
            location.file_name(), location.function_name(), location.line());
        assert(result == VK_SUCCESS);
    }
}

VKAPI_ATTR VkBool32 VKAPI_CALL Graphics::VkRenderer::DebugReportCallbackFunc(VkDebugReportFlagsEXT flags,
    VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode,
    const char* layerPrefix, const char* message, void* userData)
{
    std::printf("Debug Report %s: %s\n", layerPrefix, message);
    return VK_FALSE;
}
