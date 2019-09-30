#include "hzpch.h"
#include "VulkanRendererAPI.h"

namespace Hazel {
	
	VulkanRendererAPI::VulkanContext* VulkanRendererAPI::g_Context = new VulkanRendererAPI::VulkanContext;

	void VulkanRendererAPI::Init()
	{
	}

	void VulkanRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		g_Context->FramebufferResized = true;
	}

	void VulkanRendererAPI::SetClearColor(const glm::vec4& color)
	{
	}

	void VulkanRendererAPI::Clear()
	{
	}

	void VulkanRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
	}

}