#pragma once

// PsAi includes
#include "../util/non_copy_non_move.h"
#include "../log.h"
#include "helper_functions.h"
#include "instance.h"

// Vulkan includes
#include <vulkan/vulkan.h>

// STD library includes
#include <vector>
#include <set>
#include <string>

namespace PsAi::Renderer
{
	
	class Device : public Util::NonCopyableNonMoveable
	{
		public:
			Device(const Instance& instance, VkSurfaceKHR surface);
			~Device();

			VkPhysicalDevice get_physical_device() const { return m_physicalDevice; }
			VkDevice get_logical_device() const { return m_logicalDevice; }

			VkQueue get_graphics_queue() const { return m_graphicsQueue; }
			VkQueue get_present_queue() const { return m_presentQueue; }

		private:
			VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
			VkDevice m_logicalDevice = VK_NULL_HANDLE;

			const Instance& m_instance;
			const VkSurfaceKHR m_surface;

			VkPhysicalDeviceProperties m_physicalDeviceProperties;
			VkPhysicalDeviceFeatures m_physicalDeviceFeatures;

			std::vector<const char*> m_enabledDeviceExtensions = {};

			std::vector<VkQueueFamilyProperties> m_queueFamilyProperties = {};
			VkQueue m_graphicsQueue = VK_NULL_HANDLE;
			VkQueue m_presentQueue = VK_NULL_HANDLE;

			void select_physical_device();

			bool is_physical_device_suitable(VkPhysicalDevice physicalDevice);

			bool is_extensions_supported(VkPhysicalDevice physicalDevice, std::string extensionName);
			bool is_swapchain_supported(VkPhysicalDevice physicalDevice);
			bool is_present_supported(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);

			void set_physical_device_attributes();
			void set_queue_family_properties();

			void create_logical_device();
	};

} // PsAi::Renderer namespace
