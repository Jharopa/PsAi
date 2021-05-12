#include "render_pass.h"

namespace PsAi::Renderer
{

	RenderPass::RenderPass(const LogicalDevice& logicalDevice, const Swapchain& swapchain)
		: m_logicalDevice(logicalDevice), m_swapchain(swapchain)
	{
		VkAttachmentDescription colorAttachment{};
		colorAttachment.format = m_swapchain.get_image_format();
		colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
		colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

		VkAttachmentReference colorAttachmentRef{};
		colorAttachmentRef.attachment = 0;
		colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		VkSubpassDescription subpass{};
		subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpass.colorAttachmentCount = 1;
		subpass.pColorAttachments = &colorAttachmentRef;

		VkRenderPassCreateInfo renderPassCreateInfo{};
		renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		renderPassCreateInfo.attachmentCount = 1;
		renderPassCreateInfo.pAttachments = &colorAttachment;
		renderPassCreateInfo.subpassCount = 1;
		renderPassCreateInfo.pSubpasses = &subpass;

		if (vkCreateRenderPass(m_logicalDevice.get_logical_device(), &renderPassCreateInfo, nullptr, &m_renderPass) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create Vulkan render pass!");
		}
	}

	RenderPass::~RenderPass()
	{
		vkDestroyRenderPass(m_logicalDevice.get_logical_device(), m_renderPass, nullptr);
	}

} // PsAi::Renderer namespace
