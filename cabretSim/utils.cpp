#include "utils.h"

int utils::getBits(uint8_t x, int l, int h)
{
    x &= ((int)std::pow(2, h) - 1); // bit mask all bits higher than h-th bit
    x >>= l; // shift out bits lower than l-th bit
    return x;
}

void utils::memoryDump(uint8_t pc, std::array<uint8_t, 4> R, std::array<uint8_t, 256> M)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // How about a little color?

    std::cout << "Registers: \n|| ";
    for (int i = 0; i < 4; i++)
    {
        std::cout << "r" << i << ": " << utils::toHex(R[i]) << " || ";
    }
    std::cout << '\n';

    std::cout << "Memory: \n     ";
    for (int i = 0; i < 16; i++)
    {
        std::cout << utils::toHexShort(i) << " ";
    }

    std::cout << "\n   +------------------------------------------------\n";

    for (int i = 0; i < 16; i++)
    {
        std::cout << utils::toHexShort(i * 16) << " | ";
        for (int j = 0; j < 16; j++)
        {
            if (j + (16 * i) == pc)
            {
                SetConsoleTextAttribute(hConsole, 0x1F);
            }
            if (j + (16 * i) - 1 == pc && utils::getBits(M[pc], 4, 7) == 6)
            {
                SetConsoleTextAttribute(hConsole, 0x4F);
            }
            if ((j + (16 * i) - 1 == pc && utils::getBits(M[pc], 4, 7) != 6) ||
                (j + (16 * i) - 2 == pc && utils::getBits(M[pc], 4, 7) == 6))
            {
                SetConsoleTextAttribute(hConsole, 0xdF);
            }
            std::cout << utils::toHexShort(M[j + (16 * i)]);
            SetConsoleTextAttribute(hConsole, 0x0F);
            std::cout << ' ';
        }
        std::cout << '\n';
    }
    std::cout << "\n\n\n\n\n";
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
