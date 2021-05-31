#include "application.h"

namespace PsAi
{

	void Application::run()
	{
		while (!m_window.should_close())
		{
			glfwPollEvents();
			draw_frame();
		}

		vkDeviceWaitIdle(m_device.get_logical_device());
	}

	void Application::draw_frame()
	{
		uint32_t imageIndex;
		vkAcquireNextImageKHR(m_device.get_logical_device(), m_swapchain.get_swapchain(), UINT64_MAX, m_imageAvailableSemaphore.get_semaphore(), VK_NULL_HANDLE, &imageIndex);
	
		VkSubmitInfo submitInfo = Renderer::submit_info();

		VkSemaphore waitSemaphores[] = { m_imageAvailableSemaphore.get_semaphore() };
		VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };

		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = waitSemaphores;
		submitInfo.pWaitDstStageMask = waitStages;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &m_commandBuffer.get_command_buffer()[imageIndex];

		VkSemaphore signalSemaphores[] = { m_renderFinishedSemaphore.get_semaphore() };
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = signalSemaphores;

		if (vkQueueSubmit(m_device.get_graphics_queue(), 1, &submitInfo, VK_NULL_HANDLE) != VK_SUCCESS)
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

		vkQueueWaitIdle(m_device.get_present_queue());
	}

} // PsAi namespace
