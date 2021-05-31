#include "logical_device.h"

namespace PsAi::Renderer
{
	LogicalDevice::LogicalDevice(const Instance& instance, VkPhysicalDevice physicalDevice, VkSurfaceKHR surface)
	{
		PSAI_LOG_DEBUG("Creating logical device");

		QueueFamilyIndices indices = HelperFunctions::find_queue_families(physicalDevice, surface);

		std::vector<VkDeviceQueueCreateInfo> deviceQueueCreateInfos;
		std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };
		float queuePriority = 1.0f;

		for (uint32_t queueFamily : uniqueQueueFamilies)
		{
			VkDeviceQueueCreateInfo deviceQueueCreateInfo{};
			deviceQueueCreateInfo.queueFamilyIndex = queueFamily;
			deviceQueueCreateInfo.queueCount = 1;
			deviceQueueCreateInfo.pQueuePriorities = &queuePriority;
			deviceQueueCreateInfos.push_back(deviceQueueCreateInfo);
		}

		VkPhysicalDeviceFeatures deviceFeatures{};

		VkDeviceCreateInfo createInfo = device_create_info();

		createInfo.queueCreateInfoCount = static_cast<uint32_t>(deviceQueueCreateInfos.size());
		createInfo.pQueueCreateInfos = deviceQueueCreateInfos.data();

		createInfo.pEnabledFeatures = &deviceFeatures;

		const std::vector<const char*> extensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

		createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		createInfo.ppEnabledExtensionNames = extensions.data();

		const std::vector<const char*> enabledValidationLayers = { "VK_LAYER_KHRONOS_validation" };

		#ifndef NDEBUG

			if (instance.is_validation_enabled() == true)
			{
				createInfo.enabledLayerCount = static_cast<uint32_t>(enabledValidationLayers.size());
				createInfo.ppEnabledLayerNames = enabledValidationLayers.data();
			}
			else
			{
				createInfo.enabledLayerCount = 0;
			}

		#else
			
			createInfo.enabledLayerCount = 0;

		#endif

		if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &m_logicalDevice) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create logical device");
		}

		PSAI_LOG_DEBUG("Logical deivce successfully created");

		vkGetDeviceQueue(m_logicalDevice, indices.graphicsFamily.value(), 0, &m_graphicsQueue);
		vkGetDeviceQueue(m_logicalDevice, indices.presentFamily.value(), 0, &m_presentationQueue);
	}

	LogicalDevice::~LogicalDevice()
	{
		vkDestroyDevice(m_logicalDevice, nullptr);
	}
	
} // PsAi::Renderer namespace
