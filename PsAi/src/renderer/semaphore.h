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

	class Semaphore : public Util::NonCopyableNonMoveable
	{
		public:
			// Public member functions
			Semaphore(VkDevice logicalDevice, int numSemaphores);
			~Semaphore();

			std::vector<VkSemaphore> get_semaphores() const { return m_semaphores; }

		private:
			std::vector<VkSemaphore> m_semaphores = {};
			VkDevice m_logicalDevice = VK_NULL_HANDLE;
	};

} // PsAi::Renderer namespace
