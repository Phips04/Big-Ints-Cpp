#pragma once

#include <bitset>
#include <string>
#include <initializer_list>
#include "uint128.h"

namespace BigInts
{
	namespace uint256
	{
		class uint256
		{
		private:
			std::bitset<256> data;
		public:
			//CONSTRUCTORS *** 1.0
			uint256();
			uint256(int32_t);
			uint256(uint32_t);
			uint256(int64_t);
			uint256(uint64_t);
			uint256(uint128::uint128);
			uint256(std::bitset<256>);
			uint256(std::string);

			//METHODS *** 2.0
			//Standard arithmetic methods *** 2.1
			uint256 add(uint64_t);
			uint256 add(uint256);
			uint256 add(std::initializer_list<uint256>);
			uint256 substract(uint64_t);
			uint256 substract(uint256);
			uint256 substract(std::initializer_list<uint256>);
			uint256 multiply(uint64_t);
			uint256 multiply(uint256);
			uint256 multiply(std::initializer_list<uint256>);
			uint256 divide(uint64_t);
			uint256 divide(uint256);
			uint256 divide(std::initializer_list<uint256>);

			//Extended arithmetic methods *** 2.2
			uint256 pow(uint64_t);
			uint256 pow(uint256);
			uint256 pow(std::initializer_list<uint256>);
			uint256 log(uint256);
			uint256 log10();
			uint256 sqrt();
			uint256 mod(uint256);

			//Additional methods
			int TryToInt();
			unsigned long TryToLong();
			uint64_t TryToUint64_t();
			uint128::uint128 TryToUInt128();
			std::string ToBinaryString();
			std::bitset<256> GetBinaryData();
			std::string DivisionAdaptedSubHelpFunction(std::string, std::string);

			//OPERATORS *** 3.0
			//Arithmetic operators *** 3.1
			uint256 operator + (uint64_t);
			uint256 operator + (uint256);
			uint256 operator - (uint64_t);
			uint256 operator - (uint256);
			uint256 operator * (uint64_t);
			uint256 operator * (uint256);
			uint256 operator / (uint64_t);
			uint256 operator / (uint256);

			//Shorten arithmetic operators *** 3.2
			void operator += (uint64_t);
			void operator += (uint256);
			void operator -= (uint64_t);
			void operator -= (uint256);
			void operator *= (uint64_t);
			void operator *= (uint256);
			void operator /= (uint64_t);
			void operator /= (uint256);

			//Extended arithmetic operators *** 3.3
			uint256 operator ++();
			uint256 operator --();
			uint256 operator % (uint256);

			//Extended shorten arithmetic operators *** 3.4
			void operator %= (uint256);

			//Comparsion operators *** 3.5
			bool operator == (uint256);
			bool operator < (uint256);
			bool operator > (uint256);
			bool operator <= (uint256);
			bool operator >= (uint256);
			bool operator != (uint256);
		};

		//4.0 Makro's
		#define UINT256_MIN BigInts::uint256::uint256(std::bitset<256>(0))
		#define UINT256_MAX BigInts::uint256::uint256(std::bitset<256>{}.set())

		//5.0 EXTERNAL ITEMS
		//5.1 Global operator overloads
		std::ostream& operator << (std::ostream& os, uint256);

		//5.2 Free functions
		uint256 pow(uint256, uint256);
		uint256 pow(uint256, uint64_t);
		uint256 mod(uint256, uint256);
		uint256 mod(uint256, uint64_t);
		uint256 log(uint256, uint256);
		uint256 log(uint64_t, uint256);
		uint256 log10(uint256);
		uint256 sqrt(uint256);
	}
}

