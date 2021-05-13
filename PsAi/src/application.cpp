#include "application.h"

namespace PsAi
{

	void Application::run()
	{
		while (!m_window.should_close())
		{
			glfwPollEvents();
			drawFrame();
		}
	}

	void Application::drawFrame()
	{
	}

} // PsAi namespace
