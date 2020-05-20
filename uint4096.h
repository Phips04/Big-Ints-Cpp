#pragma once

#include "uint128.h"
#include "uint256.h"
#include "uint512.h"
#include "uint1024.h"
#include "uint2048.h"

#include <bitset>
#include <string>
#include <initializer_list>

namespace BigInts
{
	namespace uint4096
	{
		class uint4096
		{
		private:
			std::bitset<4096> data;
		public:
			//CONSTRUCTORS *** 1.0
			uint4096();
			uint4096(int32_t);
			uint4096(uint32_t);
			uint4096(int64_t);
			uint4096(uint64_t);
			uint4096(uint128::uint128);
			uint4096(uint256::uint256);
			uint4096(uint512::uint512);
			uint4096(uint1024::uint1024);
			uint4096(uint2048::uint2048);
			uint4096(std::bitset<4096>);
			uint4096(std::string);

			//METHODS *** 2.0
			//Standard arithmetic methods *** 2.1
			uint4096 add(uint64_t);
			uint4096 add(uint4096);
			uint4096 add(std::initializer_list<uint4096>);
			uint4096 substract(uint64_t);
			uint4096 substract(uint4096);
			uint4096 substract(std::initializer_list<uint4096>);
			uint4096 multiply(uint64_t);
			uint4096 multiply(uint4096);
			uint4096 multiply(std::initializer_list<uint4096>);
			uint4096 divide(uint64_t);
			uint4096 divide(uint4096);
			uint4096 divide(std::initializer_list<uint4096>);

			//Extended arithmetic methods *** 2.2
			uint4096 pow(uint64_t);
			uint4096 pow(uint4096);
			uint4096 pow(std::initializer_list<uint4096>);
			uint4096 log(uint4096);
			uint4096 log10();
			uint4096 sqrt();
			uint4096 mod(uint4096);

			//Additional methods
			int TryToInt();
			unsigned long TryToLong();
			uint64_t TryToUint64_t();
			uint128::uint128 TryToUint128();
			uint256::uint256 TryToUint256();
			uint512::uint512 TryToUint512();
			uint1024::uint1024 TryToUint1024();
			uint2048::uint2048 TryToUint2048();
			std::string ToBinaryString();
			std::bitset<4096> GetBinaryData();
			std::string DivisionAdaptedSubHelpFunction(std::string, std::string);

			//OPERATORS *** 3.0
			//Arithmetic operators *** 3.1
			uint4096 operator + (uint64_t);
			uint4096 operator + (uint4096);
			uint4096 operator - (uint64_t);
			uint4096 operator - (uint4096);
			uint4096 operator * (uint64_t);
			uint4096 operator * (uint4096);
			uint4096 operator / (uint64_t);
			uint4096 operator / (uint4096);

			//Shorten arithmetic operators *** 3.2
			void operator += (uint64_t);
			void operator += (uint4096);
			void operator -= (uint64_t);
			void operator -= (uint4096);
			void operator *= (uint64_t);
			void operator *= (uint4096);
			void operator /= (uint64_t);
			void operator /= (uint4096);

			//Extended arithmetic operators *** 3.3
			uint4096 operator ++();
			uint4096 operator --();
			uint4096 operator % (uint4096);

			//Extended shorten arithmetic operators *** 3.4
			void operator %= (uint4096);

			//Comparsion operators *** 3.5
			bool operator == (uint4096);
			bool operator < (uint4096);
			bool operator > (uint4096);
			bool operator <= (uint4096);
			bool operator >= (uint4096);
			bool operator != (uint4096);
		};

		//4.0 Makro's
		#define UINT4096_MIN BigInts::uint4096::uint4096(std::bitset<4096>(0))
		#define UINT4096_MAX BigInts::uint4096::uint4096(std::bitset<4096>{}.set())

		//5.0 EXTERNAL ITEMS
		//5.1 Global operator overloads
		std::ostream& operator << (std::ostream& os, uint4096);

		//5.2 Free functions
		uint4096 pow(uint4096, uint4096);
		uint4096 pow(uint4096, uint64_t);
		uint4096 mod(uint4096, uint4096);
		uint4096 mod(uint4096, uint64_t);
		uint4096 log(uint4096, uint4096);
		uint4096 log(uint64_t, uint4096);
		uint4096 log10(uint4096);
		uint4096 sqrt(uint4096);
	}
}