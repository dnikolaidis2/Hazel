#pragma once

#include "Hazel/Renderer/RendererAPI.h"
#include <vulkan/vulkan.h>

namespace Hazel {

	class VulkanRendererAPI : public RendererAPI
	{
	public:
		const static int MAX_FRAMES_IN_FLIGHT = 2;

		struct VulkanContext
		{
			VkInstance Instance;
			VkDebugUtilsMessengerEXT DebugMessenger;
			VkPhysicalDevice PhysicalDevice = VK_NULL_HANDLE;
			VkDevice Device;
			VkQueue GraphicsQueue;
			VkSurfaceKHR Surface;
			VkQueue PresentQueue;
			VkSwapchainKHR SwapChain;
			std::vector<VkImage> SwapChainImages;
			VkFormat SwapChainImageFormat;
			VkExtent2D SwapChainExtent;
			std::vector<VkImageView> SwapChainImageViews;
			VkRenderPass RenderPass;
			VkPipelineLayout PipelineLayout;
			VkPipeline GraphicsPipeline;
			std::vector<VkFramebuffer> SwapChainFramebuffers;
			VkCommandPool CommandPool;
			std::vector<VkCommandBuffer> CommandBuffers;
			std::vector<VkSemaphore> ImageAvailableSemaphores;
			std::vector<VkSemaphore> RenderFinishedSemaphores;
			std::vector<VkFence> InFlightFences;
			size_t CurrentFrame = 0;
			bool FramebufferResized = false;
		};

	public:
		virtual void Init() override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;

		inline static VulkanContext* GetContext() { return (RendererAPI::GetAPI() != RendererAPI::API::Vulkan) ? nullptr : g_Context; }
	private:
		static VulkanContext* g_Context;
	};


}
