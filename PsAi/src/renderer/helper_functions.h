#pragma once

// Vulkan includes
#include <vulkan/vulkan.h>

// STD library includes
#include <optional>
#include <vector>

namespace PsAi::Renderer
{
	
	struct QueueFamilyIndices;

	struct HelperFunctions
	{
		static QueueFamilyIndices find_queue_families(VkPhysicalDevice physical_device, VkSurfaceKHR surface);
	};

	struct QueueFamilyIndices
	{
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;
	};

} // PsAi::Renderer namespace
