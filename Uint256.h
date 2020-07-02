#pragma once

#include <string>
#include <bitset>

#include "BigIntsBase.h"

class Uint256 : public BigIntsBase<Uint256, 256>
{
public:
    Uint256();
    Uint256(std::string Bits);
    Uint256(std::bitset<256> array);
    Uint256(int Arg);
    Uint256(uint64_t Arg);

#define UINT256_MAX (Uint256(std::bitset<256>{}.set()));
#define UINT256_MIN (Uint256(std::bitset<256>(0)));
};