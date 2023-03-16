#include <fstream>
#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <conio.h>

#include "Utils.h"

#define DEBUG

//TODO: Find way to get Windows / POSIX in #DEFINE statement

extern const char* operators[] = { "()", "==", "=", "+", "-", "*", "/", "||", "&&", };

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
		utils::quit();
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
		utils::quit();
	}

	while (!file.eof())
	{
		in.push_back(file.get());
	}
	file.close();
	utils::removeWhitespace(in);
	std::stringstream f{ in };
	while (!f.eof())
	{
		std::string line;
		std::getline(f, line, ';');
		if (line[0] <= 0) { utils::quit(); } // check for null terminator or -1 (EOF signal)
		std::cout << line << '\n';
	}
	utils::quit();
}