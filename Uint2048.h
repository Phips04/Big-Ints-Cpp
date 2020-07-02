#pragma once

#include <string>
#include <bitset>

#include "BigIntsBase.h"

class Uint2048 : public BigIntsBase<Uint2048, 2048>
{
public:
    Uint2048();
    Uint2048(std::string Bits);
    Uint2048(std::bitset<2048> array);
    Uint2048(int Arg);
    Uint2048(uint64_t Arg);

#define UINT2048_MAX (Uint2048(std::bitset<2048>{}.set()));
#define UINT2048_MIN (Uint2048(std::bitset<2048>(0)));
};
