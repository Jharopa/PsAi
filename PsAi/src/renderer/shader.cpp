#include "shader.h"

namespace PsAi::Renderer
{
	Shader::Shader(const LogicalDevice& logicalDevice, const std::string& filePath)
		: m_logicalDevice(logicalDevice)
	{
		std::vector<char> code = read_binary(filePath);

		VkShaderModuleCreateInfo shaderModuleCreateInfo = shader_module_create_info();
		shaderModuleCreateInfo.codeSize = code.size();
		shaderModuleCreateInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

		if (vkCreateShaderModule(m_logicalDevice.get_logical_device(), &shaderModuleCreateInfo, nullptr, &m_shaderModule) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create Vulkan shader module!");
		}
	}

	Shader::~Shader()
	{
		vkDestroyShaderModule(m_logicalDevice.get_logical_device(), m_shaderModule, nullptr);
	}

	std::vector<char> Shader::read_binary(const std::string& filePath)
	{
		std::ifstream file(filePath, std::ios::ate | std::ios::binary);

		if (!file.is_open())
		{
			throw std::runtime_error("Failed to open shader file!");
		}

		size_t fileSize = (size_t)file.tellg();
		std::vector<char> buffer(fileSize);

		file.seekg(0);
		file.read(buffer.data(), fileSize);

		file.close();

		return buffer;
	}
}
