#pragma once

#include "vulkan/vulkan.h"

namespace PsAi
{

	namespace Renderer
	{
		
		class Instance
		{
			public:
				Instance(const char* applicationName, const uint32_t applicationVersion, const char* engineName, uint32_t engineVersion, uint32_t apiVersion);

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