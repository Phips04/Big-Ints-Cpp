#pragma once

#include "uint128.h"
#include "uint256.h"
#include "uint512.h"
#include "uint1024.h"

#include <bitset>
#include <string>
#include <initializer_list>

namespace BigInts
{
	namespace uint2048
	{
		class uint2048
		{
		private:
			std::bitset<2048> data;
		public:
			//CONSTRUCTORS *** 1.0
			uint2048();
			uint2048(int32_t);
			uint2048(uint32_t);
			uint2048(int64_t);
			uint2048(uint64_t);
			uint2048(uint128::uint128);
			uint2048(uint256::uint256);
			uint2048(uint512::uint512);
			uint2048(uint1024::uint1024);
			uint2048(std::bitset<2048>);
			uint2048(std::string);

			//METHODS *** 2.0
			//Standard arithmetic methods *** 2.1
			uint2048 add(uint64_t);
			uint2048 add(uint2048);
			uint2048 add(std::initializer_list<uint2048>);
			uint2048 substract(uint64_t);
			uint2048 substract(uint2048);
			uint2048 substract(std::initializer_list<uint2048>);
			uint2048 multiply(uint64_t);
			uint2048 multiply(uint2048);
			uint2048 multiply(std::initializer_list<uint2048>);
			uint2048 divide(uint64_t);
			uint2048 divide(uint2048);
			uint2048 divide(std::initializer_list<uint2048>);

			//Extended arithmetic methods *** 2.2
			uint2048 pow(uint64_t);
			uint2048 pow(uint2048);
			uint2048 pow(std::initializer_list<uint2048>);
			uint2048 log(uint2048);
			uint2048 log10();
			uint2048 sqrt();
			uint2048 mod(uint2048);

			//Additional methods
			int TryToInt();
			unsigned long TryToLong();
			uint64_t TryToUint64_t();
			uint128::uint128 TryToUint128();
			uint256::uint256 TryToUint256();
			uint512::uint512 TryToUint512();
			uint1024::uint1024 TryToUint1024();
			std::string ToBinaryString();
			std::bitset<2048> GetBinaryData();
			std::string DivisionAdaptedSubHelpFunction(std::string, std::string);

			//OPERATORS *** 3.0
			//Arithmetic operators *** 3.1
			uint2048 operator + (uint64_t);
			uint2048 operator + (uint2048);
			uint2048 operator - (uint64_t);
			uint2048 operator - (uint2048);
			uint2048 operator * (uint64_t);
			uint2048 operator * (uint2048);
			uint2048 operator / (uint64_t);
			uint2048 operator / (uint2048);

			//Shorten arithmetic operators *** 3.2
			void operator += (uint64_t);
			void operator += (uint2048);
			void operator -= (uint64_t);
			void operator -= (uint2048);
			void operator *= (uint64_t);
			void operator *= (uint2048);
			void operator /= (uint64_t);
			void operator /= (uint2048);

			//Extended arithmetic operators *** 3.3
			uint2048 operator ++();
			uint2048 operator --();
			uint2048 operator % (uint2048);

			//Extended shorten arithmetic operators *** 3.4
			void operator %= (uint2048);

			//Comparsion operators *** 3.5
			bool operator == (uint2048);
			bool operator < (uint2048);
			bool operator > (uint2048);
			bool operator <= (uint2048);
			bool operator >= (uint2048);
			bool operator != (uint2048);
		};

		//4.0 Makro's
		#define UINT2048_MIN BigInts::uint2048::uint2048(std::bitset<2048>(0))
		#define UINT2048_MAX BigInts::uint2048::uint2048(std::bitset<2048>{}.set())

		//5.0 EXTERNAL ITEMS
		//5.1 Global operator overloads
		std::ostream& operator << (std::ostream& os, uint2048);

		//5.2 Free functions
		uint2048 pow(uint2048, uint2048);
		uint2048 pow(uint2048, uint64_t);
		uint2048 mod(uint2048, uint2048);
		uint2048 mod(uint2048, uint64_t);
		uint2048 log(uint2048, uint2048);
		uint2048 log(uint64_t, uint2048);
		uint2048 log10(uint2048);
		uint2048 sqrt(uint2048);
	}
}