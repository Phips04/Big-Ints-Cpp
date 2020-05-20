#pragma once

#include "uint512.h"

#include "uint128.h"
#include "uint256.h"

#include <bitset>
#include <string>
#include <initializer_list>
#include <forward_list>
#include <limits>
#include <iostream>


namespace BigInts
{
	namespace uint512
	{
		uint512::uint512() { this->data = std::bitset<512>(); }
		uint512::uint512(int32_t init) { if (init < 0) { throw std::invalid_argument{ "argument (type of int32_t) was negative, int512 is unsigned" }; } this->data = std::bitset<512>(init); }
		uint512::uint512(uint32_t init) { this->data = std::bitset<512>(init); }
		uint512::uint512(int64_t init) { if (init < 0) { throw std::invalid_argument{ "argument (type of int64_t) was negative, int512 is unsigned" }; } this->data = std::bitset<512>(init); }
		uint512::uint512(uint64_t init) { this->data = std::bitset<512>(init); }
		uint512::uint512(uint128::uint128 init) { this->data = std::bitset<512>(0); for (size_t i = 0; i < 128; i++) { this->data[i] = init.GetBinaryData()[i]; } }
		uint512::uint512(uint256::uint256 init) { this->data = std::bitset<512>(0); for (size_t i = 0; i < 256; i++) { this->data[i] = init.GetBinaryData()[i]; } }
		uint512::uint512(std::bitset<512> init) { this->data = init; }
		uint512::uint512(std::string init)
		{
			for (size_t i = 0; i < init.length(); i++)
			{
				if (init.at(i) != *"0" && init.at(i) != *"1")
				{
					this->data = std::bitset<512>(0);
					throw std::invalid_argument{ "Argument (type of std::string) was not either '0' or '1'" };
				}
			}

			this->data = std::bitset<512>(init);
		}

		uint512 uint512::add(uint64_t arg)
		{
			return this->add(uint512(arg));
		}

