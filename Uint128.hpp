#pragma once

#include <initializer_list>
#include <iostream>
#include <string>

#include "BigIntsBase.hpp"

namespace BigInts
{
    class Uint128 : public BigInts::BigIntsBase<128>
    {
    private:
        
    public:
        Uint128() : BigIntsBase() {}
        Uint128(std::string Arg) : BigIntsBase(Arg) {}
        Uint128(std::bitset<128> Arg) : BigIntsBase(Arg) {}
        Uint128(int Arg) : BigIntsBase(Arg) {}
        Uint128(uint64_t Arg) : BigIntsBase(Arg) {}

        Uint128 Add(uint64_t Arg)
        {
            return Uint128(Internal_Add(Data, std::bitset<128>(Arg)));
        }
        Uint128 Add(Uint128 Arg, std::initializer_list<Uint128> Il)
        {
            Uint128 result(Internal_Add(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Add(result.Data, element.Data);
            }
            return result;
        }
        Uint128 Subtract(uint64_t Arg)
        {
            return Uint128(Internal_Subtract(Data, std::bitset<128>(Arg)));
        }
        Uint128 Subtract(Uint128 Arg, std::initializer_list<Uint128> Il)
        {
            Uint128 result(Internal_Subtract(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Subtract(result.Data, element.Data);
            }
            return result;
        }
        Uint128 Multiply(uint64_t Arg)
        {
            return Uint128(Internal_Multiply(Data, std::bitset<128>(Arg)));
        }
        Uint128 Multiply(Uint128 Arg, std::initializer_list<Uint128> Il)
        {
            Uint128 result(Internal_Multiply(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Multiply(result.Data, element.Data);
            }
            return result;            
        }
        Uint128 Divide(uint64_t Arg)
        {
            return Internal_Divide(Data, std::bitset<128>(Arg));
        }
        Uint128 Divide(Uint128 Arg, std::initializer_list<Uint128> Il)
        {
            Uint128 result(Internal_Divide(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Divide(result.Data, element.Data);
            }
            return result;
        }   
        Uint128 Pow(uint64_t Arg)
        {
            return Internal_Pow(Data, std::bitset<128>(Arg));
        }
        Uint128 Pow(Uint128 Arg, std::initializer_list<Uint128> Il)
        {
            Uint128 result(Internal_Pow(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Pow(result.Data, element.Data);
            }
            return result;
        }
        Uint128 Mod(uint64_t Arg)
        {
            return Internal_Mod(Data, std::bitset<128>(Arg));
        }
        Uint128 Mod(Uint128 Arg, std::initializer_list<Uint128> Il)
        {
            Uint128 result(Internal_Mod(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Mod(result.Data, element.Data);
            }
            return result;
        }
        Uint128 Log2()
        {
            return Internal_Log(Data, std::bitset<128>(2));
        }
        Uint128 Log10()
        {
            return Internal_Log(Data, std::bitset<128>(10));
        }
        Uint128	Log(uint64_t Arg)
        {
            return Internal_Log(Data, std::bitset<128>(Arg));
        }
        Uint128 Log(Uint128 Arg)
        {
            return Internal_Log(Data, Arg.Data);
        }
        Uint128 Sqrt()
        {
            return Internal_Sqrt(Data);
        }
        Uint128 Factorial()
        {
            return Internal_Factorial(Data);
        }
   
        //Operators
        Uint128 operator + (uint64_t Arg)
        {
            return Add(Arg);
        }
        Uint128 operator + (Uint128 Arg)
        {
            return Add(Arg, {});
        }
        Uint128 operator - (uint64_t Arg)
        {
            return Subtract(Arg);
        }
        Uint128 operator - (Uint128 Arg)
        {
            return Subtract(Arg, {});
        }
        Uint128 operator * (uint64_t Arg)
        {
            return Multiply(Arg);
        }
        Uint128 operator * (Uint128 Arg)
        {
            return Multiply(Arg, {});
        }
        Uint128 operator / (uint64_t Arg)
        {
            return Divide(Arg);
        }
        Uint128 operator / (Uint128 Arg)
        {
            return Divide(Arg, {});
        }
        Uint128 operator % (uint64_t Arg)
        {
            return Mod(Arg);
        }
        Uint128 operator % (Uint128 Arg)
        {
            return Mod(Arg, {});
        }

        void operator += (uint64_t Arg)
        {
            *this = Add(Arg);
        }
        void operator += (Uint128 Arg)
        {
            *this = Add(Arg, {});
        }
        void operator -= (uint64_t Arg)
        {
            *this = Subtract(Arg);
        }
        void operator -= (Uint128 Arg)
        {
            *this = Subtract(Arg, {});
        }
        void operator *= (uint64_t Arg)
        {
            *this = Multiply(Arg);
        }
        void operator *= (Uint128 Arg)
        {
            *this = Multiply(Arg, {});
        }
        void operator /= (uint64_t Arg)
        {
            *this = Divide(Arg);
        }
        void operator /= (Uint128 Arg)
        {
            *this = Divide(Arg, {});
        }
        void operator %= (uint64_t Arg)
        {
            *this = Mod(Arg);
        }
        void operator %= (Uint128 Arg)
        {
            *this = Mod(Arg, {});
        }

        Uint128 operator ++ (int)
        {
            *this = Add(1);
            return Subtract(1);
        }
        Uint128 operator -- (int)
        {
            *this = Subtract(1);
            return Add(1);
        }

        bool operator == (Uint128 Arg)
        {
            if (Data == Arg.Data)
            {
                return true;
            }
            return false;
        }
        bool operator != (Uint128 Arg)
        {
            if (Data == Arg.Data)
            {
                return false;
            }
            return true;
        }
        bool operator < (Uint128 Arg)
        {
            return FirstIsSmaller((*this).Data, Arg.Data);
        }
        bool operator > (Uint128 Arg)
        {
            return FirstIsSmaller(Arg.Data, (*this).Data);
        }
        bool operator <= (Uint128 Arg)
        {
            return !FirstIsSmaller(Arg.Data, (*this).Data);
        }
        bool operator >= (Uint128 Arg)
        {
            return !FirstIsSmaller((*this).Data, Arg.Data);
        }
   
        #define UINT_128_MIN std::bitset<128>(0)
        #define UINT_128_MAX std::bitset<128>(0).set()

        friend std::ostream& operator << (std::ostream&, Uint128);
   };

   std::ostream& operator << (std::ostream& os, Uint128 Arg)
   {
       return os << Arg.Data;
   }
}
