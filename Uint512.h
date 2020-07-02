#pragma once

#include <string>
#include <bitset>

#include "BigIntsBase.h"

class Uint512 : public BigIntsBase<Uint512, 512>
{
public:
    Uint512();
    Uint512(std::string Bits);
    Uint512(std::bitset<512> array);
    Uint512(int Arg);
    Uint512(uint64_t Arg);

#define UINT512_MAX (Uint512(std::bitset<512>{}.set()));
#define UINT512_MIN (Uint512(std::bitset<512>(0)));
};

