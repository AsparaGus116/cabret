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

	while (1)
	{
		std::cout << "How many steps would you like to go? (-1 to run until halt) \n>> ";
		int x;
		std::cin >> x;

		for (int z = 0; z < (uint32_t)x; z++) // if x == -1, run a VERY long number of steps (usually until halt or end of memory)
		{
			int opcode = utils::getBits(M[pc], 4, 7);
			int a = utils::getBits(M[pc], 2, 4);
			int b = utils::getBits(M[pc], 0, 2);

			if (pc > 0xff || (pc == 0xff && opcode == 6))
			{
				return 0;
			}

			if (M[pc] & 0x80) // reserved bit is set
			{
				// Halt
				return 0;
			}

			switch (opcode)
			{
			case 0:
				R[a] = R[b];
				++pc;
				break;
			case 1:
				R[a] += R[b];
				++pc;
				break;
			case 2:
				R[a] &= R[b];
				++pc;
				break;
			case 3:
				R[a] = M[R[b]];
				++pc;
				break;
			case 4:
				M[R[b]] = R[a];
				++pc;
				break;
			case 5:
				switch (b)
				{
				case 0:
					R[a] = ~R[a];
					++pc;
					break;
				case 1:
					R[a] = -R[a];
					++pc;
					break;
				case 2:
					R[a] = !R[a];
					++pc;
					break;
				case 3:
					R[a] = pc;
					++pc;
					break;
				}
				break;
			case 6:
				switch (b)
				{
				case 0:
					R[a] = M[pc + 1];
					pc += 2;
					break;
				case 1:
					R[a] += M[pc + 1];
					pc += 2;
					break;
				case 2:
					R[a] &= M[pc + 1];
					pc += 2;
					break;
				case 3:
					R[a] = M[M[pc + 1]];
					pc += 2;
					break;
				}
				break;
			case 7:
				if (R[a] & 0x80 || R[a] == 0) // LE 0
				{
					pc = R[b];
				}
				else
				{
					++pc;
				}
				break;
			}
			utils::memoryDump(pc, R, M);
		}
	}
	
}