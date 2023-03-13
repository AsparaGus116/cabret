#include <fstream>
#include <iostream>
#include <vector>
#include <cassert>
#include <regex>
#include <sstream>
#include <conio.h>

#define DEBUG

//TODO: Find way to get Windows / POSIX in #DEFINE statement

extern const char* operators[] = { "()", "==", "=", "+", "-", "*", "/", "||", "&&", };

void removeWhitespace(std::string& input)
{
	std::regex whitespace("[\\s]*");
	input = std::regex_replace(input, whitespace, "");
}

void quit()
{
#ifdef DEBUG
	std::cout << "Press any key to exit...";
	while(!_kbhit() ){} // Windows only, find POSIX solution
#endif

	std::exit(0);
}

int main(int argc, char* argv[])
{
	std::string filename;

	if (argc == 2)
	{
		filename = argv[1];
	}
	else if (argc > 2)
	{
		std::cout << "ERROR: TOO MANY ARGUMENTS\n";
		quit();
	}
#ifndef DEBUG
	else if (argc < 2)
	{
		std::cout << "ERROR: FILE NAME EXPECTED\n";
		quit();
	}
#endif

#ifdef DEBUG
	filename = "test.cbr";
#endif
	std::ifstream file{};
	file.open(filename, std::ios_base::in);

	std::string in;
	
	if (!file.good())
	{
		std::cout << "ERROR: BAD FILE INPUT\n";
		quit();
	}

	while (!file.eof())
	{
		in.push_back(file.get());
	}
	file.close();
	removeWhitespace(in);
	std::stringstream f{ in };
	while (!f.eof())
	{
		std::string line;
		std::getline(f, line, ';');
		if (line[0] <= 0) { quit(); } // check for null terminator or -1 (EOF signal)
		std::cout << line << '\n';
	}
}