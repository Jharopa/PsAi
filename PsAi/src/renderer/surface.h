#pragma once

// PsAi includes
#include "../util/non_copy_non_move.h"
#include "instance.h"
#include "../log.h"

// Vulkan/GLFW includes
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

// STD library includes
#include <stdexcept>

namespace PsAi::Renderer
{
	
	class Surface : public Util::NonCopyableNonMoveable
	{
		public:
			Surface(const Instance& instance, GLFWwindow* window);
			~Surface();

			const VkSurfaceKHR& get_surface() const { return m_surface; }

		private:
			VkSurfaceKHR m_surface = VK_NULL_HANDLE;
			const Instance& m_instance;
			GLFWwindow* m_window = nullptr;

			void create_surface();
	};

} // PsAi::Renderer namespace
