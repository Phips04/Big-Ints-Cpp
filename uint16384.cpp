#pragma once

#include "uint16384.h"

#include "uint128.h"
#include "uint256.h"
#include "uint512.h"
#include "uint1024.h"
#include "uint2048.h"
#include "uint4096.h"
#include "uint8192.h"

#include <bitset>
#include <string>
#include <initializer_list>
#include <forward_list>
#include <limits>
#include <iostream>


namespace BigInts
{
	namespace uint16384
	{
		uint16384::uint16384() { this->data = std::bitset<16384>(); }
		uint16384::uint16384(int32_t init) { if (init < 0) { throw std::invalid_argument{ "argument (type of int32_t) was negative, int16384 is unsigned" }; } this->data = std::bitset<16384>(init); }
		uint16384::uint16384(uint32_t init) { this->data = std::bitset<16384>(init); }
		uint16384::uint16384(int64_t init) { if (init < 0) { throw std::invalid_argument{ "argument (type of int64_t) was negative, int16384 is unsigned" }; } this->data = std::bitset<16384>(init); }
		uint16384::uint16384(uint64_t init) { this->data = std::bitset<16384>(init); }
		uint16384::uint16384(uint128::uint128 init) { this->data = std::bitset<16384>(0); for (size_t i = 0; i < 128; i++) { this->data[i] = init.GetBinaryData()[i]; } }
		uint16384::uint16384(uint256::uint256 init) { this->data = std::bitset<16384>(0); for (size_t i = 0; i < 256; i++) { this->data[i] = init.GetBinaryData()[i]; } }
		uint16384::uint16384(uint512::uint512 init) { this->data = std::bitset<16384>(0); for (size_t i = 0; i < 512; i++) { this->data[i] = init.GetBinaryData()[i]; } }
		uint16384::uint16384(uint1024::uint1024 init) { this->data = std::bitset<16384>(0); for (size_t i = 0; i < 1024; i++) { this->data[i] = init.GetBinaryData()[i]; } }
		uint16384::uint16384(uint2048::uint2048 init) { this->data = std::bitset<16384>(0); for (size_t i = 0; i < 2048; i++) { this->data[i] = init.GetBinaryData()[i]; } }
		uint16384::uint16384(uint4096::uint4096 init) { this->data = std::bitset<16384>(0); for (size_t i = 0; i < 4096; i++) { this->data[i] = init.GetBinaryData()[i]; } }
		uint16384::uint16384(uint8192::uint8192 init) { this->data = std::bitset<16384>(0); for (size_t i = 0; i < 8192; i++) { this->data[i] = init.GetBinaryData()[i]; } }
		uint16384::uint16384(std::bitset<16384> init) { this->data = init; }

		uint16384::uint16384(std::string init)
		{
			for (size_t i = 0; i < init.length(); i++)
			{
				if (init.at(i) != *"0" && init.at(i) != *"1")
				{
					this->data = std::bitset<16384>(0);
					throw std::invalid_argument{ "Argument (type of std::string) was not either '0' or '1'" };
				}
			}

			this->data = std::bitset<16384>(init);
		}

		uint16384 uint16384::add(uint64_t arg)
		{
			return this->add(uint16384(arg));
		}

