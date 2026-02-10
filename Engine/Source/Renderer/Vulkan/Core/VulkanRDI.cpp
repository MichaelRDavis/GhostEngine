#include "VulkanRDI.h"
#include "Engine/Engine.h"
#include "Core/Logging/Log.h"
#include "Platform/FileSystem/IFileSystem.h"

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
	m_surface = VK_NULL_HANDLE;

	m_graphicsQueueIndex = -1;
	m_gpu = VK_NULL_HANDLE;
	m_device = VK_NULL_HANDLE;
	m_queue = VK_NULL_HANDLE;
	m_vmaAllocator = VK_NULL_HANDLE;
	m_vertexBufferAllocation = VK_NULL_HANDLE;
	m_vertexBuffer = VK_NULL_HANDLE;

	m_swapchainDimensions = {};
	m_swapchain = VK_NULL_HANDLE;

	m_renderPass = VK_NULL_HANDLE;

	m_pipelineLayout = VK_NULL_HANDLE;
	m_pipeline = VK_NULL_HANDLE;
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
	InitVertexBuffer();
	InitSwapchain();
	InitRenderPass();
	InitPipeline();
	InitFramebuffers();
}

void CVulkanRDI::Render(F32 deltaTime)
{
	U32 index;

	auto res = AcquireNextImage(&index);
	if (res == VK_SUBOPTIMAL_KHR || res == VK_ERROR_OUT_OF_DATE_KHR)
	{
		res = AcquireNextImage(&index);
	}

	if (res != VK_SUCCESS)
	{
		vkQueueWaitIdle(m_queue);
		return;
	}

	DrawTriangle(index);
	res = PresentImage(index);
}

void CVulkanRDI::Destroy()
{
	
}

void CVulkanRDI::DrawTriangle(U32 index)
{
	VkFramebuffer framebuffer = m_swapchainFramebuffers[index];

	VkCommandBuffer cmd = m_perFrame[index].primaryCommandBuffer;

	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	vkBeginCommandBuffer(cmd, &beginInfo);

	VkClearValue clearValue { .color = {{0.01f, 0.01f, 0.033f, 1.0f}} };

	VkRenderPassBeginInfo rpBegin = {};
	rpBegin.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	rpBegin.renderPass = m_renderPass;
	rpBegin.framebuffer = framebuffer;
	rpBegin.renderArea = { .extent = {.width = m_swapchainDimensions.width, .height = m_swapchainDimensions.height} };
	rpBegin.clearValueCount = 1;
	rpBegin.pClearValues = &clearValue;

	vkCmdBeginRenderPass(cmd, &rpBegin, VK_SUBPASS_CONTENTS_INLINE);

	vkCmdBindPipeline(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipeline);

	VkViewport vp{
	.width = (F32)(m_swapchainDimensions.width),
	.height = (F32)(m_swapchainDimensions.height),
	.minDepth = 0.0f,
	.maxDepth = 1.0f };
	vkCmdSetViewport(cmd, 0, 1, &vp);

	VkRect2D scissor{
	.extent = {.width = m_swapchainDimensions.width, .height = m_swapchainDimensions.height} };
	vkCmdSetScissor(cmd, 0, 1, &scissor);

	VkDeviceSize offset = { 0 };
	vkCmdBindVertexBuffers(cmd, 0, 1, &m_vertexBuffer, &offset);

	vkCmdDraw(cmd, 3, 1, 0, 0);

	vkCmdEndRenderPass(cmd);

	vkEndCommandBuffer(cmd);

	if (m_perFrame[index].swapchainReleaseSemaphore == VK_NULL_HANDLE)
	{
		VkSemaphoreCreateInfo semaphoreInfo = {};
		semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
		vkCreateSemaphore(m_device, &semaphoreInfo, nullptr, &m_perFrame[index].swapchainReleaseSemaphore);
	}

	VkPipelineStageFlags waitStage{ VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };

	VkSubmitInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	info.waitSemaphoreCount = 1;
	info.pWaitSemaphores = &m_perFrame[index].swapchainAcquireSemaphore;
	info.pWaitDstStageMask = &waitStage;
	info.commandBufferCount = 1;
	info.pCommandBuffers = &cmd;
	info.signalSemaphoreCount = 1;
	info.pSignalSemaphores = &m_perFrame[index].swapchainReleaseSemaphore;

	vkQueueSubmit(m_queue, 1, &info, m_perFrame[index].queueSubmitFence);
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
	// Validation layers help detect errors in Vulkan API usage, only enabled in debug builds.
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

	if (!ValidateExtensions(requiredInstanceExtensions, availableInstanceExtensions))
	{
		GE_LOG(Error, "Required instance extensions are missing.");
	}

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

	if (!ValidateExtensions(requiredDeviceExtensions, deviceExtensions))
	{
		GE_LOG(Error, "Required device extensions are missing.");
		return;
	}

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

	vkGetDeviceQueue(m_device, m_graphicsQueueIndex, 0, &m_queue);

	VmaVulkanFunctions vmaVulkanFunc = {};
	vmaVulkanFunc.vkGetInstanceProcAddr = vkGetInstanceProcAddr;
	vmaVulkanFunc.vkGetDeviceProcAddr = vkGetDeviceProcAddr;

	VmaAllocatorCreateInfo allocatorInfo = {};
	allocatorInfo.physicalDevice = m_gpu;
	allocatorInfo.device = m_device;
	allocatorInfo.pVulkanFunctions = &vmaVulkanFunc;
	allocatorInfo.instance = m_instance;

	if (vmaCreateAllocator(&allocatorInfo, &m_vmaAllocator))
	{
		GE_LOG(Fatal, "Could not create allocator for VMA allocator.");
		return;
	}
}

