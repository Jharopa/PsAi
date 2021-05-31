#include "device.h"

namespace PsAi::Renderer
{
	Device::Device(const Instance& instance, VkSurfaceKHR surface)
		: m_instance(instance), m_surface(surface)
	{
		PSAI_LOG_DEBUG("Selecting suitable physical device");
		select_physical_device();
		PSAI_LOG_DEBUG("Physical device successfuly selected");

		PSAI_LOG_DEBUG("Creating Vulkan logical device");
		create_logical_device();
		PSAI_LOG_DEBUG("Vulkan logical device successfuly created");
	}

	Device::~Device()
	{
		vkDestroyDevice(m_logicalDevice, nullptr);
	}

	void Device::select_physical_device()
	{
		uint32_t deviceCount;
		vkEnumeratePhysicalDevices(m_instance.get_instance(), &deviceCount, nullptr);

		if (deviceCount == 0)
		{
			throw std::runtime_error("Failed to find GPU with Vulkan support");
		}

		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(m_instance.get_instance(), &deviceCount, devices.data());

		for (const auto& device : devices)
		{
			if(is_physical_device_suitable(device))
			{
				PSAI_LOG_DEBUG("Physical deivce selected");
				m_physicalDevice = device;
				set_physical_device_attributes();
				break;
			}
		}

		if (m_physicalDevice == VK_NULL_HANDLE)
		{
			throw std::runtime_error("Failed to find a suitable GPU!");
		}
	}

	bool Device::is_physical_device_suitable(VkPhysicalDevice physicalDevice)
	{
		VkPhysicalDeviceProperties physicalDeviceProperties;
		VkPhysicalDeviceFeatures physicalDeviceFeatures;
		vkGetPhysicalDeviceProperties(physicalDevice, &physicalDeviceProperties);
		vkGetPhysicalDeviceFeatures(physicalDevice, &physicalDeviceFeatures);

		return physicalDeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU
			&& physicalDeviceFeatures.geometryShader
			&& is_swapchain_supported(physicalDevice)
			&& is_present_supported(physicalDevice, m_surface);
	}

	bool Device::is_extensions_supported(VkPhysicalDevice physicalDevice, std::string extensionName)
	{
		uint32_t extensionCount;
		vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr);

		if (extensionCount == 0)
		{
			return false;
		}

		std::vector<VkExtensionProperties> availableExtensions(extensionCount);
		vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, availableExtensions.data());

		for (const auto& extension : availableExtensions)
		{
			if(extension.extensionName == extensionName)
			{
				return true;
			}
		}

		return false;
	}

	bool Device::is_swapchain_supported(VkPhysicalDevice physicalDevice)
	{
		return is_extensions_supported(physicalDevice, VK_KHR_SWAPCHAIN_EXTENSION_NAME);
	}

	bool Device::is_present_supported(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface)
	{
		VkBool32 presentSupported;

		vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, 0, surface, &presentSupported);

		return presentSupported == VK_TRUE;
	}

	void Device::set_physical_device_attributes()
	{
		vkGetPhysicalDeviceProperties(m_physicalDevice, &m_physicalDeviceProperties);
		vkGetPhysicalDeviceFeatures(m_physicalDevice, &m_physicalDeviceFeatures);
	}

	void Device::set_queue_family_properties()
	{
		uint32_t queueFamilyCount;
		vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice, &queueFamilyCount, nullptr);

		if (queueFamilyCount == 0)
		{
			throw std::runtime_error("Physical device doesn't support any Vulkan queues");
		}

		m_queueFamilyProperties.resize(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice, &queueFamilyCount, m_queueFamilyProperties.data());
	}

	void Device::create_logical_device()
	{
		QueueFamilyIndices indices = HelperFunctions::find_queue_families(m_physicalDevice, m_surface);

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

		m_enabledDeviceExtensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);

		createInfo.enabledExtensionCount = static_cast<uint32_t>(m_enabledDeviceExtensions.size());
		createInfo.ppEnabledExtensionNames = m_enabledDeviceExtensions.data();

		const std::vector<const char*> enabledValidationLayers = { "VK_LAYER_KHRONOS_validation" };

		#ifndef NDEBUG

			if (m_instance.is_validation_enabled() == true)
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

		if (vkCreateDevice(m_physicalDevice, &createInfo, nullptr, &m_logicalDevice) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create logical device");
		}

		PSAI_LOG_DEBUG("Logical deivce successfully created");

		vkGetDeviceQueue(m_logicalDevice, indices.graphicsFamily.value(), 0, &m_graphicsQueue);
		vkGetDeviceQueue(m_logicalDevice, indices.presentFamily.value(), 0, &m_presentQueue);
	}

} // PsAi::Renderer namespace
