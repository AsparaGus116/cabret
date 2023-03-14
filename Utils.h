#pragma once

#include <string>
#include <regex>

namespace utils
{
	void removeWhitespace(std::string& input)
	{
		std::regex whitespace("[\\s]*");
		input = std::regex_replace(input, whitespace, "");
	}

	void quit()
	{
#ifdef DEBUG
		std::cout << "Press any key to exit...";
		while (!_kbhit()) {} // Windows only, find POSIX solution
#endif

		std::exit(0);
	}
}

