#pragma once

#include "logical_device.h"

// Vulkan includes
#include <vulkan/vulkan.h>

// STD library includes
#include <vector>
#include <string>
#include <fstream>

namespace PsAi::Renderer
{
	
	class Shader
	{
		public:
			Shader(const LogicalDevice& logicalDevice, const std::string& filePath);
			~Shader();

			// Non-movable and non-copyable
			Shader(const Shader&) = delete;
			Shader(Shader&&) = delete;
			Shader& operator=(const Shader&) = delete;
			Shader& operator=(Shader&&) = delete;

			const VkShaderModule& get_shader_module() const { return m_shaderModule; }

		private:
			VkShaderModule m_shaderModule = VK_NULL_HANDLE;
			std::vector<char> read_binary(const std::string& filePath);

			const LogicalDevice& m_logicalDevice;
	};

}
