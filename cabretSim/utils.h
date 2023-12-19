#pragma once

#include <cmath>
#include <array>
#include <iostream>
#include <string>

namespace utils
{
	int getBits(uint8_t x, int l, int h); // treats a range of bits as its own number and converts to decimal
	// ^^ takes form [l, h), i.e. [4, 7)

	void memoryDump(uint8_t pc, std::array<uint8_t, 4> R, std::array<uint8_t, 256> M); // Prints registers, memory, current, and next instruction

	std::string toHex(uint8_t x);

	std::string toHexShort(uint8_t x); // Prints hex value without leading "0x"

	uint8_t fromHex(std::string s);
}

