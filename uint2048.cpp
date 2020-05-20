#pragma once

#include "uint2048.h"

#include "uint128.h"
#include "uint256.h"
#include "uint512.h"
#include "uint1024.h"

#include <bitset>
#include <string>
#include <initializer_list>
#include <forward_list>
#include <limits>
#include <iostream>


namespace BigInts
{
	namespace uint2048
	{
		uint2048::uint2048() { this->data = std::bitset<2048>(); }
		uint2048::uint2048(int32_t init) { if (init < 0) { throw std::invalid_argument{ "argument (type of int32_t) was negative, int2048 is unsigned" }; } this->data = std::bitset<2048>(init); }
		uint2048::uint2048(uint32_t init) { this->data = std::bitset<2048>(init); }
		uint2048::uint2048(int64_t init) { if (init < 0) { throw std::invalid_argument{ "argument (type of int64_t) was negative, int2048 is unsigned" }; } this->data = std::bitset<2048>(init); }
		uint2048::uint2048(uint64_t init) { this->data = std::bitset<2048>(init); }
		uint2048::uint2048(uint128::uint128 init) { this->data = std::bitset<2048>(0); for (size_t i = 0; i < 128; i++) { this->data[i] = init.GetBinaryData()[i]; } }
		uint2048::uint2048(uint256::uint256 init) { this->data = std::bitset<2048>(0); for (size_t i = 0; i < 256; i++) { this->data[i] = init.GetBinaryData()[i]; } }
		uint2048::uint2048(uint512::uint512 init) { this->data = std::bitset<2048>(0); for (size_t i = 0; i < 512; i++) { this->data[i] = init.GetBinaryData()[i]; } }
		uint2048::uint2048(uint1024::uint1024 init) { this->data = std::bitset<2048>(0); for (size_t i = 0; i < 1024; i++) { this->data[i] = init.GetBinaryData()[i]; } }
		uint2048::uint2048(std::bitset<2048> init) { this->data = init; }
		uint2048::uint2048(std::string init)
		{
			for (size_t i = 0; i < init.length(); i++)
			{
				if (init.at(i) != *"0" && init.at(i) != *"1")
				{
					this->data = std::bitset<2048>(0);
					throw std::invalid_argument{ "Argument (type of std::string) was not either '0' or '1'" };
				}
			}

			this->data = std::bitset<2048>(init);
		}

		uint2048 uint2048::add(uint64_t arg)
		{
			return this->add(uint2048(arg));
		}

