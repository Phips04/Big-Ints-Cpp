#pragma once

#include <string>
#include <bitset>

#include "BigIntsBase.h"

class Uint128 : public BigIntsBase<Uint128, 128>
{
public:
    Uint128();
    Uint128(std::string Bits);
    Uint128(std::bitset<128> array);
    Uint128(int Arg);
    Uint128(uint64_t Arg);

    #define UINT128_MAX (Uint128(std::bitset<128>{}.set()));
    #define UINT128_MIN (Uint128(std::bitset<128>(0)));
};
