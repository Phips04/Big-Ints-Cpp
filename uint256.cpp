#pragma once

#include "uint256.h"

#include "uint128.h"

#include <bitset>
#include <string>
#include <initializer_list>
#include <forward_list>
#include <limits>
#include <iostream>


namespace BigInts
{
	namespace uint256
	{
		uint256::uint256() { this->data = std::bitset<256>(); }
		uint256::uint256(int32_t init) { if (init < 0) { throw std::invalid_argument{ "argument (type of int32_t) was negative, int256 is unsigned" }; } this->data = std::bitset<256>(init); }
		uint256::uint256(uint32_t init) { this->data = std::bitset<256>(init); }
		uint256::uint256(int64_t init) { if (init < 0) { throw std::invalid_argument{ "argument (type of int64_t) was negative, int256 is unsigned" }; } this->data = std::bitset<256>(init); }
		uint256::uint256(uint64_t init) { this->data = std::bitset<256>(init); }
		uint256::uint256(uint128::uint128 init) { this->data = std::bitset<256>(0); for (size_t i = 0; i < 128; i++) { this->data[i] = init.GetBinaryData()[i]; }}
		uint256::uint256(std::bitset<256> init) { this->data = init; }
		uint256::uint256(std::string init)
		{
			for (size_t i = 0; i < init.length(); i++)
			{
				if (init.at(i) != *"0" && init.at(i) != *"1")
				{
					this->data = std::bitset<256>(0);
					throw std::invalid_argument{ "Argument (type of std::string) was not either '0' or '1'" };
				}
			}

			this->data = std::bitset<256>(init);
		}

		uint256 uint256::add(uint64_t arg)
		{
			return this->add(uint256(arg));
		}

