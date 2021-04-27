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
			VkInstance m_instance;

			// Private member functions
			void create_instance();

			// Helper functions
			std::vector<const char *> getRequiredExtensions();
		};

	} // Renderer namespace
	
	
} // PsAi namespace
