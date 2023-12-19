#include <iostream>
#include <string>

namespace utils
{
	std::string toHex(uint8_t x);

	std::string toHexShort(uint8_t x); // Prints hex value without leading "0x"

	uint8_t fromHex(std::string s);
}
