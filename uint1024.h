#pragma once

#include "uint128.h"
#include "uint256.h"
#include "uint512.h"

#include <bitset>
#include <string>
#include <initializer_list>

namespace BigInts
{
	namespace uint1024
	{
		class uint1024
		{
		private:
			std::bitset<1024> data;
		public:
			//CONSTRUCTORS *** 1.0
			uint1024();
			uint1024(int32_t);
			uint1024(uint32_t);
			uint1024(int64_t);
			uint1024(uint64_t);
			uint1024(uint128::uint128);
			uint1024(uint256::uint256);
			uint1024(uint512::uint512);
			uint1024(std::bitset<1024>);
			uint1024(std::string);

			//METHODS *** 2.0
			//Standard arithmetic methods *** 2.1
			uint1024 add(uint64_t);
			uint1024 add(uint1024);
			uint1024 add(std::initializer_list<uint1024>);
			uint1024 substract(uint64_t);
			uint1024 substract(uint1024);
			uint1024 substract(std::initializer_list<uint1024>);
			uint1024 multiply(uint64_t);
			uint1024 multiply(uint1024);
			uint1024 multiply(std::initializer_list<uint1024>);
			uint1024 divide(uint64_t);
			uint1024 divide(uint1024);
			uint1024 divide(std::initializer_list<uint1024>);

			//Extended arithmetic methods *** 2.2
			uint1024 pow(uint64_t);
			uint1024 pow(uint1024);
			uint1024 pow(std::initializer_list<uint1024>);
			uint1024 log(uint1024);
			uint1024 log10();
			uint1024 sqrt();
			uint1024 mod(uint1024);

			//Additional methods
			int TryToInt();
			unsigned long TryToLong();
			uint64_t TryToUint64_t();
			uint128::uint128 TryToUint128();
			uint256::uint256 TryToUint256();
			uint512::uint512 TryToUint512();
			std::string ToBinaryString();
			std::bitset<1024> GetBinaryData();
			std::string DivisionAdaptedSubHelpFunction(std::string, std::string);

			//OPERATORS *** 3.0
			//Arithmetic operators *** 3.1
			uint1024 operator + (uint64_t);
			uint1024 operator + (uint1024);
			uint1024 operator - (uint64_t);
			uint1024 operator - (uint1024);
			uint1024 operator * (uint64_t);
			uint1024 operator * (uint1024);
			uint1024 operator / (uint64_t);
			uint1024 operator / (uint1024);

			//Shorten arithmetic operators *** 3.2
			void operator += (uint64_t);
			void operator += (uint1024);
			void operator -= (uint64_t);
			void operator -= (uint1024);
			void operator *= (uint64_t);
			void operator *= (uint1024);
			void operator /= (uint64_t);
			void operator /= (uint1024);

			//Extended arithmetic operators *** 3.3
			uint1024 operator ++();
			uint1024 operator --();
			uint1024 operator % (uint1024);

			//Extended shorten arithmetic operators *** 3.4
			void operator %= (uint1024);

			//Comparsion operators *** 3.5
			bool operator == (uint1024);
			bool operator < (uint1024);
			bool operator > (uint1024);
			bool operator <= (uint1024);
			bool operator >= (uint1024);
			bool operator != (uint1024);
		};

		//4.0 Makro's
		#define UINT1024_MIN BigInts::uint1024::uint1024(std::bitset<1024>(0))
		#define UINT1024_MAX BigInts::uint1024::uint1024(std::bitset<1024>{}.set())

		//5.0 EXTERNAL ITEMS
		//5.1 Global operator overloads
		std::ostream& operator << (std::ostream& os, uint1024);

		//5.2 Free functions
		uint1024 pow(uint1024, uint1024);
		uint1024 pow(uint1024, uint64_t);
		uint1024 mod(uint1024, uint1024);
		uint1024 mod(uint1024, uint64_t);
		uint1024 log(uint1024, uint1024);
		uint1024 log(uint64_t, uint1024);
		uint1024 log10(uint1024);
		uint1024 sqrt(uint1024);
	}
}