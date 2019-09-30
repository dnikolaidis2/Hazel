#include "hzpch.h"
#include "RenderCommand.h"
#include "Renderer.h"

namespace Hazel {

	Ref<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}