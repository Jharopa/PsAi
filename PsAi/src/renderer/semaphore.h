#pragma once

// PsAi includes
#include "logical_device.h"

// Vulkan includes
#include <vulkan/vulkan.h>

namespace PsAi::Renderer
{

	class Semaphore
	{
	public:
		// Public member functions
		Semaphore(const LogicalDevice& logicalDevice);
		~Semaphore();

		Semaphore(const Semaphore&) = delete;
		Semaphore(Semaphore&&) = delete;
		Semaphore& operator=(const Semaphore&) = delete;
		Semaphore& operator=(Semaphore&&) = delete;

		const VkSemaphore& get_semaphore() const { return m_semaphore; }

	private:
		VkSemaphore m_semaphore = VK_NULL_HANDLE;
		const LogicalDevice& m_logicalDevice;
	};

} // PsAi::Renderer namespace
