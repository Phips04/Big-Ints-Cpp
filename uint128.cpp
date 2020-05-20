#pragma once

#include "uint128.h"

#include <bitset>
#include <string>
#include <initializer_list>
#include <forward_list>
#include <limits>
#include <iostream>


namespace BigInts
{
	namespace uint128
	{
		uint128::uint128() { this->data = std::bitset<128>(); }
		uint128::uint128(int32_t init) { if (init < 0) { throw std::invalid_argument{ "argument (type of int32_t) was negative, uint128 is unsigned" }; } this->data = std::bitset<128>(init); }
		uint128::uint128(uint32_t init) { this->data = std::bitset<128>(init); }
		uint128::uint128(int64_t init) { if (init < 0) { throw std::invalid_argument{ "argument (type of int64_t) was negative, uint128 is unsigned" }; } this->data = std::bitset<128>(init); }
		uint128::uint128(uint64_t init) { this->data = std::bitset<128>(init); }
		uint128::uint128(std::bitset<128> init) { this->data = init; }

		uint128::uint128(std::string init)
		{
			for (size_t i = 0; i < init.length(); i++)
			{
				if (init.at(i) != *"0" && init.at(i) != *"1")
				{
					this->data = std::bitset<128>(0);
					throw std::invalid_argument{ "Argument (type of std::string) was not either '0' or '1'" };
				}
			}

			this->data = std::bitset<128>(init);
		}

		uint128 uint128::add(uint64_t arg)
		{
			return this->add(uint128(arg));
		}

