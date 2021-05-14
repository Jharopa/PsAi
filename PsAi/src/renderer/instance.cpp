#include "instance.h"

namespace PsAi::Renderer
{
	
	static VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
	VkResult create_debug_utils_messenger(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
	void destroy_debug_utils_messenger(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

	Instance::Instance(const char* applicationName, const uint32_t applicationVersion, const char* engineName, const uint32_t engineVersion, const uint32_t vkAPIVersion, std::vector<std::string> extensionsList, bool validationEnabled)
		: m_validationEnabled(validationEnabled)
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
		
		// Creating VKInstance's application info
		VkApplicationInfo appInfo = application_info(applicationName, applicationVersion, engineName, engineVersion, vkAPIVersion);

		// Creating VKInstance's create info
		VkInstanceCreateInfo instanceCreateInfo = instance_create_info(appInfo);

		// Setting up VKInstance's extensions
		std::vector<const char*> enabledExtensions = {};

		#ifndef NDEBUG
			extensionsList.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		#endif

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
			// If current requested extension is supported added to enabledExtensions vector, else don't add to enabledExtensions vector
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
			
		instanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(enabledExtensions.size());
		instanceCreateInfo.ppEnabledExtensionNames = enabledExtensions.data();
			
		std::vector<const char*> enabledValidationLayers = {};
		std::string VK_LAYER_KHRONOS_validation = "VK_LAYER_KHRONOS_validation";

		// Setting up VKInstance's validation layers
		#ifndef NDEBUG
				
			if(m_validationEnabled)
			{
				PSAI_LOG_DEBUG("Vulkan validation layers enabled");

				if (is_layer_supported(VK_LAYER_KHRONOS_validation.c_str()))
				{
					PSAI_LOG_DEBUG("Instance validation layer '{}' is available on this system, adding to enabled validation layers list", VK_LAYER_KHRONOS_validation);
					enabledValidationLayers.push_back(VK_LAYER_KHRONOS_validation.c_str());
				}
				else
				{
					PSAI_LOG_DEBUG("Instance validation layer '{}' is not available on this system", VK_LAYER_KHRONOS_validation);
				}

				instanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(enabledValidationLayers.size());
				instanceCreateInfo.ppEnabledLayerNames = enabledValidationLayers.data();

				VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;

				populate_debug_messenger_create_info(debugCreateInfo);
				instanceCreateInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
			}
			else
			{
				PSAI_LOG_WARN("Vulkan validation layers disabled while in debug configuration!");
				instanceCreateInfo.enabledLayerCount = 0;
				instanceCreateInfo.pNext = nullptr;
			}

		#else
				
			instanceCreateInfo.enabledLayerCount = 0;
			instanceCreateInfo.pNext = nullptr;

		#endif

		// Create Vulkan instance using instanceCreateInfo, if unsuccessful throw a runtime error.
		if (vkCreateInstance(&instanceCreateInfo, nullptr, &m_instance) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create Vulkan instance!");
		}

		PSAI_LOG_DEBUG("Vulkan instance successfully created");

		#ifndef NDEBUG
			
			if (m_validationEnabled)
			{
				PSAI_LOG_DEBUG("Creating Vulkan debug messenger");

				setup_debug_messenger();

				PSAI_LOG_DEBUG("Vulkan debug messenger successfully Created");
			}

		#endif
	}

	Instance::~Instance()
	{
		#ifndef NDEBUG

			if(m_validationEnabled)
			{
				destroy_debug_utils_messenger(m_instance, m_debugMessenger, nullptr);
			}

		#endif


		vkDestroyInstance(m_instance, nullptr);
	}

	bool Instance::is_extension_supported(std::string extensionName)
	{
		// Get count of instance extensions available on this system
		uint32_t extensionCount;
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
			if (extension.extensionName == extensionName)
			{
				return true;
			}
		}

		// If none of the extension.extensionNames matches provided extensionName return false
		return false;
	}

	bool Instance::is_layer_supported(std::string layerName)
	{
		// Get count of instance layers available on this system
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		// If layerCount is 0 throw runtime error
		if(layerCount == 0)
		{
			throw std::runtime_error("No Vulkan validation layers available!");
		}

		// Get a vector of instance layers available on this system
		std::vector<VkLayerProperties> layers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, layers.data());

		// Iterate over instance layers in layers vector
		for (const auto& layer : layers)
		{
			// Return true if current layer.layername is the same as layerName provided to the function
			if (layer.layerName == layerName)
			{
				return true;
			}
		}

		// If none of the layer.layerNames matches the provided layerName return false
		return false;
	}

	void Instance::setup_debug_messenger()
	{
		VkDebugUtilsMessengerCreateInfoEXT createInfo;
		populate_debug_messenger_create_info(createInfo);

		if (create_debug_utils_messenger(m_instance, &createInfo, nullptr, &m_debugMessenger) != VK_SUCCESS)
		{
			throw std::runtime_error("Faile to set up Vulkan debug messenger!");
		}
	}

	void Instance::populate_debug_messenger_create_info(VkDebugUtilsMessengerCreateInfoEXT& createInfo)
	{
		createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		createInfo.pfnUserCallback = debug_callback;
		createInfo.pUserData = nullptr; // Optional
	}

	static VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData)
	{
		PSAI_LOG_DEBUG("Validation layer: {}", pCallbackData->pMessage);

		return VK_FALSE;
	}

	VkResult create_debug_utils_messenger(
		VkInstance instance,
		const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
		const VkAllocationCallbacks* pAllocator,
		VkDebugUtilsMessengerEXT* pDebugMessenger)
	{
		auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");

		if (func != nullptr)
		{
			return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
		}
		else
		{
			return VK_ERROR_EXTENSION_NOT_PRESENT;
		}
	}

	void destroy_debug_utils_messenger(
		VkInstance instance, 
		VkDebugUtilsMessengerEXT debugMessenger, 
		const VkAllocationCallbacks* pAllocator)
	{
		auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");

		if (func != nullptr)
		{
			return func(instance, debugMessenger, pAllocator);
		}
	}

} // PsAi::Renderer namespace