		uint16384 uint16384::add(uint16384 arg)
		{
			std::bitset<16384> result(0);

			int transmitter(0);

			for (size_t i = 0; i < 16384; i++)
			{
				if (arg.data[i] == 1 && this->data[i] == 1 && transmitter == 1) // OK
				{
					result[i] = 1;
					if (i == 16383)
					{
						throw std::overflow_error{ "The result will become greater than 2^16384, which is the maximal value of int16384" };
					}
					transmitter = 1;
					continue;
				}

				if ((arg.data[i] == 1 && this->data[i] == 1 && transmitter == 0) ||
					(arg.data[i] == 1 && this->data[i] == 0 && transmitter == 1) ||
					(arg.data[i] == 0 && this->data[i] == 1 && transmitter == 1))
				{
					result[i] = 0;
					if (i == 16383)
					{
						throw std::overflow_error{ "The result will grow larger than 2^16384, which is the maximal value of int16384" };
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

			return uint16384(result);
		}

		uint16384 uint16384::add(std::initializer_list<uint16384> args)
		{
			uint16384 result(*this);

			for (uint16384 arg : args)
			{
				result += arg;
			}

			return result;
		}

		uint16384 uint16384::substract(uint64_t arg)
		{
			return this->substract(uint16384(arg));
		}

		uint16384 uint16384::substract(uint16384 init)
		{
			std::bitset<16384> result(0);

			int transmitter(0);

			if (*this < init)
			{
				throw std::underflow_error{ "The result will be negative, int16384 is unsigned" };
			}

			for (size_t i = 0; i < 16384; i++)
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

				if (i == 16383 && transmitter == 1)
				{
					throw;
				}
			}

			return uint16384(result);
		}

		uint16384 uint16384::substract(std::initializer_list<uint16384> inits)
		{
			uint16384 result(*this);

			for (auto i : inits)
			{
				result -= i;
			}
			return result;

			return uint16384(result);
		}

		uint16384 uint16384::multiply(uint64_t init)
		{
			return this->multiply(uint16384(init));
		}

		uint16384 uint16384::multiply(uint16384 init)
		{
			std::forward_list<uint16384> ItemsToAdd;

			int ThisLength(0), InitLength(0);
			bool ThisLengthFound(false), InitLengthFound(false);

			for (size_t i = 0; i < 16384; i++)
			{
				if (this->data[16383 - i] == 1 && ThisLengthFound == false)
				{
					ThisLength = 16384 - i;
					ThisLengthFound = true;
				}

				if (init.data[16383 - i] == 1 && InitLengthFound == false)
				{
					InitLength = 16384 - i;
					InitLengthFound = true;
				}

				if (ThisLengthFound && InitLengthFound)
				{
					if (ThisLength + InitLength - 1 > 16384)
					{
						throw std::overflow_error{ "The result will grow larger than 2^16384, which is the maximal value of int16384" };
					}
				}
			}

			for (size_t i = 0; i < 16384; i++)
			{
				if (init.data[i] == 1)
				{
					std::bitset<16384> item(0);
					for (size_t x = 0; x < 16384; x++)
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

					ItemsToAdd.push_front(uint16384(item));
				}
			}

			uint16384 result(0);

			for (auto i : ItemsToAdd)
			{
				result += i;
			}

			return result;
		}

		uint16384 uint16384::multiply(std::initializer_list<uint16384> inits)
		{
			uint16384 result(*this);

			for (auto i : inits)
			{
				result *= i;
			}

			return result;
		}

		uint16384 uint16384::divide(uint64_t init)
		{
			return this->divide(uint16384(init));
		}

		uint16384 uint16384::divide(uint16384 init)
		{
			if (init.data == std::bitset<16384>(0))
			{
				throw std::invalid_argument{ "Argument was '0', division by '0' is not defined" };
			}

			if (*this < init)
			{
				return uint16384(0);
			}

			std::string ThisStream(""), InitStream(""), ThisCurrentStream(""), ResultStream("");
			bool StartRecordingThis(false), StartRecordingInit(false);

			for (size_t i = 0; i < 16384; i++)
			{
				if (this->data[16383 - i] == 1)
				{
					ThisStream += "1";
					StartRecordingThis = true;
				}
				else if (StartRecordingThis == true)
				{
					ThisStream += "0";
				}

				if (init.data[16383 - i] == 1)
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
				if (uint16384(ThisCurrentStream) < uint16384(InitStream))
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

			if (uint16384(ThisCurrentStream) < uint16384(InitStream))
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

			return uint16384(ResultStream);
		}

		uint16384 uint16384::divide(std::initializer_list<uint16384> inits)
		{
			uint16384 result(*this);

			for (auto i : inits)
			{
				result /= i;
			}
			return result;
		}

		uint16384 uint16384::pow(uint64_t init)
		{
			return this->pow(uint16384(init));
		}

		uint16384 uint16384::pow(uint16384 exp)
		{
			if (exp == uint16384(0))
			{
				return uint16384(1);
			}

			uint16384 result(*this);

			for (uint16384 i(1); i < exp; ++i)
			{
				result *= *this;
			}

			return result;
		}

		uint16384 uint16384::pow(std::initializer_list<uint16384> inits)
		{
			uint16384 FinalExp(1);

			for (uint16384 item : inits)
			{
				FinalExp *= item;
			}

			return this->pow(FinalExp);
		}

		uint16384 uint16384::log(uint16384 base)
		{
			if (base == uint16384(0))
			{
				throw std::invalid_argument{ "Argument was '0', logarithm which base = '0' is not defined" };
			}

			if (*this == uint16384(0))
			{
				throw std::domain_error{ "The value of the object calling the function 'log(int16384 base)' was '0', logarithm with exponent = '0' is not defined" };
			}


			if (*this < base)
			{
				return uint16384(0);
			}

			int CurrentPosition(16384 / base.TryToInt()), CurrentOffsetLength(16384 / (2 * base.TryToInt()));

			while (true)
			{
				if (base.pow(uint16384(CurrentPosition)) <= *this &&
					base.pow(uint16384(CurrentPosition + 1)) >= *this)
				{
					return CurrentPosition;
				}

				if (CurrentPosition <= 1)
				{
					return uint16384(0);
				}

				if (base.pow(uint16384(CurrentPosition)) <= *this)
				{
					CurrentPosition += CurrentOffsetLength;
					CurrentOffsetLength /= 2;
					continue;
				}

				if (base.pow(uint16384(CurrentPosition)) >= *this)
				{
					CurrentPosition -= CurrentOffsetLength;
					CurrentOffsetLength /= 2;
					continue;
				}
			}
		}

		uint16384 uint16384::log10() { return this->log(uint16384(10)); }

		uint16384 uint16384::sqrt()
		{
			if (*this == uint16384(0))
			{
				return uint16384(0);
			}

			if (*this == uint16384(1))
			{
				return uint16384(1);
			}

			uint16384 CurrentPosition(UINT8192_MAX / 2), CurrentOffsetLength(UINT8192_MAX / 4 + 1);

			while (true)
			{
				if (CurrentPosition.pow(uint16384(2)) <= *this &&
					uint16384(CurrentPosition + 1).pow(uint16384(2)) >= *this)
				{
					return CurrentPosition;
				}

				if (CurrentPosition <= 2)
				{
					return uint16384(1);
				}

				if (CurrentPosition.pow(uint16384(2)) <= *this)
				{
					CurrentPosition += CurrentOffsetLength;
					CurrentOffsetLength /= 2;
					continue;
				}

				if (CurrentPosition.pow(uint16384(2)) >= *this)
				{
					CurrentPosition -= CurrentOffsetLength;
					CurrentOffsetLength /= 2;
					continue;
				}
			}

			return uint16384();
		}

		uint16384 uint16384::mod(uint16384 init)
		{
			return (*this - (*this / init * init));
		}

		int uint16384::TryToInt()
		{
			if (*this > uint16384(INT32_MAX))
			{
				throw std::bad_cast{};
			}

			return (int)this->data.to_ulong();
		}

		unsigned long uint16384::TryToLong()
		{
			if (*this > uint16384(uint64_t(ULONG_MAX)))
			{
				throw std::bad_cast{};
			}

			return this->data.to_ulong();
		}

		uint64_t uint16384::TryToUint64_t()
		{
			if (*this > uint16384(uint64_t(ULLONG_MAX)))
			{
				throw std::bad_cast{};
			}

			return this->data.to_ullong();
		}

		uint128::uint128 uint16384::TryToUint128()
		{
			if (*this > uint16384(UINT128_MAX))
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

		uint256::uint256 uint16384::TryToUint256()
		{
			if (*this > uint16384(UINT256_MAX))
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

		uint512::uint512 uint16384::TryToUint512()
		{
			if (*this > uint16384(UINT512_MAX))
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

		uint1024::uint1024 uint16384::TryToUint1024()
		{
			if (*this > uint16384(UINT1024_MAX))
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

		uint2048::uint2048 uint16384::TryToUint2048()
		{
			if (*this > uint16384(UINT2048_MAX))
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

		uint4096::uint4096 uint16384::TryToUint4096()
		{
			if (*this > uint16384(UINT4096_MAX))
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

		uint8192::uint8192 uint16384::TryToUint8192()
		{
			if (*this > uint16384(UINT8192_MAX))
			{
				throw std::bad_cast{};
			}

			std::bitset<8192> result(0);

			for (size_t i = 0; i < 8192; i++)
			{
				result[i] = this->data[i];
			}

			return uint8192::uint8192(result);
		}

		std::string uint16384::ToBinaryString() { return this->data.to_string(); }
		std::bitset<16384> uint16384::GetBinaryData() { return this->data; }

		uint16384 uint16384::operator+(uint64_t var) { return this->add(var); }
		uint16384 uint16384::operator+(uint16384 var) { return this->add(var); }
		uint16384 uint16384::operator-(uint64_t var) { return this->substract(var); }
		uint16384 uint16384::operator-(uint16384 var) { return this->substract(var); }
		uint16384 uint16384::operator*(uint64_t var) { return this->multiply(var); }
		uint16384 uint16384::operator*(uint16384 var) { return this->multiply(var); }
		uint16384 uint16384::operator/(uint64_t var) { return this->divide(var); }
		uint16384 uint16384::operator/(uint16384 var) { return this->divide(var); }

		void uint16384::operator+=(uint64_t var) { *this = this->add(var); }
		void uint16384::operator+=(uint16384 var) { *this = this->add(var); }
		void uint16384::operator-=(uint64_t var) { *this = this->substract(var); }
		void uint16384::operator-=(uint16384 var) { *this = this->substract(var); }
		void uint16384::operator*=(uint64_t var) { *this = this->multiply(var); }
		void uint16384::operator*=(uint16384 var) { *this = this->multiply(var); }
		void uint16384::operator/=(uint64_t var) { *this = this->divide(var); }
		void uint16384::operator/=(uint16384 var) { *this = this->divide(var); }

		uint16384 uint16384::operator++()
		{
			*this += uint16384(1);
			return *this;
		}

		uint16384 uint16384::operator--()
		{
			*this -= uint16384(1);
			return *this;
		}

		uint16384 uint16384::operator%(uint16384 var) { return this->mod(var); }
		void uint16384::operator%=(uint16384 var) { *this = this->mod(var); }

		bool uint16384::operator==(uint16384 var)
		{
			for (size_t i = 0; i < 16384; i++)
			{
				if (this->data[16383 - i] != var.data[16383 - i])
				{
					return false;
				}
			}

			return true;
		}

		bool uint16384::operator<(uint16384 item)
		{
			for (size_t i = 0; i < 16384; i++)
			{
				if (this->data[16383 - i] == 1 && item.data[16383 - i] == 0)
				{
					return false;
				}
				else if (this->data[16383 - i] == 0 && item.data[16383 - i] == 1)
				{
					return true;
				}
			}

			return false;
		}

		bool uint16384::operator>(uint16384 item)
		{
			for (size_t i = 0; i < 16384; i++)
			{
				if (this->data[16383 - i] == 0 && item.data[16383 - i] == 1)
				{
					return false;
				}
				else if (this->data[16383 - i] == 1 && item.data[16383 - i] == 0)
				{
					return true;
				}
			}

			return false;
		}

		bool uint16384::operator<=(uint16384 item)
		{
			for (size_t i = 0; i < 16384; i++)
			{
				if (this->data[16383 - i] == 1 && item.data[16383 - i] == 0)
				{
					return false;
				}
				else if (this->data[16383 - i] == 0 && item.data[16383 - i] == 1)
				{
					return true;
				}
			}

			return true;
		}

		bool uint16384::operator>=(uint16384 item)
		{
			for (size_t i = 0; i < 16384; i++)
			{
				if (this->data[16383 - i] == 0 && item.data[16383 - i] == 1)
				{
					return false;
				}
				else if (this->data[16383 - i] == 1 && item.data[16383 - i] == 0)
				{
					return true;
				}
			}

			return false;
		}

		bool uint16384::operator!=(uint16384 item) { return !(*this == item); }

		std::ostream& operator << (std::ostream& os, uint16384 integer) { return os << integer.GetBinaryData(); }

		std::string uint16384::DivisionAdaptedSubHelpFunction(std::string This, std::string init)
		{
			uint16384 CThis = uint16384(This);
			uint16384 CInit = uint16384(init);

			uint16384 RawResult = CThis - CInit;

			std::string result("");
			bool StartWritingZeros(false);

			for (size_t i = 0; i < 16384; i++)
			{
				if (RawResult.data[16383 - i] == 1)
				{
					result += "1";
					StartWritingZeros = true;
				}
				if (RawResult.data[16383 - i] == 0 && StartWritingZeros == true)
				{
					result += "0";
				}
			}

			return result;
		}

		uint16384 pow(uint16384 base, uint16384 exp)
		{
			uint16384 This(base);
			return This.pow(exp);
		}

		uint16384 pow(uint16384 base, uint64_t exp)
		{
			uint16384 This(base);
			return This.pow(exp);
		}

		uint16384 mod(uint16384 divisor, uint16384 divider)
		{
			uint16384 This(divisor);
			return This.divide(divider);
		}

		uint16384 mod(uint16384 divisor, uint64_t divider)
		{
			uint16384 This(divisor);
			return This.divide(divider);
		}

		uint16384 log(uint16384 base, uint16384 pot)
		{
			uint16384 This(base);
			return This.log(pot);
		}

		uint16384 log(uint64_t base, uint16384 pot)
		{
			uint16384 This(base);
			return This.log(pot);
		}

		uint16384 log10(uint16384 pot)
		{
			return pot.log10();
		}

		uint16384 sqrt(uint16384 radiant)
		{
			return radiant.sqrt();
		}
	}
}
