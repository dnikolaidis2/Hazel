#include "hzpch.h"
#include "ImGuiCommand.h"

#include "Hazel/Renderer/Renderer.h"

#include "Platform/Vulkan/VulkanRendererAPI.h"

#include "imgui.h"
#include "examples/imgui_impl_opengl3.h"
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_vulkan.h"

namespace Hazel {

	bool ImGuiCommand::WindowInit(GLFWwindow* window, bool install_callbacks)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return false;
			case RendererAPI::API::OpenGL:  return ImGui_ImplGlfw_InitForOpenGL(window, install_callbacks);
			case RendererAPI::API::Vulkan:  return ImGui_ImplGlfw_InitForVulkan(window, install_callbacks);
		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return false;
	}

	void ImGuiCommand::WindowNewFrame()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return;
			case RendererAPI::API::OpenGL:  return ImGui_ImplGlfw_NewFrame();
			case RendererAPI::API::Vulkan:  return ImGui_ImplGlfw_NewFrame();
		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return;
	}

	void ImGuiCommand::WindowShutdown()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return;
			case RendererAPI::API::OpenGL:  return ImGui_ImplGlfw_Shutdown();
			case RendererAPI::API::Vulkan:  return ImGui_ImplGlfw_Shutdown();
		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return;
	}

	bool ImGuiCommand::RendererInit(const char * glsl_version)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return false;
			case RendererAPI::API::OpenGL:  return ImGui_ImplOpenGL3_Init(glsl_version);
			case RendererAPI::API::Vulkan:
			{
				g_vkContext = VulkanRendererAPI::GetContext();
				ImGui_ImplVulkan_InitInfo info = {};
				info.Instance = g_vkContext->Instance;
				info.PhysicalDevice = g_vkContext->PhysicalDevice;
				info.Device = g_vkContext->Device;
				info.Queue = g_vkContext->GraphicsQueue;
				info.DescriptorPool = g_vkContext->DescriptorPool;
				return ImGui_ImplVulkan_Init(&info, g_vkContext->RenderPass);
			}
		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return false;
	}

	void ImGuiCommand::RendererNewFrame()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return;
			case RendererAPI::API::OpenGL:  return ImGui_ImplOpenGL3_NewFrame();
			case RendererAPI::API::Vulkan:  return ImGui_ImplVulkan_NewFrame();
		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return;
	}

	void ImGuiCommand::RendererDrawData(ImDrawData * draw_data)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return;
			case RendererAPI::API::OpenGL:  return ImGui_ImplOpenGL3_RenderDrawData(draw_data);
			case RendererAPI::API::Vulkan:  return ImGui_ImplVulkan_RenderDrawData(draw_data, g_vkContext->CommandBuffers[g_vkContext->CurrentFrame]);
		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return;
	}

	void ImGuiCommand::RendererShutdown()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return;
			case RendererAPI::API::OpenGL:  return ImGui_ImplOpenGL3_Shutdown();
			case RendererAPI::API::Vulkan:	return ImGui_ImplVulkan_Shutdown();
		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return;
	}
}