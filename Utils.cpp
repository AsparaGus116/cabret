#include "Utils.h"

void utils::removeWhitespace(std::string& input)
{
	std::regex whitespace("[\\s]*");
	std::regex comments("(\\/\\/)(.)+\\n");
	input = std::regex_replace(input, comments, "\n");
	input = std::regex_replace(input, whitespace, "");
	
}

void utils::quit()
{
#ifdef DEBUG
	std::cout << "Press any key to exit...";
	while (!_kbhit()) {} // Windows only, find POSIX solution
#endif

	std::exit(0);
}
