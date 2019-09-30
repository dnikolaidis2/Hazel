#pragma once

namespace Hazel {

	class GraphicsContext
	{
	public:
		virtual ~GraphicsContext() {}

		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

		virtual void SetVSync(bool enabled) = 0;

		static Ref<GraphicsContext> Create(void* window);
	};

}