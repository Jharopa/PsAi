#pragma once

// PsAi includes
#include "logical_device.h"
#include "swapchain.h"

// Vulkan includes
#include <vulkan/vulkan.h>

namespace PsAi::Renderer
{

	class RenderPass
	{
		public:
			RenderPass(const LogicalDevice& logicalDevice, const Swapchain& swapchain);
			~RenderPass();

			RenderPass(const RenderPass&) = delete;
			RenderPass(RenderPass&&) = delete;
			RenderPass& operator=(const RenderPass&) = delete;
			RenderPass& operator=(RenderPass&&) = delete;

			const VkRenderPass get_render_pass() const { return m_renderPass; }

		private:
			VkRenderPass m_renderPass;

			const LogicalDevice& m_logicalDevice;
			const Swapchain& m_swapchain;
	};

} // PsAi::Renderer namespace
