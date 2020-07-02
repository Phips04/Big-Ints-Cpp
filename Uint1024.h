#pragma once

#include <string>
#include <bitset>

#include "BigIntsBase.h"

class Uint1024 : public BigIntsBase<Uint1024, 1024>
{
public:
    Uint1024();
    Uint1024(std::string Bits);
    Uint1024(std::bitset<1024> array);
    Uint1024(int Arg);
    Uint1024(uint64_t Arg);

#define UINT1024_MAX (Uint1024(std::bitset<1024>{}.set()));
#define UINT1024_MIN (Uint1024(std::bitset<1024>(0)));
};