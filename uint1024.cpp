#pragma once

#include "uint1024.h"

#include "uint128.h"
#include "uint256.h"
#include "uint512.h"

#include <bitset>
#include <string>
#include <initializer_list>
#include <forward_list>
#include <limits>
#include <iostream>


namespace BigInts
{
	namespace uint1024
	{
		uint1024::uint1024() { this->data = std::bitset<1024>(); }
		uint1024::uint1024(int32_t init) { if (init < 0) { throw std::invalid_argument{ "argument (type of int32_t) was negative, int1024 is unsigned" }; } this->data = std::bitset<1024>(init); }
		uint1024::uint1024(uint32_t init) { this->data = std::bitset<1024>(init); }
		uint1024::uint1024(int64_t init) { if (init < 0) { throw std::invalid_argument{ "argument (type of int64_t) was negative, int1024 is unsigned" }; } this->data = std::bitset<1024>(init); }
		uint1024::uint1024(uint64_t init) { this->data = std::bitset<1024>(init); }
		uint1024::uint1024(uint128::uint128 init) { this->data = std::bitset<1024>(0); for (size_t i = 0; i < 128; i++) { this->data[i] = init.GetBinaryData()[i]; } }
		uint1024::uint1024(uint256::uint256 init) { this->data = std::bitset<1024>(0); for (size_t i = 0; i < 256; i++) { this->data[i] = init.GetBinaryData()[i]; } }
		uint1024::uint1024(uint512::uint512 init) { this->data = std::bitset<1024>(0); for (size_t i = 0; i < 512; i++) { this->data[i] = init.GetBinaryData()[i]; } }
		uint1024::uint1024(std::bitset<1024> init) { this->data = init; }
		uint1024::uint1024(std::string init)
		{
			for (size_t i = 0; i < init.length(); i++)
			{
				if (init.at(i) != *"0" && init.at(i) != *"1")
				{
					this->data = std::bitset<1024>(0);
					throw std::invalid_argument{ "Argument (type of std::string) was not either '0' or '1'" };
				}
			}

			this->data = std::bitset<1024>(init);
		}

		uint1024 uint1024::add(uint64_t arg)
		{
			return this->add(uint1024(arg));
		}

