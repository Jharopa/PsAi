#pragma once

// Vulkan/GLFW includes
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

// STD includes
#include <string>
#include <stdexcept>

namespace PsAi
{
	namespace Renderer
	{
		
		class Window
		{
		public:
			// Public member variables
			Window(int w, int h, std::string name);
			~Window();

			Window(const Window&) = delete;
			Window& operator=(const Window&) = delete;

			// Public member functions
			bool should_close() { return glfwWindowShouldClose(m_window); }
			void create_window_surface(VkInstance instance, VkSurfaceKHR* surface);

		private:
			// Private member variables
			const int m_width;
			const int m_height;

			GLFWwindow* m_window;
			std::string m_windowName;

			// Private member functions
			void init_window();
		};

	} // PsAi namespace
	
} // PsAi namespace
