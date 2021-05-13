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

			const VkSwapchainKHR& get_swapchain() const { return m_swapchain; }
			const std::vector<VkImageView> get_swapchain_image_views() const { return m_swapchainImageViews; }
			const VkFormat& get_image_format() const { return m_swapchainImageFormat; }
			const VkExtent2D& get_extent() const { return m_swapchainExtent; }

		private:
			VkSwapchainKHR m_swapchain = VK_NULL_HANDLE;
			std::vector<VkImage> m_swapchainImages;
			std::vector<VkImageView> m_swapchainImageViews;
			VkFormat m_swapchainImageFormat;
			VkExtent2D m_swapchainExtent;

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
