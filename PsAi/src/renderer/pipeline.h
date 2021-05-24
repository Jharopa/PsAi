#pragma once

// PsAi includes
#include "../util/non_copy_non_move.h"
#include "../log.h"
#include "vulkan_structures.h"
#include "logical_device.h"
#include "render_pass.h"
#include "shader.h"

// STD library includes
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

namespace PsAi::Renderer 
{
	
	class Pipeline : public Util::NonCopyableNonMoveable
	{
		public:
			// Public member functions
			Pipeline(const LogicalDevice& logicalDevice, const RenderPass& renderPass, const Shader& vertShader, const Shader& fragShader, int width, int height);
			~Pipeline();
			
			const VkPipeline& get_graphics_pipeline() const { return m_graphicsPipeline; }

		private:
			// Private member variables
			VkPipeline m_graphicsPipeline;
			VkPipelineLayout m_pipelineLayout;

			const LogicalDevice& m_logicalDevice;
			const RenderPass& m_renderPass;
			const Shader& m_vertShader;
			const Shader& m_fragShader;
	};

} // PsAi::Renderer namespace
