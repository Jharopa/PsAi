#pragma once

// PsAi includes
#include "logical_device.h"
#include "shader.h"
#include "../log.h"

// STD library includes
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

namespace PsAi::Renderer
{
	
	class Pipeline
	{
		public:
			// Public member functions
			Pipeline(const LogicalDevice& logicalDevice, const Shader& vertShader, const Shader& fragShader, int window_width, int window_height);
			~Pipeline();

		private:
			// Private member variables
			VkPipelineLayout m_pipelineLayout;

			const LogicalDevice& m_logicalDevice;
			const Shader& m_vertShader;
			const Shader& m_fragShader;
	};

} // PsAi::Renderer namespace