		uint1024 uint1024::add(uint1024 arg)
		{
			std::bitset<1024> result(0);

			int transmitter(0);

			for (size_t i = 0; i < 1024; i++)
			{
				if (arg.data[i] == 1 && this->data[i] == 1 && transmitter == 1) // OK
				{
					result[i] = 1;
					if (i == 1023)
					{
						throw std::overflow_error{ "The result will become greater than 2^1024, which is the maximal value of int1024" };
					}
					transmitter = 1;
					continue;
				}

				if ((arg.data[i] == 1 && this->data[i] == 1 && transmitter == 0) ||
					(arg.data[i] == 1 && this->data[i] == 0 && transmitter == 1) ||
					(arg.data[i] == 0 && this->data[i] == 1 && transmitter == 1))
				{
					result[i] = 0;
					if (i == 1023)
					{
						throw std::overflow_error{ "The result will grow larger than 2^1024, which is the maximal value of int1024" };
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

			return uint1024(result);
		}

		uint1024 uint1024::add(std::initializer_list<uint1024> args)
		{
			uint1024 result(*this);

			for (uint1024 arg : args)
			{
				result += arg;
			}

			return result;
		}

		uint1024 uint1024::substract(uint64_t arg)
		{
			return this->substract(uint1024(arg));
		}

		uint1024 uint1024::substract(uint1024 init)
		{
			std::bitset<1024> result(0);

			int transmitter(0);

			if (*this < init)
			{
				throw std::underflow_error{ "The result will be negative, int1024 is unsigned" };
			}

			for (size_t i = 0; i < 1024; i++)
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

				if (i == 1023 && transmitter == 1)
				{
					throw;
				}
			}

			return uint1024(result);
		}

		uint1024 uint1024::substract(std::initializer_list<uint1024> inits)
		{
			uint1024 result(*this);

			for (auto i : inits)
			{
				result -= i;
			}
			return result;

			return uint1024(result);
		}

		uint1024 uint1024::multiply(uint64_t init)
		{
			return this->multiply(uint1024(init));
		}

		uint1024 uint1024::multiply(uint1024 init)
		{
			std::forward_list<uint1024> ItemsToAdd;

			int ThisLength(0), InitLength(0);
			bool ThisLengthFound(false), InitLengthFound(false);

			for (size_t i = 0; i < 1024; i++)
			{
				if (this->data[1023 - i] == 1 && ThisLengthFound == false)
				{
					ThisLength = 1024 - i;
					ThisLengthFound = true;
				}

				if (init.data[1023 - i] == 1 && InitLengthFound == false)
				{
					InitLength = 1024 - i;
					InitLengthFound = true;
				}

				if (ThisLengthFound && InitLengthFound)
				{
					if (ThisLength + InitLength - 1 > 1024)
					{
						throw std::overflow_error{ "The result will grow larger than 2^1024, which is the maximal value of int1024" };
					}
				}
			}

			for (size_t i = 0; i < 1024; i++)
			{
				if (init.data[i] == 1)
				{
					std::bitset<1024> item(0);
					for (size_t x = 0; x < 1024; x++)
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

					ItemsToAdd.push_front(uint1024(item));
				}
			}

			uint1024 result(0);

			for (auto i : ItemsToAdd)
			{
				result += i;
			}

			return result;
		}

		uint1024 uint1024::multiply(std::initializer_list<uint1024> inits)
		{
			uint1024 result(*this);

			for (auto i : inits)
			{
				result *= i;
			}

			return result;
		}

		uint1024 uint1024::divide(uint64_t init)
		{
			return this->divide(uint1024(init));
		}

		uint1024 uint1024::divide(uint1024 init)
		{
			if (init.data == std::bitset<1024>(0))
			{
				throw std::invalid_argument{ "Argument was '0', division by '0' is not defined" };
			}

			if (*this < init)
			{
				return uint1024(0);
			}

			std::string ThisStream(""), InitStream(""), ThisCurrentStream(""), ResultStream("");
			bool StartRecordingThis(false), StartRecordingInit(false);

			for (size_t i = 0; i < 1024; i++)
			{
				if (this->data[1023 - i] == 1)
				{
					ThisStream += "1";
					StartRecordingThis = true;
				}
				else if (StartRecordingThis == true)
				{
					ThisStream += "0";
				}

				if (init.data[1023 - i] == 1)
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
				if (uint1024(ThisCurrentStream) < uint1024(InitStream))
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

			if (uint1024(ThisCurrentStream) < uint1024(InitStream))
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

			return uint1024(ResultStream);
		}

		uint1024 uint1024::divide(std::initializer_list<uint1024> inits)
		{
			uint1024 result(*this);

			for (auto i : inits)
			{
				result /= i;
			}
			return result;
		}

		uint1024 uint1024::pow(uint64_t init)
		{
			return this->pow(uint1024(init));
		}

		uint1024 uint1024::pow(uint1024 exp)
		{
			if (exp == uint1024(0))
			{
				return uint1024(1);
			}

			uint1024 result(*this);

			for (uint1024 i(1); i < exp; ++i)
			{
				result *= *this;
			}

			return result;
		}

		uint1024 uint1024::pow(std::initializer_list<uint1024> inits)
		{
			uint1024 FinalExp(1);

			for (uint1024 item : inits)
			{
				FinalExp *= item;
			}

			return this->pow(FinalExp);
		}

		uint1024 uint1024::log(uint1024 base)
		{
			if (base == uint1024(0))
			{
				throw std::invalid_argument{ "Argument was '0', logarithm which base = '0' is not defined" };
			}

			if (*this == uint1024(0))
			{
				throw std::domain_error{ "The value of the object calling the function 'log(int1024 base)' was '0', logarithm with exponent = '0' is not defined" };
			}


			if (*this < base)
			{
				return uint1024(0);
			}

			int CurrentPosition(1024 / base.TryToInt()), CurrentOffsetLength(1024 / (2 * base.TryToInt()));

			while (true)
			{
				if (base.pow(uint1024(CurrentPosition)) <= *this &&
					base.pow(uint1024(CurrentPosition + 1)) >= *this)
				{
					return CurrentPosition;
				}

				if (CurrentPosition <= 1)
				{
					return uint1024(0);
				}

				if (base.pow(uint1024(CurrentPosition)) <= *this)
				{
					CurrentPosition += CurrentOffsetLength;
					CurrentOffsetLength /= 2;
					continue;
				}

				if (base.pow(uint1024(CurrentPosition)) >= *this)
				{
					CurrentPosition -= CurrentOffsetLength;
					CurrentOffsetLength /= 2;
					continue;
				}
			}
		}

		uint1024 uint1024::log10() { return this->log(uint1024(10)); }

		uint1024 uint1024::sqrt()
		{
			if (*this == uint1024(0))
			{
				return uint1024(0);
			}

			if (*this == uint1024(1))
			{
				return uint1024(1);
			}

			uint1024 CurrentPosition(UINT512_MAX / 2), CurrentOffsetLength(UINT512_MAX / 4 + 1);

			while (true)
			{
				if (CurrentPosition.pow(uint1024(2)) <= *this &&
					uint1024(CurrentPosition + 1).pow(uint1024(2)) >= *this)
				{
					return CurrentPosition;
				}

				if (CurrentPosition <= 2)
				{
					return uint1024(1);
				}

				if (CurrentPosition.pow(uint1024(2)) <= *this)
				{
					CurrentPosition += CurrentOffsetLength;
					CurrentOffsetLength /= 2;
					continue;
				}

				if (CurrentPosition.pow(uint1024(2)) >= *this)
				{
					CurrentPosition -= CurrentOffsetLength;
					CurrentOffsetLength /= 2;
					continue;
				}
			}

			return uint1024();
		}

		uint1024 uint1024::mod(uint1024 init)
		{
			return (*this - (*this / init * init));
		}

		int uint1024::TryToInt()
		{
			if (*this > uint1024(INT32_MAX))
			{
				throw std::bad_cast{};
			}

			return (int)this->data.to_ulong();
		}

		unsigned long uint1024::TryToLong()
		{
			if (*this > uint1024(uint64_t(ULONG_MAX)))
			{
				throw std::bad_cast{};
			}

			return this->data.to_ulong();
		}

		uint64_t uint1024::TryToUint64_t()
		{
			if (*this > uint1024(uint64_t(ULLONG_MAX)))
			{
				throw std::bad_cast{};
			}

			return this->data.to_ullong();
		}

		uint128::uint128 uint1024::TryToUint128()
		{
			if (*this > uint1024(UINT128_MAX))
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

		uint256::uint256 uint1024::TryToUint256()
		{
			if (*this > uint1024(UINT256_MAX))
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

		uint512::uint512 uint1024::TryToUint512()
		{
			if (*this > uint1024(UINT512_MAX))
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

		std::string uint1024::ToBinaryString() { return this->data.to_string(); }
		std::bitset<1024> uint1024::GetBinaryData() { return this->data; }

		uint1024 uint1024::operator+(uint64_t var) { return this->add(var); }
		uint1024 uint1024::operator+(uint1024 var) { return this->add(var); }
		uint1024 uint1024::operator-(uint64_t var) { return this->substract(var); }
		uint1024 uint1024::operator-(uint1024 var) { return this->substract(var); }
		uint1024 uint1024::operator*(uint64_t var) { return this->multiply(var); }
		uint1024 uint1024::operator*(uint1024 var) { return this->multiply(var); }
		uint1024 uint1024::operator/(uint64_t var) { return this->divide(var); }
		uint1024 uint1024::operator/(uint1024 var) { return this->divide(var); }

		void uint1024::operator+=(uint64_t var) { *this = this->add(var); }
		void uint1024::operator+=(uint1024 var) { *this = this->add(var); }
		void uint1024::operator-=(uint64_t var) { *this = this->substract(var); }
		void uint1024::operator-=(uint1024 var) { *this = this->substract(var); }
		void uint1024::operator*=(uint64_t var) { *this = this->multiply(var); }
		void uint1024::operator*=(uint1024 var) { *this = this->multiply(var); }
		void uint1024::operator/=(uint64_t var) { *this = this->divide(var); }
		void uint1024::operator/=(uint1024 var) { *this = this->divide(var); }

		uint1024 uint1024::operator++()
		{
			*this += uint1024(1);
			return *this;
		}

		uint1024 uint1024::operator--()
		{
			*this -= uint1024(1);
			return *this;
		}

		uint1024 uint1024::operator%(uint1024 var) { return this->mod(var); }
		void uint1024::operator%=(uint1024 var) { *this = this->mod(var); }

		bool uint1024::operator==(uint1024 var)
		{
			for (size_t i = 0; i < 1024; i++)
			{
				if (this->data[1023 - i] != var.data[1023 - i])
				{
					return false;
				}
			}

			return true;
		}

		bool uint1024::operator<(uint1024 item)
		{
			for (size_t i = 0; i < 1024; i++)
			{
				if (this->data[1023 - i] == 1 && item.data[1023 - i] == 0)
				{
					return false;
				}
				else if (this->data[1023 - i] == 0 && item.data[1023 - i] == 1)
				{
					return true;
				}
			}

			return false;
		}

		bool uint1024::operator>(uint1024 item)
		{
			for (size_t i = 0; i < 1024; i++)
			{
				if (this->data[1023 - i] == 0 && item.data[1023 - i] == 1)
				{
					return false;
				}
				else if (this->data[1023 - i] == 1 && item.data[1023 - i] == 0)
				{
					return true;
				}
			}

			return false;
		}

		bool uint1024::operator<=(uint1024 item)
		{
			for (size_t i = 0; i < 1024; i++)
			{
				if (this->data[1023 - i] == 1 && item.data[1023 - i] == 0)
				{
					return false;
				}
				else if (this->data[1023 - i] == 0 && item.data[1023 - i] == 1)
				{
					return true;
				}
			}

			return true;
		}

		bool uint1024::operator>=(uint1024 item)
		{
			for (size_t i = 0; i < 1024; i++)
			{
				if (this->data[1023 - i] == 0 && item.data[1023 - i] == 1)
				{
					return false;
				}
				else if (this->data[1023 - i] == 1 && item.data[1023 - i] == 0)
				{
					return true;
				}
			}

			return false;
		}

		bool uint1024::operator!=(uint1024 item) { return !(*this == item); }

		std::ostream& operator << (std::ostream& os, uint1024 integer) { return os << integer.GetBinaryData(); }

		std::string uint1024::DivisionAdaptedSubHelpFunction(std::string This, std::string init)
		{
			uint1024 CThis = uint1024(This);
			uint1024 CInit = uint1024(init);

			uint1024 RawResult = CThis - CInit;

			std::string result("");
			bool StartWritingZeros(false);

			for (size_t i = 0; i < 1024; i++)
			{
				if (RawResult.data[1023 - i] == 1)
				{
					result += "1";
					StartWritingZeros = true;
				}
				if (RawResult.data[1023 - i] == 0 && StartWritingZeros == true)
				{
					result += "0";
				}
			}

			return result;
		}

		uint1024 pow(uint1024 base, uint1024 exp)
		{
			uint1024 This(base);
			return This.pow(exp);
		}

		uint1024 pow(uint1024 base, uint64_t exp)
		{
			uint1024 This(base);
			return This.pow(exp);
		}

		uint1024 mod(uint1024 divisor, uint1024 divider)
		{
			uint1024 This(divisor);
			return This.divide(divider);
		}

		uint1024 mod(uint1024 divisor, uint64_t divider)
		{
			uint1024 This(divisor);
			return This.divide(divider);
		}

		uint1024 log(uint1024 base, uint1024 pot)
		{
			uint1024 This(base);
			return This.log(pot);
		}

		uint1024 log(uint64_t base, uint1024 pot)
		{
			uint1024 This(base);
			return This.log(pot);
		}

		uint1024 log10(uint1024 pot)
		{
			return pot.log10();
		}

		uint1024 sqrt(uint1024 radiant)
		{
			return radiant.sqrt();
		}
	}
}