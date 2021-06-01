#include  "semaphore.h"

namespace PsAi::Renderer
{
	
	Semaphore::Semaphore(VkDevice logicalDevice, int numSemaphores)
		: m_logicalDevice(logicalDevice)
	{
		VkSemaphoreCreateInfo semephoreCreateInfo = semaphore_create_info();

		m_semaphores.resize(numSemaphores);

		for (size_t i = 0; i < numSemaphores; i++)
		{
			if (vkCreateSemaphore(m_logicalDevice, &semephoreCreateInfo, nullptr, &m_semaphores[i]) != VK_SUCCESS)
			{
				throw std::runtime_error("Failed to create Vulkan semaphore!");
			}
		}
	}

	Semaphore::~Semaphore()
	{
		for (auto semaphore : m_semaphores)
		{
			vkDestroySemaphore(m_logicalDevice, semaphore, nullptr);
		}
	}

} // PsAi::Renderer namespace
