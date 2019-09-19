#include "hzpch.h"
#include "ImGuiCommand.h"

#include "Hazel/Renderer/Renderer.h"

#include "imgui.h"
#include "examples/imgui_impl_opengl3.h"
#include "examples/imgui_impl_glfw.h"

namespace Hazel {
	bool ImGuiCommand::WindowInit(GLFWwindow* window, bool install_callbacks)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return false;
		case RendererAPI::API::OpenGL:  return ImGui_ImplGlfw_InitForOpenGL(window, install_callbacks);
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
		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return;
	}
}