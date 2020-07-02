#include "Uint16384.h"

Uint16384::Uint16384() : BigIntsBase() {}
Uint16384::Uint16384(std::string Bits) : BigIntsBase(Bits) {}
Uint16384::Uint16384(std::bitset<16384> array) : BigIntsBase(array) {}
Uint16384::Uint16384(int Arg) : BigIntsBase(Arg) {}
Uint16384::Uint16384(uint64_t Arg) : BigIntsBase(Arg) {}
