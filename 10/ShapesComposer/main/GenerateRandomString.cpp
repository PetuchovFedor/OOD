#include "GenerateRandomString.h"

std::string GenerateRandomString()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> dist('a', 'z');
    std::string rndStr(6, ' ');
    for (auto& ch : rndStr)
    {
        ch = dist(rng);
    }
    return rndStr;
}
