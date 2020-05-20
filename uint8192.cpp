#pragma once

#include "uint8192.h"

#include "uint128.h"
#include "uint256.h"
#include "uint512.h"
#include "uint1024.h"
#include "uint2048.h"
#include "uint4096.h"

#include <bitset>
#include <string>
#include <initializer_list>
#include <forward_list>
#include <limits>
#include <iostream>


namespace BigInts
{
	namespace uint8192
	{
		uint8192::uint8192() { this->data = std::bitset<8192>(); }
		uint8192::uint8192(int32_t init) { if (init < 0) { throw std::invalid_argument{ "argument (type of int32_t) was negative, int8192 is unsigned" }; } this->data = std::bitset<8192>(init); }
		uint8192::uint8192(uint32_t init) { this->data = std::bitset<8192>(init); }
		uint8192::uint8192(int64_t init) { if (init < 0) { throw std::invalid_argument{ "argument (type of int64_t) was negative, int8192 is unsigned" }; } this->data = std::bitset<8192>(init); }
		uint8192::uint8192(uint64_t init) { this->data = std::bitset<8192>(init); }
		uint8192::uint8192(uint128::uint128 init) { this->data = std::bitset<8192>(0); for (size_t i = 0; i < 128; i++) { this->data[i] = init.GetBinaryData()[i]; } }
		uint8192::uint8192(uint256::uint256 init) { this->data = std::bitset<8192>(0); for (size_t i = 0; i < 256; i++) { this->data[i] = init.GetBinaryData()[i]; } }
		uint8192::uint8192(uint512::uint512 init) { this->data = std::bitset<8192>(0); for (size_t i = 0; i < 512; i++) { this->data[i] = init.GetBinaryData()[i]; } }
		uint8192::uint8192(uint1024::uint1024 init) { this->data = std::bitset<8192>(0); for (size_t i = 0; i < 1024; i++) { this->data[i] = init.GetBinaryData()[i]; } }
		uint8192::uint8192(uint2048::uint2048 init) { this->data = std::bitset<8192>(0); for (size_t i = 0; i < 2048; i++) { this->data[i] = init.GetBinaryData()[i]; } }
		uint8192::uint8192(uint4096::uint4096 init) { this->data = std::bitset<8192>(0); for (size_t i = 0; i < 4096; i++) { this->data[i] = init.GetBinaryData()[i]; } }
		uint8192::uint8192(std::bitset<8192> init) { this->data = init; }
		uint8192::uint8192(std::string init)
		{
			for (size_t i = 0; i < init.length(); i++)
			{
				if (init.at(i) != *"0" && init.at(i) != *"1")
				{
					this->data = std::bitset<8192>(0);
					throw std::invalid_argument{ "Argument (type of std::string) was not either '0' or '1'" };
				}
			}

			this->data = std::bitset<8192>(init);
		}

		uint8192 uint8192::add(uint64_t arg)
		{
			return this->add(uint8192(arg));
		}

		uint8192 uint8192::add(uint8192 arg)
		{
			std::bitset<8192> result(0);

			int transmitter(0);

			for (size_t i = 0; i < 8192; i++)
			{
				if (arg.data[i] == 1 && this->data[i] == 1 && transmitter == 1) // OK
				{
					result[i] = 1;
					if (i == 8191)
					{
						throw std::overflow_error{ "The result will become greater than 2^8192, which is the maximal value of int8192" };
					}
					transmitter = 1;
					continue;
				}

				if ((arg.data[i] == 1 && this->data[i] == 1 && transmitter == 0) ||
					(arg.data[i] == 1 && this->data[i] == 0 && transmitter == 1) ||
					(arg.data[i] == 0 && this->data[i] == 1 && transmitter == 1))
				{
					result[i] = 0;
					if (i == 8191)
					{
						throw std::overflow_error{ "The result will grow larger than 2^8192, which is the maximal value of int8192" };
					}
					transmitter = 1;
					continue;
				}
				if ((arg.data[i] == 1 && this->data[i] == 0 && transmitter == 0) ||
					(arg.data[i] == 0 && this->data[i] == 1 && transmitter == 0) ||
					(arg.data[i] == 0 && this->data[i] == 0 && transmitter == 1))
				{
					result[i] = 1;
					transmitter = 0;
					continue;
				}
				else
				{
					result[i] = 0;
					transmitter = 0;
					continue;
				}
			}

			return uint8192(result);
		}

