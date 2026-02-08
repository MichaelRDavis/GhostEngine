#include "VulkanDevice.h"
#include "VulkanInstance.h"
#include "Core/Logging/Log.h"

CVulkanDevice::CVulkanDevice(CVulkanInstance& instance)
	: m_instance(instance)
{
	m_gpu = VK_NULL_HANDLE;
	m_device = VK_NULL_HANDLE;
	m_graphicsQueueIndex = 0;
}

CVulkanDevice::~CVulkanDevice()
{

}

void CVulkanDevice::Init(VkSurfaceKHR surface)
{
	GE_LOG(Log, "Initializing Vulkan device.");

	U32 gpuCount = 0;
	vkEnumeratePhysicalDevices(m_instance.GetInstance(), &gpuCount, nullptr);
	if (gpuCount < 1)
	{
		GE_LOG(Fatal, "No physical device found.");
		return;
	}

	std::vector<VkPhysicalDevice> gpus(gpuCount);
	vkEnumeratePhysicalDevices(m_instance.GetInstance(), &gpuCount, gpus.data());

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
			vkGetPhysicalDeviceSurfaceSupportKHR(m_gpu, i, surface, &supportsPresent);

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

void CVulkanDevice::Destroy()
{

}
