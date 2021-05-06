#pragma once

// PsAi includes
#include "../log.h"
#include "window.h"

// Vulkan includes
#include <vulkan/vulkan.h>

// STD library includes
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <typeinfo>

namespace PsAi::Renderer
{
		
	class Instance
	{
		public:
			Instance(const char* applicationName, const uint32_t applicationVersion, const char* engineName, const uint32_t engineVersion, const uint32_t vkAPIVersion, std::vector<std::string> extensionsList, bool validationEnabled);
			~Instance();

			// Non-copyable and non-movable
			Instance(const Instance&) = delete;
			Instance(Instance&&) = delete;
			Instance& operator=(const Instance&) = delete;
			Instance& operator=(Instance&&) = delete;

			const VkInstance& get_instance() const { return m_instance; }
			bool is_validation_enabled() const { return m_validationEnabled == true; }

		private:
			VkInstance m_instance = VK_NULL_HANDLE;
			VkDebugUtilsMessengerEXT m_debugMessenger = VK_NULL_HANDLE;
			bool m_validationEnabled;

			bool is_extension_supported(std::string extensionName);
			bool is_layer_supported(std::string layerName);
				
			void setup_debug_messenger();
			void populate_debug_messenger_create_info(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
	};

} // PsAi::Renderer namespace