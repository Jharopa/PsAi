// PsAi includes
#include "application.h"
#include "log.h"

// STD library includes
#include <iostream>

int main()
{
	PsAi::Log::init();
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
