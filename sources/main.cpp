#include <c_external_functions.h>
#include <colors.hpp>
#include <iostream>
#include <man_webserv.hpp>

static bool valid_argc(const int argc)
{
  std::string message = "";

  if (argc == 1)
    message = "missing config file";
  else if (argc > 2)
    message = "too many arguments";

  if (message != "")
  {
    errno = 42;
    std::cout
      << "webserv: " << message << std::endl
      << "Try \'webserv --help\' for more information." << std::endl;

    return (false);
  }

  return (true);
}

static bool help_option(const std::string& option)
{
  if (option == "-h" || option == "--help")
  {
    std::cout<< HELP << std::endl;

    return (true);
  }

  return (false);
}

int main( int argc, char* argv[])
{
  errno = 0;

  if (!valid_argc(argc))
    return (errno);
  if (help_option(argv[1]))
    return (0);

  std::cout << "errno = " << errno << std::endl;

  return (0);
}
