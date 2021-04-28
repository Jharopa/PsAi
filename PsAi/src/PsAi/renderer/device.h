#pragma once

// PsAi imports
#include "../window.h"

// STD library imports
#include <vector>

// Vulkan imports
#include "vulkan/vulkan.h"

namespace PsAi
{
	
	namespace Renderer
	{
		
		class Device
		{
		public:
			// Constructors
			Device(Window & window);
			~Device();

			// Singleton
			void operator=(Device &) = delete;
			Device(Device &) = delete;
			void operator=(Device &&) = delete;
			Device(Device &&) = delete;

		private:
			// Private member variables
			VkInstance m_instance = VK_NULL_HANDLE;

			// Private member functions
			void create_instance();

			// Helper functions
			std::vector<const char *> get_required_extensions();
			void check_available_extentions();
		};

	} // Renderer namespace
	
	
} // PsAi namespace
