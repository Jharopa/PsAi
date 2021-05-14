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
		VkApplicationInfo applicationInfo {};
		applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		applicationInfo.pApplicationName = applicationName;
		applicationInfo.applicationVersion = applicationVersion;
		applicationInfo.pEngineName = engineName;
		applicationInfo.engineVersion = engineVersion;
		applicationInfo.apiVersion = vkAPIVersion;

		return applicationInfo;
	}

	inline VkInstanceCreateInfo instance_create_info(VkApplicationInfo& applicationInfo)
	{
		VkInstanceCreateInfo instanceCreateInfo {};
		instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instanceCreateInfo.pApplicationInfo = &applicationInfo;

		return instanceCreateInfo;
	}

	inline VkSwapchainCreateInfoKHR swapchain_create_info()
	{
		VkSwapchainCreateInfoKHR swapchainCreateInfo {};
		swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;

		return swapchainCreateInfo;
	}

	inline VkImageViewCreateInfo image_view_create_info()
	{
		VkImageViewCreateInfo imageViewCreateInfo {};
		imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;

		return imageViewCreateInfo;
	}

	inline VkDeviceCreateInfo device_create_info()
	{
		VkDeviceCreateInfo deviceCreateInfo {};
		deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

		return deviceCreateInfo;
	}

	inline VkDeviceQueueCreateInfo device_queue_create_info()
	{
		VkDeviceQueueCreateInfo deviceQueueCreateInfo {};
		deviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;

		return deviceQueueCreateInfo;
	}

	inline VkRenderPassCreateInfo render_pass_create_info()
	{
		VkRenderPassCreateInfo renderPassCreateInfo {};
		renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;

		return renderPassCreateInfo;
	}

	inline VkShaderModuleCreateInfo shader_module_create_info()
	{
		VkShaderModuleCreateInfo shaderModuleCreateInfo {};
		shaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;

		return shaderModuleCreateInfo;
	}

	inline VkPipelineShaderStageCreateInfo pipeline_vertex_shader_stage_create_info()
	{
		VkPipelineShaderStageCreateInfo vertexShaderStageCreateInfo {};
		vertexShaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		vertexShaderStageCreateInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;

		return vertexShaderStageCreateInfo;
	}

	inline VkPipelineShaderStageCreateInfo pipeline_fragment_shader_stage_create_info()
	{
		VkPipelineShaderStageCreateInfo fragmentShaderStageCreateInfo {};
		fragmentShaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		fragmentShaderStageCreateInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;

		return fragmentShaderStageCreateInfo;
	}

	inline VkPipelineVertexInputStateCreateInfo pipeline_vertex_input_stage_create_info()
	{
		VkPipelineVertexInputStateCreateInfo vertexInputStageCreateInfo {};
		vertexInputStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

		return vertexInputStageCreateInfo;
	}

	inline VkPipelineInputAssemblyStateCreateInfo pipeline_input_assembly_state_create_info()
	{
		VkPipelineInputAssemblyStateCreateInfo inputAssemblyStateCreateInfo {};
		inputAssemblyStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;

		return inputAssemblyStateCreateInfo;
	}

	inline VkPipelineViewportStateCreateInfo pipeline_viewport_state_create_info()
	{
		VkPipelineViewportStateCreateInfo viewportStateCreateInfo {};
		viewportStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;

		return viewportStateCreateInfo;
	}

	inline VkPipelineRasterizationStateCreateInfo pipeline_rasterization_create_info()
	{
		VkPipelineRasterizationStateCreateInfo rasterizationStateCreateInfo {};
		rasterizationStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;

		return rasterizationStateCreateInfo;
	}

	inline VkPipelineMultisampleStateCreateInfo pipeline_multisample_state_create_info()
	{
		VkPipelineMultisampleStateCreateInfo multisampleStateCreateInfo {};
		multisampleStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;

		return multisampleStateCreateInfo;
	}

	inline VkPipelineColorBlendStateCreateInfo pipeline_color_blend_state_create_info()
	{
		VkPipelineColorBlendStateCreateInfo colorBlendStateCreateInfo {};
		colorBlendStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;

		return colorBlendStateCreateInfo;
	}

	inline VkPipelineLayoutCreateInfo pipeline_layout_create_info()
	{
		VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo {};
		pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;

		return pipelineLayoutCreateInfo;
	}

	inline VkGraphicsPipelineCreateInfo graphics_pipeline_create_info()
	{
		VkGraphicsPipelineCreateInfo graphicsPipelineCreateInfo {};
		graphicsPipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		graphicsPipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
		graphicsPipelineCreateInfo.basePipelineIndex = -1;

		return graphicsPipelineCreateInfo;
	}

} // PsAi::Renderer namespace
