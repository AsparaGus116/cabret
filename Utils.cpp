#include "Utils.h"

#include <iostream>
#include <conio.h>

#define DEBUG

std::regex_constants::syntax_option_type icase{ std::regex_constants::syntax_option_type::icase };

void utils::preProcess(std::string& input)
{
	std::regex define("#define\\s+(\\w+)\n?",icase);
	std::regex undef("#undef\\s+(\\w+)\n?", icase);
	std::regex whitespace("[\\s]*");
	std::regex comments("(\\/\\/)(.)+\\n");

	input = std::regex_replace(input, comments, "\n");
	input = std::regex_replace(input, define, "#$1;");
	input = std::regex_replace(input, undef, "^$1;");
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
