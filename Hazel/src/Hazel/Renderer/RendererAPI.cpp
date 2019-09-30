#include "hzpch.h"
#include "RendererAPI.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"
#include "Platform/Vulkan/VulkanRendererAPI.h"

namespace Hazel {

	RendererAPI::API RendererAPI::s_API = RendererAPI::API::Vulkan;

	Ref<RendererAPI> RendererAPI::Create()
	{
		switch (GetAPI())
		{
		case RendererAPI::API::None:    HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLRendererAPI>();
		case RendererAPI::API::Vulkan:  return std::make_shared<VulkanRendererAPI>();
		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}