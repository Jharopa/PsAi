#include "fence.h"

namespace PsAi::Renderer
{
	
	Fence::Fence(VkDevice logicalDevice, int numFences)
		: m_logicalDevice(logicalDevice)
	{
		VkFenceCreateInfo fenceCreateInfo = fence_create_info();

		m_fences.resize(numFences);

		for (size_t i = 0; i < numFences; i++)
		{
			if (vkCreateFence(m_logicalDevice, &fenceCreateInfo, nullptr, &m_fences[i]) != VK_SUCCESS)
			{
				throw std::runtime_error("Failed to create Vulkan fence");
			}
		}
	}

	Fence::~Fence()
	{
		for (auto fence : m_fences)
		{
			vkDestroyFence(m_logicalDevice, fence, nullptr);
		}
	}

} // PsAi::Renderer namespace
