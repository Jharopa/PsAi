#pragma once

// PsAi includes
#include "renderer/vulkan_structures.h"
#include "renderer/window.h"
#include "renderer/instance.h"
#include "renderer/surface.h"
#include "renderer/device.h"
#include "renderer/swapchain.h"
#include "renderer/render_pass.h"
#include "renderer/shader.h"
#include "renderer/pipeline.h"
#include "renderer/framebuffer.h"
#include "renderer/command_pool.h"
#include "renderer/command_buffer.h"
#include "renderer/semaphore.h"
#include "renderer/fence.h"
#include "renderer/vulkan_structures.h"

// Vulkan includes
#include <vulkan/vulkan.h>

// STD library includes
#include <vector>
#include <memory>

namespace PsAi 
{

	class Application 
	{
		public:
			// Public member variables
			static constexpr int WIDTH = 800;
			static constexpr int HEIGHT = 600;
			static constexpr int MAX_FRAMES_IN_FLIGHT = 2;

			// Public member functions
			Application();
			~Application();

			void run();
			void draw_frame();

		private:
			// Private member variables
			const std::vector<std::string> m_instanceExtensions = {};
			VkApplicationInfo m_applicationInfo = Renderer::application_info("PsAi", VK_MAKE_VERSION(0, 0, 1), "No Engine", VK_MAKE_VERSION(0, 0, 1), VK_API_VERSION_1_2);

			std::unique_ptr<Renderer::Window> m_window;
			std::unique_ptr<Renderer::Instance> m_instance;
			std::unique_ptr<Renderer::Surface> m_surface;
			std::unique_ptr<Renderer::Device> m_device;
			std::unique_ptr<Renderer::Swapchain> m_swapchain;
			std::unique_ptr<Renderer::RenderPass> m_renderPass;
			std::unique_ptr<Renderer::Shader> m_vertShader;
			std::unique_ptr<Renderer::Shader> m_fragShader;
			std::unique_ptr<Renderer::Pipeline> m_pipeline;
			std::unique_ptr<Renderer::Framebuffer> m_framebuffers;
			std::unique_ptr<Renderer::CommandPool> m_commandPool;
			std::unique_ptr<Renderer::CommandBuffer> m_commandBuffer;
			std::unique_ptr<Renderer::Semaphore> m_imageAvailableSemaphores;
			std::unique_ptr<Renderer::Semaphore> m_renderFinishedSemaphores;
			std::unique_ptr<Renderer::Fence> m_inFlightFences;
			std::unique_ptr<Renderer::Fence> m_imagesInFlight;
			size_t m_currentFrame = 0;
	};

} // PsAi namespace
