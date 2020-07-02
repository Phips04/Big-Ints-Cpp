#include "Uint512.h"

Uint512::Uint512() : BigIntsBase() {}
Uint512::Uint512(std::string Bits) : BigIntsBase(Bits) {}
Uint512::Uint512(std::bitset<512> array) : BigIntsBase(array) {}
Uint512::Uint512(int Arg) : BigIntsBase(Arg) {}
Uint512::Uint512(uint64_t Arg) : BigIntsBase(Arg) {}