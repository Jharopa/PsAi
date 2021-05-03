#pragma once

// PsAi includes
#include "../log.h"
#include "window.h"

// Vulkan includes
#include <vulkan/vulkan.h>

// STD library includes
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

namespace PsAi
{

	namespace Renderer
	{
		
		class Instance
		{
			public:
				Instance(const char* applicationName, const uint32_t applicationVersion, const char* engineName, const uint32_t engineVersion, const uint32_t vkAPIVersion);
				~Instance();

				// Non-copyable and non-movable
				Instance(const Instance&) = delete;
				Instance(Instance&&) = delete;
				Instance& operator=(const Instance&) = delete;
				Instance& operator=(Instance&&) = delete;

			private:
				VkInstance m_instance = VK_NULL_HANDLE;
		};

	} // Renderer namespace

} // PsAi namespace