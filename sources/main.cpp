#include <c_external_functions.h>
#include <colors.hpp>
#include <iostream>

int main(void)
{
  errno = 0;

  std::cout << "errno = " << errno << std::endl;

  return (0);
}
