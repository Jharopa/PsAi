#pragma once

// PsAi includes
#include "../util/non_copy_non_move.h"
#include "logical_device.h"

// Vulkan includes
#include <vulkan/vulkan.h>

namespace PsAi::Renderer
{

	class Semaphore : public Util::NonCopyableNonMoveable
	{
		public:
			// Public member functions
			Semaphore(const LogicalDevice& logicalDevice);
			~Semaphore();

			const VkSemaphore& get_semaphore() const { return m_semaphore; }

		private:
			VkSemaphore m_semaphore = VK_NULL_HANDLE;
			const LogicalDevice& m_logicalDevice;
	};

} // PsAi::Renderer namespace
