#include "VulkanRDI.h"
#include "Engine/Engine.h"
#include "Core/Logging/Log.h"

#ifdef _DEBUG
static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageType,
	const VkDebugUtilsMessengerCallbackDataEXT* callbackData,
	void* userData)
{
	if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
	{
		GE_LOG(Error, "{%d} Validation Layer: Error: {%s}: {%s}", callbackData->messageIdNumber, callbackData->pMessageIdName, callbackData->pMessage)
	}
	else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
	{
		GE_LOG(Error, "{%d} Validation Layer: Warning: {%s}: {%s}", callbackData->messageIdNumber, callbackData->pMessageIdName, callbackData->pMessage)
	}
	else if (messageType & VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT)
	{
		GE_LOG(Log, "{%d} Validation Layer: Performance warning: {%s}: {%s}", callbackData->messageIdNumber, callbackData->pMessageIdName, callbackData->pMessage)
	}
	else
	{
		GE_LOG(Log,"{%d} Validation Layer: Information: {%s}: {%s}", callbackData->messageIdNumber, callbackData->pMessageIdName, callbackData->pMessage)
	}

	return VK_FALSE;
}
#endif

CVulkanRDI::CVulkanRDI()
{
	m_viewport = { };

	m_instance = VK_NULL_HANDLE;
#ifdef _DEBUG
	m_debugCallback = VK_NULL_HANDLE;
#endif
	m_graphicsQueueIndex = -1;
	m_gpu = VK_NULL_HANDLE;
	m_device = VK_NULL_HANDLE;

	m_surface = VK_NULL_HANDLE;
}

CVulkanRDI::~CVulkanRDI()
{
	Destroy();
}

void CVulkanRDI::Init(const Viewport& viewport)
{
	m_viewport = viewport;
	InitInstance();
	InitSurface();
	InitDevice();
}

void CVulkanRDI::Render()
{

}

void CVulkanRDI::Destroy()
{
	DestroyInstance();
	DestroyDevice();
}

void CVulkanRDI::InitInstance()
{
	GE_LOG(Log, "Initializing Vulkan instance.")

	if (volkInitialize())
	{
		GE_LOG(Fatal, "Failed to initialize volk.");
		return;
	}

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

	// TODO: Validate instance extensions

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

#ifdef _DEBUG
	VkDebugUtilsMessengerCreateInfoEXT debugUtilsCreateInfo = {};
	debugUtilsCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	if (hasDebugUtils)
	{
		debugUtilsCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT;
		debugUtilsCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;
		debugUtilsCreateInfo.pfnUserCallback = DebugCallback;

		instanceInfo.pNext = &debugUtilsCreateInfo;
	}
#endif

	if (vkCreateInstance(&instanceInfo, nullptr, &m_instance))
	{
		GE_LOG(Fatal, "Failed to create Vulkan instance");
		return;
	}

	volkLoadInstance(m_instance);

#ifdef _DEBUG
	if (hasDebugUtils)
	{
		vkCreateDebugUtilsMessengerEXT(m_instance, &debugUtilsCreateInfo, nullptr, &m_debugCallback);
	}
#endif
}

void CVulkanRDI::DestroyInstance()
{

}

void CVulkanRDI::InitSurface()
{
#ifdef GE_WINDOWS_PLATFORM
	VkWin32SurfaceCreateInfoKHR surfaceInfo = {};
	surfaceInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	surfaceInfo.pNext = nullptr;
	surfaceInfo.flags = 0;
	surfaceInfo.hinstance = GetModuleHandleA(0);
	surfaceInfo.hwnd = (HWND)m_viewport.viewportHandle;
	if (vkCreateWin32SurfaceKHR(m_instance, &surfaceInfo, nullptr, &m_surface))
	{
		GE_LOG(Fatal, "Win32 surface creation failed.");
		return;
	}
#endif
}

void CVulkanRDI::InitDevice()
{
	GE_LOG(Log, "Initializing Vulkan device.")

	U32 gpuCount = 0;
	vkEnumeratePhysicalDevices(m_instance, &gpuCount, nullptr);
	if (gpuCount < 1)
	{
		GE_LOG(Fatal, "No physical device found.");
		return;
	}

	std::vector<VkPhysicalDevice> gpus(gpuCount);
	vkEnumeratePhysicalDevices(m_instance, &gpuCount, gpus.data());

	for (U32 i = 0; i < gpuCount && (m_graphicsQueueIndex < 0); i++)
	{
		m_gpu = gpus[i];

		U32 queueFamilyCount;
		vkGetPhysicalDeviceQueueFamilyProperties(m_gpu, &queueFamilyCount, nullptr);

		if (queueFamilyCount < 1)
		{
			GE_LOG(Fatal, "No queue family found.");
			return;
		}

		std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(m_gpu, &queueFamilyCount, queueFamilyProperties.data());

		for (U32 i = 0; i < queueFamilyCount; i++)
		{
			VkBool32 supportsPresent;
			vkGetPhysicalDeviceSurfaceSupportKHR(m_gpu, i, m_surface, &supportsPresent);

			if ((queueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) && supportsPresent)
			{
				m_graphicsQueueIndex = i;
				break;
			}
		}
	}

	if (m_graphicsQueueIndex < 0)
	{
		GE_LOG(Fatal, "Did not find suitable device with a queue that supports graphics and presentation.");
		return;
	}

	U32 deviceExtensionCount;
	vkEnumerateDeviceExtensionProperties(m_gpu, nullptr, &deviceExtensionCount, nullptr);
	std::vector<VkExtensionProperties> deviceExtensions(deviceExtensionCount);
	vkEnumerateDeviceExtensionProperties(m_gpu, nullptr, &deviceExtensionCount, deviceExtensions.data());

	std::vector<const char*> requiredDeviceExtensions;
	requiredDeviceExtensions.emplace_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);

	// TODO: Validate device extensions 

	const float queuePriority = 0.5f;

	VkDeviceQueueCreateInfo queueInfo = {};
	queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queueInfo.queueFamilyIndex = m_graphicsQueueIndex;
	queueInfo.queueCount = 1;
	queueInfo.pQueuePriorities = &queuePriority;

	VkDeviceCreateInfo deviceInfo = {};
	deviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceInfo.queueCreateInfoCount = 1;
	deviceInfo.pQueueCreateInfos = &queueInfo;
	deviceInfo.enabledExtensionCount = (U32)requiredDeviceExtensions.size();
	deviceInfo.ppEnabledExtensionNames = requiredDeviceExtensions.data();

	if (vkCreateDevice(m_gpu, &deviceInfo, nullptr, &m_device))
	{
		GE_LOG(Fatal, "Failed to create Vulkan device.");
		return;
	}

	volkLoadDevice(m_device);
}

void CVulkanRDI::DestroyDevice()
{

}