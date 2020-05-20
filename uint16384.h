#pragma once

#include "uint128.h"
#include "uint256.h"
#include "uint512.h"
#include "uint1024.h"
#include "uint2048.h"
#include "uint4096.h"
#include "uint8192.h"

#include <bitset>
#include <string>
#include <initializer_list>

namespace BigInts
{
	namespace uint16384
	{
		class uint16384
		{
		private:
			std::bitset<16384> data;
		public:
			//CONSTRUCTORS *** 1.0
			uint16384();
			uint16384(int32_t);
			uint16384(uint32_t);
			uint16384(int64_t);
			uint16384(uint64_t);
			uint16384(uint128::uint128);
			uint16384(uint256::uint256);
			uint16384(uint512::uint512);
			uint16384(uint1024::uint1024);
			uint16384(uint2048::uint2048);
			uint16384(uint4096::uint4096);
			uint16384(uint8192::uint8192);
			uint16384(std::bitset<16384>);
			uint16384(std::string);

			//METHODS *** 2.0
			//Standard arithmetic methods *** 2.1
			uint16384 add(uint64_t);
			uint16384 add(uint16384);
			uint16384 add(std::initializer_list<uint16384>);
			uint16384 substract(uint64_t);
			uint16384 substract(uint16384);
			uint16384 substract(std::initializer_list<uint16384>);
			uint16384 multiply(uint64_t);
			uint16384 multiply(uint16384);
			uint16384 multiply(std::initializer_list<uint16384>);
			uint16384 divide(uint64_t);
			uint16384 divide(uint16384);
			uint16384 divide(std::initializer_list<uint16384>);

			//Extended arithmetic methods *** 2.2
			uint16384 pow(uint64_t);
			uint16384 pow(uint16384);
			uint16384 pow(std::initializer_list<uint16384>);
			uint16384 log(uint16384);
			uint16384 log10();
			uint16384 sqrt();
			uint16384 mod(uint16384);

			//Additional methods
			int TryToInt();
			unsigned long TryToLong();
			uint64_t TryToUint64_t();
			uint128::uint128 TryToUint128();
			uint256::uint256 TryToUint256();
			uint512::uint512 TryToUint512();
			uint1024::uint1024 TryToUint1024();
			uint2048::uint2048 TryToUint2048();
			uint4096::uint4096 TryToUint4096();
			uint8192::uint8192 TryToUint8192();
			std::string ToBinaryString();
			std::bitset<16384> GetBinaryData();
			std::string DivisionAdaptedSubHelpFunction(std::string, std::string);

			//OPERATORS *** 3.0
			//Arithmetic operators *** 3.1
			uint16384 operator + (uint64_t);
			uint16384 operator + (uint16384);
			uint16384 operator - (uint64_t);
			uint16384 operator - (uint16384);
			uint16384 operator * (uint64_t);
			uint16384 operator * (uint16384);
			uint16384 operator / (uint64_t);
			uint16384 operator / (uint16384);

			//Shorten arithmetic operators *** 3.2
			void operator += (uint64_t);
			void operator += (uint16384);
			void operator -= (uint64_t);
			void operator -= (uint16384);
			void operator *= (uint64_t);
			void operator *= (uint16384);
			void operator /= (uint64_t);
			void operator /= (uint16384);

			//Extended arithmetic operators *** 3.3
			uint16384 operator ++();
			uint16384 operator --();
			uint16384 operator % (uint16384);

			//Extended shorten arithmetic operators *** 3.4
			void operator %= (uint16384);

			//Comparsion operators *** 3.5
			bool operator == (uint16384);
			bool operator < (uint16384);
			bool operator > (uint16384);
			bool operator <= (uint16384);
			bool operator >= (uint16384);
			bool operator != (uint16384);
		};

		//4.0 Makro's
		#define UINT16384_MIN BigInts::uint16384::uint16384(std::bitset<16384>(0))
		#define UINT16384_MAX BigInts::uint16384::uint16384(std::bitset<16384>{}.set())

		//5.0 EXTERNAL ITEMS
		//5.1 Global operator overloads
		std::ostream& operator << (std::ostream& os, uint16384);

		//5.2 Free functions
		uint16384 pow(uint16384, uint16384);
		uint16384 pow(uint16384, uint64_t);
		uint16384 mod(uint16384, uint16384);
		uint16384 mod(uint16384, uint64_t);
		uint16384 log(uint16384, uint16384);
		uint16384 log(uint64_t, uint16384);
		uint16384 log10(uint16384);
		uint16384 sqrt(uint16384);
	}
}