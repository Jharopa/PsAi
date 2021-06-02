#pragma once

// PsAi includes
#include "../util/non_copy_non_move.h"
#include "device.h"
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

	class Framebuffer : public Util::NonCopyableNonMoveable
	{
		public:
			Framebuffer(VkDevice logicalDevice, std::vector<VkImageView> swapchainImageViews, VkExtent2D swapchainImageExtent, VkRenderPass renderPass);
			~Framebuffer();

			std::vector<VkFramebuffer> get_swapchain_framebuffers() const { return m_swapchaninFramebuffers; }

		private:
			std::vector<VkFramebuffer> m_swapchaninFramebuffers;

			VkDevice m_logicalDevice;
	};

} // PsAi::Renderer namespace
