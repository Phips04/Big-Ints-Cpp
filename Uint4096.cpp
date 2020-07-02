#include "Uint4096.h"

Uint4096::Uint4096() : BigIntsBase() {}
Uint4096::Uint4096(std::string Bits) : BigIntsBase(Bits) {}
Uint4096::Uint4096(std::bitset<4096> array) : BigIntsBase(array) {}
Uint4096::Uint4096(int Arg) : BigIntsBase(Arg) {}
Uint4096::Uint4096(uint64_t Arg) : BigIntsBase(Arg) {}