		uint8192 uint8192::add(std::initializer_list<uint8192> args)
		{
			uint8192 result(*this);

			for (uint8192 arg : args)
			{
				result += arg;
			}

			return result;
		}

		uint8192 uint8192::substract(uint64_t arg)
		{
			return this->substract(uint8192(arg));
		}

		uint8192 uint8192::substract(uint8192 init)
		{
			std::bitset<8192> result(0);

			int transmitter(0);

			if (*this < init)
			{
				throw std::underflow_error{ "The result will be negative, int8192 is unsigned" };
			}

			for (size_t i = 0; i < 8192; i++)
			{

				if ((this->data[i] == 1 && init.data[i] == 1 && transmitter == 1) ||
					(this->data[i] == 0 && init.data[i] == 1 && transmitter == 0) ||
					(this->data[i] == 0 && init.data[i] == 0 && transmitter == 1))
				{
					result[i] = 1;
					transmitter = 1;
					continue;
				}
				if ((this->data[i] == 1 && init.data[i] == 1 && transmitter == 0) ||
					(this->data[i] == 1 && init.data[i] == 0 && transmitter == 1) ||
					(this->data[i] == 0 && init.data[i] == 0 && transmitter == 0))
				{
					result[i] = 0;
					transmitter = 0;
					continue;
				}

				if (this->data[i] == 0 && init.data[i] == 1 && transmitter == 1)
				{
					result[i] = 0;
					transmitter = 1;
					continue;
				}

				if (this->data[i] == 1 && init.data[i] == 0 && transmitter == 0)
				{
					result[i] = 1;
					transmitter = 0;
					continue;
				}

				if (i == 8191 && transmitter == 1)
				{
					throw;
				}
			}

			return uint8192(result);
		}

		uint8192 uint8192::substract(std::initializer_list<uint8192> inits)
		{
			uint8192 result(*this);

			for (auto i : inits)
			{
				result -= i;
			}
			return result;

			return uint8192(result);
		}

		uint8192 uint8192::multiply(uint64_t init)
		{
			return this->multiply(uint8192(init));
		}

		uint8192 uint8192::multiply(uint8192 init)
		{
			std::forward_list<uint8192> ItemsToAdd;

			int ThisLength(0), InitLength(0);
			bool ThisLengthFound(false), InitLengthFound(false);

			for (size_t i = 0; i < 8192; i++)
			{
				if (this->data[8191 - i] == 1 && ThisLengthFound == false)
				{
					ThisLength = 8192 - i;
					ThisLengthFound = true;
				}

				if (init.data[8191 - i] == 1 && InitLengthFound == false)
				{
					InitLength = 8192 - i;
					InitLengthFound = true;
				}

				if (ThisLengthFound && InitLengthFound)
				{
					if (ThisLength + InitLength - 1 > 8192)
					{
						throw std::overflow_error{ "The result will grow larger than 2^8192, which is the maximal value of int8192" };
					}
				}
			}

			for (size_t i = 0; i < 8192; i++)
			{
				if (init.data[i] == 1)
				{
					std::bitset<8192> item(0);
					for (size_t x = 0; x < 8192; x++)
					{
						if (x < i)
						{
							item[x] = 0;
						}
						else
						{
							item[x] = this->data[x - i];
						}
					}

					ItemsToAdd.push_front(uint8192(item));
				}
			}

			uint8192 result(0);

			for (auto i : ItemsToAdd)
			{
				result += i;
			}

			return result;
		}

		uint8192 uint8192::multiply(std::initializer_list<uint8192> inits)
		{
			uint8192 result(*this);

			for (auto i : inits)
			{
				result *= i;
			}

			return result;
		}

		uint8192 uint8192::divide(uint64_t init)
		{
			return this->divide(uint8192(init));
		}

