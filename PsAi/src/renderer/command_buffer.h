#pragma once

// PsAi includes
#include "../util/non_copy_non_move.h"
#include "vulkan_structures.h"
#include "logical_device.h"
#include "framebuffer.h"
#include "command_pool.h"
#include "render_pass.h"
#include "pipeline.h"

// Vulkan includes
#include <vulkan/vulkan.h>

// STD library includes
#include <vector>

namespace PsAi::Renderer
{

	class CommandBuffer : public Util::NonCopyableNonMoveable
	{
		public:
			CommandBuffer(VkDevice logicalDevice, const Swapchain& swapchain, const Framebuffer& framebuffers, VkCommandPool commandPool, VkRenderPass renderPass, VkPipeline graphicsPipeline);
			~CommandBuffer();

			const std::vector<VkCommandBuffer>& get_command_buffer() const { return m_commandBuffers; }

		private:
			std::vector<VkCommandBuffer> m_commandBuffers;
			VkDevice m_logicalDevice;
	};

} // PsAi::Renderer namespace
