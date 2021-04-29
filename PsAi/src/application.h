#pragma once

// PsAi imports
#include "window.h"
#include "renderer/pipeline.h"
#include "renderer/device.h"

namespace PsAi 
{

	class Application 
	{
		public:
			// Public member variables
			static constexpr int WIDTH = 800;
			static constexpr int HEIGHT = 600;

			// Public member functions
			void run();

		private:
			// Private member variables
			Window m_window{ WIDTH, HEIGHT, "First App!" };
			Renderer::Device m_device{ m_window };
			Renderer::Pipeline m_pipeline{ m_device, "shaders/bytecode/simple.vert.spv", "shaders/bytecode/simple.frag.spv" };
	};

} // PsAi namespace
