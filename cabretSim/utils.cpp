#include "utils.h"

int utils::getBits(uint8_t x, int l, int h)
{
    x &= ((int)std::pow(2, h) - 1); // bit mask all bits higher than h-th bit
    x >>= l; // shift out bits lower than l-th bit
    return x;
}
std::string utils::toHex(uint8_t x)
{
    std::string res = "0x";
    return res + toHexShort(x);

}

std::string utils::toHexShort(uint8_t x)
{
    std::string res = "";
    char c = x % 16 + '0';
    x /= 16;
    char d = x % 16 + '0';
    if (c > '9')
    {
        c += 7; // Ascii table magic
    }
    if (d > '9')
    {
        d += 7;
    }
    res += d;
    res += c;
    return res;
}

uint8_t utils::fromHex(std::string s)
{
    int a;
    int b;
    if (s.size() == 4) // 0xab format
    {
        a = s[2];
        b = s[3];
    }
    else if (s.size() == 2) // ab format
    {
        a = s[0];
        b = s[1];
    }

    if (a > '9')
    {
        a -= 7;
    }
    if (b > '9')
    {
        b -= 7;
    }
    a -= '0';
    b -= '0';

    return (uint8_t)(a * 16 + b);
}
