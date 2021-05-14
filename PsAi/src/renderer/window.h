#pragma once

// Vulkan/GLFW includes
#define GLFW_INCLUDE_VULKAN
#define VK_USE_PLATFORM_WIN32_KHR
#include <GLFW/glfw3.h>

// STD includes
#include <string>
#include <stdexcept>

namespace PsAi::Renderer
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
		GLFWwindow* get_window() { return m_window; }

		bool should_close() { return glfwWindowShouldClose(m_window); }
		void create_window_surface(VkInstance instance, VkSurfaceKHR* surface);

		const uint32_t get_width() const { return m_width; }
		const uint32_t get_height() const { return m_height; }

	private:
		// Private member variables
		uint32_t m_width;
		uint32_t m_height;

		GLFWwindow* m_window;
		std::string m_windowName;

		// Private member functions
		void init_window();
	};
	
} // PsAi::Renderer namespace
