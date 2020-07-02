#include "Uint256.h"

Uint256::Uint256() : BigIntsBase() {}
Uint256::Uint256(std::string Bits) : BigIntsBase(Bits) {}
Uint256::Uint256(std::bitset<256> array) : BigIntsBase(array) {}
Uint256::Uint256(int Arg) : BigIntsBase(Arg) {}
Uint256::Uint256(uint64_t Arg) : BigIntsBase(Arg) {}
