#pragma once

// PsAi includes
#include "../util/non_copy_non_move.h"
#include "vulkan_structures.h"

// Vulkan includes
#include <vulkan/vulkan.h>

// STD library includes
#include <stdexcept>
#include <vector>

namespace PsAi::Renderer
{
	
	class Fence : public Util::NonCopyableNonMoveable
	{
		public:
			Fence(VkDevice logicalDevice, int numFences);
			~Fence();

			std::vector<VkFence> get_fences() const { return m_fences; }

		private:
			std::vector<VkFence> m_fences = {};

			VkDevice m_logicalDevice;
	};

} // PsAi::Renderer namespace