		uint512 uint512::add(uint512 arg)
		{
			std::bitset<512> result(0);

			int transmitter(0);

			for (size_t i = 0; i < 512; i++)
			{
				if (arg.data[i] == 1 && this->data[i] == 1 && transmitter == 1) // OK
				{
					result[i] = 1;
					if (i == 511)
					{
						throw std::overflow_error{ "The result will become greater than 2^512, which is the maximal value of int512" };
					}
					transmitter = 1;
					continue;
				}

				if ((arg.data[i] == 1 && this->data[i] == 1 && transmitter == 0) ||
					(arg.data[i] == 1 && this->data[i] == 0 && transmitter == 1) ||
					(arg.data[i] == 0 && this->data[i] == 1 && transmitter == 1))
				{
					result[i] = 0;
					if (i == 511)
					{
						throw std::overflow_error{ "The result will grow larger than 2^512, which is the maximal value of int512" };
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

			return uint512(result);
		}

		uint512 uint512::add(std::initializer_list<uint512> args)
		{
			uint512 result(*this);

			for (uint512 arg : args)
			{
				result += arg;
			}

			return result;
		}

		uint512 uint512::substract(uint64_t arg)
		{
			return this->substract(uint512(arg));
		}

		uint512 uint512::substract(uint512 init)
		{
			std::bitset<512> result(0);

			int transmitter(0);

			if (*this < init)
			{
				throw std::underflow_error{ "The result will be negative, int512 is unsigned" };
			}

			for (size_t i = 0; i < 512; i++)
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

				if (i == 511 && transmitter == 1)
				{
					throw;
				}
			}

			return uint512(result);
		}

		uint512 uint512::substract(std::initializer_list<uint512> inits)
		{
			uint512 result(*this);

			for (auto i : inits)
			{
				result -= i;
			}
			return result;

			return uint512(result);
		}

		uint512 uint512::multiply(uint64_t init)
		{
			return this->multiply(uint512(init));
		}

		uint512 uint512::multiply(uint512 init)
		{
			std::forward_list<uint512> ItemsToAdd;

			int ThisLength(0), InitLength(0);
			bool ThisLengthFound(false), InitLengthFound(false);

			for (size_t i = 0; i < 512; i++)
			{
				if (this->data[511 - i] == 1 && ThisLengthFound == false)
				{
					ThisLength = 512 - i;
					ThisLengthFound = true;
				}

				if (init.data[511 - i] == 1 && InitLengthFound == false)
				{
					InitLength = 512 - i;
					InitLengthFound = true;
				}

				if (ThisLengthFound && InitLengthFound)
				{
					if (ThisLength + InitLength - 1 > 512)
					{
						throw std::overflow_error{ "The result will grow larger than 2^512, which is the maximal value of int512" };
					}
				}
			}

			for (size_t i = 0; i < 512; i++)
			{
				if (init.data[i] == 1)
				{
					std::bitset<512> item(0);
					for (size_t x = 0; x < 512; x++)
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

					ItemsToAdd.push_front(uint512(item));
				}
			}

			uint512 result(0);

			for (auto i : ItemsToAdd)
			{
				result += i;
			}

			return result;
		}

		uint512 uint512::multiply(std::initializer_list<uint512> inits)
		{
			uint512 result(*this);

			for (auto i : inits)
			{
				result *= i;
			}

			return result;
		}

		uint512 uint512::divide(uint64_t init)
		{
			return this->divide(uint512(init));
		}

		uint512 uint512::divide(uint512 init)
		{
			if (init.data == std::bitset<512>(0))
			{
				throw std::invalid_argument{ "Argument was '0', division by '0' is not defined" };
			}

			if (*this < init)
			{
				return uint512(0);
			}

			std::string ThisStream(""), InitStream(""), ThisCurrentStream(""), ResultStream("");
			bool StartRecordingThis(false), StartRecordingInit(false);

			for (size_t i = 0; i < 512; i++)
			{
				if (this->data[511 - i] == 1)
				{
					ThisStream += "1";
					StartRecordingThis = true;
				}
				else if (StartRecordingThis == true)
				{
					ThisStream += "0";
				}

				if (init.data[511 - i] == 1)
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
				if (uint512(ThisCurrentStream) < uint512(InitStream))
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

			if (uint512(ThisCurrentStream) < uint512(InitStream))
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

			return uint512(ResultStream);
		}

		uint512 uint512::divide(std::initializer_list<uint512> inits)
		{
			uint512 result(*this);

			for (auto i : inits)
			{
				result /= i;
			}
			return result;
		}

		uint512 uint512::pow(uint64_t init)
		{
			return this->pow(uint512(init));
		}

		uint512 uint512::pow(uint512 exp)
		{
			if (exp == uint512(0))
			{
				return uint512(1);
			}

			uint512 result(*this);

			for (uint512 i(1); i < exp; ++i)
			{
				result *= *this;
			}

			return result;
		}

		uint512 uint512::pow(std::initializer_list<uint512> inits)
		{
			uint512 FinalExp(1);

			for (uint512 item : inits)
			{
				FinalExp *= item;
			}

			return this->pow(FinalExp);
		}

		uint512 uint512::log(uint512 base)
		{
			if (base == uint512(0))
			{
				throw std::invalid_argument{ "Argument was '0', logarithm which base = '0' is not defined" };
			}

			if (*this == uint512(0))
			{
				throw std::domain_error{ "The value of the object calling the function 'log(int512 base)' was '0', logarithm with exponent = '0' is not defined" };
			}


			if (*this < base)
			{
				return uint512(0);
			}

			int CurrentPosition(512 / base.TryToInt()), CurrentOffsetLength(512 / (2 * base.TryToInt()));

			while (true)
			{
				if (base.pow(uint512(CurrentPosition)) <= *this &&
					base.pow(uint512(CurrentPosition + 1)) >= *this)
				{
					return CurrentPosition;
				}

				if (CurrentPosition <= 1)
				{
					return uint512(0);
				}

				if (base.pow(uint512(CurrentPosition)) <= *this)
				{
					CurrentPosition += CurrentOffsetLength;
					CurrentOffsetLength /= 2;
					continue;
				}

				if (base.pow(uint512(CurrentPosition)) >= *this)
				{
					CurrentPosition -= CurrentOffsetLength;
					CurrentOffsetLength /= 2;
					continue;
				}
			}
		}

		uint512 uint512::log10() { return this->log(uint512(10)); }

		uint512 uint512::sqrt()
		{
			if (*this == uint512(0))
			{
				return uint512(0);
			}

			if (*this == uint512(1))
			{
				return uint512(1);
			}

			uint512 CurrentPosition(UINT256_MAX / 2), CurrentOffsetLength(UINT256_MAX / 4 + 1);

			while (true)
			{
				if (CurrentPosition.pow(uint512(2)) <= *this &&
					uint512(CurrentPosition + 1).pow(uint512(2)) >= *this)
				{
					return CurrentPosition;
				}

				if (CurrentPosition <= 2)
				{
					return uint512(1);
				}

				if (CurrentPosition.pow(uint512(2)) <= *this)
				{
					CurrentPosition += CurrentOffsetLength;
					CurrentOffsetLength /= 2;
					continue;
				}

				if (CurrentPosition.pow(uint512(2)) >= *this)
				{
					CurrentPosition -= CurrentOffsetLength;
					CurrentOffsetLength /= 2;
					continue;
				}
			}

			return uint512();
		}

		uint512 uint512::mod(uint512 init)
		{
			return (*this - (*this / init * init));
		}

		int uint512::TryToInt()
		{
			if (*this > uint512(INT32_MAX))
			{
				throw std::bad_cast{};
			}

			return (int)this->data.to_ulong();
		}

		unsigned long uint512::TryToLong()
		{
			if (*this > uint512(uint64_t(ULONG_MAX)))
			{
				throw std::bad_cast{};
			}

			return this->data.to_ulong();
		}

		uint64_t uint512::TryToUint64_t()
		{
			if (*this > uint512(uint64_t(ULLONG_MAX)))
			{
				throw std::bad_cast{};
			}

			return this->data.to_ullong();
		}

		uint128::uint128 uint512::TryToUint128()
		{
			if (*this > uint512(UINT128_MAX))
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

		uint256::uint256 uint512::TryToUint256()
		{
			if (*this > uint512(UINT256_MAX))
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

		std::string uint512::ToBinaryString() { return this->data.to_string(); }
		std::bitset<512> uint512::GetBinaryData() { return this->data; }

		uint512 uint512::operator+(uint64_t var) { return this->add(var); }
		uint512 uint512::operator+(uint512 var) { return this->add(var); }
		uint512 uint512::operator-(uint64_t var) { return this->substract(var); }
		uint512 uint512::operator-(uint512 var) { return this->substract(var); }
		uint512 uint512::operator*(uint64_t var) { return this->multiply(var); }
		uint512 uint512::operator*(uint512 var) { return this->multiply(var); }
		uint512 uint512::operator/(uint64_t var) { return this->divide(var); }
		uint512 uint512::operator/(uint512 var) { return this->divide(var); }

		void uint512::operator+=(uint64_t var) { *this = this->add(var); }
		void uint512::operator+=(uint512 var) { *this = this->add(var); }
		void uint512::operator-=(uint64_t var) { *this = this->substract(var); }
		void uint512::operator-=(uint512 var) { *this = this->substract(var); }
		void uint512::operator*=(uint64_t var) { *this = this->multiply(var); }
		void uint512::operator*=(uint512 var) { *this = this->multiply(var); }
		void uint512::operator/=(uint64_t var) { *this = this->divide(var); }
		void uint512::operator/=(uint512 var) { *this = this->divide(var); }

		uint512 uint512::operator++()
		{
			*this += uint512(1);
			return *this;
		}

		uint512 uint512::operator--()
		{
			*this -= uint512(1);
			return *this;
		}

		uint512 uint512::operator%(uint512 var) { return this->mod(var); }
		void uint512::operator%=(uint512 var) { *this = this->mod(var); }

		bool uint512::operator==(uint512 var)
		{
			for (size_t i = 0; i < 512; i++)
			{
				if (this->data[511 - i] != var.data[511 - i])
				{
					return false;
				}
			}

			return true;
		}

		bool uint512::operator<(uint512 item)
		{
			for (size_t i = 0; i < 512; i++)
			{
				if (this->data[511 - i] == 1 && item.data[511 - i] == 0)
				{
					return false;
				}
				else if (this->data[511 - i] == 0 && item.data[511 - i] == 1)
				{
					return true;
				}
			}

			return false;
		}

		bool uint512::operator>(uint512 item)
		{
			for (size_t i = 0; i < 512; i++)
			{
				if (this->data[511 - i] == 0 && item.data[511 - i] == 1)
				{
					return false;
				}
				else if (this->data[511 - i] == 1 && item.data[511 - i] == 0)
				{
					return true;
				}
			}

			return false;
		}

		bool uint512::operator<=(uint512 item)
		{
			for (size_t i = 0; i < 512; i++)
			{
				if (this->data[511 - i] == 1 && item.data[511 - i] == 0)
				{
					return false;
				}
				else if (this->data[511 - i] == 0 && item.data[511 - i] == 1)
				{
					return true;
				}
			}

			return true;
		}

		bool uint512::operator>=(uint512 item)
		{
			for (size_t i = 0; i < 512; i++)
			{
				if (this->data[511 - i] == 0 && item.data[511 - i] == 1)
				{
					return false;
				}
				else if (this->data[511 - i] == 1 && item.data[511 - i] == 0)
				{
					return true;
				}
			}

			return false;
		}

		bool uint512::operator!=(uint512 item) { return !(*this == item); }

		std::ostream& operator << (std::ostream& os, uint512 integer) { return os << integer.GetBinaryData(); }

		std::string uint512::DivisionAdaptedSubHelpFunction(std::string This, std::string init)
		{
			uint512 CThis = uint512(This);
			uint512 CInit = uint512(init);

			uint512 RawResult = CThis - CInit;

			std::string result("");
			bool StartWritingZeros(false);

			for (size_t i = 0; i < 512; i++)
			{
				if (RawResult.data[511 - i] == 1)
				{
					result += "1";
					StartWritingZeros = true;
				}
				if (RawResult.data[511 - i] == 0 && StartWritingZeros == true)
				{
					result += "0";
				}
			}

			return result;
		}

		uint512 pow(uint512 base, uint512 exp)
		{
			uint512 This(base);
			return This.pow(exp);
		}

		uint512 pow(uint512 base, uint64_t exp)
		{
			uint512 This(base);
			return This.pow(exp);
		}

		uint512 mod(uint512 divisor, uint512 divider)
		{
			uint512 This(divisor);
			return This.divide(divider);
		}

		uint512 mod(uint512 divisor, uint64_t divider)
		{
			uint512 This(divisor);
			return This.divide(divider);
		}

		uint512 log(uint512 base, uint512 pot)
		{
			uint512 This(base);
			return This.log(pot);
		}

		uint512 log(uint64_t base, uint512 pot)
		{
			uint512 This(base);
			return This.log(pot);
		}

		uint512 log10(uint512 pot)
		{
			return pot.log10();
		}

		uint512 sqrt(uint512 radiant)
		{
			return radiant.sqrt();
		}
	}
}
