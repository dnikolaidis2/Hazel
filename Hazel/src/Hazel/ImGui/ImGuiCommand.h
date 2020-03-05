#pragma once

#include "imgui.h"

#include <GLFW/glfw3.h>

struct ImGui_ImplVulkan_InitInfo;

struct VkContext;

namespace Hazel {
	class ImGuiCommand
	{
	public:
		static bool WindowInit(GLFWwindow* window, bool install_callbacks);
		static void WindowNewFrame();
		static void WindowShutdown();

		static bool RendererInit(const char* glsl_version = NULL);
		static void RendererNewFrame();
		static void RendererDrawData(ImDrawData* draw_data);
		static void RendererShutdown();
	
	private:
		static VkContext* g_vkContext;
	};
}
