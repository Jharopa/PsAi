#include "device.h"

// STD library imports
#include <iostream>

namespace PsAi
{

	namespace Renderer
	{
		Device::Device(Window& window) 
		{
			create_instance();
		}

		Device::~Device() 
		{
			vkDestroyInstance(m_instance, nullptr);
		}

		void Device::create_instance() 
		{
			VkApplicationInfo appInfo {};
			appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
			appInfo.pApplicationName = "PsAi";
			appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
			appInfo.pEngineName = "No Engine";
			appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 1);
			appInfo.apiVersion = VK_API_VERSION_1_2;

			VkInstanceCreateInfo createInfo {};
			createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			createInfo.pApplicationInfo = &appInfo;

			std::vector<const char*> extensions = get_required_extensions();
			createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
			createInfo.ppEnabledExtensionNames = extensions.data();

			if (vkCreateInstance(&createInfo, nullptr, &m_instance) != VK_SUCCESS)
			{
				std::cout << "Failed to create vulkan instance!\n";
			}

			check_available_extentions();
		}

		std::vector<const char*> Device::get_required_extensions()
		{
			uint32_t glfwExtensionCount = 0;
			const char** glfwExtensions;
			glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

			std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

			return extensions;
		}

		void Device::check_available_extentions()
		{
			uint32_t extensionCount = 0;
			vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

			std::vector<VkExtensionProperties> extensions(extensionCount);
			vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

			std::cout << "Available extensions:\n";

			for (const auto& extension : extensions)
			{
				std::cout << '\t' << extension.extensionName << '\n';
			}
		}

	}

}