#pragma once

#include "uint128.h"
#include "uint256.h"

#include <bitset>
#include <string>
#include <initializer_list>

namespace BigInts
{
	namespace uint512
	{
		class uint512
		{
		private:
			std::bitset<512> data;
		public:
			//CONSTRUCTORS *** 1.0
			uint512();
			uint512(int32_t);
			uint512(uint32_t);
			uint512(int64_t);
			uint512(uint64_t);
			uint512(uint128::uint128);
			uint512(uint256::uint256);
			uint512(std::bitset<512>);
			uint512(std::string);

			//METHODS *** 2.0
			//Standard arithmetic methods *** 2.1
			uint512 add(uint64_t);
			uint512 add(uint512);
			uint512 add(std::initializer_list<uint512>);
			uint512 substract(uint64_t);
			uint512 substract(uint512);
			uint512 substract(std::initializer_list<uint512>);
			uint512 multiply(uint64_t);
			uint512 multiply(uint512);
			uint512 multiply(std::initializer_list<uint512>);
			uint512 divide(uint64_t);
			uint512 divide(uint512);
			uint512 divide(std::initializer_list<uint512>);

			//Extended arithmetic methods *** 2.2
			uint512 pow(uint64_t);
			uint512 pow(uint512);
			uint512 pow(std::initializer_list<uint512>);
			uint512 log(uint512);
			uint512 log10();
			uint512 sqrt();
			uint512 mod(uint512);

			//Additional methods
			int TryToInt();
			unsigned long TryToLong();
			uint64_t TryToUint64_t();
			uint128::uint128 TryToUint128();
			uint256::uint256 TryToUint256();
			std::string ToBinaryString();
			std::bitset<512> GetBinaryData();
			std::string DivisionAdaptedSubHelpFunction(std::string, std::string);

			//OPERATORS *** 3.0
			//Arithmetic operators *** 3.1
			uint512 operator + (uint64_t);
			uint512 operator + (uint512);
			uint512 operator - (uint64_t);
			uint512 operator - (uint512);
			uint512 operator * (uint64_t);
			uint512 operator * (uint512);
			uint512 operator / (uint64_t);
			uint512 operator / (uint512);

			//Shorten arithmetic operators *** 3.2
			void operator += (uint64_t);
			void operator += (uint512);
			void operator -= (uint64_t);
			void operator -= (uint512);
			void operator *= (uint64_t);
			void operator *= (uint512);
			void operator /= (uint64_t);
			void operator /= (uint512);

			//Extended arithmetic operators *** 3.3
			uint512 operator ++();
			uint512 operator --();
			uint512 operator % (uint512);

			//Extended shorten arithmetic operators *** 3.4
			void operator %= (uint512);

			//Comparsion operators *** 3.5
			bool operator == (uint512);
			bool operator < (uint512);
			bool operator > (uint512);
			bool operator <= (uint512);
			bool operator >= (uint512);
			bool operator != (uint512);
		};

		//4.0 Makro's
		#define UINT512_MIN BigInts::uint512::uint512(std::bitset<512>(0))
		#define UINT512_MAX BigInts::uint512::uint512(std::bitset<512>{}.set())

		//5.0 EXTERNAL ITEMS
		//5.1 Global operator overloads
		std::ostream& operator << (std::ostream& os, uint512);

		//5.2 Free functions
		uint512 pow(uint512, uint512);
		uint512 pow(uint512, uint64_t);
		uint512 mod(uint512, uint512);
		uint512 mod(uint512, uint64_t);
		uint512 log(uint512, uint512);
		uint512 log(uint64_t, uint512);
		uint512 log10(uint512);
		uint512 sqrt(uint512);
	}
}

