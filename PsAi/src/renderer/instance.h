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

namespace PsAi
{

	namespace Renderer
	{
		
		class Instance
		{
			public:
				Instance(const char* applicationName, const uint32_t applicationVersion, const char* engineName, const uint32_t engineVersion, const uint32_t vkAPIVersion, std::vector<std::string> extensionsList, bool validationLayersEnabled);
				~Instance();

				// Non-copyable and non-movable
				Instance(const Instance&) = delete;
				Instance(Instance&&) = delete;
				Instance& operator=(const Instance&) = delete;
				Instance& operator=(Instance&&) = delete;

			private:
				VkInstance m_instance = VK_NULL_HANDLE;
				bool is_extension_supported(std::string extensionName);
				bool is_layer_supported(std::string layerName);
		};

	} // Renderer namespace

} // PsAi namespace