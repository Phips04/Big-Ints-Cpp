#include "Uint128.h"

Uint128::Uint128() : BigIntsBase() {}
Uint128::Uint128(std::string Bits) : BigIntsBase(Bits) {}
Uint128::Uint128(std::bitset<128> array) : BigIntsBase(array) {}
Uint128::Uint128(int Arg) : BigIntsBase(Arg) {}
Uint128::Uint128(uint64_t Arg) : BigIntsBase(Arg) {}
