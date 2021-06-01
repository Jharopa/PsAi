#pragma once

// PsAi includes
#include "renderer/vulkan_structures.h"
#include "renderer/window.h"
#include "renderer/instance.h"
#include "renderer/surface.h"
#include "renderer/device.h"
#include "renderer/swapchain.h"
#include "renderer/render_pass.h"
#include "renderer/shader.h"
#include "renderer/pipeline.h"
#include "renderer/framebuffer.h"
#include "renderer/command_pool.h"
#include "renderer/command_buffer.h"
#include "renderer/semaphore.h"
#include "renderer/fence.h"
#include "renderer/vulkan_structures.h"

// Vulkan includes
#include <vulkan/vulkan.h>

// STD library includes
#include <vector>

namespace PsAi 
{

	class Application 
	{
		public:
			// Public member variables
			static constexpr int WIDTH = 800;
			static constexpr int HEIGHT = 600;
			static constexpr int MAX_FRAMES_IN_FLIGHT = 2;

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
			Renderer::Device m_device{ m_instance, m_surface.get_surface() }; 
			Renderer::Swapchain m_swapchain{ m_device.get_physical_device(), m_device.get_logical_device(), m_surface.get_surface(), m_window.get_window() };
			Renderer::RenderPass m_renderPass{ m_device.get_logical_device(), m_swapchain };
			Renderer::Shader m_vertShader{ m_device.get_logical_device(), "shaders/bytecode/simple.vert.spv" };
			Renderer::Shader m_fragShader{ m_device.get_logical_device(), "shaders/bytecode/simple.frag.spv" };
			Renderer::Pipeline m_pipeline{ m_device.get_logical_device(), m_renderPass.get_render_pass(), m_vertShader.get_shader_module(), m_fragShader.get_shader_module(), WIDTH, HEIGHT };
			Renderer::Framebuffer m_framebuffers{ m_device.get_logical_device(), m_swapchain, m_renderPass.get_render_pass() };
			Renderer::CommandPool m_commandPool{ m_device.get_logical_device(), m_device.get_physical_device(), m_surface.get_surface() };
			Renderer::CommandBuffer m_commandBuffer{ m_device.get_logical_device(), m_swapchain, m_framebuffers, m_commandPool.get_command_pool(), m_renderPass.get_render_pass(), m_pipeline.get_graphics_pipeline() };
			Renderer::Semaphore m_imageAvailableSemaphores = { m_device.get_logical_device(), MAX_FRAMES_IN_FLIGHT };
			Renderer::Semaphore m_renderFinishedSemaphores = { m_device.get_logical_device(), MAX_FRAMES_IN_FLIGHT };
			Renderer::Fence m_inFlightFences = { m_device.get_logical_device(), MAX_FRAMES_IN_FLIGHT };
			Renderer::Fence m_imagesInFlight = { m_device.get_logical_device(), m_swapchain.get_swapchain_image_count() };
			size_t currentFrame = 0;
	};

} // PsAi namespace
