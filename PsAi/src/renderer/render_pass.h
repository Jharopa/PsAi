#pragma once

// PsAi includes
#include "../util/non_copy_non_move.h"
#include "logical_device.h"
#include "swapchain.h"

// Vulkan includes
#include <vulkan/vulkan.h>

namespace PsAi::Renderer
{

	class RenderPass : public Util::NonCopyableNonMoveable
	{
		public:
			RenderPass(const LogicalDevice& logicalDevice, const Swapchain& swapchain);
			~RenderPass();

			const VkRenderPass& get_render_pass() const { return m_renderPass; }

		private:
			VkRenderPass m_renderPass;

			const LogicalDevice& m_logicalDevice;
			const Swapchain& m_swapchain;
	};

} // PsAi::Renderer namespace
