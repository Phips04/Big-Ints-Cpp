#include "Uint2048.h"

Uint2048::Uint2048() : BigIntsBase() {}
Uint2048::Uint2048(std::string Bits) : BigIntsBase(Bits) {}
Uint2048::Uint2048(std::bitset<2048> array) : BigIntsBase(array) {}
Uint2048::Uint2048(int Arg) : BigIntsBase(Arg) {}
Uint2048::Uint2048(uint64_t Arg) : BigIntsBase(Arg) {}