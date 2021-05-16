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

		VkSwapchainCreateInfoKHR swapchainCreateInfo = swapchain_create_info_ext();
		swapchainCreateInfo.surface = m_surface.get_surface();

		swapchainCreateInfo.minImageCount = imageCount;
		swapchainCreateInfo.imageFormat = surfaceFormat.format;
		swapchainCreateInfo.imageColorSpace = surfaceFormat.colorSpace;
		swapchainCreateInfo.imageExtent = extent;
		swapchainCreateInfo.imageArrayLayers = 1;
		swapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		QueueFamilyIndices indices = HelperFunctions::find_queue_families(m_physicalDevice.get_physical_device(), m_surface.get_surface());
		uint32_t queueFamiliesIndices[] = { indices.graphicsFamily.value(), indices.presentFamily.value() };

		if (indices.graphicsFamily != indices.presentFamily)
		{
			swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			swapchainCreateInfo.queueFamilyIndexCount = 2;
			swapchainCreateInfo.pQueueFamilyIndices = queueFamiliesIndices;
		}
		else
		{
			swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
			swapchainCreateInfo.queueFamilyIndexCount = 0;
			swapchainCreateInfo.pQueueFamilyIndices = nullptr;
		}

		swapchainCreateInfo.preTransform = swapchainSupport.capabilites.currentTransform;
		swapchainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		swapchainCreateInfo.presentMode = presentMode;
		swapchainCreateInfo.clipped = VK_TRUE;

		swapchainCreateInfo.oldSwapchain = VK_NULL_HANDLE;

		if (vkCreateSwapchainKHR(m_logicalDevice.get_logical_device(), &swapchainCreateInfo, nullptr, &m_swapchain) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create swap chain!");
		}

		vkGetSwapchainImagesKHR(m_logicalDevice.get_logical_device(), m_swapchain, &imageCount, nullptr);
		m_swapchainImages.resize(imageCount);
		vkGetSwapchainImagesKHR(m_logicalDevice.get_logical_device(), m_swapchain, &imageCount, m_swapchainImages.data());
		
		m_swapchainImageFormat = surfaceFormat.format;
		m_swapchainExtent = extent;

		m_swapchainImageViews.resize(m_swapchainImages.size());

		for (size_t i = 0; i < m_swapchainImages.size(); i++)
		{
			VkImageViewCreateInfo imageViewCreateInfo = image_view_create_info();
			imageViewCreateInfo.image = m_swapchainImages[i];
			imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
			imageViewCreateInfo.format = m_swapchainImageFormat;
			imageViewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
			imageViewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
			imageViewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
			imageViewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
			imageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			imageViewCreateInfo.subresourceRange.baseMipLevel = 0;
			imageViewCreateInfo.subresourceRange.levelCount = 1;
			imageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
			imageViewCreateInfo.subresourceRange.layerCount = 1;

			if (vkCreateImageView(m_logicalDevice.get_logical_device(), &imageViewCreateInfo, nullptr, &m_swapchainImageViews[i]) != VK_SUCCESS)
			{
				throw std::runtime_error("Failed to create Vulkan image views!");
			}
		}
	}

	Swapchain::~Swapchain()
	{
		for (auto imageView : m_swapchainImageViews)
		{
			vkDestroyImageView(m_logicalDevice.get_logical_device(), imageView, nullptr);
		}

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