void CVulkanRDI::InitVertexBuffer()
{
	const std::vector<Vertex> vertices = {
	{{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}},
	{{0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
	{{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}} };

	const VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

	VkBufferCreateInfo bufferInfo = {};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.size = bufferSize;
	bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;

	VmaAllocationCreateInfo bufferAllocCreateInfo = {};
	bufferAllocCreateInfo.flags = VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT | VMA_ALLOCATION_CREATE_MAPPED_BIT;
	bufferAllocCreateInfo.usage = VMA_MEMORY_USAGE_AUTO;
	bufferAllocCreateInfo.requiredFlags = VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

	VmaAllocationInfo bufferAllocInfo = {};
	vmaCreateBuffer(m_vmaAllocator, &bufferInfo, &bufferAllocCreateInfo, &m_vertexBuffer, &m_vertexBufferAllocation, &bufferAllocInfo);
	if (bufferAllocInfo.pMappedData)
	{
		CMemory::Memcpy(bufferAllocInfo.pMappedData, vertices.data(), bufferSize);
	}
	else
	{
		GE_LOG(Fatal, "Could not map vertex buffer.");
		return;
	}
}

void CVulkanRDI::InitSwapchain()
{
	VkSurfaceCapabilitiesKHR surfaceProperties;
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_gpu, m_surface, &surfaceProperties);

	VkSurfaceFormatKHR format = SelectSurfaceFormat(m_gpu, m_surface);

	VkExtent2D swapchainSize = {};
	if (surfaceProperties.minImageExtent.width == 0xFFFFFFFF)
	{
		swapchainSize.width = m_viewport.width;
		swapchainSize.height = m_viewport.height;
	}
	else
	{
		swapchainSize = surfaceProperties.currentExtent;
	}

	VkPresentModeKHR swapchainPresentMode = VK_PRESENT_MODE_FIFO_KHR;

	U32 desiredSwapchainImages = surfaceProperties.minImageCount + 1;
	if ((surfaceProperties.maxImageCount > 0) && (desiredSwapchainImages > surfaceProperties.maxImageCount))
	{
		desiredSwapchainImages = surfaceProperties.maxImageCount;
	}

	VkSurfaceTransformFlagBitsKHR preTransform;
	if (surfaceProperties.supportedTransforms & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR)
	{
		preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
	}
	else
	{
		preTransform = surfaceProperties.currentTransform;
	}

	VkSwapchainKHR oldSwapchain = m_swapchain;

	VkCompositeAlphaFlagBitsKHR composite = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	if (surfaceProperties.supportedCompositeAlpha & VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR)
	{
		composite = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	}
	else if (surfaceProperties.supportedCompositeAlpha & VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR)
	{
		composite = VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR;
	}
	else if (surfaceProperties.supportedCompositeAlpha & VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR)
	{
		composite = VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR;
	}
	else if (surfaceProperties.supportedCompositeAlpha & VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR)
	{
		composite = VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR;
	}

	VkSwapchainCreateInfoKHR info = {};
	info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	info.surface = m_surface;
	info.minImageCount = desiredSwapchainImages;
	info.imageFormat = format.format;
	info.imageColorSpace = format.colorSpace;
	info.imageExtent = swapchainSize;
	info.imageArrayLayers = 1;
	info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	info.preTransform = preTransform;
	info.compositeAlpha = composite;
	info.presentMode = swapchainPresentMode;
	info.clipped = true;
	info.oldSwapchain = oldSwapchain;

	if (vkCreateSwapchainKHR(m_device, &info, nullptr, &m_swapchain))
	{
		GE_LOG(Fatal, "Failed to create Vulkan swapchain.");
		return;
	}

	if (oldSwapchain != VK_NULL_HANDLE)
	{
		for (VkImageView imageView : m_swapchainImageViews)
		{
			vkDestroyImageView(m_device, imageView, nullptr);
		}

		for (auto& perFrame : m_perFrame)
		{
			TeardownPerFrame(perFrame);
		}

		m_swapchainImageViews.clear();

		vkDestroySwapchainKHR(m_device, oldSwapchain, nullptr);
	}

	m_swapchainDimensions = { swapchainSize.width, swapchainSize.height, format.format };

	U32 imageCount;
	vkGetSwapchainImagesKHR(m_device, m_swapchain, &imageCount, nullptr);
	std::vector<VkImage> swapchainImages(imageCount);
	vkGetSwapchainImagesKHR(m_device, m_swapchain, &imageCount, swapchainImages.data());

	m_perFrame.clear();
	m_perFrame.resize(imageCount);

	for (U32 i = 0; i < imageCount; i++)
	{
		InitPerFrame(m_perFrame[i]);
	}

	for (U32 i = 0; i < imageCount; i++)
	{
		VkImageViewCreateInfo viewInfo = {};
		viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		viewInfo.image = swapchainImages[i];
		viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		viewInfo.format = m_swapchainDimensions.format;
		viewInfo.subresourceRange = { .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT, .baseMipLevel = 0, .levelCount = 1, .baseArrayLayer = 0, .layerCount = 1 };

		VkImageView imageView;
		vkCreateImageView(m_device, &viewInfo, nullptr, &imageView);

		m_swapchainImageViews.push_back(imageView);
	}
}

void CVulkanRDI::InitRenderPass()
{
	VkAttachmentDescription attachment = {};
	attachment.format = m_swapchainDimensions.format;
	attachment.samples = VK_SAMPLE_COUNT_1_BIT;
	attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	attachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	VkAttachmentReference colorRef = { 0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL };

	VkSubpassDescription subpass = {};
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpass.colorAttachmentCount = 1;
	subpass.pColorAttachments = &colorRef;

	VkSubpassDependency dependency = {};
	dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
	dependency.dstSubpass = 0;
	dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

	dependency.srcAccessMask = 0;
	dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

	VkRenderPassCreateInfo rpInfo = {};
	rpInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	rpInfo.attachmentCount = 1;
	rpInfo.pAttachments = &attachment;
	rpInfo.subpassCount = 1;
	rpInfo.pSubpasses = &subpass;
	rpInfo.dependencyCount = 1;
	rpInfo.pDependencies = &dependency;

	vkCreateRenderPass(m_device, &rpInfo, nullptr, &m_renderPass);
}

void CVulkanRDI::InitPipeline()
{
	VkPipelineLayoutCreateInfo layoutInfo = {};
	layoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	vkCreatePipelineLayout(m_device, &layoutInfo, nullptr, &m_pipelineLayout);

	VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
	inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

	VkVertexInputBindingDescription bindingDescription = {};
	bindingDescription.binding = 0;
	bindingDescription.stride = sizeof(Vertex);
	bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

	std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{
		{{.location = 0, .binding = 0, .format = VK_FORMAT_R32G32_SFLOAT, .offset = offsetof(Vertex, position)},
		 {.location = 1, .binding = 0, .format = VK_FORMAT_R32G32B32_SFLOAT, .offset = offsetof(Vertex, color)}} };

	VkPipelineVertexInputStateCreateInfo vertexInput = {};
	vertexInput.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	vertexInput.vertexBindingDescriptionCount = 1;
	vertexInput.pVertexBindingDescriptions = &bindingDescription;
	vertexInput.vertexAttributeDescriptionCount = (U32)attributeDescriptions.size();
	vertexInput.pVertexAttributeDescriptions = attributeDescriptions.data();

	VkPipelineRasterizationStateCreateInfo raster = {};
	raster.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	raster.cullMode = VK_CULL_MODE_BACK_BIT;
	raster.frontFace = VK_FRONT_FACE_CLOCKWISE;
	raster.lineWidth = 1.0f;

	VkPipelineColorBlendAttachmentState blendAttachment = {};
	blendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

	VkPipelineColorBlendStateCreateInfo blend = {};
	blend.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	blend.attachmentCount = 1;
	blend.pAttachments = &blendAttachment;

	VkPipelineViewportStateCreateInfo viewport = {};
	viewport.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewport.viewportCount = 1;
	viewport.scissorCount = 1;

	VkPipelineDepthStencilStateCreateInfo depthStencil = {};
	depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;

	VkPipelineMultisampleStateCreateInfo multisample = {};
	multisample.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	multisample.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

	std::array<VkDynamicState, 2> dynamics{ VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };

	VkPipelineDynamicStateCreateInfo dynamic = {};
	dynamic.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	dynamic.dynamicStateCount = (U32)dynamics.size();
	dynamic.pDynamicStates = dynamics.data();

	std::array<VkPipelineShaderStageCreateInfo, 2> shaderStages{};

	shaderStages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	shaderStages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
	shaderStages[0].module = LoadShaderModule("Shaders/glsl/triangle.vert.spv");
	shaderStages[0].pName = "main";

	shaderStages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	shaderStages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	shaderStages[1].module = LoadShaderModule("Shaders/glsl/triangle.frag.spv");
	shaderStages[1].pName = "main";

	VkGraphicsPipelineCreateInfo pipe = {};
	pipe.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipe.stageCount = (U32)shaderStages.size();
	pipe.pStages = shaderStages.data();
	pipe.pVertexInputState = &vertexInput;
	pipe.pInputAssemblyState = &inputAssembly;
	pipe.pViewportState = &viewport;
	pipe.pRasterizationState = &raster;
	pipe.pMultisampleState = &multisample;
	pipe.pDepthStencilState = &depthStencil;
	pipe.pColorBlendState = &blend;
	pipe.pDynamicState = &dynamic;
	pipe.layout = m_pipelineLayout;
	pipe.renderPass = m_renderPass;

	if (vkCreateGraphicsPipelines(m_device, VK_NULL_HANDLE, 1, &pipe, nullptr, &m_pipeline) != VK_SUCCESS)
	{
		GE_LOG(Fatal, "Failed to create Vulkan graphics piepline.");
		return;
	}

	vkDestroyShaderModule(m_device, shaderStages[0].module, nullptr);
	vkDestroyShaderModule(m_device, shaderStages[1].module, nullptr);
}

void CVulkanRDI::InitFramebuffers()
{
	m_swapchainFramebuffers.clear();

	for (auto& imageView : m_swapchainImageViews)
	{
		VkFramebufferCreateInfo fbInfo = {};
		fbInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		fbInfo.renderPass = m_renderPass;
		fbInfo.attachmentCount = 1;
		fbInfo.pAttachments = &imageView;
		fbInfo.width = m_swapchainDimensions.width;
		fbInfo.height = m_swapchainDimensions.height;
		fbInfo.layers = 1;

		VkFramebuffer framebuffer;
		vkCreateFramebuffer(m_device, &fbInfo, nullptr, &framebuffer);

		m_swapchainFramebuffers.emplace_back(framebuffer);
	}
}

void CVulkanRDI::InitPerFrame(PerFrame& perFrame)
{
	VkFenceCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	info.flags = VK_FENCE_CREATE_SIGNALED_BIT;
	vkCreateFence(m_device, &info, nullptr, &perFrame.queueSubmitFence);

	VkCommandPoolCreateInfo cmdPoolInfo = {};
	cmdPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	cmdPoolInfo.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
	cmdPoolInfo.queueFamilyIndex = (U32)m_graphicsQueueIndex;
	vkCreateCommandPool(m_device, &cmdPoolInfo, nullptr, &perFrame.primaryCommandPool);

	VkCommandBufferAllocateInfo cmdBufferInfo = {};
	cmdBufferInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	cmdBufferInfo.commandPool = perFrame.primaryCommandPool;
	cmdBufferInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	cmdBufferInfo.commandBufferCount = 1;

	vkAllocateCommandBuffers(m_device, &cmdBufferInfo, &perFrame.primaryCommandBuffer);
}

void CVulkanRDI::TeardownPerFrame(PerFrame& perFrame)
{
	if (perFrame.queueSubmitFence != VK_NULL_HANDLE)
	{
		vkDestroyFence(m_device, perFrame.queueSubmitFence, nullptr);
		perFrame.queueSubmitFence = VK_NULL_HANDLE;
	}

	if (perFrame.primaryCommandBuffer != VK_NULL_HANDLE)
	{
		vkFreeCommandBuffers(m_device, perFrame.primaryCommandPool, 1, &perFrame.primaryCommandBuffer);

		perFrame.primaryCommandBuffer = VK_NULL_HANDLE;
	}

	if (perFrame.primaryCommandPool != VK_NULL_HANDLE)
	{
		vkDestroyCommandPool(m_device, perFrame.primaryCommandPool, nullptr);

		perFrame.primaryCommandPool = VK_NULL_HANDLE;
	}

	if (perFrame.swapchainAcquireSemaphore != VK_NULL_HANDLE)
	{
		vkDestroySemaphore(m_device, perFrame.swapchainAcquireSemaphore, nullptr);

		perFrame.swapchainAcquireSemaphore = VK_NULL_HANDLE;
	}

	if (perFrame.swapchainReleaseSemaphore != VK_NULL_HANDLE)
	{
		vkDestroySemaphore(m_device, perFrame.swapchainReleaseSemaphore, nullptr);

		perFrame.swapchainReleaseSemaphore = VK_NULL_HANDLE;
	}
}

bool CVulkanRDI::ValidateExtensions(const std::vector<const char*>& required, const std::vector<VkExtensionProperties>& available)
{
	for (auto extension : required)
	{
		bool found = false;
		for (auto& availableExtension : available)
		{
			if (strcmp(availableExtension.extensionName, extension) == 0)
			{
				found = true;
				break;
			}
		}

		if (!found)
		{
			return false;
		}
	}

	return true;
}

VkSurfaceFormatKHR CVulkanRDI::SelectSurfaceFormat(
	VkPhysicalDevice gpu, 
	VkSurfaceKHR surface, 
	std::vector<VkFormat> const& preferredFormats)
{
	U32 surfaceFormatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(gpu, surface, &surfaceFormatCount, nullptr);
	std::vector<VkSurfaceFormatKHR> supportedSurfaceFormats(surfaceFormatCount);
	vkGetPhysicalDeviceSurfaceFormatsKHR(gpu, surface, &surfaceFormatCount, supportedSurfaceFormats.data());

	auto it = std::ranges::find_if(supportedSurfaceFormats,
		[&preferredFormats](VkSurfaceFormatKHR surface_format) {
			return std::ranges::any_of(preferredFormats,
				[&surface_format](VkFormat format) { return format == surface_format.format; });
		});

	return it != supportedSurfaceFormats.end() ? *it : supportedSurfaceFormats[0];
}

VkShaderModule CVulkanRDI::LoadShaderModule(const char* path)
{
	auto spriv = IFileSystem::ReadFile(path);

	VkShaderModuleCreateInfo moduleInfo = {};
	moduleInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	moduleInfo.codeSize = spriv.size();
	moduleInfo.pCode = (U32*)spriv.data();

	VkShaderModule shaderModule;
	vkCreateShaderModule(m_device, &moduleInfo, nullptr, &shaderModule);

	return shaderModule;
}

VkResult CVulkanRDI::AcquireNextImage(U32* image)
{
	VkSemaphore acquireSemaphore;
	if (m_recycledSemaphores.empty())
	{
		VkSemaphoreCreateInfo info = {};
		info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
		vkCreateSemaphore(m_device, &info, nullptr, &acquireSemaphore);
	}
	else
	{
		acquireSemaphore = m_recycledSemaphores.back();
		m_recycledSemaphores.pop_back();
	}

	VkResult res = vkAcquireNextImageKHR(m_device, m_swapchain, UINT64_MAX, acquireSemaphore, VK_NULL_HANDLE, image);
	if (res != VK_SUCCESS)
	{
		m_recycledSemaphores.push_back(acquireSemaphore);
		return res;
	}

	if (m_perFrame[*image].queueSubmitFence != VK_NULL_HANDLE)
	{
		vkWaitForFences(m_device, 1, &m_perFrame[*image].queueSubmitFence, true, UINT64_MAX);
		vkResetFences(m_device, 1, &m_perFrame[*image].queueSubmitFence);
	}

	if (m_perFrame[*image].primaryCommandPool != VK_NULL_HANDLE)
	{
		vkResetCommandPool(m_device, m_perFrame[*image].primaryCommandPool, 0);
	}

	VkSemaphore oldSemaphore = m_perFrame[*image].swapchainAcquireSemaphore;
	if (oldSemaphore != VK_NULL_HANDLE)
	{
		m_recycledSemaphores.push_back(oldSemaphore);
	}

	m_perFrame[*image].swapchainAcquireSemaphore = acquireSemaphore;

	return VK_SUCCESS;
}

VkResult CVulkanRDI::PresentImage(U32 index)
{
	VkPresentInfoKHR present = {};
	present.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	present.waitSemaphoreCount = 1;
	present.pWaitSemaphores = &m_perFrame[index].swapchainReleaseSemaphore;
	present.swapchainCount = 1;
	present.pSwapchains = &m_swapchain;
	present.pImageIndices = &index;

	return vkQueuePresentKHR(m_queue, &present);
}
