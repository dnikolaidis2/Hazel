#pragma once

#include "Hazel/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Hazel {

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		virtual ~OpenGLContext();

		virtual void Init() override;
		virtual void SwapBuffers() override;

		virtual void SetVSync(bool vSync) override;
	private:
		GLFWwindow* m_WindowHandle;
	};

}