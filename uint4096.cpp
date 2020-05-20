#pragma once

#include "uint4096.h"

#include "uint128.h"
#include "uint256.h"
#include "uint512.h"
#include "uint1024.h"
#include "uint2048.h"

#include <bitset>
#include <string>
#include <initializer_list>
#include <forward_list>
#include <limits>
#include <iostream>


namespace BigInts
{
	namespace uint4096
	{
		uint4096::uint4096() { this->data = std::bitset<4096>(); }
		uint4096::uint4096(int32_t init) { if (init < 0) { throw std::invalid_argument{ "argument (type of int32_t) was negative, int4096 is unsigned" }; } this->data = std::bitset<4096>(init); }
		uint4096::uint4096(uint32_t init) { this->data = std::bitset<4096>(init); }
		uint4096::uint4096(int64_t init) { if (init < 0) { throw std::invalid_argument{ "argument (type of int64_t) was negative, int4096 is unsigned" }; } this->data = std::bitset<4096>(init); }
		uint4096::uint4096(uint64_t init) { this->data = std::bitset<4096>(init); }
		uint4096::uint4096(uint128::uint128 init) { this->data = std::bitset<4096>(0); for (size_t i = 0; i < 128; i++) { this->data[i] = init.GetBinaryData()[i]; } }
		uint4096::uint4096(uint256::uint256 init) { this->data = std::bitset<4096>(0); for (size_t i = 0; i < 256; i++) { this->data[i] = init.GetBinaryData()[i]; } }
		uint4096::uint4096(uint512::uint512 init) { this->data = std::bitset<4096>(0); for (size_t i = 0; i < 512; i++) { this->data[i] = init.GetBinaryData()[i]; } }
		uint4096::uint4096(uint1024::uint1024 init) { this->data = std::bitset<4096>(0); for (size_t i = 0; i < 1024; i++) { this->data[i] = init.GetBinaryData()[i]; } }
		uint4096::uint4096(uint2048::uint2048 init) { this->data = std::bitset<4096>(0); for (size_t i = 0; i < 2048; i++) { this->data[i] = init.GetBinaryData()[i]; } }
		uint4096::uint4096(std::bitset<4096> init) { this->data = init; }
		uint4096::uint4096(std::string init)
		{
			for (size_t i = 0; i < init.length(); i++)
			{
				if (init.at(i) != *"0" && init.at(i) != *"1")
				{
					this->data = std::bitset<4096>(0);
					throw std::invalid_argument{ "Argument (type of std::string) was not either '0' or '1'" };
				}
			}

			this->data = std::bitset<4096>(init);
		}

		uint4096 uint4096::add(uint64_t arg)
		{
			return this->add(uint4096(arg));
		}

