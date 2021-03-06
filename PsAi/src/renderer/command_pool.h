#pragma once

// PsAi includes
#include "../util/non_copy_non_move.h"
#include "device.h"
#include "surface.h"
#include "device.h"
#include "helper_functions.h"

// Vulkan includes
#include <vulkan/vulkan.h>

namespace PsAi::Renderer
{

	class CommandPool : public Util::NonCopyableNonMoveable
	{
		public:
			CommandPool(VkDevice logicalDevice, VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
			~CommandPool();

			VkCommandPool get_command_pool() const { return m_commandPool; }

		private:
			VkCommandPool m_commandPool = VK_NULL_HANDLE;

			VkDevice m_logicalDevice;
	};

} // PsAi::Renderer namespace
