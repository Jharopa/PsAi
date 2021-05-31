#pragma once

// PsAi includes
#include "../util/non_copy_non_move.h"
#include "logical_device.h"

// Vulkan includes
#include <vulkan/vulkan.h>

// STD library includes
#include <vector>
#include <string>
#include <fstream>

namespace PsAi::Renderer
{

	class Shader : public Util::NonCopyableNonMoveable
	{
		public:
			Shader(VkDevice logicalDevice, const std::string& filePath);
			~Shader();

			const VkShaderModule& get_shader_module() const { return m_shaderModule; }

		private:
			VkShaderModule m_shaderModule = VK_NULL_HANDLE;
			VkDevice m_logicalDevice;

			std::vector<char> read_binary(const std::string& filePath);
	};

}