		uint4096 uint4096::add(uint4096 arg)
		{
			std::bitset<4096> result(0);

			int transmitter(0);

			for (size_t i = 0; i < 4096; i++)
			{
				if (arg.data[i] == 1 && this->data[i] == 1 && transmitter == 1) // OK
				{
					result[i] = 1;
					if (i == 4095)
					{
						throw std::overflow_error{ "The result will become greater than 2^4096, which is the maximal value of int4096" };
					}
					transmitter = 1;
					continue;
				}

				if ((arg.data[i] == 1 && this->data[i] == 1 && transmitter == 0) ||
					(arg.data[i] == 1 && this->data[i] == 0 && transmitter == 1) ||
					(arg.data[i] == 0 && this->data[i] == 1 && transmitter == 1))
				{
					result[i] = 0;
					if (i == 4095)
					{
						throw std::overflow_error{ "The result will grow larger than 2^4096, which is the maximal value of int4096" };
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

			return uint4096(result);
		}

		uint4096 uint4096::add(std::initializer_list<uint4096> args)
		{
			uint4096 result(*this);

			for (uint4096 arg : args)
			{
				result += arg;
			}

			return result;
		}

		uint4096 uint4096::substract(uint64_t arg)
		{
			return this->substract(uint4096(arg));
		}

		uint4096 uint4096::substract(uint4096 init)
		{
			std::bitset<4096> result(0);

			int transmitter(0);

			if (*this < init)
			{
				throw std::underflow_error{ "The result will be negative, int4096 is unsigned" };
			}

			for (size_t i = 0; i < 4096; i++)
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

				if (i == 4095 && transmitter == 1)
				{
					throw;
				}
			}

			return uint4096(result);
		}

		uint4096 uint4096::substract(std::initializer_list<uint4096> inits)
		{
			uint4096 result(*this);

			for (auto i : inits)
			{
				result -= i;
			}
			return result;

			return uint4096(result);
		}

		uint4096 uint4096::multiply(uint64_t init)
		{
			return this->multiply(uint4096(init));
		}

		uint4096 uint4096::multiply(uint4096 init)
		{
			std::forward_list<uint4096> ItemsToAdd;

			int ThisLength(0), InitLength(0);
			bool ThisLengthFound(false), InitLengthFound(false);

			for (size_t i = 0; i < 4096; i++)
			{
				if (this->data[4095 - i] == 1 && ThisLengthFound == false)
				{
					ThisLength = 4096 - i;
					ThisLengthFound = true;
				}

				if (init.data[4095 - i] == 1 && InitLengthFound == false)
				{
					InitLength = 4096 - i;
					InitLengthFound = true;
				}

				if (ThisLengthFound && InitLengthFound)
				{
					if (ThisLength + InitLength - 1 > 4096)
					{
						throw std::overflow_error{ "The result will grow larger than 2^4096, which is the maximal value of int4096" };
					}
				}
			}

			for (size_t i = 0; i < 4096; i++)
			{
				if (init.data[i] == 1)
				{
					std::bitset<4096> item(0);
					for (size_t x = 0; x < 4096; x++)
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

					ItemsToAdd.push_front(uint4096(item));
				}
			}

			uint4096 result(0);

			for (auto i : ItemsToAdd)
			{
				result += i;
			}

			return result;
		}

		uint4096 uint4096::multiply(std::initializer_list<uint4096> inits)
		{
			uint4096 result(*this);

			for (auto i : inits)
			{
				result *= i;
			}

			return result;
		}

		uint4096 uint4096::divide(uint64_t init)
		{
			return this->divide(uint4096(init));
		}

		uint4096 uint4096::divide(uint4096 init)
		{
			if (init.data == std::bitset<4096>(0))
			{
				throw std::invalid_argument{ "Argument was '0', division by '0' is not defined" };
			}

			if (*this < init)
			{
				return uint4096(0);
			}

			std::string ThisStream(""), InitStream(""), ThisCurrentStream(""), ResultStream("");
			bool StartRecordingThis(false), StartRecordingInit(false);

			for (size_t i = 0; i < 4096; i++)
			{
				if (this->data[4095 - i] == 1)
				{
					ThisStream += "1";
					StartRecordingThis = true;
				}
				else if (StartRecordingThis == true)
				{
					ThisStream += "0";
				}

				if (init.data[4095 - i] == 1)
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
				if (uint4096(ThisCurrentStream) < uint4096(InitStream))
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

			if (uint4096(ThisCurrentStream) < uint4096(InitStream))
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

			return uint4096(ResultStream);
		}

		uint4096 uint4096::divide(std::initializer_list<uint4096> inits)
		{
			uint4096 result(*this);

			for (auto i : inits)
			{
				result /= i;
			}
			return result;
		}

		uint4096 uint4096::pow(uint64_t init)
		{
			return this->pow(uint4096(init));
		}

		uint4096 uint4096::pow(uint4096 exp)
		{
			if (exp == uint4096(0))
			{
				return uint4096(1);
			}

			uint4096 result(*this);

			for (uint4096 i(1); i < exp; ++i)
			{
				result *= *this;
			}

			return result;
		}

		uint4096 uint4096::pow(std::initializer_list<uint4096> inits)
		{
			uint4096 FinalExp(1);

			for (uint4096 item : inits)
			{
				FinalExp *= item;
			}

			return this->pow(FinalExp);
		}

		uint4096 uint4096::log(uint4096 base)
		{
			if (base == uint4096(0))
			{
				throw std::invalid_argument{ "Argument was '0', logarithm which base = '0' is not defined" };
			}

			if (*this == uint4096(0))
			{
				throw std::domain_error{ "The value of the object calling the function 'log(int4096 base)' was '0', logarithm with exponent = '0' is not defined" };
			}


			if (*this < base)
			{
				return uint4096(0);
			}

			int CurrentPosition(4096 / base.TryToInt()), CurrentOffsetLength(4096 / (2 * base.TryToInt()));

			while (true)
			{
				if (base.pow(uint4096(CurrentPosition)) <= *this &&
					base.pow(uint4096(CurrentPosition + 1)) >= *this)
				{
					return CurrentPosition;
				}

				if (CurrentPosition <= 1)
				{
					return uint4096(0);
				}

				if (base.pow(uint4096(CurrentPosition)) <= *this)
				{
					CurrentPosition += CurrentOffsetLength;
					CurrentOffsetLength /= 2;
					continue;
				}

				if (base.pow(uint4096(CurrentPosition)) >= *this)
				{
					CurrentPosition -= CurrentOffsetLength;
					CurrentOffsetLength /= 2;
					continue;
				}
			}
		}

		uint4096 uint4096::log10() { return this->log(uint4096(10)); }

		uint4096 uint4096::sqrt()
		{
			if (*this == uint4096(0))
			{
				return uint4096(0);
			}

			if (*this == uint4096(1))
			{
				return uint4096(1);
			}

			uint4096 CurrentPosition(UINT2048_MAX / 2), CurrentOffsetLength(UINT2048_MAX / 4 + 1);

			while (true)
			{
				if (CurrentPosition.pow(uint4096(2)) <= *this &&
					uint4096(CurrentPosition + 1).pow(uint4096(2)) >= *this)
				{
					return CurrentPosition;
				}

				if (CurrentPosition <= 2)
				{
					return uint4096(1);
				}

				if (CurrentPosition.pow(uint4096(2)) <= *this)
				{
					CurrentPosition += CurrentOffsetLength;
					CurrentOffsetLength /= 2;
					continue;
				}

				if (CurrentPosition.pow(uint4096(2)) >= *this)
				{
					CurrentPosition -= CurrentOffsetLength;
					CurrentOffsetLength /= 2;
					continue;
				}
			}

			return uint4096();
		}

		uint4096 uint4096::mod(uint4096 init)
		{
			return (*this - (*this / init * init));
		}

		int uint4096::TryToInt()
		{
			if (*this > uint4096(INT32_MAX))
			{
				throw std::bad_cast{};
			}

			return (int)this->data.to_ulong();
		}

		unsigned long uint4096::TryToLong()
		{
			if (*this > uint4096(uint64_t(ULONG_MAX)))
			{
				throw std::bad_cast{};
			}

			return this->data.to_ulong();
		}

		uint64_t uint4096::TryToUint64_t()
		{
			if (*this > uint4096(uint64_t(ULLONG_MAX)))
			{
				throw std::bad_cast{};
			}

			return this->data.to_ullong();
		}

		uint128::uint128 uint4096::TryToUint128()
		{
			if (*this > uint4096(UINT128_MAX))
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

		uint256::uint256 uint4096::TryToUint256()
		{
			if (*this > uint4096(UINT256_MAX))
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

		uint512::uint512 uint4096::TryToUint512()
		{
			if (*this > uint4096(UINT512_MAX))
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

		uint1024::uint1024 uint4096::TryToUint1024()
		{
			if (*this > uint4096(UINT1024_MAX))
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

		uint2048::uint2048 uint4096::TryToUint2048()
		{
			if (*this > uint4096(UINT2048_MAX))
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

		std::string uint4096::ToBinaryString() { return this->data.to_string(); }
		std::bitset<4096> uint4096::GetBinaryData() { return this->data; }

		uint4096 uint4096::operator+(uint64_t var) { return this->add(var); }
		uint4096 uint4096::operator+(uint4096 var) { return this->add(var); }
		uint4096 uint4096::operator-(uint64_t var) { return this->substract(var); }
		uint4096 uint4096::operator-(uint4096 var) { return this->substract(var); }
		uint4096 uint4096::operator*(uint64_t var) { return this->multiply(var); }
		uint4096 uint4096::operator*(uint4096 var) { return this->multiply(var); }
		uint4096 uint4096::operator/(uint64_t var) { return this->divide(var); }
		uint4096 uint4096::operator/(uint4096 var) { return this->divide(var); }

		void uint4096::operator+=(uint64_t var) { *this = this->add(var); }
		void uint4096::operator+=(uint4096 var) { *this = this->add(var); }
		void uint4096::operator-=(uint64_t var) { *this = this->substract(var); }
		void uint4096::operator-=(uint4096 var) { *this = this->substract(var); }
		void uint4096::operator*=(uint64_t var) { *this = this->multiply(var); }
		void uint4096::operator*=(uint4096 var) { *this = this->multiply(var); }
		void uint4096::operator/=(uint64_t var) { *this = this->divide(var); }
		void uint4096::operator/=(uint4096 var) { *this = this->divide(var); }

		uint4096 uint4096::operator++()
		{
			*this += uint4096(1);
			return *this;
		}

		uint4096 uint4096::operator--()
		{
			*this -= uint4096(1);
			return *this;
		}

		uint4096 uint4096::operator%(uint4096 var) { return this->mod(var); }
		void uint4096::operator%=(uint4096 var) { *this = this->mod(var); }

		bool uint4096::operator==(uint4096 var)
		{
			for (size_t i = 0; i < 4096; i++)
			{
				if (this->data[4095 - i] != var.data[4095 - i])
				{
					return false;
				}
			}

			return true;
		}

		bool uint4096::operator<(uint4096 item)
		{
			for (size_t i = 0; i < 4096; i++)
			{
				if (this->data[4095 - i] == 1 && item.data[4095 - i] == 0)
				{
					return false;
				}
				else if (this->data[4095 - i] == 0 && item.data[4095 - i] == 1)
				{
					return true;
				}
			}

			return false;
		}

		bool uint4096::operator>(uint4096 item)
		{
			for (size_t i = 0; i < 4096; i++)
			{
				if (this->data[4095 - i] == 0 && item.data[4095 - i] == 1)
				{
					return false;
				}
				else if (this->data[4095 - i] == 1 && item.data[4095 - i] == 0)
				{
					return true;
				}
			}

			return false;
		}

		bool uint4096::operator<=(uint4096 item)
		{
			for (size_t i = 0; i < 4096; i++)
			{
				if (this->data[4095 - i] == 1 && item.data[4095 - i] == 0)
				{
					return false;
				}
				else if (this->data[4095 - i] == 0 && item.data[4095 - i] == 1)
				{
					return true;
				}
			}

			return true;
		}

		bool uint4096::operator>=(uint4096 item)
		{
			for (size_t i = 0; i < 4096; i++)
			{
				if (this->data[4095 - i] == 0 && item.data[4095 - i] == 1)
				{
					return false;
				}
				else if (this->data[4095 - i] == 1 && item.data[4095 - i] == 0)
				{
					return true;
				}
			}

			return false;
		}

		bool uint4096::operator!=(uint4096 item) { return !(*this == item); }

		std::ostream& operator << (std::ostream& os, uint4096 integer) { return os << integer.GetBinaryData(); }

		std::string uint4096::DivisionAdaptedSubHelpFunction(std::string This, std::string init)
		{
			uint4096 CThis = uint4096(This);
			uint4096 CInit = uint4096(init);

			uint4096 RawResult = CThis - CInit;

			std::string result("");
			bool StartWritingZeros(false);

			for (size_t i = 0; i < 4096; i++)
			{
				if (RawResult.data[4095 - i] == 1)
				{
					result += "1";
					StartWritingZeros = true;
				}
				if (RawResult.data[4095 - i] == 0 && StartWritingZeros == true)
				{
					result += "0";
				}
			}

			return result;
		}

		uint4096 pow(uint4096 base, uint4096 exp)
		{
			uint4096 This(base);
			return This.pow(exp);
		}

		uint4096 pow(uint4096 base, uint64_t exp)
		{
			uint4096 This(base);
			return This.pow(exp);
		}

		uint4096 mod(uint4096 divisor, uint4096 divider)
		{
			uint4096 This(divisor);
			return This.divide(divider);
		}

		uint4096 mod(uint4096 divisor, uint64_t divider)
		{
			uint4096 This(divisor);
			return This.divide(divider);
		}

		uint4096 log(uint4096 base, uint4096 pot)
		{
			uint4096 This(base);
			return This.log(pot);
		}

		uint4096 log(uint64_t base, uint4096 pot)
		{
			uint4096 This(base);
			return This.log(pot);
		}

		uint4096 log10(uint4096 pot)
		{
			return pot.log10();
		}

		uint4096 sqrt(uint4096 radiant)
		{
			return radiant.sqrt();
		}
	}
}
