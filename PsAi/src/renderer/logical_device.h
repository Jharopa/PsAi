#pragma once

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

	class LogicalDevice
	{
		public:
			LogicalDevice(const Instance& instance, const PhysicalDevice& physicalDevice, const Surface& surface);
			~LogicalDevice();

			// Non-copyable and non-movable
			LogicalDevice(const LogicalDevice&) = delete;
			LogicalDevice(LogicalDevice&&) = delete;
			LogicalDevice& operator=(const LogicalDevice&) = delete;
			LogicalDevice& operator=(LogicalDevice&&) = delete;

			const VkDevice& get_logical_device() const { return m_logicalDevice; }

		private:
			VkDevice m_logicalDevice = VK_NULL_HANDLE;

			VkQueue m_graphicsQueue;
			VkQueue m_presentationQueue;

			const Instance& m_instance;
			const PhysicalDevice& m_physicalDevice;
			const Surface& m_surface;
	};

} // PsAi::Renderer namespace