		uint8192 uint8192::divide(uint8192 init)
		{
			if (init.data == std::bitset<8192>(0))
			{
				throw std::invalid_argument{ "Argument was '0', division by '0' is not defined" };
			}

			if (*this < init)
			{
				return uint8192(0);
			}

			std::string ThisStream(""), InitStream(""), ThisCurrentStream(""), ResultStream("");
			bool StartRecordingThis(false), StartRecordingInit(false);

			for (size_t i = 0; i < 8192; i++)
			{
				if (this->data[8191 - i] == 1)
				{
					ThisStream += "1";
					StartRecordingThis = true;
				}
				else if (StartRecordingThis == true)
				{
					ThisStream += "0";
				}

				if (init.data[8191 - i] == 1)
				{
					InitStream += "1";
					StartRecordingInit = true;
				}
				else if (StartRecordingInit == true)
				{
					InitStream += "0";
				}
			}

			ThisStream.erase(ThisStream.begin());
			ThisCurrentStream = "1";

			while (ThisStream.length() > 0)
			{
				if (uint8192(ThisCurrentStream) < uint8192(InitStream))
				{
					ThisCurrentStream += *ThisStream.begin();
					ThisStream.erase(ThisStream.begin());
					ResultStream += "0";
				}
				else
				{
					ThisCurrentStream = DivisionAdaptedSubHelpFunction(ThisCurrentStream, InitStream);
					ThisCurrentStream += *ThisStream.begin();
					ThisStream.erase(ThisStream.begin());
					ResultStream += "1";
				}
			}

			if (uint8192(ThisCurrentStream) < uint8192(InitStream))
			{
				ResultStream += "0";
			}
			else
			{
				ResultStream += "1";
			}

			while (*ResultStream.begin() == *"0")
			{
				ResultStream.erase(ResultStream.begin());
			}

			return uint8192(ResultStream);
		}

		uint8192 uint8192::divide(std::initializer_list<uint8192> inits)
		{
			uint8192 result(*this);

			for (auto i : inits)
			{
				result /= i;
			}
			return result;
		}

		uint8192 uint8192::pow(uint64_t init)
		{
			return this->pow(uint8192(init));
		}

		uint8192 uint8192::pow(uint8192 exp)
		{
			if (exp == uint8192(0))
			{
				return uint8192(1);
			}

			uint8192 result(*this);

			for (uint8192 i(1); i < exp; ++i)
			{
				result *= *this;
			}

			return result;
		}

		uint8192 uint8192::pow(std::initializer_list<uint8192> inits)
		{
			uint8192 FinalExp(1);

			for (uint8192 item : inits)
			{
				FinalExp *= item;
			}

			return this->pow(FinalExp);
		}

		uint8192 uint8192::log(uint8192 base)
		{
			if (base == uint8192(0))
			{
				throw std::invalid_argument{ "Argument was '0', logarithm which base = '0' is not defined" };
			}

			if (*this == uint8192(0))
			{
				throw std::domain_error{ "The value of the object calling the function 'log(int8192 base)' was '0', logarithm with exponent = '0' is not defined" };
			}


			if (*this < base)
			{
				return uint8192(0);
			}

			int CurrentPosition(8192 / base.TryToInt()), CurrentOffsetLength(8192 / (2 * base.TryToInt()));

			while (true)
			{
				if (base.pow(uint8192(CurrentPosition)) <= *this &&
					base.pow(uint8192(CurrentPosition + 1)) >= *this)
				{
					return CurrentPosition;
				}

				if (CurrentPosition <= 1)
				{
					return uint8192(0);
				}

				if (base.pow(uint8192(CurrentPosition)) <= *this)
				{
					CurrentPosition += CurrentOffsetLength;
					CurrentOffsetLength /= 2;
					continue;
				}

				if (base.pow(uint8192(CurrentPosition)) >= *this)
				{
					CurrentPosition -= CurrentOffsetLength;
					CurrentOffsetLength /= 2;
					continue;
				}
			}
		}

		uint8192 uint8192::log10() { return this->log(uint8192(10)); }

		uint8192 uint8192::sqrt()
		{
			if (*this == uint8192(0))
			{
				return uint8192(0);
			}

			if (*this == uint8192(1))
			{
				return uint8192(1);
			}

			uint8192 CurrentPosition(UINT4096_MAX / 2), CurrentOffsetLength(UINT4096_MAX / 4 + 1);

			while (true)
			{
				if (CurrentPosition.pow(uint8192(2)) <= *this &&
					uint8192(CurrentPosition + 1).pow(uint8192(2)) >= *this)
				{
					return CurrentPosition;
				}

				if (CurrentPosition <= 2)
				{
					return uint8192(1);
				}

				if (CurrentPosition.pow(uint8192(2)) <= *this)
				{
					CurrentPosition += CurrentOffsetLength;
					CurrentOffsetLength /= 2;
					continue;
				}

				if (CurrentPosition.pow(uint8192(2)) >= *this)
				{
					CurrentPosition -= CurrentOffsetLength;
					CurrentOffsetLength /= 2;
					continue;
				}
			}

			return uint8192();
		}

