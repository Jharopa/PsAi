#pragma once

// PsAi includes
#include "physical_device.h"
#include "logical_device.h"
#include "surface.h"
#include "helper_functions.h"

// Vulkan includes
#include <vulkan/vulkan.h>

// STD library includes
#include <vector>
#include <stdexcept>
#include <cstdint>
#include <algorithm>

namespace PsAi::Renderer
{
	struct SwapchainSupportDetails;

	class Swapchain
	{
		public:
			Swapchain(PhysicalDevice& physicalDevice, LogicalDevice& logicalDevice, Surface& surface, GLFWwindow* window);
			~Swapchain();

			// Non-copyable and non-movable
			Swapchain(const Swapchain&) = delete;
			Swapchain(Swapchain&&) = delete;
			Swapchain& operator=(const Swapchain&) = delete;
			Swapchain& operator=(Swapchain&&) = delete;

		private:
			VkSwapchainKHR m_swapchain;

			PhysicalDevice& m_physicalDevice;
			LogicalDevice& m_logicalDevice;
			Surface& m_surface;
			GLFWwindow* m_window;

			SwapchainSupportDetails query_swapchain_support();
			VkSurfaceFormatKHR choose_swap_surface_format(const std::vector<VkSurfaceFormatKHR>& availableFormats);
			VkPresentModeKHR choose_swap_present_mode(const std::vector<VkPresentModeKHR>& availablePresentModes);
			VkExtent2D choose_swap_extent(const VkSurfaceCapabilitiesKHR& capabilities);
	};

	struct SwapchainSupportDetails
	{
		VkSurfaceCapabilitiesKHR capabilites;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

} // PsAi::Renderer namespace
