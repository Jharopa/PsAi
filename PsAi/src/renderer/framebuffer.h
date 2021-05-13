#pragma once

// PsAi includes
#include "logical_device.h"
#include "swapchain.h"
#include "render_pass.h"

// Vulkan includes
#include <vulkan/vulkan.h>

// STD library includes
#include <vector>

// TODO: This class going to be an ecapsulation of several VKFramebuffers,
// might be better to have it be just encapsulate of one and make a vector
// of framebuffers outside using the framebuffer class outside the class.
// Need to do some research and look into others code. This is fine for
// now I think, just trying to get the triangle on screen right now tbh.
namespace PsAi::Renderer
{

	class Framebuffer
	{
		public:
			Framebuffer(const LogicalDevice& logicalDevice, const Swapchain& swapchain, const RenderPass& renderPass);
			~Framebuffer();

			// Non-copyable and non-movable
			Framebuffer(const Framebuffer&) = delete;
			Framebuffer(Framebuffer&&) = delete;
			Framebuffer& operator=(const Framebuffer&) = delete;
			Framebuffer& operator=(Framebuffer&&) = delete;

			std::vector<VkFramebuffer> get_swapchain_framebuffers() const { return m_swapchaninFramebuffers; }

		private:
			std::vector<VkFramebuffer> m_swapchaninFramebuffers;

			const LogicalDevice& m_logicalDevice;
	};

} // PsAi::Renderer namespace