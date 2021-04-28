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

			const std::vector<const char*> m_validationLayers = { "VK_LAYER_KHRONOS_validation" };

			// Private member functions
			void create_instance();

			// Helper functions
			std::vector<const char *> get_required_extensions();
			void check_available_extentions();
			bool check_validation_layer_support();
		};

	} // Renderer namespace
	
	
} // PsAi namespace