		uint8192 uint8192::mod(uint8192 init)
		{
			return (*this - (*this / init * init));
		}

		int uint8192::TryToInt()
		{
			if (*this > uint8192(INT32_MAX))
			{
				throw std::bad_cast{};
			}

			return (int)this->data.to_ulong();
		}

		unsigned long uint8192::TryToLong()
		{
			if (*this > uint8192(uint64_t(ULONG_MAX)))
			{
				throw std::bad_cast{};
			}

			return this->data.to_ulong();
		}

		uint64_t uint8192::TryToUint64_t()
		{
			if (*this > uint8192(uint64_t(ULLONG_MAX)))
			{
				throw std::bad_cast{};
			}

			return this->data.to_ullong();
		}

		uint128::uint128 uint8192::TryToUint128()
		{
			if (*this > uint8192(UINT128_MAX))
			{
				throw std::bad_cast{};
			}

			std::bitset<128> result(0);

			for (size_t i = 0; i < 128; i++)
			{
				result[i] = this->data[i];
			}

			return uint128::uint128(result);
		}

		uint256::uint256 uint8192::TryToUint256()
		{
			if (*this > uint8192(UINT256_MAX))
			{
				throw std::bad_cast{};
			}

			std::bitset<256> result(0);

			for (size_t i = 0; i < 256; i++)
			{
				result[i] = this->data[i];
			}

			return uint256::uint256(result);
		}

		uint512::uint512 uint8192::TryToUint512()
		{
			if (*this > uint8192(UINT512_MAX))
			{
				throw std::bad_cast{};
			}

			std::bitset<512> result(0);

			for (size_t i = 0; i < 512; i++)
			{
				result[i] = this->data[i];
			}

			return uint512::uint512(result);
		}

		uint1024::uint1024 uint8192::TryToUint1024()
		{
			if (*this > uint8192(UINT1024_MAX))
			{
				throw std::bad_cast{};
			}

			std::bitset<1024> result(0);

			for (size_t i = 0; i < 1024; i++)
			{
				result[i] = this->data[i];
			}

			return uint1024::uint1024(result);
		}

		uint2048::uint2048 uint8192::TryToUint2048()
		{
			if (*this > uint8192(UINT2048_MAX))
			{
				throw std::bad_cast{};
			}

			std::bitset<2048> result(0);

			for (size_t i = 0; i < 2048; i++)
			{
				result[i] = this->data[i];
			}

			return uint2048::uint2048(result);
		}

		uint4096::uint4096 uint8192::TryToUint4096()
		{
			if (*this > uint8192(UINT4096_MAX))
			{
				throw std::bad_cast{};
			}

			std::bitset<4096> result(0);

			for (size_t i = 0; i < 4096; i++)
			{
				result[i] = this->data[i];
			}

			return uint4096::uint4096(result);
		}

		std::string uint8192::ToBinaryString() { return this->data.to_string(); }
		std::bitset<8192> uint8192::GetBinaryData() { return this->data; }

		uint8192 uint8192::operator+(uint64_t var) { return this->add(var); }
		uint8192 uint8192::operator+(uint8192 var) { return this->add(var); }
		uint8192 uint8192::operator-(uint64_t var) { return this->substract(var); }
		uint8192 uint8192::operator-(uint8192 var) { return this->substract(var); }
		uint8192 uint8192::operator*(uint64_t var) { return this->multiply(var); }
		uint8192 uint8192::operator*(uint8192 var) { return this->multiply(var); }
		uint8192 uint8192::operator/(uint64_t var) { return this->divide(var); }
		uint8192 uint8192::operator/(uint8192 var) { return this->divide(var); }

