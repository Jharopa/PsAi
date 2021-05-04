#include "instance.h"

namespace PsAi
{
	
	namespace Renderer
	{
		
		Instance::Instance(const char* applicationName, const uint32_t applicationVersion, const char* engineName, const uint32_t engineVersion, const uint32_t vkAPIVersion, std::vector<std::string> extensionsList)
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

			std::vector<const char*> enabledExtensions = {};

			// Get GLFW extensions and extension count
			uint32_t glfwExtensionCount = 0;
			const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

			// If no required GLFW instance extensions throw runtime error
			if(glfwExtensionCount == 0)
			{
				throw std::runtime_error("glfwGetRequiredInstanceExtensions found 0 required GLFW instance extensions!");
			}

			PSAI_LOG_DEBUG("Number of required GLFW instance extensions: {}", glfwExtensionCount);

			// Move required GLFW instance extensions from const char** to vector<const char*>
			std::vector<const char*> glfwExtensionsList(glfwExtensions, glfwExtensions + glfwExtensionCount);

			PSAI_LOG_DEBUG("Required GLFW instance extensions:");

			// Iterate over glfwExensionList and add to extensionList
			for (const auto& glfwExtension : glfwExtensionsList)
			{
				PSAI_LOG_DEBUG("'{}', adding to extension list", glfwExtension);
				extensionsList.push_back(glfwExtension);
			}

			// Iterate over extensionList vector
			for (const auto& requestedExtension : extensionsList)
			{
				// If requested extension is supported added to enabledExtensions vector, else don't add to enabledExtensions vector
				if (is_extension_supported(requestedExtension.c_str()))
				{
					PSAI_LOG_DEBUG("Instance extension '{}' is available on this system, adding to enabled extensions list", requestedExtension);
					enabledExtensions.push_back(requestedExtension.c_str());
				}
				else
				{
					PSAI_LOG_DEBUG("Instance extension '{}' is not available on this system", requestedExtension);
				}
			}
			
			VkInstanceCreateInfo instanceCreateInfo{};
			instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			instanceCreateInfo.pApplicationInfo = &appInfo;

			instanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(enabledExtensions.size());
			instanceCreateInfo.ppEnabledExtensionNames = enabledExtensions.data();

			instanceCreateInfo.enabledLayerCount = 0;
			instanceCreateInfo.pNext = nullptr;

			// Create Vulkan instance or throw runtime error.
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

		bool Instance::is_extension_supported(std::string extensionName)
		{
			// Get count of instance extensions available on this system
			uint32_t extensionCount = 0;
			vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

			// If extensionCount is 0 throw runtime error 
			if(extensionCount == 0)
			{
				throw std::runtime_error("No Vulkan extensions availible!");
			}

			// Get a vector of instance extensions available on this system
			std::vector<VkExtensionProperties> extensions(extensionCount);
			vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
			
			// Iterate over instance extensions in extensions vector
			for (const auto& extension : extensions)
			{
				// Return true if current extension.extensionName is the same as extensionName provided to the function
				if(extension.extensionName == extensionName)
				{
					return true;
				}
			}

			// If none of the extension.extensionName matches provided extensionName return false
			return false;
		}

	} // Renderer namespace

} // PsAi namespace