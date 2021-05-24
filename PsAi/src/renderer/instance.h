#pragma once

// PsAi includes
#include "../util/non_copy_non_move.h"
#include "../log.h"
#include "window.h"
#include "vulkan_structures.h"

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

	class Instance : public Util::NonCopyableNonMoveable
	{
		public:
			// Ctor + dtor
			Instance(VkApplicationInfo applicationInfo, std::vector<std::string> requestedExtensions, bool validationEnabled);
			~Instance();

			const VkInstance& get_instance() const { return m_instance; }
			bool is_validation_enabled() const { return m_validationEnabled; }
			const std::vector<const char*> get_enabled_extensions() const { return m_enabledExtensions; }
			const std::vector<const char*> get_enabled_layers() const { return m_enabledLayers; }

		private:
			VkInstance m_instance = VK_NULL_HANDLE;
			VkDebugUtilsMessengerEXT m_debugMessenger = VK_NULL_HANDLE;
			bool m_validationEnabled;
			std::vector<const char*> m_enabledExtensions = {};
			std::vector<const char*> m_enabledLayers = {};

			bool is_extension_supported(std::string extensionName);
			bool is_layer_supported(std::string layerName);
				
			void setup_debug_messenger();
			void populate_debug_messenger_create_info(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
	};

} // PsAi::Renderer namespace