#include <array>
#include <iostream>
#include <fstream>
#include "utils.h"
std::array<uint8_t, 4> R; // Registers
std::array<uint8_t, 256> M; // Memory array

int pc; // Program counter
int main(int argc, char* argv[])
{
	std::ifstream file;

	pc = 0;
	if (argc >= 2) // File input
	{
		file.open(argv[1], std::ios::in);
	}
	else
	{
		std::string filename;
		std::cout << "Enter filename: " << "\n>> ";
		std::cin >> filename;
		file.open(filename);
	}

	if (!file.good())
	{
		std::cout << "ERR: Invalid file\n";
		return -1;
	}


	while (!file.eof())
	{
		std::string in;
		file >> in;
		M[pc] = utils::fromHex(in);
		++pc;
	}
	
	pc = 0;
	
}