		uint256 uint256::add(uint256 arg)
		{
			std::bitset<256> result(0);

			int transmitter(0);

			for (size_t i = 0; i < 256; i++)
			{
				if (arg.data[i] == 1 && this->data[i] == 1 && transmitter == 1) // OK
				{
					result[i] = 1;
					if (i == 255)
					{
						throw std::overflow_error{ "The result will become greater than 2^256, which is the maximal value of int256" };
					}
					transmitter = 1;
					continue;
				}

				if ((arg.data[i] == 1 && this->data[i] == 1 && transmitter == 0) ||
					(arg.data[i] == 1 && this->data[i] == 0 && transmitter == 1) ||
					(arg.data[i] == 0 && this->data[i] == 1 && transmitter == 1))
				{
					result[i] = 0;
					if (i == 255)
					{
						throw std::overflow_error{ "The result will grow larger than 2^256, which is the maximal value of int256" };
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

			return uint256(result);
		}

		uint256 uint256::add(std::initializer_list<uint256> args)
		{
			uint256 result(*this);

			for (uint256 arg : args)
			{
				result += arg;
			}

			return result;
		}

		uint256 uint256::substract(uint64_t arg)
		{
			return this->substract(uint256(arg));
		}

		uint256 uint256::substract(uint256 init)
		{
			std::bitset<256> result(0);

			int transmitter(0);

			if (*this < init)
			{
				throw std::underflow_error{ "The result will be negative, int256 is unsigned" };
			}

			for (size_t i = 0; i < 256; i++)
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

				if (i == 255 && transmitter == 1)
				{
					throw;
				}
			}

			return uint256(result);
		}

		uint256 uint256::substract(std::initializer_list<uint256> inits)
		{
			uint256 result(*this);

			for (auto i : inits)
			{
				result -= i;
			}
			return result;

			return uint256(result);
		}

		uint256 uint256::multiply(uint64_t init)
		{
			return this->multiply(uint256(init));
		}

		uint256 uint256::multiply(uint256 init)
		{
			std::forward_list<uint256> ItemsToAdd;

			int ThisLength(0), InitLength(0);
			bool ThisLengthFound(false), InitLengthFound(false);

			for (size_t i = 0; i < 256; i++)
			{
				if (this->data[255 - i] == 1 && ThisLengthFound == false)
				{
					ThisLength = 256 - i;
					ThisLengthFound = true;
				}

				if (init.data[255 - i] == 1 && InitLengthFound == false)
				{
					InitLength = 256 - i;
					InitLengthFound = true;
				}

				if (ThisLengthFound && InitLengthFound)
				{
					if (ThisLength + InitLength - 1 > 256)
					{
						throw std::overflow_error{ "The result will grow larger than 2^256, which is the maximal value of int256" };
					}
				}
			}

			for (size_t i = 0; i < 256; i++)
			{
				if (init.data[i] == 1)
				{
					std::bitset<256> item(0);
					for (size_t x = 0; x < 256; x++)
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

					ItemsToAdd.push_front(uint256(item));
				}
			}

			uint256 result(0);

			for (auto i : ItemsToAdd)
			{
				result += i;
			}

			return result;
		}

		uint256 uint256::multiply(std::initializer_list<uint256> inits)
		{
			uint256 result(*this);

			for (auto i : inits)
			{
				result *= i;
			}

			return result;
		}

		uint256 uint256::divide(uint64_t init)
		{
			return this->divide(uint256(init));
		}

		uint256 uint256::divide(uint256 init)
		{
			if (init.data == std::bitset<256>(0))
			{
				throw std::invalid_argument{ "Argument was '0', division by '0' is not defined" };
			}

			if (*this < init)
			{
				return uint256(0);
			}

			std::string ThisStream(""), InitStream(""), ThisCurrentStream(""), ResultStream("");
			bool StartRecordingThis(false), StartRecordingInit(false);

			for (size_t i = 0; i < 256; i++)
			{
				if (this->data[255 - i] == 1)
				{
					ThisStream += "1";
					StartRecordingThis = true;
				}
				else if (StartRecordingThis == true)
				{
					ThisStream += "0";
				}

				if (init.data[255 - i] == 1)
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
				if (uint256(ThisCurrentStream) < uint256(InitStream))
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

			if (uint256(ThisCurrentStream) < uint256(InitStream))
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

			return uint256(ResultStream);
		}

		uint256 uint256::divide(std::initializer_list<uint256> inits)
		{
			uint256 result(*this);

			for (auto i : inits)
			{
				result /= i;
			}
			return result;
		}

		uint256 uint256::pow(uint64_t init)
		{
			return this->pow(uint256(init));
		}

		uint256 uint256::pow(uint256 exp)
		{
			if (exp == uint256(0))
			{
				return uint256(1);
			}

			uint256 result(*this);

			for (uint256 i(1); i < exp; ++i)
			{
				result *= *this;
			}

			return result;
		}

		uint256 uint256::pow(std::initializer_list<uint256> inits)
		{
			uint256 FinalExp(1);

			for (uint256 item : inits)
			{
				FinalExp *= item;
			}

			return this->pow(FinalExp);
		}

		uint256 uint256::log(uint256 base)
		{
			if (base == uint256(0))
			{
				throw std::invalid_argument{ "Argument was '0', logarithm which base = '0' is not defined" };
			}

			if (*this == uint256(0))
			{
				throw std::domain_error{ "The value of the object calling the function 'log(int256 base)' was '0', logarithm with exponent = '0' is not defined" };
			}


			if (*this < base)
			{
				return uint256(0);
			}

			int CurrentPosition(256 / base.TryToInt()), CurrentOffsetLength(256 / (2 * base.TryToInt()));

			while (true)
			{
				if (base.pow(uint256(CurrentPosition)) <= *this &&
					base.pow(uint256(CurrentPosition + 1)) >= *this)
				{
					return CurrentPosition;
				}

				if (CurrentPosition <= 1)
				{
					return uint256(0);
				}

				if (base.pow(uint256(CurrentPosition)) <= *this)
				{
					CurrentPosition += CurrentOffsetLength;
					CurrentOffsetLength /= 2;
					continue;
				}

				if (base.pow(uint256(CurrentPosition)) >= *this)
				{
					CurrentPosition -= CurrentOffsetLength;
					CurrentOffsetLength /= 2;
					continue;
				}
			}
		}

		uint256 uint256::log10() { return this->log(uint256(10)); }

		uint256 uint256::sqrt()
		{
			if (*this == uint256(0))
			{
				return uint256(0);
			}

			if (*this == uint256(1))
			{
				return uint256(1);
			}

			uint256 CurrentPosition(UINT128_MAX / 2), CurrentOffsetLength(UINT128_MAX / 4 + 1);

			while (true)
			{
				if (CurrentPosition.pow(uint256(2)) <= *this &&
					uint256(CurrentPosition + 1).pow(uint256(2)) >= *this)
				{
					return CurrentPosition;
				}

				if (CurrentPosition <= 2)
				{
					return uint256(1);
				}

				if (CurrentPosition.pow(uint256(2)) <= *this)
				{
					CurrentPosition += CurrentOffsetLength;
					CurrentOffsetLength /= 2;
					continue;
				}

				if (CurrentPosition.pow(uint256(2)) >= *this)
				{
					CurrentPosition -= CurrentOffsetLength;
					CurrentOffsetLength /= 2;
					continue;
				}
			}

			return uint256();
		}

		uint256 uint256::mod(uint256 init)
		{
			return (*this - (*this / init * init));
		}

		int uint256::TryToInt()
		{
			if (*this > uint256(INT32_MAX))
			{
				throw std::bad_cast{};
			}

			return (int)this->data.to_ulong();
		}

		unsigned long uint256::TryToLong()
		{
			if (*this > uint256(uint64_t(ULONG_MAX)))
			{
				throw std::bad_cast{};
			}

			return this->data.to_ulong();
		}

		uint64_t uint256::TryToUint64_t()
		{
			if (*this > uint256(uint64_t(ULLONG_MAX)))
			{
				throw std::bad_cast{};
			}

			return this->data.to_ullong();
		}

		uint128::uint128 uint256::TryToUInt128()
		{
			if (*this > uint256(UINT128_MAX))
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

		std::string uint256::ToBinaryString() { return this->data.to_string(); }
		std::bitset<256> uint256::GetBinaryData() { return this->data; }

		uint256 uint256::operator+(uint64_t var) { return this->add(var); }
		uint256 uint256::operator+(uint256 var) { return this->add(var); }
		uint256 uint256::operator-(uint64_t var) { return this->substract(var); }
		uint256 uint256::operator-(uint256 var) { return this->substract(var); }
		uint256 uint256::operator*(uint64_t var) { return this->multiply(var); }
		uint256 uint256::operator*(uint256 var) { return this->multiply(var); }
		uint256 uint256::operator/(uint64_t var) { return this->divide(var); }
		uint256 uint256::operator/(uint256 var) { return this->divide(var); }

		void uint256::operator+=(uint64_t var) { *this = this->add(var); }
		void uint256::operator+=(uint256 var) { *this = this->add(var); }
		void uint256::operator-=(uint64_t var) { *this = this->substract(var); }
		void uint256::operator-=(uint256 var) { *this = this->substract(var); }
		void uint256::operator*=(uint64_t var) { *this = this->multiply(var); }
		void uint256::operator*=(uint256 var) { *this = this->multiply(var); }
		void uint256::operator/=(uint64_t var) { *this = this->divide(var); }
		void uint256::operator/=(uint256 var) { *this = this->divide(var); }

		uint256 uint256::operator++()
		{
			*this += uint256(1);
			return *this;
		}

		uint256 uint256::operator--()
		{
			*this -= uint256(1);
			return *this;
		}

		uint256 uint256::operator%(uint256 var) { return this->mod(var); }
		void uint256::operator%=(uint256 var) { *this = this->mod(var); }

		bool uint256::operator==(uint256 var)
		{
			for (size_t i = 0; i < 256; i++)
			{
				if (this->data[255 - i] != var.data[255 - i])
				{
					return false;
				}
			}

			return true;
		}

		bool uint256::operator<(uint256 item)
		{
			for (size_t i = 0; i < 256; i++)
			{
				if (this->data[255 - i] == 1 && item.data[255 - i] == 0)
				{
					return false;
				}
				else if (this->data[255 - i] == 0 && item.data[255 - i] == 1)
				{
					return true;
				}
			}

			return false;
		}

		bool uint256::operator>(uint256 item)
		{
			for (size_t i = 0; i < 256; i++)
			{
				if (this->data[255 - i] == 0 && item.data[255 - i] == 1)
				{
					return false;
				}
				else if (this->data[255 - i] == 1 && item.data[255 - i] == 0)
				{
					return true;
				}
			}

			return false;
		}

		bool uint256::operator<=(uint256 item)
		{
			for (size_t i = 0; i < 256; i++)
			{
				if (this->data[255 - i] == 1 && item.data[255 - i] == 0)
				{
					return false;
				}
				else if (this->data[255 - i] == 0 && item.data[255 - i] == 1)
				{
					return true;
				}
			}

			return true;
		}

		bool uint256::operator>=(uint256 item)
		{
			for (size_t i = 0; i < 256; i++)
			{
				if (this->data[255 - i] == 0 && item.data[255 - i] == 1)
				{
					return false;
				}
				else if (this->data[255 - i] == 1 && item.data[255 - i] == 0)
				{
					return true;
				}
			}

			return false;
		}

		bool uint256::operator!=(uint256 item) { return !(*this == item); }

		std::ostream& operator << (std::ostream& os, uint256 integer) { return os << integer.GetBinaryData(); }

		std::string uint256::DivisionAdaptedSubHelpFunction(std::string This, std::string init)
		{
			uint256 CThis = uint256(This);
			uint256 CInit = uint256(init);

			uint256 RawResult = CThis - CInit;

			std::string result("");
			bool StartWritingZeros(false);

			for (size_t i = 0; i < 256; i++)
			{
				if (RawResult.data[255 - i] == 1)
				{
					result += "1";
					StartWritingZeros = true;
				}
				if (RawResult.data[255 - i] == 0 && StartWritingZeros == true)
				{
					result += "0";
				}
			}

			return result;
		}

		uint256 pow(uint256 base, uint256 exp)
		{
			uint256 This(base);
			return This.pow(exp);
		}

		uint256 pow(uint256 base, uint64_t exp)
		{
			uint256 This(base);
			return This.pow(exp);
		}

		uint256 mod(uint256 divisor, uint256 divider)
		{
			uint256 This(divisor);
			return This.divide(divider);
		}

		uint256 mod(uint256 divisor, uint64_t divider)
		{
			uint256 This(divisor);
			return This.divide(divider);
		}

		uint256 log(uint256 base, uint256 pot)
		{
			uint256 This(base);
			return This.log(pot);
		}

		uint256 log(uint64_t base, uint256 pot)
		{
			uint256 This(base);
			return This.log(pot);
		}

		uint256 log10(uint256 pot)
		{
			return pot.log10();
		}

		uint256 sqrt(uint256 radiant)
		{
			return radiant.sqrt();
		}
	}
}