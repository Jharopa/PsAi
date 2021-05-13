#include "command_buffer.h"
namespace PsAi::Renderer
{

	CommandBuffer::CommandBuffer(const LogicalDevice& logicalDevice, const Swapchain& swapchain, const Framebuffer& framebuffers, const CommandPool& commandPool, const RenderPass& renderPass, const Pipeline& graphicsPipeline)
		: m_logicalDevice(logicalDevice)
	{
		m_commandBuffers.resize(framebuffers.get_swapchain_framebuffers().size());

		VkCommandBufferAllocateInfo allocateInfo{};
		allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocateInfo.commandBufferCount = (uint32_t)m_commandBuffers.size();
		allocateInfo.commandPool = commandPool.get_command_pool();
		allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;

		if (vkAllocateCommandBuffers(m_logicalDevice.get_logical_device(), &allocateInfo, m_commandBuffers.data()) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to allocate Vulkan command buffers!");
		}

		for (size_t i = 0; i < m_commandBuffers.size(); i++)
		{
			VkCommandBufferBeginInfo beginInfo{};
			beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

			if (vkBeginCommandBuffer(m_commandBuffers[i], &beginInfo) != VK_SUCCESS)
			{
				throw std::runtime_error("Failed to begin recording Vulkan command buffer!");
			}

			VkRenderPassBeginInfo renderPassInfo{};
			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderPassInfo.renderPass = renderPass.get_render_pass();
			renderPassInfo.framebuffer = framebuffers.get_swapchain_framebuffers()[i];
			renderPassInfo.renderArea.offset = { 0, 0 };
			renderPassInfo.renderArea.extent = swapchain.get_extent();

			VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f};
			renderPassInfo.clearValueCount = 1;
			renderPassInfo.pClearValues = &clearColor;

			vkCmdBeginRenderPass(m_commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

			vkCmdBindPipeline(m_commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline.get_graphics_pipeline());

			vkCmdDraw(m_commandBuffers[i], 3, 1, 0, 0);

			vkCmdEndRenderPass(m_commandBuffers[i]);

			if (vkEndCommandBuffer(m_commandBuffers[i]) != VK_SUCCESS) {
				throw std::runtime_error("Failed to record Vulkan command buffer!");
			}
		}
	}

	CommandBuffer::~CommandBuffer()
	{
	}

} // PsAi::Renderer namespace
