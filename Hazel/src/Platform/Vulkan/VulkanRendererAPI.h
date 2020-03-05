#pragma once

#include "Hazel/Renderer/RendererAPI.h"
#include <vulkan/vulkan.h>
#include <glm/glm.hpp>

namespace Hazel {

	struct VkContext
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
		VkBuffer VertexBuffer;
		VkDeviceMemory VertexBufferMemory;
		VkBuffer IndexBuffer;
		VkDeviceMemory IndexBufferMemory;
		VkDescriptorPool DescriptorPool;
		std::vector<VkFramebuffer> SwapChainFramebuffers;
		VkCommandPool CommandPool;
		std::vector<VkCommandBuffer> CommandBuffers;
		std::vector<VkSemaphore> ImageAvailableSemaphores;
		std::vector<VkSemaphore> RenderFinishedSemaphores;
		std::vector<VkFence> InFlightFences;
		size_t CurrentFrame = 0;
		bool FramebufferResized = false;
		std::function<void()> ResizeCallback;
		uint32_t CurrentImageIndex = 0;
	};

	class VulkanRendererAPI : public RendererAPI
	{
	public:
		struct Vertex {
			glm::vec2 pos;
			glm::vec3 color;

			static VkVertexInputBindingDescription GetBindingDescription() {
				VkVertexInputBindingDescription bindingDescription = {};
				bindingDescription.binding = 0;
				bindingDescription.stride = sizeof(Vertex);
				bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

				return bindingDescription;
			}

			static std::array<VkVertexInputAttributeDescription, 2> GetAttributeDescriptions() {
				std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions = {};

				attributeDescriptions[0].binding = 0;
				attributeDescriptions[0].location = 0;
				attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
				attributeDescriptions[0].offset = offsetof(Vertex, pos);

				attributeDescriptions[1].binding = 0;
				attributeDescriptions[1].location = 1;
				attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
				attributeDescriptions[1].offset = offsetof(Vertex, color);

				return attributeDescriptions;
			}
		};

		const static int MAX_FRAMES_IN_FLIGHT = 2;

	public:
		virtual void Init() override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void StartRenderPass() override;
		virtual void EndRenderPass() override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;

		inline static VkContext* GetContext() { return (RendererAPI::GetAPI() != RendererAPI::API::Vulkan) ? nullptr : g_vkContext; }
	private:
		const VkFramebuffer GetCurrentFrameBuffer();
		const VkCommandBuffer GetCurrentCommandBuffer();

		glm::vec4 m_ClearColor;
	private:
		static VkContext* g_vkContext;
	};


}
