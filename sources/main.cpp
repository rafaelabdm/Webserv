#include <c_external_functions.h>
#include <colors.hpp>
#include <iostream>
#include <man_webserv.hpp>

int	main(int argc, char* argv[])
{
	(void)argc;
	if (manual_option(argv[1]))
		return (0);
	else
		std::cout << MAGENTA << "Hello World" << RESET_COLOR << std::endl;

	return (0);
}