		uint2048 uint2048::add(uint2048 arg)
		{
			std::bitset<2048> result(0);

			int transmitter(0);

			for (size_t i = 0; i < 2048; i++)
			{
				if (arg.data[i] == 1 && this->data[i] == 1 && transmitter == 1) // OK
				{
					result[i] = 1;
					if (i == 2047)
					{
						throw std::overflow_error{ "The result will become greater than 2^2048, which is the maximal value of int2048" };
					}
					transmitter = 1;
					continue;
				}

				if ((arg.data[i] == 1 && this->data[i] == 1 && transmitter == 0) ||
					(arg.data[i] == 1 && this->data[i] == 0 && transmitter == 1) ||
					(arg.data[i] == 0 && this->data[i] == 1 && transmitter == 1))
				{
					result[i] = 0;
					if (i == 2047)
					{
						throw std::overflow_error{ "The result will grow larger than 2^2048, which is the maximal value of int2048" };
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

			return uint2048(result);
		}

		uint2048 uint2048::add(std::initializer_list<uint2048> args)
		{
			uint2048 result(*this);

			for (uint2048 arg : args)
			{
				result += arg;
			}

			return result;
		}

		uint2048 uint2048::substract(uint64_t arg)
		{
			return this->substract(uint2048(arg));
		}

		uint2048 uint2048::substract(uint2048 init)
		{
			std::bitset<2048> result(0);

			int transmitter(0);

			if (*this < init)
			{
				throw std::underflow_error{ "The result will be negative, int2048 is unsigned" };
			}

			for (size_t i = 0; i < 2048; i++)
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

				if (i == 2047 && transmitter == 1)
				{
					throw;
				}
			}

			return uint2048(result);
		}

		uint2048 uint2048::substract(std::initializer_list<uint2048> inits)
		{
			uint2048 result(*this);

			for (auto i : inits)
			{
				result -= i;
			}
			return result;

			return uint2048(result);
		}

		uint2048 uint2048::multiply(uint64_t init)
		{
			return this->multiply(uint2048(init));
		}

		uint2048 uint2048::multiply(uint2048 init)
		{
			std::forward_list<uint2048> ItemsToAdd;

			int ThisLength(0), InitLength(0);
			bool ThisLengthFound(false), InitLengthFound(false);

			for (size_t i = 0; i < 2048; i++)
			{
				if (this->data[2047 - i] == 1 && ThisLengthFound == false)
				{
					ThisLength = 2048 - i;
					ThisLengthFound = true;
				}

				if (init.data[2047 - i] == 1 && InitLengthFound == false)
				{
					InitLength = 2048 - i;
					InitLengthFound = true;
				}

				if (ThisLengthFound && InitLengthFound)
				{
					if (ThisLength + InitLength - 1 > 2048)
					{
						throw std::overflow_error{ "The result will grow larger than 2^2048, which is the maximal value of int2048" };
					}
				}
			}

			for (size_t i = 0; i < 2048; i++)
			{
				if (init.data[i] == 1)
				{
					std::bitset<2048> item(0);
					for (size_t x = 0; x < 2048; x++)
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

					ItemsToAdd.push_front(uint2048(item));
				}
			}

			uint2048 result(0);

			for (auto i : ItemsToAdd)
			{
				result += i;
			}

			return result;
		}

		uint2048 uint2048::multiply(std::initializer_list<uint2048> inits)
		{
			uint2048 result(*this);

			for (auto i : inits)
			{
				result *= i;
			}

			return result;
		}

		uint2048 uint2048::divide(uint64_t init)
		{
			return this->divide(uint2048(init));
		}

		uint2048 uint2048::divide(uint2048 init)
		{
			if (init.data == std::bitset<2048>(0))
			{
				throw std::invalid_argument{ "Argument was '0', division by '0' is not defined" };
			}

			if (*this < init)
			{
				return uint2048(0);
			}

			std::string ThisStream(""), InitStream(""), ThisCurrentStream(""), ResultStream("");
			bool StartRecordingThis(false), StartRecordingInit(false);

			for (size_t i = 0; i < 2048; i++)
			{
				if (this->data[2047 - i] == 1)
				{
					ThisStream += "1";
					StartRecordingThis = true;
				}
				else if (StartRecordingThis == true)
				{
					ThisStream += "0";
				}

				if (init.data[2047 - i] == 1)
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
				if (uint2048(ThisCurrentStream) < uint2048(InitStream))
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

			if (uint2048(ThisCurrentStream) < uint2048(InitStream))
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

			return uint2048(ResultStream);
		}

		uint2048 uint2048::divide(std::initializer_list<uint2048> inits)
		{
			uint2048 result(*this);

			for (auto i : inits)
			{
				result /= i;
			}
			return result;
		}

		uint2048 uint2048::pow(uint64_t init)
		{
			return this->pow(uint2048(init));
		}

		uint2048 uint2048::pow(uint2048 exp)
		{
			if (exp == uint2048(0))
			{
				return uint2048(1);
			}

			uint2048 result(*this);

			for (uint2048 i(1); i < exp; ++i)
			{
				result *= *this;
			}

			return result;
		}

		uint2048 uint2048::pow(std::initializer_list<uint2048> inits)
		{
			uint2048 FinalExp(1);

			for (uint2048 item : inits)
			{
				FinalExp *= item;
			}

			return this->pow(FinalExp);
		}

		uint2048 uint2048::log(uint2048 base)
		{
			if (base == uint2048(0))
			{
				throw std::invalid_argument{ "Argument was '0', logarithm which base = '0' is not defined" };
			}

			if (*this == uint2048(0))
			{
				throw std::domain_error{ "The value of the object calling the function 'log(int2048 base)' was '0', logarithm with exponent = '0' is not defined" };
			}


			if (*this < base)
			{
				return uint2048(0);
			}

			int CurrentPosition(2048 / base.TryToInt()), CurrentOffsetLength(2048 / (2 * base.TryToInt()));

			while (true)
			{
				if (base.pow(uint2048(CurrentPosition)) <= *this &&
					base.pow(uint2048(CurrentPosition + 1)) >= *this)
				{
					return CurrentPosition;
				}

				if (CurrentPosition <= 1)
				{
					return uint2048(0);
				}

				if (base.pow(uint2048(CurrentPosition)) <= *this)
				{
					CurrentPosition += CurrentOffsetLength;
					CurrentOffsetLength /= 2;
					continue;
				}

				if (base.pow(uint2048(CurrentPosition)) >= *this)
				{
					CurrentPosition -= CurrentOffsetLength;
					CurrentOffsetLength /= 2;
					continue;
				}
			}
		}

		uint2048 uint2048::log10() { return this->log(uint2048(10)); }

		uint2048 uint2048::sqrt()
		{
			if (*this == uint2048(0))
			{
				return uint2048(0);
			}

			if (*this == uint2048(1))
			{
				return uint2048(1);
			}

			uint2048 CurrentPosition(UINT1024_MAX / 2), CurrentOffsetLength(UINT1024_MAX / 4 + 1);

			while (true)
			{
				if (CurrentPosition.pow(uint2048(2)) <= *this &&
					uint2048(CurrentPosition + 1).pow(uint2048(2)) >= *this)
				{
					return CurrentPosition;
				}

				if (CurrentPosition <= 2)
				{
					return uint2048(1);
				}

				if (CurrentPosition.pow(uint2048(2)) <= *this)
				{
					CurrentPosition += CurrentOffsetLength;
					CurrentOffsetLength /= 2;
					continue;
				}

				if (CurrentPosition.pow(uint2048(2)) >= *this)
				{
					CurrentPosition -= CurrentOffsetLength;
					CurrentOffsetLength /= 2;
					continue;
				}
			}

			return uint2048();
		}

		uint2048 uint2048::mod(uint2048 init)
		{
			return (*this - (*this / init * init));
		}

		int uint2048::TryToInt()
		{
			if (*this > uint2048(INT32_MAX))
			{
				throw std::bad_cast{};
			}

			return (int)this->data.to_ulong();
		}

		unsigned long uint2048::TryToLong()
		{
			if (*this > uint2048(uint64_t(ULONG_MAX)))
			{
				throw std::bad_cast{};
			}

			return this->data.to_ulong();
		}

		uint64_t uint2048::TryToUint64_t()
		{
			if (*this > uint2048(uint64_t(ULLONG_MAX)))
			{
				throw std::bad_cast{};
			}

			return this->data.to_ullong();
		}

		uint128::uint128 uint2048::TryToUint128()
		{
			if (*this > uint2048(UINT128_MAX))
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

		uint256::uint256 uint2048::TryToUint256()
		{
			if (*this > uint2048(UINT256_MAX))
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

		uint512::uint512 uint2048::TryToUint512()
		{
			if (*this > uint2048(UINT512_MAX))
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

		uint1024::uint1024 uint2048::TryToUint1024()
		{
			if (*this > uint2048(UINT1024_MAX))
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

		std::string uint2048::ToBinaryString() { return this->data.to_string(); }
		std::bitset<2048> uint2048::GetBinaryData() { return this->data; }

		uint2048 uint2048::operator+(uint64_t var) { return this->add(var); }
		uint2048 uint2048::operator+(uint2048 var) { return this->add(var); }
		uint2048 uint2048::operator-(uint64_t var) { return this->substract(var); }
		uint2048 uint2048::operator-(uint2048 var) { return this->substract(var); }
		uint2048 uint2048::operator*(uint64_t var) { return this->multiply(var); }
		uint2048 uint2048::operator*(uint2048 var) { return this->multiply(var); }
		uint2048 uint2048::operator/(uint64_t var) { return this->divide(var); }
		uint2048 uint2048::operator/(uint2048 var) { return this->divide(var); }

		void uint2048::operator+=(uint64_t var) { *this = this->add(var); }
		void uint2048::operator+=(uint2048 var) { *this = this->add(var); }
		void uint2048::operator-=(uint64_t var) { *this = this->substract(var); }
		void uint2048::operator-=(uint2048 var) { *this = this->substract(var); }
		void uint2048::operator*=(uint64_t var) { *this = this->multiply(var); }
		void uint2048::operator*=(uint2048 var) { *this = this->multiply(var); }
		void uint2048::operator/=(uint64_t var) { *this = this->divide(var); }
		void uint2048::operator/=(uint2048 var) { *this = this->divide(var); }

		uint2048 uint2048::operator++()
		{
			*this += uint2048(1);
			return *this;
		}

		uint2048 uint2048::operator--()
		{
			*this -= uint2048(1);
			return *this;
		}

		uint2048 uint2048::operator%(uint2048 var) { return this->mod(var); }
		void uint2048::operator%=(uint2048 var) { *this = this->mod(var); }

		bool uint2048::operator==(uint2048 var)
		{
			for (size_t i = 0; i < 2048; i++)
			{
				if (this->data[2047 - i] != var.data[2047 - i])
				{
					return false;
				}
			}

			return true;
		}

		bool uint2048::operator<(uint2048 item)
		{
			for (size_t i = 0; i < 2048; i++)
			{
				if (this->data[2047 - i] == 1 && item.data[2047 - i] == 0)
				{
					return false;
				}
				else if (this->data[2047 - i] == 0 && item.data[2047 - i] == 1)
				{
					return true;
				}
			}

			return false;
		}

		bool uint2048::operator>(uint2048 item)
		{
			for (size_t i = 0; i < 2048; i++)
			{
				if (this->data[2047 - i] == 0 && item.data[2047 - i] == 1)
				{
					return false;
				}
				else if (this->data[2047 - i] == 1 && item.data[2047 - i] == 0)
				{
					return true;
				}
			}

			return false;
		}

		bool uint2048::operator<=(uint2048 item)
		{
			for (size_t i = 0; i < 2048; i++)
			{
				if (this->data[2047 - i] == 1 && item.data[2047 - i] == 0)
				{
					return false;
				}
				else if (this->data[2047 - i] == 0 && item.data[2047 - i] == 1)
				{
					return true;
				}
			}

			return true;
		}

		bool uint2048::operator>=(uint2048 item)
		{
			for (size_t i = 0; i < 2048; i++)
			{
				if (this->data[2047 - i] == 0 && item.data[2047 - i] == 1)
				{
					return false;
				}
				else if (this->data[2047 - i] == 1 && item.data[2047 - i] == 0)
				{
					return true;
				}
			}

			return false;
		}

		bool uint2048::operator!=(uint2048 item) { return !(*this == item); }

		std::ostream& operator << (std::ostream& os, uint2048 integer) { return os << integer.GetBinaryData(); }

		std::string uint2048::DivisionAdaptedSubHelpFunction(std::string This, std::string init)
		{
			uint2048 CThis = uint2048(This);
			uint2048 CInit = uint2048(init);

			uint2048 RawResult = CThis - CInit;

			std::string result("");
			bool StartWritingZeros(false);

			for (size_t i = 0; i < 2048; i++)
			{
				if (RawResult.data[2047 - i] == 1)
				{
					result += "1";
					StartWritingZeros = true;
				}
				if (RawResult.data[2047 - i] == 0 && StartWritingZeros == true)
				{
					result += "0";
				}
			}

			return result;
		}

		uint2048 pow(uint2048 base, uint2048 exp)
		{
			uint2048 This(base);
			return This.pow(exp);
		}

		uint2048 pow(uint2048 base, uint64_t exp)
		{
			uint2048 This(base);
			return This.pow(exp);
		}

		uint2048 mod(uint2048 divisor, uint2048 divider)
		{
			uint2048 This(divisor);
			return This.divide(divider);
		}

		uint2048 mod(uint2048 divisor, uint64_t divider)
		{
			uint2048 This(divisor);
			return This.divide(divider);
		}

		uint2048 log(uint2048 base, uint2048 pot)
		{
			uint2048 This(base);
			return This.log(pot);
		}

		uint2048 log(uint64_t base, uint2048 pot)
		{
			uint2048 This(base);
			return This.log(pot);
		}

		uint2048 log10(uint2048 pot)
		{
			return pot.log10();
		}

		uint2048 sqrt(uint2048 radiant)
		{
			return radiant.sqrt();
		}
	}
}
