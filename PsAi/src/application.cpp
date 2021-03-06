#include "application.h"

namespace PsAi
{
	Application::Application()
	{
		m_window = std::make_unique<Renderer::Window>(800, 600, "PsAi Renderer");
		m_instance = std::make_unique<Renderer::Instance>(m_applicationInfo, m_instanceExtensions, true);
		m_surface = std::make_unique<Renderer::Surface>(m_instance->get_instance(), m_window->get_window());
		m_device = std::make_unique<Renderer::Device>(m_instance->get_instance(), m_surface->get_surface(), m_instance->is_validation_enabled());
		m_swapchain = std::make_unique<Renderer::Swapchain>(VK_NULL_HANDLE, m_device->get_physical_device(), m_device->get_logical_device(), m_surface->get_surface(), m_window->get_window());
		m_renderPass = std::make_unique<Renderer::RenderPass>(m_device->get_logical_device(), m_swapchain->get_image_format());
		m_vertShader = std::make_unique<Renderer::Shader>(m_device->get_logical_device(), "shaders/bytecode/simple.vert.spv");
		m_fragShader = std::make_unique<Renderer::Shader>(m_device->get_logical_device(), "shaders/bytecode/simple.frag.spv");
		m_pipeline = std::make_unique<Renderer::Pipeline>(m_device->get_logical_device(), m_renderPass->get_render_pass(), m_vertShader->get_shader_module(), m_fragShader->get_shader_module(), m_window->get_width(), m_window->get_height());
		m_framebuffers = std::make_unique<Renderer::Framebuffer>(m_device->get_logical_device(), m_swapchain->get_swapchain_image_views(), m_swapchain->get_image_extent(), m_renderPass->get_render_pass());
		m_commandPool = std::make_unique<Renderer::CommandPool>(m_device->get_logical_device(), m_device->get_physical_device(), m_surface->get_surface());
		m_commandBuffer = std::make_unique<Renderer::CommandBuffer>(m_device->get_logical_device(), m_swapchain->get_image_extent(), m_framebuffers->get_swapchain_framebuffers(), m_commandPool->get_command_pool(), m_renderPass->get_render_pass(), m_pipeline->get_graphics_pipeline());
		m_imageAvailableSemaphores = std::make_unique<Renderer::Semaphore>(m_device->get_logical_device(), MAX_FRAMES_IN_FLIGHT);
		m_renderFinishedSemaphores = std::make_unique<Renderer::Semaphore>(m_device->get_logical_device(), MAX_FRAMES_IN_FLIGHT);
		m_inFlightFences = std::make_unique<Renderer::Fence>(m_device->get_logical_device(), MAX_FRAMES_IN_FLIGHT);
		m_imagesInFlight = std::make_unique<Renderer::Fence>(m_device->get_logical_device(), m_swapchain->get_swapchain_image_count());
	
		m_window->set_user_ptr(this);

		GLFWframebuffersizefun lambdaFramebufferResizeCallback = [](GLFWwindow* window, int width, int height)
		{
			Application* application = static_cast<Application*>(glfwGetWindowUserPointer(window));
			application->m_windowResized = true;
		};

		m_window->set_resize_callback(lambdaFramebufferResizeCallback);
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		PSAI_LOG_DEBUG("Running application");

		while (!m_window->should_close())
		{
			glfwPollEvents();
			draw_frame();
		}

		vkDeviceWaitIdle(m_device->get_logical_device());
	}

	void Application::draw_frame()
	{
		vkWaitForFences(m_device->get_logical_device(), 1, &m_inFlightFences->get_fences()[m_currentFrame], VK_TRUE, UINT64_MAX);

		uint32_t imageIndex;
		VkResult result = vkAcquireNextImageKHR(m_device->get_logical_device(), m_swapchain->get_swapchain(), UINT64_MAX, m_imageAvailableSemaphores->get_semaphores()[m_currentFrame], VK_NULL_HANDLE, &imageIndex);
		
		if (result == VK_ERROR_OUT_OF_DATE_KHR)
		{
			recreate_swapchain();
			return;
		}
		else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) 
		{
			throw std::runtime_error("Failed to acquire swapchain image!");
		}

		if (m_imagesInFlight->get_fences()[imageIndex] != VK_NULL_HANDLE)
		{
			vkWaitForFences(m_device->get_logical_device(), 1, &m_imagesInFlight->get_fences()[imageIndex], VK_TRUE, UINT64_MAX);
		}

		m_imagesInFlight->get_fences()[imageIndex] = m_inFlightFences->get_fences()[m_currentFrame];

		VkSubmitInfo submitInfo = Renderer::submit_info();

		VkSemaphore waitSemaphores[] = { m_imageAvailableSemaphores->get_semaphores()[m_currentFrame] };
		VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };

		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = waitSemaphores;
		submitInfo.pWaitDstStageMask = waitStages;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &m_commandBuffer->get_command_buffer()[imageIndex];

		VkSemaphore signalSemaphores[] = { m_renderFinishedSemaphores->get_semaphores()[m_currentFrame] };
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = signalSemaphores;

		vkResetFences(m_device->get_logical_device(), 1, &m_inFlightFences->get_fences()[m_currentFrame]);

		if (vkQueueSubmit(m_device->get_graphics_queue(), 1, &submitInfo, m_inFlightFences->get_fences()[m_currentFrame]) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to submit Vulkan draw command buffer");
		}

		VkPresentInfoKHR presentInfo = Renderer::present_info_ext();
		
		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = signalSemaphores;

		VkSwapchainKHR  swapchains[] = { m_swapchain->get_swapchain() };
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = swapchains;
		presentInfo.pImageIndices = &imageIndex;

		presentInfo.pResults = nullptr;

		result = vkQueuePresentKHR(m_device->get_present_queue(), &presentInfo);

		if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || m_windowResized)
		{
			m_windowResized = false;
			recreate_swapchain();
		}
		else if (result != VK_SUCCESS) 
		{
			throw std::runtime_error("Failed to present swapchain image!");
		}

		m_currentFrame = (m_currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
	}

	void Application::recreate_swapchain()
	{
		m_window->resize_window_dimensions();

		vkDeviceWaitIdle(m_device->get_logical_device());

		VkSwapchainKHR oldSwapchain = m_swapchain->get_swapchain();

		m_swapchain.reset();
		m_swapchain = std::make_unique<Renderer::Swapchain>(oldSwapchain, m_device->get_physical_device(), m_device->get_logical_device(), m_surface->get_surface(), m_window->get_window());
		m_renderPass.reset();
		m_renderPass = std::make_unique<Renderer::RenderPass>(m_device->get_logical_device(), m_swapchain->get_image_format());
		m_pipeline.reset();
		m_pipeline = std::make_unique<Renderer::Pipeline>(m_device->get_logical_device(), m_renderPass->get_render_pass(), m_vertShader->get_shader_module(), m_fragShader->get_shader_module(), m_window->get_width(), m_window->get_height());
		m_framebuffers.reset();
		m_framebuffers = std::make_unique<Renderer::Framebuffer>(m_device->get_logical_device(), m_swapchain->get_swapchain_image_views(), m_swapchain->get_image_extent(), m_renderPass->get_render_pass());
		m_commandBuffer.reset();
		m_commandBuffer = std::make_unique<Renderer::CommandBuffer>(m_device->get_logical_device(), m_swapchain->get_image_extent(), m_framebuffers->get_swapchain_framebuffers(), m_commandPool->get_command_pool(), m_renderPass->get_render_pass(), m_pipeline->get_graphics_pipeline());
	}

} // PsAi namespace
