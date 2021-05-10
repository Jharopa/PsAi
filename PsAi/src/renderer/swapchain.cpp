#include "swapchain.h"

namespace PsAi::Renderer
{
	
	Swapchain::Swapchain(PhysicalDevice& physicalDevice, LogicalDevice& logicalDevice, Surface& surface, GLFWwindow* window)
		: m_physicalDevice(physicalDevice), m_logicalDevice(logicalDevice), m_surface(surface), m_window(window)
	{
		SwapchainSupportDetails swapchainSupport = query_swapchain_support();
		VkSurfaceFormatKHR surfaceFormat = choose_swap_surface_format(swapchainSupport.formats);
		VkPresentModeKHR presentMode = choose_swap_present_mode(swapchainSupport.presentModes);
		VkExtent2D extent = choose_swap_extent(swapchainSupport.capabilites);

		uint32_t imageCount = swapchainSupport.capabilites.minImageCount + 1;
		
		if (swapchainSupport.capabilites.maxImageCount > 0 && imageCount > swapchainSupport.capabilites.maxImageCount)
		{
			imageCount = swapchainSupport.capabilites.maxImageCount;
		}

		VkSwapchainCreateInfoKHR createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface = m_surface.get_surface();

		createInfo.minImageCount = imageCount;
		createInfo.imageFormat = surfaceFormat.format;
		createInfo.imageColorSpace = surfaceFormat.colorSpace;
		createInfo.imageExtent = extent;
		createInfo.imageArrayLayers = 1;
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		QueueFamilyIndices indices = HelperFunctions::find_queue_families(m_physicalDevice.get_physical_device(), m_surface.get_surface());
		uint32_t queueFamiliesIndices[] = { indices.graphicsFamily.value(), indices.presentFamily.value() };

		if (indices.graphicsFamily != indices.presentFamily)
		{
			createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = 2;
			createInfo.pQueueFamilyIndices = queueFamiliesIndices;
		}
		else
		{
			createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
			createInfo.queueFamilyIndexCount = 0;
			createInfo.pQueueFamilyIndices = nullptr;
		}

		createInfo.preTransform = swapchainSupport.capabilites.currentTransform;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		createInfo.presentMode = presentMode;
		createInfo.clipped = VK_TRUE;

		createInfo.oldSwapchain = VK_NULL_HANDLE;

		if (vkCreateSwapchainKHR(m_logicalDevice.get_logical_device(), &createInfo, nullptr, &m_swapchain) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create swap chain!");
		}
	}

	Swapchain::~Swapchain()
	{
		vkDestroySwapchainKHR(m_logicalDevice.get_logical_device(), m_swapchain, nullptr);
	}

	SwapchainSupportDetails Swapchain::query_swapchain_support()
	{
		SwapchainSupportDetails details;

		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_physicalDevice.get_physical_device(), m_surface.get_surface(), &details.capabilites);

		uint32_t formatCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(m_physicalDevice.get_physical_device(), m_surface.get_surface(), &formatCount, nullptr);

		if (formatCount != 0)
		{
			details.formats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(m_physicalDevice.get_physical_device(), m_surface.get_surface(), &formatCount, details.formats.data());
		}

		uint32_t presentModeCount;
		vkGetPhysicalDeviceSurfacePresentModesKHR(m_physicalDevice.get_physical_device(), m_surface.get_surface(), &presentModeCount, nullptr);

		if (presentModeCount != 0)
		{
			details.presentModes.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(m_physicalDevice.get_physical_device(), m_surface.get_surface(), &presentModeCount, details.presentModes.data());
		}

		return details;
	}

	VkSurfaceFormatKHR Swapchain::choose_swap_surface_format(const std::vector<VkSurfaceFormatKHR>& availableFormats)
	{
		for (const auto& availableFormat : availableFormats)
		{
			if (availableFormat.format == VK_FORMAT_B8G8R8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
			{
				return availableFormat;
			}
		}

		return availableFormats[0];
	}

	VkPresentModeKHR Swapchain::choose_swap_present_mode(const std::vector<VkPresentModeKHR>& availablePresentModes)
	{
		for (const auto& availablePresentMode : availablePresentModes)
		{
			if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
			{
				return availablePresentMode;
			}
		}

		return VK_PRESENT_MODE_FIFO_KHR;
	}

	VkExtent2D Swapchain::choose_swap_extent(const VkSurfaceCapabilitiesKHR& capabilities)
	{
		if (capabilities.currentExtent.width != UINT32_MAX)
		{
			return capabilities.currentExtent;
		}
		else
		{
			int width, height;
			glfwGetFramebufferSize(m_window, &width, &height);

			VkExtent2D actualExtent = {
				static_cast<uint32_t>(width),
				static_cast<uint32_t>(height)
			};

			actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
			actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));

			return actualExtent;
		}
	}

} // PsAi::Renderer namespace
