#pragma once

// PsAi includes
#include "renderer/window.h"
#include "renderer/instance.h"
#include "renderer/physical_device.h"
#include "renderer/surface.h"
#include "renderer/logical_device.h"
#include "log.h"

#include <vulkan/vulkan.h>

namespace PsAi 
{

	class Application 
	{
		public:
			// Public member variables
			static constexpr int WIDTH = 800;
			static constexpr int HEIGHT = 600;

			// Public member functions
			void run();

		private:
			// Private member variables
			Renderer::Window m_window{ WIDTH, HEIGHT, "First App!" };
			const std::vector<std::string> m_instanceExtensions = {};
			Renderer::Instance m_instance{ "PsAi", VK_MAKE_VERSION(0, 0, 1), "No Engine", VK_MAKE_VERSION(0, 0, 1), VK_API_VERSION_1_2, m_instanceExtensions , 0 };
			Renderer::Surface m_surface{ m_instance, m_window.get_window() };
			Renderer::PhysicalDevice m_physicalDevice{ m_instance };
			Renderer::LogicalDevice m_logicalDevice{ m_instance, m_physicalDevice, m_surface };
	};

} // PsAi namespace
