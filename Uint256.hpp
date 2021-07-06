#pragma once

#include <initializer_list>
#include <iostream>
#include <string>

#include "BigIntsBase.hpp"

namespace BigInts
{
    class Uint256 : public BigInts::BigIntsBase<256>
    {
    private:
        
    public:
        Uint256() : BigIntsBase() {}
        Uint256(std::string Arg) : BigIntsBase(Arg) {}
        Uint256(std::bitset<256> Arg) : BigIntsBase(Arg) {}
        Uint256(int Arg) : BigIntsBase(Arg) {}
        Uint256(uint64_t Arg) : BigIntsBase(Arg) {}

        Uint256 Add(uint64_t Arg)
        {
            return Uint256(Internal_Add(Data, std::bitset<256>(Arg)));
        }
        Uint256 Add(Uint256 Arg, std::initializer_list<Uint256> Il)
        {
            Uint256 result(Internal_Add(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Add(result.Data, element.Data);
            }
            return result;
        }
        Uint256 Subtract(uint64_t Arg)
        {
            return Uint256(Internal_Subtract(Data, std::bitset<256>(Arg)));
        }
        Uint256 Subtract(Uint256 Arg, std::initializer_list<Uint256> Il)
        {
            Uint256 result(Internal_Subtract(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Subtract(result.Data, element.Data);
            }
            return result;
        }
        Uint256 Multiply(uint64_t Arg)
        {
            return Uint256(Internal_Multiply(Data, std::bitset<256>(Arg)));
        }
        Uint256 Multiply(Uint256 Arg, std::initializer_list<Uint256> Il)
        {
            Uint256 result(Internal_Multiply(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Multiply(result.Data, element.Data);
            }
            return result;            
        }
        Uint256 Divide(uint64_t Arg)
        {
            return Internal_Divide(Data, std::bitset<256>(Arg));
        }
        Uint256 Divide(Uint256 Arg, std::initializer_list<Uint256> Il)
        {
            Uint256 result(Internal_Divide(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Divide(result.Data, element.Data);
            }
            return result;
        }   
        Uint256 Pow(uint64_t Arg)
        {
            return Internal_Pow(Data, std::bitset<256>(Arg));
        }
        Uint256 Pow(Uint256 Arg, std::initializer_list<Uint256> Il)
        {
            Uint256 result(Internal_Pow(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Pow(result.Data, element.Data);
            }
            return result;
        }
        Uint256 Mod(uint64_t Arg)
        {
            return Internal_Mod(Data, std::bitset<256>(Arg));
        }
        Uint256 Mod(Uint256 Arg, std::initializer_list<Uint256> Il)
        {
            Uint256 result(Internal_Mod(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Mod(result.Data, element.Data);
            }
            return result;
        }
        Uint256 Log2()
        {
            return Internal_Log(Data, std::bitset<256>(2));
        }
        Uint256 Log10()
        {
            return Internal_Log(Data, std::bitset<256>(10));
        }
        Uint256	Log(uint64_t Arg)
        {
            return Internal_Log(Data, std::bitset<256>(Arg));
        }
        Uint256 Log(Uint256 Arg)
        {
            return Internal_Log(Data, Arg.Data);
        }
        Uint256 Sqrt()
        {
            return Internal_Sqrt(Data);
        }
        Uint256 Factorial()
        {
            return Internal_Factorial(Data);
        }
   
        //Operators
        Uint256 operator + (uint64_t Arg)
        {
            return Add(Arg);
        }
        Uint256 operator + (Uint256 Arg)
        {
            return Add(Arg, {});
        }
        Uint256 operator - (uint64_t Arg)
        {
            return Subtract(Arg);
        }
        Uint256 operator - (Uint256 Arg)
        {
            return Subtract(Arg, {});
        }
        Uint256 operator * (uint64_t Arg)
        {
            return Multiply(Arg);
        }
        Uint256 operator * (Uint256 Arg)
        {
            return Multiply(Arg, {});
        }
        Uint256 operator / (uint64_t Arg)
        {
            return Divide(Arg);
        }
        Uint256 operator / (Uint256 Arg)
        {
            return Divide(Arg, {});
        }
        Uint256 operator % (uint64_t Arg)
        {
            return Mod(Arg);
        }
        Uint256 operator % (Uint256 Arg)
        {
            return Mod(Arg, {});
        }

        void operator += (uint64_t Arg)
        {
            *this = Add(Arg);
        }
        void operator += (Uint256 Arg)
        {
            *this = Add(Arg, {});
        }
        void operator -= (uint64_t Arg)
        {
            *this = Subtract(Arg);
        }
        void operator -= (Uint256 Arg)
        {
            *this = Subtract(Arg, {});
        }
        void operator *= (uint64_t Arg)
        {
            *this = Multiply(Arg);
        }
        void operator *= (Uint256 Arg)
        {
            *this = Multiply(Arg, {});
        }
        void operator /= (uint64_t Arg)
        {
            *this = Divide(Arg);
        }
        void operator /= (Uint256 Arg)
        {
            *this = Divide(Arg, {});
        }
        void operator %= (uint64_t Arg)
        {
            *this = Mod(Arg);
        }
        void operator %= (Uint256 Arg)
        {
            *this = Mod(Arg, {});
        }

        Uint256 operator ++ (int)
        {
            *this = Add(1);
            return Subtract(1);
        }
        Uint256 operator -- (int)
        {
            *this = Subtract(1);
            return Add(1);
        }

        bool operator == (Uint256 Arg)
        {
            if (Data == Arg.Data)
            {
                return true;
            }
            return false;
        }
        bool operator != (Uint256 Arg)
        {
            if (Data == Arg.Data)
            {
                return false;
            }
            return true;
        }
        bool operator < (Uint256 Arg)
        {
            return FirstIsSmaller((*this).Data, Arg.Data);
        }
        bool operator > (Uint256 Arg)
        {
            return FirstIsSmaller(Arg.Data, (*this).Data);
        }
        bool operator <= (Uint256 Arg)
        {
            return !FirstIsSmaller(Arg.Data, (*this).Data);
        }
        bool operator >= (Uint256 Arg)
        {
            return !FirstIsSmaller((*this).Data, Arg.Data);
        }
   
        #define UINT_256_MIN std::bitset<256>(0)
        #define UINT_256_MAX std::bitset<256>(0).set()

        friend std::ostream& operator << (std::ostream&, Uint256);
   };

   std::ostream& operator << (std::ostream& os, Uint256 Arg)
   {
       return os << Arg.Data;
   }
}
