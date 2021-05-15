#include  "semaphore.h"

namespace PsAi::Renderer
{
	
	Semaphore::Semaphore(const LogicalDevice& logicalDevice)
		: m_logicalDevice(logicalDevice)
	{
		VkSemaphoreCreateInfo semephoreCreateInfo = semaphore_create_info();

		if (vkCreateSemaphore(m_logicalDevice.get_logical_device(), &semephoreCreateInfo, nullptr, &m_semaphore) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create Vulkan semaphore!");
		}
	}

	Semaphore::~Semaphore()
	{
		vkDestroySemaphore(m_logicalDevice.get_logical_device(), m_semaphore, nullptr);
	}

} // PsAi::Renderer namespace
