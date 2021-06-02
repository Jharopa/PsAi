#include "framebuffer.h"

namespace PsAi::Renderer
{

	Framebuffer::Framebuffer(VkDevice logicalDevice, std::vector<VkImageView> swapchainImageViews, VkExtent2D swapchainImageExtent, VkRenderPass renderPass)
		: m_logicalDevice(logicalDevice)
	{
		m_swapchaninFramebuffers.resize(swapchainImageViews.size());

		for (size_t i = 0; i < swapchainImageViews.size(); i++)
		{
			VkImageView attachments[] = { swapchainImageViews[i] };

			VkFramebufferCreateInfo framebufferCreateInfo = frame_buffer_create_info();
			framebufferCreateInfo.renderPass = renderPass;
			framebufferCreateInfo.attachmentCount = 1;
			framebufferCreateInfo.pAttachments = attachments;
			framebufferCreateInfo.width = swapchainImageExtent.width;
			framebufferCreateInfo.height = swapchainImageExtent.height;
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
