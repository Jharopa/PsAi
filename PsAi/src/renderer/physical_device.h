#pragma once

// Vulkan includes
#include <vulkan/vulkan.h>

// STD library includes
#include <vector>
#include <iostream>
#include <string>
#include <set>
#include <optional>

namespace PsAi::Renderer
{
	
	struct QueueFamilyIndices;

	class PhysicalDevice
	{
		public:
			PhysicalDevice(const VkInstance& instance);
			~PhysicalDevice();

			// Non-copyable and Non-movable
			PhysicalDevice(const PhysicalDevice&) = delete;
			PhysicalDevice(PhysicalDevice&&) = delete;
			PhysicalDevice& operator=(const PhysicalDevice&) = delete;
			PhysicalDevice& operator=(PhysicalDevice&&) = delete;

			VkPhysicalDevice get_physical_device() { return m_physicalDevice; }

			VkPhysicalDeviceProperties get_physical_device_properties() { return m_physicalDeviceProperties; }
			VkPhysicalDeviceFeatures get_physical_device_features() { return m_physicalDeviceFeatures; }

		private:
			VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
			const std::vector<const char*> m_deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

			VkPhysicalDeviceProperties m_physicalDeviceProperties;
			VkPhysicalDeviceFeatures m_physicalDeviceFeatures;

			bool is_physical_device_suitable(VkPhysicalDevice physicalDevice);
			bool has_requested_extension_support(VkPhysicalDevice physicalDevice);

			void populate_attributes();
	};

} // PsAi::Renderer namespace