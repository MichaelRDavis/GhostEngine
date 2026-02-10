#pragma once

#include "Renderer/RDI.h"
#include "Renderer/Vulkan/VulkanIncludes.h"
#include "Core/Core.h"

struct Vertex
{
	Vec3 position;
	Vec3 color;
};

struct PerFrame
{
	VkFence queueSubmitFence = VK_NULL_HANDLE;
	VkCommandPool primaryCommandPool = VK_NULL_HANDLE;
	VkCommandBuffer primaryCommandBuffer = VK_NULL_HANDLE;
	VkSemaphore swapchainAcquireSemaphore = VK_NULL_HANDLE;
	VkSemaphore swapchainReleaseSemaphore = VK_NULL_HANDLE;
};

struct SwapchainDimensions
{
	U32 width = 0;
	U32 height = 0;
	VkFormat format = VK_FORMAT_UNDEFINED;
};

class CVulkanRDI : public IRDI
{
public:
	CVulkanRDI();
	~CVulkanRDI();

	void Init(const Viewport& viewport);

	void Render(F32 deltaTime);

	void Destroy();

	void DrawTriangle(U32 index);

private:
	void InitInstance();
	void DestroyInstance();

	void InitSurface();

	void InitDevice();
	void DestroyDevice();

	void InitVertexBuffer();

	void InitSwapchain();

	void InitRenderPass();

	void InitPipeline();

	void InitFramebuffers();

	bool ValidateExtensions(const std::vector<const char*>& required, const std::vector<VkExtensionProperties>& available);

	VkSurfaceFormatKHR SelectSurfaceFormat(
		VkPhysicalDevice gpu, 
		VkSurfaceKHR surface, 
		std::vector<VkFormat> const& preferredFormats = {
		VK_FORMAT_R8G8B8A8_SRGB, 
		VK_FORMAT_B8G8R8A8_SRGB, 
		VK_FORMAT_A8B8G8R8_SRGB_PACK32 });

	VkShaderModule LoadShaderModule(const char* path);

	VkResult AcquireNextImage(U32* image);

private:
	Viewport m_viewport;

	VkInstance m_instance;
#ifdef _DEBUG
	VkDebugUtilsMessengerEXT m_debugCallback;
#endif
	I32 m_graphicsQueueIndex;
	VkPhysicalDevice m_gpu;
	VkDevice m_device;

	VkSurfaceKHR m_surface;

	VmaAllocator m_vmaAllocator;
	VmaAllocation m_vertexBufferAllocation;
	VkBuffer m_vertexBuffer;

	VkSwapchainKHR m_swapchain;
	std::vector<VkImageView> m_swapchainImageViews;
	std::vector<PerFrame> m_perFrame;
	SwapchainDimensions m_swapchainDimensions;

	VkRenderPass m_renderPass;

	VkPipelineLayout m_pipelineLayout;
	VkPipeline m_pipeline;

	std::vector<VkFramebuffer> m_swapchainFramebuffers;

	std::vector<VkSemaphore> m_recycledSemaphores;
};