#pragma once

// PsAi imports
#include "../window.h"

// STD library imports
#include <vector>
#include <optional>

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
			Device(Window& window);
			~Device();

			// Singleton
			void operator=(Device &) = delete;
			Device(Device &) = delete;
			void operator=(Device &&) = delete;
			Device(Device &&) = delete;

		private:
			// Private member variables
			VkInstance m_instance = VK_NULL_HANDLE;
			VkDebugUtilsMessengerEXT m_debugMessenger;
			VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
			VkDevice m_logicalDevice;

			const std::vector<const char*> m_validationLayers = { "VK_LAYER_KHRONOS_validation" };

			// Private member functions
			void create_instance();
			void setup_debug_messenger();
			void pick_physical_device();
			void create_logical_device();

			// Helper functions
			std::vector<const char *> has_required_extensions();
			void check_available_extentions();
			bool check_validation_layer_support();
			void populate_debug_messenger_create_info(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
			bool is_physical_device_suitable(VkPhysicalDevice device);
			QueueFamilyIndices find_queue_families(VkPhysicalDevice device);
		};

		struct QueueFamilyIndices
		{
			std::optional<uint32_t> graphicsFamily;
		};

	} // Renderer namespace
	
	
} // PsAi namespace
