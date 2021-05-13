#pragma once

// PsAi includes
#include "physical_device.h"
#include "surface.h"
#include "logical_device.h"
#include "helper_functions.h"

// Vulkan includes
#include <vulkan/vulkan.h>

namespace PsAi::Renderer
{

	class CommandPool
	{
		public:
			CommandPool(const LogicalDevice& logicalDevice, const PhysicalDevice& physicalDevice, const Surface& surface);
			~CommandPool();

			// Non-copyable and non-movable
			CommandPool(const CommandPool&) = delete;
			CommandPool(CommandPool&&) = delete;
			CommandPool& operator=(const CommandPool&) = delete;
			CommandPool& operator=(CommandPool&&) = delete;

			const VkCommandPool& get_command_pool() const { return m_commandPool; }

		private:
			VkCommandPool m_commandPool = VK_NULL_HANDLE;

			const LogicalDevice& m_logicalDevice;
	};

} // PsAi::Renderer namespace