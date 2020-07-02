#pragma once

#include <string>
#include <bitset>

#include "BigIntsBase.h"

class Uint8192 : public BigIntsBase<Uint8192, 8192>
{
public:
    Uint8192();
    Uint8192(std::string Bits);
    Uint8192(std::bitset<8192> array);
    Uint8192(int Arg);
    Uint8192(uint64_t Arg);

#define UINT8192_MAX (Uint8192(std::bitset<8192>{}.set()));
#define UINT8192_MIN (Uint8192(std::bitset<8192>(0)));
};