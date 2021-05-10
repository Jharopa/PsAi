#include "logical_device.h"

namespace PsAi::Renderer
{
	LogicalDevice::LogicalDevice(const Instance& instance, const PhysicalDevice& physicalDevice, const Surface& surface)
		: m_instance(instance), m_physicalDevice(physicalDevice), m_surface(surface)
	{
		PSAI_LOG_DEBUG("Creating logical device");

		QueueFamilyIndices indices = HelperFunctions::find_queue_families(m_physicalDevice.get_physical_device(), m_surface.get_surface());

		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
		std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };
		float queuePriority = 1.0f;

		for (uint32_t queueFamily : uniqueQueueFamilies)
		{
			VkDeviceQueueCreateInfo queueCreateInfo{};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = queueFamily;
			queueCreateInfo.queueCount = 1;
			queueCreateInfo.pQueuePriorities = &queuePriority;
			queueCreateInfos.push_back(queueCreateInfo);
		}

		VkPhysicalDeviceFeatures deviceFeatures{};

		VkDeviceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

		createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
		createInfo.pQueueCreateInfos = queueCreateInfos.data();

		createInfo.pEnabledFeatures = &deviceFeatures;

		const std::vector<const char*> extensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

		createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		createInfo.ppEnabledExtensionNames = extensions.data();

		const std::vector<const char*> enabledValidationLayers = { "VK_LAYER_KHRONOS_validation" };

		if (m_instance.is_validation_enabled() == true)
		{
			createInfo.enabledLayerCount = static_cast<uint32_t>(enabledValidationLayers.size());
			createInfo.ppEnabledLayerNames = enabledValidationLayers.data();
		}
		else
		{
			createInfo.enabledLayerCount = 0;
		}

		if (vkCreateDevice(m_physicalDevice.get_physical_device(), &createInfo, nullptr, &m_logicalDevice) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create logical device");
		}

		PSAI_LOG_DEBUG("Logical deivce successfully created");

		vkGetDeviceQueue(m_logicalDevice, indices.graphicsFamily.value(), 0, &m_graphicsQueue);
		vkGetDeviceQueue(m_logicalDevice, indices.presentFamily.value(), 0, &m_presentationQueue);
	}

	LogicalDevice::~LogicalDevice()
	{
	}
	
} // PsAi::Renderer namespace
