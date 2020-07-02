#pragma once

#include <string>
#include <bitset>

#include "BigIntsBase.h"

class Uint16384 : public BigIntsBase<Uint16384, 16384>
{
public:
    Uint16384();
    Uint16384(std::string Bits);
    Uint16384(std::bitset<16384> array);
    Uint16384(int Arg);
    Uint16384(uint64_t Arg);

#define UINT16384_MAX (Uint16384(std::bitset<16384>{}.set()));
#define UINT16384_MIN (Uint16384(std::bitset<16384>(0)));
};
