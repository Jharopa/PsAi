#include "pipeline.h"

namespace PsAi::Renderer
{
	
	Pipeline::Pipeline(const LogicalDevice& logicalDevice, const Shader& vertShader, const Shader& fragShader)
		: m_logicalDevice(logicalDevice), m_vertShader(vertShader), m_fragShader(fragShader)
	{
		VkPipelineShaderStageCreateInfo vertShaderStageCreateInfo{};
		vertShaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		vertShaderStageCreateInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
		vertShaderStageCreateInfo.module = m_vertShader.get_shader_module();
		vertShaderStageCreateInfo.pName = "main";

		VkPipelineShaderStageCreateInfo fragShaderStageCreateInfo{};
		vertShaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		vertShaderStageCreateInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		vertShaderStageCreateInfo.module = m_fragShader.get_shader_module();
		vertShaderStageCreateInfo.pName = "main";

		VkPipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageCreateInfo, fragShaderStageCreateInfo };
	}

} // PsAi::Renderer namespace
