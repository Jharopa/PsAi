#pragma once

// PsAi includes
#include "instance.h"
#include "../log.h"

// Vulkan/GLFW includes
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

// STD library includes
#include <stdexcept>

namespace PsAi::Renderer
{
	
	class Surface
	{
		public:
			Surface(const Instance* instance, GLFWwindow* window);
			~Surface();

			// Non-copyable and non-movable
			Surface(const Surface&) = delete;
			Surface(Surface&&) = delete;
			Surface& operator=(const Surface&) = delete;
			Surface& operator=(Surface&&) = delete;

		private:
			const Instance* m_instance = nullptr;
			GLFWwindow* m_window = nullptr;
			VkSurfaceKHR m_surface = VK_NULL_HANDLE;

			void create_surface();
			void destroy_surface();
	};

} // PsAi::Renderer namespace
