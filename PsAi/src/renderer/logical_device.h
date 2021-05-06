#pragma once

#include "instance.h"
#include "physical_device.h"
#include "surface.h"

// Vulkan includes
#include <vulkan/vulkan.h>

// STD library includes
#include <optional>

namespace PsAi::Renderer
{
	struct QueueFamilyIndices;

	class LogicalDevice
	{
		public:
			LogicalDevice(const Instance* instance, const PhysicalDevice* physicalDevice, const Surface* surface);
			~LogicalDevice();

			// Non-copyable and non-movable
			LogicalDevice(const LogicalDevice&) = delete;
			LogicalDevice(LogicalDevice&&) = delete;
			LogicalDevice& operator=(const LogicalDevice&) = delete;
			LogicalDevice& operator=(LogicalDevice&&) = delete;

		private:
			VkDevice m_logicalDevice = VK_NULL_HANDLE;

			VkQueue m_graphicsQueue;
			VkQueue m_presentationQueue;

			QueueFamilyIndices find_queue_families(const PhysicalDevice* physicalDevice, const Surface* surface);
	};

	struct QueueFamilyIndices
	{
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;
	};

} // PsAi::Renderer namespace