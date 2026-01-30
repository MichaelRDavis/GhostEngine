#include "VulkanRDI.h"
#include "Engine/Engine.h"
#include "Core/Logging/Log.h"

CVulkanRDI::CVulkanRDI()
{
	m_instance = VK_NULL_HANDLE;
}

CVulkanRDI::~CVulkanRDI()
{

}

void CVulkanRDI::Init()
{
	InitInstance();
}

void CVulkanRDI::Render()
{

}

void CVulkanRDI::Destroy()
{

}

void CVulkanRDI::InitInstance()
{
	std::vector<const char*> requiredInstanceExtensions;
	requiredInstanceExtensions.emplace_back(VK_KHR_SURFACE_EXTENSION_NAME);

	U32 instanceExtensionCount;
	vkEnumerateInstanceExtensionProperties(nullptr, &instanceExtensionCount, nullptr);
	std::vector<VkExtensionProperties> availableInstanceExtensions(instanceExtensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &instanceExtensionCount, availableInstanceExtensions.data());

#ifdef _DEBUG
	bool hasDebugUtils = false;
	for (const auto& extension : availableInstanceExtensions)
	{
		if (strcmp(extension.extensionName, VK_EXT_DEBUG_UTILS_EXTENSION_NAME) == 0)
		{
			hasDebugUtils = true;
			requiredInstanceExtensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
			break;
		}
	}

	if (!hasDebugUtils)
	{
		GE_LOG(Warning, "{%s} not supported or available", VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}
#endif

#ifdef GE_WINDOWS_PLATFORM
	requiredInstanceExtensions.emplace_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
#elif GE_LINUX_PLATFORM
	
#else
	#error "Platform not supported!"
#endif

	// TODO: Validate extensions

	std::vector<const char*> requestedInstanceLayers;
#ifdef _DEBUG
	char const* validationLayer = "VK_LAYER_KHRONOS_validation";

	U32 instanceLayerCount;
	vkEnumerateInstanceLayerProperties(&instanceLayerCount, nullptr);
	std::vector<VkLayerProperties> supportedInstanceLayers(instanceLayerCount);
	vkEnumerateInstanceLayerProperties(&instanceLayerCount, supportedInstanceLayers.data());

	if (std::ranges::any_of(supportedInstanceLayers, [&validationLayer](auto const& layer) { return strcmp(layer.layerName, validationLayer) == 0; }))
	{
		requestedInstanceLayers.emplace_back(validationLayer);
		GE_LOG(Log, "Enabled Validation Layer {%s}", validationLayer);
	}
	else
	{
		GE_LOG(Warning, "Validation Layer {%s} is not available", validationLayer);
	}
#endif

	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Sandbox";
	appInfo.pEngineName = "GhostEngine";
	appInfo.apiVersion = VK_API_VERSION_1_1;

	VkInstanceCreateInfo instanceInfo = {};
	instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceInfo.pApplicationInfo = &appInfo;
	instanceInfo.enabledExtensionCount = (U32)requestedInstanceLayers.size();
	instanceInfo.ppEnabledLayerNames = requestedInstanceLayers.data();
	instanceInfo.enabledExtensionCount = (U32)requiredInstanceExtensions.size();
	instanceInfo.ppEnabledExtensionNames = requiredInstanceExtensions.data();

	if (vkCreateInstance(&instanceInfo, nullptr, &m_instance))
	{
		GE_LOG(Fatal, "Failed to create Vulkan instance");
		return;
	}
}