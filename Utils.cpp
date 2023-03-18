#include "Utils.h"

#include <iostream>
#include <string>
#include <conio.h>

#define DEBUG

const std::string def_delim{ "|" };
const std::string undef_delim{ "%" };

void utils::quit()
{
#ifdef DEBUG
	std::cout << "Press any key to exit...";
	while (!_kbhit()) {} // Windows only, find POSIX solution
#endif

	std::exit(0);
}
