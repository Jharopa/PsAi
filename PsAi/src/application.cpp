// PsAi imports
#include "application.h"

namespace PsAi
{

	void Application::run()
	{
		while (!m_window.should_close())
		{
			glfwPollEvents();
		}
	}

} // PsAi namespace
