#pragma once

// PsAi includes
#include "../util/non_copy_non_move.h"
#include "surface.h"
#include "helper_functions.h"
#include "vulkan_structures.h"

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

	class Swapchain : public Util::NonCopyableNonMoveable
	{
		public:
			Swapchain(VkSwapchainKHR oldSwapchain, VkPhysicalDevice physicalDevice, VkDevice logicalDevice, VkSurfaceKHR surface, GLFWwindow* window);
			~Swapchain();

			const VkSwapchainKHR& get_swapchain() const { return m_swapchain; }
			std::vector<VkImageView> get_swapchain_image_views() const { return m_swapchainImageViews; }
			VkFormat get_image_format() const { return m_swapchainSurfaceFormat.format; }
			VkExtent2D get_image_extent() const { return m_swapchainImageExtent; }
			uint32_t get_swapchain_image_count() const { return m_swapchainImageCount; }

		private:
			VkSwapchainKHR m_swapchain = VK_NULL_HANDLE;

			std::vector<VkImage> m_swapchainImages;
			std::vector<VkImageView> m_swapchainImageViews;
			uint32_t m_swapchainImageCount = 0;

			VkSurfaceFormatKHR m_swapchainSurfaceFormat;
			VkPresentModeKHR m_presentMode;
			VkExtent2D m_swapchainImageExtent;

			VkPhysicalDevice m_physicalDevice;
			VkDevice m_logicalDevice;
			VkSurfaceKHR m_surface;
			GLFWwindow* m_window;

			SwapchainSupportDetails query_swapchain_support();
			VkSurfaceFormatKHR choose_swapchain_surface_format(const std::vector<VkSurfaceFormatKHR>& availableFormats);
			VkPresentModeKHR choose_swapchain_present_mode(const std::vector<VkPresentModeKHR>& availablePresentModes);
			VkExtent2D choose_swapchain_image_extent(const VkSurfaceCapabilitiesKHR& capabilities);
	};

	struct SwapchainSupportDetails
	{
		VkSurfaceCapabilitiesKHR capabilites;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

} // PsAi::Renderer namespace
