#pragma once

// PsAi includes
#include "../util/non_copy_non_move.h"
#include "device.h"
#include "swapchain.h"

// Vulkan includes
#include <vulkan/vulkan.h>

namespace PsAi::Renderer
{

	class RenderPass : public Util::NonCopyableNonMoveable
	{
		public:
			RenderPass(VkDevice logicalDevice, VkFormat swapchainImageFormat);
			~RenderPass();

			const VkRenderPass& get_render_pass() const { return m_renderPass; }

		private:
			VkRenderPass m_renderPass;

			VkDevice m_logicalDevice;
	};

} // PsAi::Renderer namespace
