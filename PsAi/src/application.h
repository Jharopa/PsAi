#pragma once

// PsAi includes
#include "renderer/vulkan_structures.h"
#include "renderer/window.h"
#include "renderer/instance.h"
#include "renderer/physical_device.h"
#include "renderer/surface.h"
#include "renderer/logical_device.h"
#include "renderer/swapchain.h"
#include "renderer/render_pass.h"
#include "renderer/shader.h"
#include "renderer/pipeline.h"
#include "renderer/framebuffer.h"
#include "renderer/command_pool.h"
#include "renderer/command_buffer.h"
#include "renderer/semaphore.h"
#include "renderer/vulkan_structures.h"

// Vulkan includes
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
			void draw_frame();

		private:
			// Private member variables
			Renderer::Window m_window{ WIDTH, HEIGHT, "First App!" };
			const std::vector<std::string> m_instanceExtensions = {};
			VkApplicationInfo applicationInfo = Renderer::application_info("PsAi", VK_MAKE_VERSION(0, 0, 1), "No Engine", VK_MAKE_VERSION(0, 0, 1), VK_API_VERSION_1_2);
			Renderer::Instance m_instance{ applicationInfo, m_instanceExtensions , 1 };
			Renderer::Surface m_surface{ m_instance, m_window.get_window() };
			Renderer::PhysicalDevice m_physicalDevice{ m_instance };
			Renderer::LogicalDevice m_logicalDevice{ m_instance, m_physicalDevice, m_surface };
			Renderer::Swapchain m_swapchain{ m_physicalDevice, m_logicalDevice, m_surface, m_window.get_window() };
			Renderer::RenderPass m_renderPass{ m_logicalDevice, m_swapchain };
			Renderer::Shader m_vertShader{ m_logicalDevice, "shaders/bytecode/simple.vert.spv" };
			Renderer::Shader m_fragShader{ m_logicalDevice, "shaders/bytecode/simple.frag.spv" };
			Renderer::Pipeline m_pipeline{ m_logicalDevice, m_renderPass, m_vertShader, m_fragShader, WIDTH, HEIGHT };
			Renderer::Framebuffer m_framebuffers{ m_logicalDevice, m_swapchain, m_renderPass };
			Renderer::CommandPool m_commandPool{ m_logicalDevice, m_physicalDevice, m_surface };
			Renderer::CommandBuffer m_commandBuffer{ m_logicalDevice, m_swapchain, m_framebuffers, m_commandPool, m_renderPass, m_pipeline };
			Renderer::Semaphore m_imageAvailableSemaphore{ m_logicalDevice };
			Renderer::Semaphore m_renderFinishedSemaphore{ m_logicalDevice };
	};

} // PsAi namespace
