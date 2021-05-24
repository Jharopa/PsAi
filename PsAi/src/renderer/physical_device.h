#pragma once

// PsAi includes
#include "../util/non_copy_non_move.h"
#include "../log.h"
#include "instance.h"

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

	class PhysicalDevice : public Util::NonCopyableNonMoveable
	{
		public:
			PhysicalDevice(const Instance& instance);
			~PhysicalDevice();

			const VkPhysicalDevice& get_physical_device() const { return m_physicalDevice; }

			const std::vector<const char*> get_device_extensions() const { return m_deviceExtensions; }

			const VkPhysicalDeviceProperties& get_physical_device_properties() const { return m_physicalDeviceProperties; }
			const VkPhysicalDeviceFeatures& get_physical_device_features() const { return m_physicalDeviceFeatures; }
			const std::vector<VkQueueFamilyProperties>& get_queue_family_properties() const { return m_queueFamilyProperties; }

		private:
			VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
			const Instance& m_instance;

			const std::vector<const char*> m_deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
			
			VkPhysicalDeviceProperties m_physicalDeviceProperties;
			VkPhysicalDeviceFeatures m_physicalDeviceFeatures;

			std::vector<VkQueueFamilyProperties> m_queueFamilyProperties;

			bool is_physical_device_suitable(VkPhysicalDevice physicalDevice);
			bool has_requested_extension_support(VkPhysicalDevice physicalDevice);

			void set_physical_device_attributes();
			void set_queue_family_properties();
	};

} // PsAi::Renderer namespace