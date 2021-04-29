#pragma once

// Vulkan/GLFW imports
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

// STD import
#include <string>

namespace PsAi
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
