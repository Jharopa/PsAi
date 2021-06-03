#include "command_buffer.h"
namespace PsAi::Renderer
{

	CommandBuffer::CommandBuffer(VkDevice logicalDevice, VkExtent2D swapchainImageExtent, std::vector<VkFramebuffer> swapchainFramebuffers, VkCommandPool commandPool, VkRenderPass renderPass, VkPipeline graphicsPipeline)
		: m_logicalDevice(logicalDevice), m_commandPool(commandPool)
	{
		m_commandBuffers.resize(swapchainFramebuffers.size());

		VkCommandBufferAllocateInfo allocateInfo = command_buffer_allocate_info();
		allocateInfo.commandBufferCount = (uint32_t)m_commandBuffers.size();
		allocateInfo.commandPool = commandPool;
		allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;

		if (vkAllocateCommandBuffers(m_logicalDevice, &allocateInfo, m_commandBuffers.data()) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to allocate Vulkan command buffers!");
		}

		for (size_t i = 0; i < m_commandBuffers.size(); i++)
		{
			VkCommandBufferBeginInfo beginInfo = command_buffer_begin_info();

			if (vkBeginCommandBuffer(m_commandBuffers[i], &beginInfo) != VK_SUCCESS)
			{
				throw std::runtime_error("Failed to begin recording Vulkan command buffer!");
			}

			VkRenderPassBeginInfo renderPassInfo = render_pass_begin_info();
			renderPassInfo.renderPass = renderPass;
			renderPassInfo.framebuffer = swapchainFramebuffers[i];
			renderPassInfo.renderArea.offset = { 0, 0 };
			renderPassInfo.renderArea.extent = swapchainImageExtent;

			VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f};
			renderPassInfo.clearValueCount = 1;
			renderPassInfo.pClearValues = &clearColor;

			vkCmdBeginRenderPass(m_commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

			vkCmdBindPipeline(m_commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);

			vkCmdDraw(m_commandBuffers[i], 3, 1, 0, 0);

			vkCmdEndRenderPass(m_commandBuffers[i]);

			if (vkEndCommandBuffer(m_commandBuffers[i]) != VK_SUCCESS) {
				throw std::runtime_error("Failed to record Vulkan command buffer!");
			}
		}
	}

	CommandBuffer::~CommandBuffer()
	{
		vkFreeCommandBuffers(m_logicalDevice, m_commandPool, static_cast<uint32_t>(m_commandBuffers.size()), m_commandBuffers.data());
	}

} // PsAi::Renderer namespace
