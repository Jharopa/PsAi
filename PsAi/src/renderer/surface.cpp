#include "surface.h"

namespace PsAi::Renderer
{

	Surface::Surface(const Instance& instance, GLFWwindow* window)
		: m_instance(instance), m_window(window)
	{
		PSAI_LOG_DEBUG("Creating Vulkan surface");
		create_surface();
		PSAI_LOG_DEBUG("Vulkan surface successfully created");
	}

	Surface::~Surface()
	{
		vkDestroySurfaceKHR(m_instance.get_instance(), m_surface, nullptr);
	}

	void Surface::create_surface()
	{
		if (glfwCreateWindowSurface(m_instance.get_instance(), m_window, nullptr, &m_surface) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create Vulkan window surface");
		}
	}

} // PsAi::Renderer namespace
