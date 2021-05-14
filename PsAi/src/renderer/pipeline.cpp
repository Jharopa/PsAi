#include "pipeline.h"

namespace PsAi::Renderer
{
	
	Pipeline::Pipeline(const LogicalDevice& logicalDevice, const RenderPass& renderPass, const Shader& vertShader, const Shader& fragShader, int width, int height)
		: m_logicalDevice(logicalDevice), m_renderPass(renderPass), m_vertShader(vertShader), m_fragShader(fragShader)
	{
		PSAI_LOG_DEBUG("Creating Vulkan pipline layout");

		// Vertex shader stage create info 
		VkPipelineShaderStageCreateInfo vertShaderCreateInfo = pipeline_vertex_shader_stage_create_info();
		vertShaderCreateInfo.module = m_vertShader.get_shader_module();
		vertShaderCreateInfo.pName = "main";

		// Fragment shader stage create info 
		VkPipelineShaderStageCreateInfo fragShaderCreateInfo = pipeline_fragment_shader_stage_create_info();
		fragShaderCreateInfo.module = m_fragShader.get_shader_module();
		fragShaderCreateInfo.pName = "main";

		VkPipelineShaderStageCreateInfo shaderStages[] = { vertShaderCreateInfo, fragShaderCreateInfo };

		// Vertex input state create info
		VkPipelineVertexInputStateCreateInfo vertexInputCreateInfo = pipeline_vertex_input_stage_create_info();
		vertexInputCreateInfo.vertexBindingDescriptionCount = 0;
		vertexInputCreateInfo.pVertexBindingDescriptions = nullptr;
		vertexInputCreateInfo.vertexAttributeDescriptionCount = 0;
		vertexInputCreateInfo.pVertexAttributeDescriptions = nullptr;

		// Input assembly state create info
		VkPipelineInputAssemblyStateCreateInfo inputAssemblyCreateInfo = pipeline_input_assembly_state_create_info();
		inputAssemblyCreateInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		inputAssemblyCreateInfo.primitiveRestartEnable = VK_FALSE;

		// Pipeline viewport
		VkViewport viewport{};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = (float)width;
		viewport.height = (float)height;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

		// Pipeline scissor
		VkRect2D scissor{};
		scissor.offset = { 0, 0 };
		scissor.extent = { static_cast<uint32_t>(width) , static_cast<uint32_t>(height) };

		// Viewport state create info
		VkPipelineViewportStateCreateInfo viewportStateCreateInfo = pipeline_viewport_state_create_info();
		viewportStateCreateInfo.viewportCount = 1;
		viewportStateCreateInfo.pViewports = &viewport;
		viewportStateCreateInfo.scissorCount = 1;
		viewportStateCreateInfo.pScissors = &scissor;

		// Rasterizer state create info
		VkPipelineRasterizationStateCreateInfo rasterizer = pipeline_rasterization_create_info();
		rasterizer.depthClampEnable = VK_FALSE;
		rasterizer.rasterizerDiscardEnable = VK_FALSE;
		rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
		rasterizer.lineWidth = 1.0f;
		rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
		rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
		rasterizer.depthBiasEnable = VK_FALSE;
		rasterizer.depthBiasConstantFactor = 0.0f;
		rasterizer.depthBiasClamp = 0.0f;
		rasterizer.depthBiasSlopeFactor = 0.0f;

		// Multisample state create info
		VkPipelineMultisampleStateCreateInfo multisampling = pipeline_multisample_state_create_info();
		multisampling.sampleShadingEnable = VK_FALSE;
		multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
		multisampling.minSampleShading = 1.0f;
		multisampling.pSampleMask = nullptr;
		multisampling.alphaToCoverageEnable = VK_FALSE;
		multisampling.alphaToOneEnable = VK_FALSE;

		// Color blend attachment state
		VkPipelineColorBlendAttachmentState colorBlendAttachment{};
		colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		colorBlendAttachment.blendEnable = VK_TRUE;
		colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
		colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
		colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
		colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
		colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
		colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

		// Color blend state create info
		VkPipelineColorBlendStateCreateInfo colorBlending = pipeline_color_blend_state_create_info();
		colorBlending.logicOpEnable = VK_FALSE; // TODO: Look deeper into how this works and how to set it up properly, set false for the time being.
		colorBlending.logicOp = VK_LOGIC_OP_COPY;
		colorBlending.attachmentCount = 1;
		colorBlending.pAttachments = &colorBlendAttachment;
		colorBlending.blendConstants[0] = 0.0f;
		colorBlending.blendConstants[1] = 0.0f;
		colorBlending.blendConstants[2] = 0.0f;
		colorBlending.blendConstants[3] = 0.0f;

		// Pipeline layout create info
		VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo = pipeline_layout_create_info();
		pipelineLayoutCreateInfo.setLayoutCount = 0;
		pipelineLayoutCreateInfo.pSetLayouts = nullptr;
		pipelineLayoutCreateInfo.pushConstantRangeCount = 0;
		pipelineLayoutCreateInfo.pPushConstantRanges = nullptr;

		if (vkCreatePipelineLayout(m_logicalDevice.get_logical_device(), &pipelineLayoutCreateInfo, nullptr, &m_pipelineLayout) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create Vulkan pipeline layout!");
		}

		PSAI_LOG_DEBUG("Vulkan pipline layout successfuly created");

		PSAI_LOG_DEBUG("Creating Vulkan graphics pipeline");

		// Graphics pipeline create info
		VkGraphicsPipelineCreateInfo pipelineCreateInfo = graphics_pipeline_create_info();
		pipelineCreateInfo.stageCount = 2;
		pipelineCreateInfo.pStages = shaderStages;
		pipelineCreateInfo.pVertexInputState = &vertexInputCreateInfo;
		pipelineCreateInfo.pInputAssemblyState = &inputAssemblyCreateInfo;
		pipelineCreateInfo.pViewportState = &viewportStateCreateInfo;
		pipelineCreateInfo.pRasterizationState = &rasterizer;
		pipelineCreateInfo.pMultisampleState = &multisampling;
		pipelineCreateInfo.pDepthStencilState = nullptr;
		pipelineCreateInfo.pColorBlendState = &colorBlending;
		pipelineCreateInfo.pDynamicState = nullptr;
		pipelineCreateInfo.layout = m_pipelineLayout;
		pipelineCreateInfo.renderPass = m_renderPass.get_render_pass();

		if (vkCreateGraphicsPipelines(m_logicalDevice.get_logical_device(), VK_NULL_HANDLE, 1, &pipelineCreateInfo, nullptr, &m_graphicsPipeline) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create Vulkan graphics pipeline");
		}

		PSAI_LOG_DEBUG("Vulkan graphics pipeline successfuly created");
	}

	Pipeline::~Pipeline()
	{
		vkDestroyPipeline(m_logicalDevice.get_logical_device(), m_graphicsPipeline, nullptr);
		vkDestroyPipelineLayout(m_logicalDevice.get_logical_device(), m_pipelineLayout, nullptr);
	}

} // PsAi::Renderer namespace
