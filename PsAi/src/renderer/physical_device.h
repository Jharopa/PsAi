#pragma once

// Vulkan includes
#include <vulkan/vulkan.h>

// STD library includes
#include <vector>
#include <iostream>
#include <string>
#include <set>

namespace PsAi::Renderer
{
	
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

		private:
			VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
			const std::vector<const char*> m_deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

			bool is_physical_device_suitable(VkPhysicalDevice physicalDevice);
			bool has_requested_extension_support(VkPhysicalDevice physicalDevice);
	};

} // PsAi::Renderer namespace