		void uint8192::operator+=(uint64_t var) { *this = this->add(var); }
		void uint8192::operator+=(uint8192 var) { *this = this->add(var); }
		void uint8192::operator-=(uint64_t var) { *this = this->substract(var); }
		void uint8192::operator-=(uint8192 var) { *this = this->substract(var); }
		void uint8192::operator*=(uint64_t var) { *this = this->multiply(var); }
		void uint8192::operator*=(uint8192 var) { *this = this->multiply(var); }
		void uint8192::operator/=(uint64_t var) { *this = this->divide(var); }
		void uint8192::operator/=(uint8192 var) { *this = this->divide(var); }

		uint8192 uint8192::operator++()
		{
			*this += uint8192(1);
			return *this;
		}

		uint8192 uint8192::operator--()
		{
			*this -= uint8192(1);
			return *this;
		}

		uint8192 uint8192::operator%(uint8192 var) { return this->mod(var); }
		void uint8192::operator%=(uint8192 var) { *this = this->mod(var); }

		bool uint8192::operator==(uint8192 var)
		{
			for (size_t i = 0; i < 8192; i++)
			{
				if (this->data[8191 - i] != var.data[8191 - i])
				{
					return false;
				}
			}

			return true;
		}

		bool uint8192::operator<(uint8192 item)
		{
			for (size_t i = 0; i < 8192; i++)
			{
				if (this->data[8191 - i] == 1 && item.data[8191 - i] == 0)
				{
					return false;
				}
				else if (this->data[8191 - i] == 0 && item.data[8191 - i] == 1)
				{
					return true;
				}
			}

			return false;
		}

		bool uint8192::operator>(uint8192 item)
		{
			for (size_t i = 0; i < 8192; i++)
			{
				if (this->data[8191 - i] == 0 && item.data[8191 - i] == 1)
				{
					return false;
				}
				else if (this->data[8191 - i] == 1 && item.data[8191 - i] == 0)
				{
					return true;
				}
			}

			return false;
		}

		bool uint8192::operator<=(uint8192 item)
		{
			for (size_t i = 0; i < 8192; i++)
			{
				if (this->data[8191 - i] == 1 && item.data[8191 - i] == 0)
				{
					return false;
				}
				else if (this->data[8191 - i] == 0 && item.data[8191 - i] == 1)
				{
					return true;
				}
			}

			return true;
		}

		bool uint8192::operator>=(uint8192 item)
		{
			for (size_t i = 0; i < 8192; i++)
			{
				if (this->data[8191 - i] == 0 && item.data[8191 - i] == 1)
				{
					return false;
				}
				else if (this->data[8191 - i] == 1 && item.data[8191 - i] == 0)
				{
					return true;
				}
			}

			return false;
		}

		bool uint8192::operator!=(uint8192 item) { return !(*this == item); }

		std::ostream& operator << (std::ostream& os, uint8192 integer) { return os << integer.GetBinaryData(); }

		std::string uint8192::DivisionAdaptedSubHelpFunction(std::string This, std::string init)
		{
			uint8192 CThis = uint8192(This);
			uint8192 CInit = uint8192(init);

			uint8192 RawResult = CThis - CInit;

			std::string result("");
			bool StartWritingZeros(false);

			for (size_t i = 0; i < 8192; i++)
			{
				if (RawResult.data[8191 - i] == 1)
				{
					result += "1";
					StartWritingZeros = true;
				}
				if (RawResult.data[8191 - i] == 0 && StartWritingZeros == true)
				{
					result += "0";
				}
			}

			return result;
		}

		uint8192 pow(uint8192 base, uint8192 exp)
		{
			uint8192 This(base);
			return This.pow(exp);
		}

		uint8192 pow(uint8192 base, uint64_t exp)
		{
			uint8192 This(base);
			return This.pow(exp);
		}

		uint8192 mod(uint8192 divisor, uint8192 divider)
		{
			uint8192 This(divisor);
			return This.divide(divider);
		}

		uint8192 mod(uint8192 divisor, uint64_t divider)
		{
			uint8192 This(divisor);
			return This.divide(divider);
		}

		uint8192 log(uint8192 base, uint8192 pot)
		{
			uint8192 This(base);
			return This.log(pot);
		}

		uint8192 log(uint64_t base, uint8192 pot)
		{
			uint8192 This(base);
			return This.log(pot);
		}

		uint8192 log10(uint8192 pot)
		{
			return pot.log10();
		}

		uint8192 sqrt(uint8192 radiant)
		{
			return radiant.sqrt();
		}
	}
}