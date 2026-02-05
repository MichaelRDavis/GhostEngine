#pragma once

#include "Renderer/RDI.h"
#include "Renderer/Vulkan/VulkanIncludes.h"
#include "Core/Core.h"

struct Vertex
{
	Vec3 position;
	Vec3 color;
};

class CVulkanRDI : public IRDI
{
public:
	CVulkanRDI();
	~CVulkanRDI();

	void Init(const Viewport& viewport);

	void Render();

	void Destroy();

private:
	void InitInstance();
	void DestroyInstance();

	void InitSurface();

	void InitDevice();
	void DestroyDevice();

	void InitVertexBuffer();

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
};