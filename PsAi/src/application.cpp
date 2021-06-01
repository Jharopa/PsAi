#include "application.h"

namespace PsAi
{

	void Application::run()
	{
		PSAI_LOG_DEBUG("Running application");

		while (!m_window.should_close())
		{
			glfwPollEvents();
			draw_frame();
		}

		vkDeviceWaitIdle(m_device.get_logical_device());
	}

	void Application::draw_frame()
	{
		vkWaitForFences(m_device.get_logical_device(), 1, &m_inFlightFences.get_fences()[currentFrame], VK_TRUE, UINT64_MAX);

		uint32_t imageIndex;
		vkAcquireNextImageKHR(m_device.get_logical_device(), m_swapchain.get_swapchain(), UINT64_MAX, m_imageAvailableSemaphores.get_semaphores()[currentFrame], VK_NULL_HANDLE, &imageIndex);
		
		if (m_imagesInFlight.get_fences()[imageIndex] != VK_NULL_HANDLE)
		{
			vkWaitForFences(m_device.get_logical_device(), 1, &m_imagesInFlight.get_fences()[imageIndex], VK_TRUE, UINT64_MAX);
		}

		m_imagesInFlight.get_fences()[imageIndex] = m_inFlightFences.get_fences()[currentFrame];

		VkSubmitInfo submitInfo = Renderer::submit_info();

		VkSemaphore waitSemaphores[] = { m_imageAvailableSemaphores.get_semaphores()[currentFrame] };
		VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };

		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = waitSemaphores;
		submitInfo.pWaitDstStageMask = waitStages;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &m_commandBuffer.get_command_buffer()[imageIndex];

		VkSemaphore signalSemaphores[] = { m_renderFinishedSemaphores.get_semaphores()[currentFrame] };
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = signalSemaphores;

		vkResetFences(m_device.get_logical_device(), 1, &m_inFlightFences.get_fences()[currentFrame]);

		if (vkQueueSubmit(m_device.get_graphics_queue(), 1, &submitInfo, m_inFlightFences.get_fences()[currentFrame]) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to submit Vulkan draw command buffer");
		}

		VkPresentInfoKHR presentInfo = Renderer::present_info_ext();
		
		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = signalSemaphores;

		VkSwapchainKHR  swapchains[] = { m_swapchain.get_swapchain() };
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = swapchains;
		presentInfo.pImageIndices = &imageIndex;

		presentInfo.pResults = nullptr;

		vkQueuePresentKHR(m_device.get_present_queue(), &presentInfo);

		currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
	}

} // PsAi namespace
