#include "instance.h"

namespace PsAi
{
	
	namespace Renderer
	{
		
		Instance::Instance(const char* applicationName, const uint32_t applicationVersion, const char* engineName, const uint32_t engineVersion, const uint32_t vkAPIVersion)
		{
			PSAI_LOG_DEBUG("Creating Vulkan instance");

			// Application info debug
			PSAI_LOG_DEBUG("Application name: '{}'", applicationName);
			PSAI_LOG_DEBUG("Application version: {}.{}.{}", 
				VK_VERSION_MAJOR(applicationVersion), 
				VK_VERSION_MINOR(applicationVersion), 
				VK_VERSION_PATCH(applicationVersion));
			PSAI_LOG_DEBUG("Engine name: '{}'", engineName);
			PSAI_LOG_DEBUG("Engine version: {}.{}.{}",
				VK_VERSION_MAJOR(engineVersion),
				VK_VERSION_MINOR(engineVersion),
				VK_VERSION_PATCH(engineVersion));
			PSAI_LOG_DEBUG("Vulkan API version: {}.{}.{}", 
				VK_VERSION_MAJOR(vkAPIVersion),
				VK_VERSION_MINOR(vkAPIVersion),
				VK_VERSION_PATCH(vkAPIVersion));

			VkApplicationInfo appInfo{};
			appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
			appInfo.pApplicationName = applicationName;
			appInfo.applicationVersion = applicationVersion;
			appInfo.pEngineName = engineName;
			appInfo.engineVersion = engineVersion;
			appInfo.apiVersion = vkAPIVersion;

			VkInstanceCreateInfo instanceCreateInfo{};
			instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			instanceCreateInfo.pApplicationInfo = &appInfo;

			uint32_t glfwExtensionCount = 0;
			const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

			if(glfwExtensionCount == 0)
			{
				throw std::runtime_error("glfwGetRequiredInstanceExtensions found 0 required instance extensions!");
			}

			PSAI_LOG_DEBUG("Number of required GLFW instance extensions: {}", glfwExtensionCount);

			std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

			PSAI_LOG_DEBUG("Required GLFW instance extensions:");

			for (const auto& extension : extensions)
			{
				PSAI_LOG_DEBUG("'{}'", extension);
			}

			instanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
			instanceCreateInfo.ppEnabledExtensionNames = extensions.data();

			instanceCreateInfo.enabledLayerCount = 0;
			instanceCreateInfo.pNext = nullptr;

			if (vkCreateInstance(&instanceCreateInfo, nullptr, &m_instance) != VK_SUCCESS)
			{
				throw std::runtime_error("Failed to create Vulkan instance!");
			}

			PSAI_LOG_DEBUG("Vulkan instance successfully created");
		}

		Instance::~Instance()
		{
			vkDestroyInstance(m_instance, nullptr);
		}

	} // Renderer namespace

} // PsAi namespace