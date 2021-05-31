#include "command_pool.h"

namespace PsAi::Renderer
{

	CommandPool::CommandPool(VkDevice logicalDevice, VkPhysicalDevice physicalDevice, VkSurfaceKHR surface)
		: m_logicalDevice(logicalDevice)
	{
		QueueFamilyIndices queueFamilyIndices = HelperFunctions::find_queue_families(physicalDevice, surface);

		VkCommandPoolCreateInfo commandPoolCreateInfo = command_pool_create_info();
		commandPoolCreateInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
		commandPoolCreateInfo.flags = 0;

		if (vkCreateCommandPool(m_logicalDevice, &commandPoolCreateInfo, nullptr, &m_commandPool) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create Vulkan command pool");
		}
	}

	CommandPool::~CommandPool()
	{
		vkDestroyCommandPool(m_logicalDevice, m_commandPool, nullptr);
	}

} // PsAi::Renderer namespace