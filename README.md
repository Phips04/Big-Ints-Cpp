# Big-Ints-Cpp
Use unsigned integers providing 128, 256, 512, ..., 16384 bits of memory, written in standard C++

Types for big integers based on bit arrays providing up to 16384 bits, in standard C++

The given types provide access to eight different types for calculations with extremly large natural numbers.
Types are Uint128, ...256, ...512, ..., Uint16384. Because of the base class witch holds nearly every important item,
its very easy to extend the existing types using your own classes. At least constructors and macros must be included.

Exrensive computations might have a massive impact on performance.
Mostly affected are:

*Square root
*Logarithm
*Division

This mainly depends on time expensive conversions to std::string during the process of division.
Finding the logarithm requires Log2(Log2(Max value of type)) computations. e.g. Uint1024 => 10

Sqrt requires Log2(Sqrt(Max value of type)) computations. e.g. Uint8192 => 91

A corresponding library for .NET core exists, written in C#
