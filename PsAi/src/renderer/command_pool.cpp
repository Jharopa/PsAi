#include "command_pool.h"

namespace PsAi::Renderer
{

	CommandPool::CommandPool(const LogicalDevice& logicalDevice, const PhysicalDevice& physicalDevice, const Surface& surface)
		: m_logicalDevice(logicalDevice)
	{
		QueueFamilyIndices queueFamilyIndices = HelperFunctions::find_queue_families(physicalDevice.get_physical_device(), surface.get_surface());

		VkCommandPoolCreateInfo commandPoolCreateInfo{};
		commandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		commandPoolCreateInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
		commandPoolCreateInfo.flags = 0;

		if (vkCreateCommandPool(m_logicalDevice.get_logical_device(), &commandPoolCreateInfo, nullptr, &m_commandPool) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create Vulkan command pool");
		}
	}

	CommandPool::~CommandPool()
	{
		vkDestroyCommandPool(m_logicalDevice.get_logical_device(), m_commandPool, nullptr);
	}

} // PsAi::Renderer namespace