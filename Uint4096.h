#pragma once

#include <string>
#include <bitset>

#include "BigIntsBase.h"

class Uint4096 : public BigIntsBase<Uint4096, 4096>
{
public:
    Uint4096();
    Uint4096(std::string Bits);
    Uint4096(std::bitset<4096> array);
    Uint4096(int Arg);
    Uint4096(uint64_t Arg);

#define UINT4096_MAX (Uint4096(std::bitset<4096>{}.set()));
#define UINT4096_MIN (Uint4096(std::bitset<4096>(0)));
};
