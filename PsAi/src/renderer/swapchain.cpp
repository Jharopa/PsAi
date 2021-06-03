#include "swapchain.h"

namespace PsAi::Renderer
{
	
	Swapchain::Swapchain(VkSwapchainKHR oldSwapchain, VkPhysicalDevice physicalDevice, VkDevice logicalDevice, VkSurfaceKHR surface, GLFWwindow* window)
		: m_physicalDevice(physicalDevice), m_logicalDevice(logicalDevice), m_surface(surface), m_window(window)
	{
		SwapchainSupportDetails swapchainSupport = query_swapchain_support();
		m_swapchainSurfaceFormat = choose_swapchain_surface_format(swapchainSupport.formats);
		m_presentMode = choose_swapchain_present_mode(swapchainSupport.presentModes);
		m_swapchainImageExtent = choose_swapchain_image_extent(swapchainSupport.capabilites);

		m_swapchainImageCount = swapchainSupport.capabilites.minImageCount + 1;
		
		if (swapchainSupport.capabilites.maxImageCount > 0 && m_swapchainImageCount > swapchainSupport.capabilites.maxImageCount)
		{
			m_swapchainImageCount = swapchainSupport.capabilites.maxImageCount;
		}

		VkSwapchainCreateInfoKHR swapchainCreateInfo = swapchain_create_info_ext();
		swapchainCreateInfo.surface = m_surface;

		swapchainCreateInfo.minImageCount = m_swapchainImageCount;
		swapchainCreateInfo.imageFormat = m_swapchainSurfaceFormat.format;
		swapchainCreateInfo.imageColorSpace = m_swapchainSurfaceFormat.colorSpace;
		swapchainCreateInfo.imageExtent = m_swapchainImageExtent;
		swapchainCreateInfo.imageArrayLayers = 1;
		swapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		QueueFamilyIndices indices = HelperFunctions::find_queue_families(m_physicalDevice, m_surface);
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
		swapchainCreateInfo.presentMode = m_presentMode;
		swapchainCreateInfo.clipped = VK_TRUE;

		if (oldSwapchain != VK_NULL_HANDLE)
		{
			swapchainCreateInfo.oldSwapchain = oldSwapchain;
		}

		if (vkCreateSwapchainKHR(m_logicalDevice, &swapchainCreateInfo, nullptr, &m_swapchain) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create swap chain!");
		}

		vkGetSwapchainImagesKHR(m_logicalDevice, m_swapchain, &m_swapchainImageCount, nullptr);
		m_swapchainImages.resize(m_swapchainImageCount);
		vkGetSwapchainImagesKHR(m_logicalDevice, m_swapchain, &m_swapchainImageCount, m_swapchainImages.data());

		m_swapchainImageViews.resize(m_swapchainImages.size());

		for (size_t i = 0; i < m_swapchainImages.size(); i++)
		{
			VkImageViewCreateInfo imageViewCreateInfo = image_view_create_info();
			imageViewCreateInfo.image = m_swapchainImages[i];
			imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
			imageViewCreateInfo.format = m_swapchainSurfaceFormat.format;
			imageViewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
			imageViewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
			imageViewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
			imageViewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
			imageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			imageViewCreateInfo.subresourceRange.baseMipLevel = 0;
			imageViewCreateInfo.subresourceRange.levelCount = 1;
			imageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
			imageViewCreateInfo.subresourceRange.layerCount = 1;

			if (vkCreateImageView(m_logicalDevice, &imageViewCreateInfo, nullptr, &m_swapchainImageViews[i]) != VK_SUCCESS)
			{
				throw std::runtime_error("Failed to create Vulkan image views!");
			}
		}
	}

	Swapchain::~Swapchain()
	{
		for (auto imageView : m_swapchainImageViews)
		{
			vkDestroyImageView(m_logicalDevice, imageView, nullptr);
		}

		vkDestroySwapchainKHR(m_logicalDevice, m_swapchain, nullptr);
	}

	SwapchainSupportDetails Swapchain::query_swapchain_support()
	{
		SwapchainSupportDetails details;

		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_physicalDevice, m_surface, &details.capabilites);

		uint32_t formatCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(m_physicalDevice, m_surface, &formatCount, nullptr);

		if (formatCount != 0)
		{
			details.formats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(m_physicalDevice, m_surface, &formatCount, details.formats.data());
		}

		uint32_t presentModeCount;
		vkGetPhysicalDeviceSurfacePresentModesKHR(m_physicalDevice, m_surface, &presentModeCount, nullptr);

		if (presentModeCount != 0)
		{
			details.presentModes.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(m_physicalDevice, m_surface, &presentModeCount, details.presentModes.data());
		}

		return details;
	}

	VkSurfaceFormatKHR Swapchain::choose_swapchain_surface_format(const std::vector<VkSurfaceFormatKHR>& availableFormats)
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

	VkPresentModeKHR Swapchain::choose_swapchain_present_mode(const std::vector<VkPresentModeKHR>& availablePresentModes)
	{
		
		if (std::find(availablePresentModes.begin(), availablePresentModes.end(), VK_PRESENT_MODE_MAILBOX_KHR) != availablePresentModes.end())
		{
			return VK_PRESENT_MODE_MAILBOX_KHR;
		}
		else if (std::find(availablePresentModes.begin(), availablePresentModes.end(), VK_PRESENT_MODE_FIFO_KHR) != availablePresentModes.end())
		{
			return VK_PRESENT_MODE_FIFO_KHR;
		}
		else if (std::find(availablePresentModes.begin(), availablePresentModes.end(), VK_PRESENT_MODE_FIFO_RELAXED_KHR) != availablePresentModes.end())
		{
			return VK_PRESENT_MODE_FIFO_RELAXED_KHR;
		}
		else if (std::find(availablePresentModes.begin(), availablePresentModes.end(), VK_PRESENT_MODE_IMMEDIATE_KHR) != availablePresentModes.end())
		{
			return VK_PRESENT_MODE_IMMEDIATE_KHR;
		}

		throw std::runtime_error("There are no appropriate present modes available");
	}

	VkExtent2D Swapchain::choose_swapchain_image_extent(const VkSurfaceCapabilitiesKHR& capabilities)
	{
		if (capabilities.currentExtent.width != UINT32_MAX)
		{
			return capabilities.currentExtent;
		}
		else
		{
			int width, height;
			glfwGetFramebufferSize(m_window, &width, &height);

			VkExtent2D actualImageExtent = {
				static_cast<uint32_t>(width),
				static_cast<uint32_t>(height)
			};

			actualImageExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualImageExtent.width));
			actualImageExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualImageExtent.height));

			return actualImageExtent;
		}
	}

} // PsAi::Renderer namespace
