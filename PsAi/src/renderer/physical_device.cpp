#include "physical_device.h"

namespace PsAi::Renderer
{
	
	PhysicalDevice::PhysicalDevice(const VkInstance& instance)
	{
		uint32_t deviceCount;
		vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

		if (deviceCount == 0)
		{
			throw std::runtime_error("Failed to find a GPU with Vulkan support");
		}

		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

		for (const auto& device : devices)
		{
			if (is_physical_device_suitable(device))
			{
				m_physicalDevice = device;
				populate_attributes();
				break;
			}
		}

		if (m_physicalDevice == VK_NULL_HANDLE)
		{
			throw std::runtime_error("Failed to find a suitable GPU!");
		}
	}

	PhysicalDevice::~PhysicalDevice() {}

	bool PhysicalDevice::is_physical_device_suitable(VkPhysicalDevice physicalDevice)
	{
		VkPhysicalDeviceProperties physicalDeviceProperties;
		VkPhysicalDeviceFeatures physicalDeviceFeatures;
		vkGetPhysicalDeviceProperties(physicalDevice, &physicalDeviceProperties);
		vkGetPhysicalDeviceFeatures(physicalDevice, &physicalDeviceFeatures);

		bool extensionsSupported = has_requested_extension_support(physicalDevice);

		return physicalDeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU
			   && physicalDeviceFeatures.geometryShader
			   && extensionsSupported;
	}

	bool PhysicalDevice::has_requested_extension_support(VkPhysicalDevice physicalDevice)
	{
		uint32_t extensionCount;
		vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr);

		if (extensionCount == 0)
		{
			return false;
		}

		std::vector<VkExtensionProperties> availableExtensions(extensionCount);
		vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, availableExtensions.data());
	
		std::set<std::string> requiredExtensions(m_deviceExtensions.begin(), m_deviceExtensions.end());

		for (const auto& extension : availableExtensions)
		{
			requiredExtensions.erase(extension.extensionName);
		}

		return requiredExtensions.empty();
	}

	void PhysicalDevice::populate_attributes()
	{
		vkGetPhysicalDeviceProperties(m_physicalDevice, &m_physicalDeviceProperties);
		vkGetPhysicalDeviceFeatures(m_physicalDevice, &m_physicalDeviceFeatures);
	}

} // PsAi::Renderer namespace