#include "Uint1024.h"

Uint1024::Uint1024() : BigIntsBase() {}
Uint1024::Uint1024(std::string Bits) : BigIntsBase(Bits) {}
Uint1024::Uint1024(std::bitset<1024> array) : BigIntsBase(array) {}
Uint1024::Uint1024(int Arg) : BigIntsBase(Arg) {}
Uint1024::Uint1024(uint64_t Arg) : BigIntsBase(Arg) {}