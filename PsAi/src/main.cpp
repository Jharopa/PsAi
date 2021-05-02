// PsAi imports
#include "application.h"
#include "Log.h"

#include <iostream>

int main()
{
	PsAi::Log::init();

	PSAI_LOG_DEBUG("Test");

	PsAi::Application app{};

	try
	{
		app.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
