#include "Includes.h"
#include "Application.h"

int main()
{
	Main::Application application;

	try
	{
		application.Run();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();

		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
