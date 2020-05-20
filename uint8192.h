#pragma once

#include "uint128.h"
#include "uint256.h"
#include "uint512.h"
#include "uint1024.h"
#include "uint2048.h"
#include "uint4096.h"

#include <bitset>
#include <string>
#include <initializer_list>

namespace BigInts
{
	namespace uint8192
	{
		class uint8192
		{
		private:
			std::bitset<8192> data;
		public:
			//CONSTRUCTORS *** 1.0
			uint8192();
			uint8192(int32_t);
			uint8192(uint32_t);
			uint8192(int64_t);
			uint8192(uint64_t);
			uint8192(uint128::uint128);
			uint8192(uint256::uint256);
			uint8192(uint512::uint512);
			uint8192(uint1024::uint1024);
			uint8192(uint2048::uint2048);
			uint8192(uint4096::uint4096);
			uint8192(std::bitset<8192>);
			uint8192(std::string);

			//METHODS *** 2.0
			//Standard arithmetic methods *** 2.1
			uint8192 add(uint64_t);
			uint8192 add(uint8192);
			uint8192 add(std::initializer_list<uint8192>);
			uint8192 substract(uint64_t);
			uint8192 substract(uint8192);
			uint8192 substract(std::initializer_list<uint8192>);
			uint8192 multiply(uint64_t);
			uint8192 multiply(uint8192);
			uint8192 multiply(std::initializer_list<uint8192>);
			uint8192 divide(uint64_t);
			uint8192 divide(uint8192);
			uint8192 divide(std::initializer_list<uint8192>);

			//Extended arithmetic methods *** 2.2
			uint8192 pow(uint64_t);
			uint8192 pow(uint8192);
			uint8192 pow(std::initializer_list<uint8192>);
			uint8192 log(uint8192);
			uint8192 log10();
			uint8192 sqrt();
			uint8192 mod(uint8192);

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
			std::string ToBinaryString();
			std::bitset<8192> GetBinaryData();
			std::string DivisionAdaptedSubHelpFunction(std::string, std::string);

			//OPERATORS *** 3.0
			//Arithmetic operators *** 3.1
			uint8192 operator + (uint64_t);
			uint8192 operator + (uint8192);
			uint8192 operator - (uint64_t);
			uint8192 operator - (uint8192);
			uint8192 operator * (uint64_t);
			uint8192 operator * (uint8192);
			uint8192 operator / (uint64_t);
			uint8192 operator / (uint8192);

			//Shorten arithmetic operators *** 3.2
			void operator += (uint64_t);
			void operator += (uint8192);
			void operator -= (uint64_t);
			void operator -= (uint8192);
			void operator *= (uint64_t);
			void operator *= (uint8192);
			void operator /= (uint64_t);
			void operator /= (uint8192);

			//Extended arithmetic operators *** 3.3
			uint8192 operator ++();
			uint8192 operator --();
			uint8192 operator % (uint8192);

			//Extended shorten arithmetic operators *** 3.4
			void operator %= (uint8192);

			//Comparsion operators *** 3.5
			bool operator == (uint8192);
			bool operator < (uint8192);
			bool operator > (uint8192);
			bool operator <= (uint8192);
			bool operator >= (uint8192);
			bool operator != (uint8192);
		};

		//4.0 Makro's
		#define UINT8192_MIN BigInts::uint8192::uint8192(std::bitset<8192>(0))
		#define UINT8192_MAX BigInts::uint8192::uint8192(std::bitset<8192>{}.set())

		//5.0 EXTERNAL ITEMS
		//5.1 Global operator overloads
		std::ostream& operator << (std::ostream& os, uint8192);

		//5.2 Free functions
		uint8192 pow(uint8192, uint8192);
		uint8192 pow(uint8192, uint64_t);
		uint8192 mod(uint8192, uint8192);
		uint8192 mod(uint8192, uint64_t);
		uint8192 log(uint8192, uint8192);
		uint8192 log(uint64_t, uint8192);
		uint8192 log10(uint8192);
		uint8192 sqrt(uint8192);
	}
}