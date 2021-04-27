#include "device.h"

// STD library imports
#include <iostream>

namespace PsAi
{

	namespace Renderer
	{
		Device::Device(Window& window) {}

		Device::~Device() {}

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

			std::vector<const char*> extentions = getRequiredExtensions();
			createInfo.enabledExtensionCount = static_cast<uint32_t>(extentions.size());
			createInfo.ppEnabledExtensionNames = extentions.data();

			if (vkCreateInstance(&createInfo, nullptr, &m_instance) != VK_SUCCESS)
			{
				std::cout << "Failed to create vulkan instance!" << std::endl;
			}
		}

		std::vector<const char*> Device::getRequiredExtensions()
		{
			uint32_t glfwExtentionCount = 0;
			const char** glfwExtensions;
			glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtentionCount);

			std::vector<const char*> extenstions(glfwExtensions, glfwExtensions + glfwExtentionCount);

			return extenstions;
		}

	}

}