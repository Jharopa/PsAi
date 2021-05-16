#pragma once

#include <vulkan/vulkan.h>

namespace PsAi::Renderer
{

	inline VkApplicationInfo application_info(
		const char* applicationName, 
		uint32_t applicationVersion, 
		const char* engineName,
		uint32_t engineVersion,
		uint32_t vkAPIVersion)
	{
		VkApplicationInfo ret {};
		ret.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		ret.pApplicationName = applicationName;
		ret.applicationVersion = applicationVersion;
		ret.pEngineName = engineName;
		ret.engineVersion = engineVersion;
		ret.apiVersion = vkAPIVersion;

		return ret;
	}

	inline VkInstanceCreateInfo instance_create_info(VkApplicationInfo& applicationInfo)
	{
		VkInstanceCreateInfo ret {};
		ret.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		ret.pApplicationInfo = &applicationInfo;

		return ret;
	}

	inline VkDebugUtilsMessengerCreateInfoEXT debug_utils_messenger_create_info()
	{
		VkDebugUtilsMessengerCreateInfoEXT ret {};
		ret.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		ret.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		ret.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	
		return ret;
	}

	inline VkSwapchainCreateInfoKHR swapchain_create_info_ext()
	{
		VkSwapchainCreateInfoKHR ret {};
		ret.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;

		return ret;
	}

	inline VkImageViewCreateInfo image_view_create_info()
	{
		VkImageViewCreateInfo ret {};
		ret.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;

		return ret;
	}

	inline VkDeviceCreateInfo device_create_info()
	{
		VkDeviceCreateInfo ret {};
		ret.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

		return ret;
	}

	inline VkDeviceQueueCreateInfo device_queue_create_info()
	{
		VkDeviceQueueCreateInfo ret {};
		ret.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;

		return ret;
	}

	inline VkRenderPassCreateInfo render_pass_create_info()
	{
		VkRenderPassCreateInfo ret {};
		ret.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;

		return ret;
	}

	inline VkShaderModuleCreateInfo shader_module_create_info()
	{
		VkShaderModuleCreateInfo ret {};
		ret.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;

		return ret;
	}

	inline VkPipelineShaderStageCreateInfo pipeline_vertex_shader_stage_create_info()
	{
		VkPipelineShaderStageCreateInfo ret {};
		ret.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		ret.stage = VK_SHADER_STAGE_VERTEX_BIT;

		return ret;
	}

	inline VkPipelineShaderStageCreateInfo pipeline_fragment_shader_stage_create_info()
	{
		VkPipelineShaderStageCreateInfo ret {};
		ret.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		ret.stage = VK_SHADER_STAGE_FRAGMENT_BIT;

		return ret;
	}

	inline VkPipelineVertexInputStateCreateInfo pipeline_vertex_input_stage_create_info()
	{
		VkPipelineVertexInputStateCreateInfo ret {};
		ret.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

		return ret;
	}

	inline VkPipelineInputAssemblyStateCreateInfo pipeline_input_assembly_state_create_info()
	{
		VkPipelineInputAssemblyStateCreateInfo ret {};
		ret.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;

		return ret;
	}

	inline VkPipelineViewportStateCreateInfo pipeline_viewport_state_create_info()
	{
		VkPipelineViewportStateCreateInfo ret {};
		ret.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;

		return ret;
	}

	inline VkPipelineRasterizationStateCreateInfo pipeline_rasterization_create_info()
	{
		VkPipelineRasterizationStateCreateInfo ret {};
		ret.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;

		return ret;
	}

	inline VkPipelineMultisampleStateCreateInfo pipeline_multisample_state_create_info()
	{
		VkPipelineMultisampleStateCreateInfo ret {};
		ret.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;

		return ret;
	}

	inline VkPipelineColorBlendStateCreateInfo pipeline_color_blend_state_create_info()
	{
		VkPipelineColorBlendStateCreateInfo ret {};
		ret.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;

		return ret;
	}

	inline VkPipelineLayoutCreateInfo pipeline_layout_create_info()
	{
		VkPipelineLayoutCreateInfo ret {};
		ret.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;

		return ret;
	}

	inline VkGraphicsPipelineCreateInfo graphics_pipeline_create_info()
	{
		VkGraphicsPipelineCreateInfo ret {};
		ret.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		ret.basePipelineHandle = VK_NULL_HANDLE;
		ret.basePipelineIndex = -1;

		return ret;
	}

	inline VkFramebufferCreateInfo frame_buffer_create_info()
	{
		VkFramebufferCreateInfo ret {};
		ret.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;

		return ret;
	}

	inline VkCommandPoolCreateInfo command_pool_create_info()
	{
		VkCommandPoolCreateInfo ret {};
		ret.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;

		return ret;
	}

	inline VkCommandBufferAllocateInfo command_buffer_allocate_info()
	{
		VkCommandBufferAllocateInfo ret {};
		ret.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;

		return ret;
	}

	inline VkCommandBufferBeginInfo command_buffer_begin_info()
	{
		VkCommandBufferBeginInfo ret {};
		ret.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

		return ret;
	}

	inline VkRenderPassBeginInfo render_pass_begin_info()
	{
		VkRenderPassBeginInfo ret {};
		ret.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;

		return ret;
	}

	inline VkSemaphoreCreateInfo semaphore_create_info()
	{
		VkSemaphoreCreateInfo ret {};
		ret.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

		return ret;
	}

	inline VkSubmitInfo submit_info()
	{
		VkSubmitInfo ret {};
		ret.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

		return ret;
	}

	inline VkPresentInfoKHR present_info_ext()
	{
		VkPresentInfoKHR ret {};
		ret.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

		return ret;
	}

} // PsAi::Renderer namespace