		uint128 uint128::add(uint128 arg)
		{
			std::bitset<128> result(0);

			int transmitter(0);

			for (size_t i = 0; i < 128; i++)
			{
				if (arg.data[i] == 1 && this->data[i] == 1 && transmitter == 1) // OK
				{
					result[i] = 1;
					if (i == 127)
					{
						throw std::overflow_error{ "The result will become greater than 2^128, which is the maximal value of uint128" };
					}
					transmitter = 1;
					continue;
				}

				if ((arg.data[i] == 1 && this->data[i] == 1 && transmitter == 0) ||
					(arg.data[i] == 1 && this->data[i] == 0 && transmitter == 1) ||
					(arg.data[i] == 0 && this->data[i] == 1 && transmitter == 1))
				{
					result[i] = 0;
					if (i == 127)
					{
						throw std::overflow_error{ "The result will grow larger than 2^128, which is the maximal value of uint128" };
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

			return uint128(result);
		}

		uint128 uint128::add(std::initializer_list<uint128> args)
		{
			uint128 result(*this);

			for (uint128 arg : args)
			{
				result += arg;
			}

			return result;
		}

		uint128 uint128::substract(uint64_t arg)
		{
			return this->substract(uint128(arg));
		}

		uint128 uint128::substract(uint128 init)
		{
			std::bitset<128> result(0);

			int transmitter(0);

			if (*this < init)
			{
				throw std::underflow_error{ "The result will be negative, uint128 is unsigned" };
			}

			for (size_t i = 0; i < 128; i++)
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

				if (i == 127 && transmitter == 1)
				{
					throw;
				}
			}

			return uint128(result);
		}

		uint128 uint128::substract(std::initializer_list<uint128> inits)
		{
			uint128 result(*this);

			for (auto i : inits)
			{
				result -= i;
			}
			return result;

			return uint128(result);
		}

		uint128 uint128::multiply(uint64_t init)
		{
			return this->multiply(uint128(init));
		}

		uint128 uint128::multiply(uint128 init)
		{
			std::forward_list<uint128> ItemsToAdd;

			int ThisLength(0), InitLength(0);
			bool ThisLengthFound(false), InitLengthFound(false);

			for (size_t i = 0; i < 128; i++)
			{
				if (this->data[127 - i] == 1 && ThisLengthFound == false)
				{
					ThisLength = 128 - i;
					ThisLengthFound = true;
				}

				if (init.data[127 - i] == 1 && InitLengthFound == false)
				{
					InitLength = 128 - i;
					InitLengthFound = true;
				}

				if (ThisLengthFound && InitLengthFound)
				{
					if (ThisLength + InitLength - 1 > 128)
					{
						throw std::overflow_error{ "The result will grow larger than 2^128, which is the maximal value of int128" };
					}
				}
			}

			for (size_t i = 0; i < 128; i++)
			{
				if (init.data[i] == 1)
				{
					std::bitset<128> item(0);
					for (size_t x = 0; x < 128; x++)
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

					ItemsToAdd.push_front(uint128(item));
				}
			}

			uint128 result(0);

			for (auto i : ItemsToAdd)
			{
				result += i;
			}

			return result;
		}

		uint128 uint128::multiply(std::initializer_list<uint128> inits)
		{
			uint128 result(*this);

			for (auto i : inits)
			{
				result *= i;
			}

			return result;
		}

		uint128 uint128::divide(uint64_t init)
		{
			return this->divide(uint128(init));
		}

		uint128 uint128::divide(uint128 init)
		{
			if (init.data == std::bitset<128>(0))
			{
				throw std::invalid_argument{ "Argument was '0', division by '0' is not defined" };
			}

			if (*this < init)
			{
				return uint128(0);
			}

			std::string ThisStream(""), InitStream(""), ThisCurrentStream(""), ResultStream("");
			bool StartRecordingThis(false), StartRecordingInit(false);

			for (size_t i = 0; i < 128; i++)
			{
				if (this->data[127 - i] == 1)
				{
					ThisStream += "1";
					StartRecordingThis = true;
				}
				else if (StartRecordingThis == true)
				{
					ThisStream += "0";
				}

				if (init.data[127 - i] == 1)
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
				if (uint128(ThisCurrentStream) < uint128(InitStream))
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

			if (uint128(ThisCurrentStream) < uint128(InitStream))
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

			return uint128(ResultStream);
		}

		uint128 uint128::divide(std::initializer_list<uint128> inits)
		{
			uint128 result(*this);

			for (auto i : inits)
			{
				result /= i;
			}
			return result;
		}

		uint128 uint128::pow(uint64_t init)
		{
			return this->pow(uint128(init));
		}

		uint128 uint128::pow(uint128 exp)
		{
			if (exp == uint128(0))
			{
				return uint128(1);
			}

			uint128 result(*this);

			for (uint128 i(1); i < exp; ++i)
			{
				result *= *this;
			}

			return result;
		}

		uint128 uint128::pow(std::initializer_list<uint128> inits)
		{
			uint128 FinalExp(1);

			for (uint128 item : inits)
			{
				FinalExp *= item;
			}

			return this->pow(FinalExp);
		}

		uint128 uint128::log(uint128 base)
		{
			if (base == uint128(0))
			{
				throw std::invalid_argument{ "Argument was '0', logarithm which base = '0' is not defined" };
			}

			if (*this == uint128(0))
			{
				throw std::domain_error{ "The value of the object calling the function 'log(uint128 base)' was '0', logarithm with exponent = '0' is not defined" };
			}


			if (*this < base)
			{
				return uint128(0);
			}

			int CurrentPosition(128 / base.TryToInt()), CurrentOffsetLength(128 / (2 * base.TryToInt()));

			while (true)
			{
				if (base.pow(uint128(CurrentPosition)) <= *this &&
					base.pow(uint128(CurrentPosition + 1)) >= *this)
				{
					return CurrentPosition;
				}

				if (CurrentPosition <= 1)
				{
					return uint128(0);
				}

				if (base.pow(uint128(CurrentPosition)) <= *this)
				{
					CurrentPosition += CurrentOffsetLength;
					CurrentOffsetLength /= 2;
					continue;
				}

				if (base.pow(uint128(CurrentPosition)) >= *this)
				{
					CurrentPosition -= CurrentOffsetLength;
					CurrentOffsetLength /= 2;
					continue;
				}
			}
		}

		uint128 uint128::log10() { return this->log(uint128(10)); }

		uint128 uint128::sqrt()
		{
			if (*this == uint128(0))
			{
				return uint128(0);
			}

			if (*this == uint128(1))
			{
				return uint128(1);
			}

			uint128 CurrentPosition(UINT64_MAX / 2), CurrentOffsetLength(UINT64_MAX / 4 + 1);

			while (true)
			{
				if (CurrentPosition.pow(uint128(2)) <= *this &&
					uint128(CurrentPosition + 1).pow(uint128(2)) >= *this)
				{
					return CurrentPosition;
				}

				if (CurrentPosition <= 2)
				{
					return uint128(1);
				}

				if (CurrentPosition.pow(uint128(2)) <= *this)
				{
					CurrentPosition += CurrentOffsetLength;
					CurrentOffsetLength /= 2;
					continue;
				}

				if (CurrentPosition.pow(uint128(2)) >= *this)
				{
					CurrentPosition -= CurrentOffsetLength;
					CurrentOffsetLength /= 2;
					continue;
				}
			}

			return uint128();
		}

		uint128 uint128::mod(uint128 init)
		{
			return (*this - (*this / init * init));
		}

		int uint128::TryToInt()
		{
			if (*this > uint128(INT32_MAX))
			{
				throw std::bad_cast{};
			}

			return (int)this->data.to_ulong();
		}

		unsigned long uint128::TryToLong()
		{
			if (*this > uint128(uint64_t(ULONG_MAX)))
			{
				throw std::bad_cast{};
			}

			return this->data.to_ulong();
		}

		uint64_t uint128::TryToUint64_t()
		{
			if (*this > uint128(uint64_t(ULLONG_MAX)))
			{
				throw std::bad_cast{};
			}

			return this->data.to_ullong();
		}

		std::string uint128::ToBinaryString() { return this->data.to_string(); }
		std::bitset<128> uint128::GetBinaryData() { return this->data; }

		uint128 uint128::operator+(uint64_t var) { return this->add(var); }
		uint128 uint128::operator+(uint128 var) { return this->add(var); }
		uint128 uint128::operator-(uint64_t var) { return this->substract(var); }
		uint128 uint128::operator-(uint128 var) { return this->substract(var); }
		uint128 uint128::operator*(uint64_t var) { return this->multiply(var); }
		uint128 uint128::operator*(uint128 var) { return this->multiply(var); }
		uint128 uint128::operator/(uint64_t var) { return this->divide(var); }
		uint128 uint128::operator/(uint128 var) { return this->divide(var); }

		void uint128::operator+=(uint64_t var) { *this = this->add(var); }
		void uint128::operator+=(uint128 var) { *this = this->add(var); }
		void uint128::operator-=(uint64_t var) { *this = this->substract(var); }
		void uint128::operator-=(uint128 var) { *this = this->substract(var); }
		void uint128::operator*=(uint64_t var) { *this = this->multiply(var); }
		void uint128::operator*=(uint128 var) { *this = this->multiply(var); }
		void uint128::operator/=(uint64_t var) { *this = this->divide(var); }
		void uint128::operator/=(uint128 var) { *this = this->divide(var); }

		uint128 uint128::operator++()
		{
			*this += uint128(1);
			return *this;
		}

		uint128 uint128::operator--()
		{
			*this -= uint128(1);
			return *this;
		}

		uint128 uint128::operator%(uint128 var) { return this->mod(var); }
		void uint128::operator%=(uint128 var) { *this = this->mod(var); }

		bool uint128::operator==(uint128 var)
		{
			for (size_t i = 0; i < 128; i++)
			{
				if (this->data[127 - i] != var.data[127 - i])
				{
					return false;
				}
			}

			return true;
		}

		bool uint128::operator<(uint128 item)
		{
			for (size_t i = 0; i < 128; i++)
			{
				if (this->data[127 - i] == 1 && item.data[127 - i] == 0)
				{
					return false;
				}
				else if (this->data[127 - i] == 0 && item.data[127 - i] == 1)
				{
					return true;
				}
			}

			return false;
		}

		bool uint128::operator>(uint128 item)
		{
			for (size_t i = 0; i < 128; i++)
			{
				if (this->data[127 - i] == 0 && item.data[127 - i] == 1)
				{
					return false;
				}
				else if (this->data[127 - i] == 1 && item.data[127 - i] == 0)
				{
					return true;
				}
			}

			return false;
		}

		bool uint128::operator<=(uint128 item)
		{
			for (size_t i = 0; i < 128; i++)
			{
				if (this->data[127 - i] == 1 && item.data[127 - i] == 0)
				{
					return false;
				}
				else if (this->data[127 - i] == 0 && item.data[127 - i] == 1)
				{
					return true;
				}
			}

			return true;
		}

		bool uint128::operator>=(uint128 item)
		{
			for (size_t i = 0; i < 128; i++)
			{
				if (this->data[127 - i] == 0 && item.data[127 - i] == 1)
				{
					return false;
				}
				else if (this->data[127 - i] == 1 && item.data[127 - i] == 0)
				{
					return true;
				}
			}

			return false;
		}

		bool uint128::operator!=(uint128 item) { return !(*this == item); }

		std::ostream& operator << (std::ostream& os, uint128 integer) { return os << integer.GetBinaryData(); }

		std::string uint128::DivisionAdaptedSubHelpFunction(std::string This, std::string init)
		{
			uint128 CThis = uint128(This);
			uint128 CInit = uint128(init);

			uint128 RawResult = CThis - CInit;

			std::string result("");
			bool StartWritingZeros(false);

			for (size_t i = 0; i < 128; i++)
			{
				if (RawResult.data[127 - i] == 1)
				{
					result += "1";
					StartWritingZeros = true;
				}
				if (RawResult.data[127 - i] == 0 && StartWritingZeros == true)
				{
					result += "0";
				}
			}

			return result;
		}

		uint128 pow(uint128 base, uint128 exp)
		{
			uint128 This(base);
			return This.pow(exp);
		}

		uint128 pow(uint128 base, uint64_t exp)
		{
			uint128 This(base);
			return This.pow(exp);
		}

		uint128 mod(uint128 divisor, uint128 divider)
		{
			uint128 This(divisor);
			return This.divide(divider);
		}

		uint128 mod(uint128 divisor, uint64_t divider)
		{
			uint128 This(divisor);
			return This.divide(divider);
		}

		uint128 log(uint128 base, uint128 pot)
		{
			uint128 This(base);
			return This.log(pot);
		}

		uint128 log(uint64_t base, uint128 pot)
		{
			uint128 This(base);
			return This.log(pot);
		}

		uint128 log10(uint128 pot)
		{
			return pot.log10();
		}

		uint128 sqrt(uint128 radiant)
		{
			return radiant.sqrt();
		}
	}
}