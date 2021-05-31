#include "framebuffer.h"

namespace PsAi::Renderer
{

	Framebuffer::Framebuffer(VkDevice logicalDevice, const Swapchain& swapchain, VkRenderPass renderPass)
		: m_logicalDevice(logicalDevice)
	{
		m_swapchaninFramebuffers.resize(swapchain.get_swapchain_image_views().size());

		for (size_t i = 0; i < swapchain.get_swapchain_image_views().size(); i++)
		{
			VkImageView attachments[] = { swapchain.get_swapchain_image_views()[i] };

			VkFramebufferCreateInfo framebufferCreateInfo = frame_buffer_create_info();
			framebufferCreateInfo.renderPass = renderPass;
			framebufferCreateInfo.attachmentCount = 1;
			framebufferCreateInfo.pAttachments = attachments;
			framebufferCreateInfo.width = swapchain.get_extent().width;
			framebufferCreateInfo.height = swapchain.get_extent().height;
			framebufferCreateInfo.layers = 1;

			if (vkCreateFramebuffer(m_logicalDevice, &framebufferCreateInfo, nullptr, &m_swapchaninFramebuffers[i]) != VK_SUCCESS)
			{
				throw std::runtime_error("Failed to create Vulkan framebuffer!");
			}
		}
	}

	Framebuffer::~Framebuffer()
	{
		for (auto framebuffer : m_swapchaninFramebuffers)
		{
			vkDestroyFramebuffer(m_logicalDevice, framebuffer, nullptr);
		}
	}

} // PsAi::Renderer namespace
