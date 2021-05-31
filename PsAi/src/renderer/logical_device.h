#pragma once

// PsAi includes
#include "../util/non_copy_non_move.h"
#include "instance.h"
#include "physical_device.h"
#include "surface.h"
#include "helper_functions.h"

// Vulkan includes
#include <vulkan/vulkan.h>

// STD library includes
#include <optional>

namespace PsAi::Renderer
{

	class LogicalDevice : public Util::NonCopyableNonMoveable
	{
		public:
			LogicalDevice(const Instance& instance, VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
			~LogicalDevice();

			VkDevice get_logical_device() const { return m_logicalDevice; }
			VkQueue get_graphics_queue() const { return m_graphicsQueue; }
			VkQueue get_present_queue() const { return m_presentationQueue; }

		private:
			VkDevice m_logicalDevice = VK_NULL_HANDLE;

			VkQueue m_graphicsQueue = VK_NULL_HANDLE;
			VkQueue m_presentationQueue = VK_NULL_HANDLE;
	};

} // PsAi::Renderer namespace