// PsAi imports
#include "application.h"

#include "math/vec3.h"

#include <iostream>

int main()
{
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
