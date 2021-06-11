#pragma once

// PsAi includes
#include "../util/non_copy_non_move.h"
#include "../log.h"
#include "vulkan_structures.h"
#include "device.h"
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
			Pipeline(VkDevice logicalDevice, VkRenderPass renderPass, VkShaderModule vertShader, VkShaderModule fragShader, int width, int height);
			~Pipeline();
			
			VkPipeline get_graphics_pipeline() const { return m_graphicsPipeline; }

		private:
			// Private member variables
			VkPipeline m_graphicsPipeline;
			VkPipelineLayout m_pipelineLayout;

			VkDevice m_logicalDevice;
			VkRenderPass m_renderPass;
			VkShaderModule m_vertShader;
			VkShaderModule m_fragShader;
	};

} // PsAi::Renderer namespace
