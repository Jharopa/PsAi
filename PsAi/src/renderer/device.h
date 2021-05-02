#pragma once

// PsAi imports
#include "../window.h"

// STD library imports
#include <vector>
#include <optional>
#include <iostream>
#include <cstring>
#include <set>

// Vulkan imports
#include "vulkan/vulkan.h"

namespace PsAi
{
	
	namespace Renderer
	{
		struct QueueFamilyIndices;

		class Device
		{
		public:
			// Public member variables
			#ifdef NDEBUG
				const bool m_enableValidationLayers = false;
			#else
				const bool m_enableValidationLayers = true;
			#endif
			
			// Public member functions
			// Constructors
			Device(Window& window, VkInstance& instance);
			~Device();

			// Non-copyable and non-movable
			Device(const Device &) = delete;
			Device(Device&&) = delete;
			Device& operator=(const Device&) = delete;
			Device& operator=(Device &&) = delete;
			

		private:
			// Private member variables
			VkInstance m_instance = VK_NULL_HANDLE;
			VkDebugUtilsMessengerEXT m_debugMessenger;
			VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
			VkDevice m_logicalDevice;
			VkQueue m_graphicsQueue;
			VkQueue m_presentQueue;
			Window& m_window;
			VkSurfaceKHR m_surface;

			const std::vector<const char*> m_validationLayers = { "VK_LAYER_KHRONOS_validation" };
			const std::vector<const char*> m_deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

			// Private member functions
			void create_instance();
			void setup_debug_messenger();
			void create_surface();
			void pick_physical_device();
			void create_logical_device();

			// Helper functions
			std::vector<const char *> get_required_extensions();
			void check_available_extentions();
			bool check_validation_layer_support();
			void populate_debug_messenger_create_info(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
			bool is_physical_device_suitable(VkPhysicalDevice device);
			QueueFamilyIndices find_queue_families(VkPhysicalDevice device);
			bool check_device_extension_support(VkPhysicalDevice device);
		};

		struct QueueFamilyIndices
		{
			std::optional<uint32_t> graphicsFamily;
			std::optional<uint32_t> presentFamily;
		};

	} // Renderer namespace
	
} // PsAi namespace
