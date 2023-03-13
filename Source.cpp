#include <fstream>
#include <iostream>
#include <vector>
#include <cassert>
#include <regex>
#include <sstream>
#include <conio.h>

//TODO: Find way to get Windows / POSIX in #DEFINE statement

extern const char* operators[] = { "()", "==", "=", "+", "-", "*", "/", "||", "&&", };

void removeWhitespace(std::string& input)
{
	std::regex whitespace("[\\s]*");
	input = std::regex_replace(input, whitespace, "");
}

void quit()
{
	std::cout << "Press any key to exit...";
	while(!_kbhit() ){} // Windows only, find POSIX solution
	std::exit(-1);
}

int main(int argc, char* argv[])
{
	std::ifstream file{};
	file.open("test.cbr", std::ios_base::in);

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

	std::string line;
	std::getline(f, line, ';');
	std::cout << line;
}