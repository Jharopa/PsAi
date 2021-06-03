#include "window.h"

namespace PsAi::Renderer
{

	Window::Window(int w, int h, std::string name) : m_width(w), m_height(h), m_windowName(name)
	{
		init_window();
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}

	void Window::create_window_surface(VkInstance instance, VkSurfaceKHR* surface)
	{
		if (glfwCreateWindowSurface(instance, m_window, nullptr, surface) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create Vulkan window surface");
		}
	}

	void Window::resize_window_dimensions()
	{
		int new_width = 0;
		int new_height = 0;

		glfwGetFramebufferSize(m_window, &new_width, &new_height);

		while (new_width == 0 || new_width == 0) 
		{
			glfwGetFramebufferSize(m_window, &new_width, &new_width);
			glfwWaitEvents();
		}

		m_width = new_width;
		m_height = new_height;
	}

	void Window::set_user_ptr(void* userPtr)
	{
		glfwSetWindowUserPointer(m_window, userPtr);
	}

	void Window::set_resize_callback(GLFWframebuffersizefun frameBufferResizeCallback)
	{
		glfwSetFramebufferSizeCallback(m_window, frameBufferResizeCallback);
	}

	void Window::init_window()
	{
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		m_window = glfwCreateWindow(m_width, m_height, m_windowName.c_str(), nullptr, nullptr);
	}

} // PsAi::Renderer namespace
