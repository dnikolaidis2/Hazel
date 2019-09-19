#pragma once

#include <GLFW/glfw3.h>
#include "imgui.h"

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
			
	};
}
