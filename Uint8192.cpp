#include "Uint8192.h"

Uint8192::Uint8192() : BigIntsBase() {}
Uint8192::Uint8192(std::string Bits) : BigIntsBase(Bits) {}
Uint8192::Uint8192(std::bitset<8192> array) : BigIntsBase(array) {}
Uint8192::Uint8192(int Arg) : BigIntsBase(Arg) {}
Uint8192::Uint8192(uint64_t Arg) : BigIntsBase(Arg) {}