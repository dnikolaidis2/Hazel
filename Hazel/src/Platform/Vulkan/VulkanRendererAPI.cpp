#include "hzpch.h"
#include "VulkanRendererAPI.h"

namespace Hazel {
	
	VkContext* VulkanRendererAPI::g_vkContext = new VkContext;

	void VulkanRendererAPI::Init()
	{
	}

	void VulkanRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		g_vkContext->FramebufferResized = true;
	}

	void VulkanRendererAPI::SetClearColor(const glm::vec4& color)
	{
		m_ClearColor = color;
	}

	void VulkanRendererAPI::Clear()
	{

	}

	void VulkanRendererAPI::StartRenderPass()
	{
		vkWaitForFences(g_vkContext->Device, 1, &g_vkContext->InFlightFences[g_vkContext->CurrentFrame], VK_TRUE, UINT64_MAX);

		VkResult result = vkAcquireNextImageKHR(g_vkContext->Device, g_vkContext->SwapChain, UINT64_MAX, g_vkContext->ImageAvailableSemaphores[g_vkContext->CurrentFrame], VK_NULL_HANDLE, &(g_vkContext->CurrentImageIndex));

		if (result == VK_ERROR_OUT_OF_DATE_KHR) {
			g_vkContext->ResizeCallback();
			return;
		}
		else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
			throw std::runtime_error("failed to acquire swap chain image!");
		}

		VkCommandBuffer currentCommandBuffer = GetCurrentCommandBuffer();
		VkCommandBufferBeginInfo beginInfo = {};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = 0; // Optional
		beginInfo.pInheritanceInfo = nullptr; // Optional

		result = vkBeginCommandBuffer(currentCommandBuffer, &beginInfo);
		HZ_CORE_ASSERT(!result, "failed to begin recording command buffer!");

		VkRenderPassBeginInfo renderPassInfo = {};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = g_vkContext->RenderPass;
		renderPassInfo.framebuffer = GetCurrentFrameBuffer();
		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = g_vkContext->SwapChainExtent;

		VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
		renderPassInfo.clearValueCount = 1;
		renderPassInfo.pClearValues = &clearColor;

		vkCmdBeginRenderPass(currentCommandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

		vkCmdBindPipeline(currentCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, g_vkContext->GraphicsPipeline);
	}

	void VulkanRendererAPI::EndRenderPass()
	{
	}

	void VulkanRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
	}

	const VkFramebuffer VulkanRendererAPI::GetCurrentFrameBuffer()
	{
		return g_vkContext->SwapChainFramebuffers[g_vkContext->CurrentFrame];
	}

	const VkCommandBuffer VulkanRendererAPI::GetCurrentCommandBuffer()
	{
		return g_vkContext->CommandBuffers[g_vkContext->CurrentFrame];
	}

}