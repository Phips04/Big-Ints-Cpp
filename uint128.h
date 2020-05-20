#pragma once

#include <bitset>
#include <string>
#include <initializer_list>

namespace BigInts
{
	namespace uint128
	{
		class uint128
		{
		private:
			std::bitset<128> data;
		public:
			//CONSTRUCTORS *** 1.0
			uint128();
			uint128(int32_t);
			uint128(uint32_t);
			uint128(int64_t);
			uint128(uint64_t);
			uint128(std::bitset<128>);
			uint128(std::string);

			//METHODS *** 2.0
			//Standard arithmetic methods *** 2.1
			uint128 add(uint64_t);
			uint128 add(uint128);
			uint128 add(std::initializer_list<uint128>);
			uint128 substract(uint64_t);
			uint128 substract(uint128);
			uint128 substract(std::initializer_list<uint128>);
			uint128 multiply(uint64_t);
			uint128 multiply(uint128);
			uint128 multiply(std::initializer_list<uint128>);
			uint128 divide(uint64_t);
			uint128 divide(uint128);
			uint128 divide(std::initializer_list<uint128>);

			//Extended arithmetic methods *** 2.2
			uint128 pow(uint64_t);
			uint128 pow(uint128);
			uint128 pow(std::initializer_list<uint128>);
			uint128 log(uint128);
			uint128 log10();
			uint128 sqrt();
			uint128 mod(uint128);

			//Additional methods
			int TryToInt();
			unsigned long TryToLong();
			uint64_t TryToUint64_t();
			std::string ToBinaryString();
			std::bitset<128> GetBinaryData();
			std::string DivisionAdaptedSubHelpFunction(std::string, std::string);

			//OPERATORS *** 3.0
			//Arithmetic operators *** 3.1
			uint128 operator + (uint64_t);
			uint128 operator + (uint128);
			uint128 operator - (uint64_t);
			uint128 operator - (uint128);
			uint128 operator * (uint64_t);
			uint128 operator * (uint128);
			uint128 operator / (uint64_t);
			uint128 operator / (uint128);

			//Shorten arithmetic operators *** 3.2
			void operator += (uint64_t);
			void operator += (uint128);
			void operator -= (uint64_t);
			void operator -= (uint128);
			void operator *= (uint64_t);
			void operator *= (uint128);
			void operator /= (uint64_t);
			void operator /= (uint128);

			//Extended arithmetic operators *** 3.3
			uint128 operator ++();
			uint128 operator --();
			uint128 operator % (uint128);

			//Extended shorten arithmetic operators *** 3.4
			void operator %= (uint128);

			//Comparsion operators *** 3.5
			bool operator == (uint128);
			bool operator < (uint128);
			bool operator > (uint128);
			bool operator <= (uint128);
			bool operator >= (uint128);
			bool operator != (uint128);
		};

		//4.0 Makro's
		#define UINT128_MIN BigInts::uint128::uint128(std::bitset<128>(0))
		#define UINT128_MAX BigInts::uint128::uint128(std::bitset<128>{}.set())

		//5.0 EXTERNAL ITEMS
		//5.1 Global operator overloads
		std::ostream& operator << (std::ostream& os, uint128);

		//5.2 Free functions
		uint128 pow(uint128, uint128);
		uint128 pow(uint128, uint64_t);
		uint128 mod(uint128, uint128);
		uint128 mod(uint128, uint64_t);
		uint128 log(uint128, uint128);
		uint128 log(uint64_t, uint128);
		uint128 log10(uint128);
		uint128 sqrt(uint128);
	}
}