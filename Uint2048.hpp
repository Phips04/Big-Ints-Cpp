#pragma once

#include <initializer_list>
#include <iostream>
#include <string>

#include "BigIntsBase.hpp"

namespace BigInts
{
    class Uint2048 : public BigInts::BigIntsBase<2048>
    {
    private:
        
    public:
        Uint2048() : BigIntsBase() {}
        Uint2048(std::string Arg) : BigIntsBase(Arg) {}
        Uint2048(std::bitset<2048> Arg) : BigIntsBase(Arg) {}
        Uint2048(int Arg) : BigIntsBase(Arg) {}
        Uint2048(uint64_t Arg) : BigIntsBase(Arg) {}

        Uint2048 Add(uint64_t Arg)
        {
            return Uint2048(Internal_Add(Data, std::bitset<2048>(Arg)));
        }
        Uint2048 Add(Uint2048 Arg, std::initializer_list<Uint2048> Il)
        {
            Uint2048 result(Internal_Add(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Add(result.Data, element.Data);
            }
            return result;
        }
        Uint2048 Subtract(uint64_t Arg)
        {
            return Uint2048(Internal_Subtract(Data, std::bitset<2048>(Arg)));
        }
        Uint2048 Subtract(Uint2048 Arg, std::initializer_list<Uint2048> Il)
        {
            Uint2048 result(Internal_Subtract(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Subtract(result.Data, element.Data);
            }
            return result;
        }
        Uint2048 Multiply(uint64_t Arg)
        {
            return Uint2048(Internal_Multiply(Data, std::bitset<2048>(Arg)));
        }
        Uint2048 Multiply(Uint2048 Arg, std::initializer_list<Uint2048> Il)
        {
            Uint2048 result(Internal_Multiply(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Multiply(result.Data, element.Data);
            }
            return result;            
        }
        Uint2048 Divide(uint64_t Arg)
        {
            return Internal_Divide(Data, std::bitset<2048>(Arg));
        }
        Uint2048 Divide(Uint2048 Arg, std::initializer_list<Uint2048> Il)
        {
            Uint2048 result(Internal_Divide(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Divide(result.Data, element.Data);
            }
            return result;
        }   
        Uint2048 Pow(uint64_t Arg)
        {
            return Internal_Pow(Data, std::bitset<2048>(Arg));
        }
        Uint2048 Pow(Uint2048 Arg, std::initializer_list<Uint2048> Il)
        {
            Uint2048 result(Internal_Pow(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Pow(result.Data, element.Data);
            }
            return result;
        }
        Uint2048 Mod(uint64_t Arg)
        {
            return Internal_Mod(Data, std::bitset<2048>(Arg));
        }
        Uint2048 Mod(Uint2048 Arg, std::initializer_list<Uint2048> Il)
        {
            Uint2048 result(Internal_Mod(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Mod(result.Data, element.Data);
            }
            return result;
        }
        Uint2048 Log2()
        {
            return Internal_Log(Data, std::bitset<2048>(2));
        }
        Uint2048 Log10()
        {
            return Internal_Log(Data, std::bitset<2048>(10));
        }
        Uint2048	Log(uint64_t Arg)
        {
            return Internal_Log(Data, std::bitset<2048>(Arg));
        }
        Uint2048 Log(Uint2048 Arg)
        {
            return Internal_Log(Data, Arg.Data);
        }
        Uint2048 Sqrt()
        {
            return Internal_Sqrt(Data);
        }
        Uint2048 Factorial()
        {
            return Internal_Factorial(Data);
        }
   
        //Operators
        Uint2048 operator + (uint64_t Arg)
        {
            return Add(Arg);
        }
        Uint2048 operator + (Uint2048 Arg)
        {
            return Add(Arg, {});
        }
        Uint2048 operator - (uint64_t Arg)
        {
            return Subtract(Arg);
        }
        Uint2048 operator - (Uint2048 Arg)
        {
            return Subtract(Arg, {});
        }
        Uint2048 operator * (uint64_t Arg)
        {
            return Multiply(Arg);
        }
        Uint2048 operator * (Uint2048 Arg)
        {
            return Multiply(Arg, {});
        }
        Uint2048 operator / (uint64_t Arg)
        {
            return Divide(Arg);
        }
        Uint2048 operator / (Uint2048 Arg)
        {
            return Divide(Arg, {});
        }
        Uint2048 operator % (uint64_t Arg)
        {
            return Mod(Arg);
        }
        Uint2048 operator % (Uint2048 Arg)
        {
            return Mod(Arg, {});
        }

        void operator += (uint64_t Arg)
        {
            *this = Add(Arg);
        }
        void operator += (Uint2048 Arg)
        {
            *this = Add(Arg, {});
        }
        void operator -= (uint64_t Arg)
        {
            *this = Subtract(Arg);
        }
        void operator -= (Uint2048 Arg)
        {
            *this = Subtract(Arg, {});
        }
        void operator *= (uint64_t Arg)
        {
            *this = Multiply(Arg);
        }
        void operator *= (Uint2048 Arg)
        {
            *this = Multiply(Arg, {});
        }
        void operator /= (uint64_t Arg)
        {
            *this = Divide(Arg);
        }
        void operator /= (Uint2048 Arg)
        {
            *this = Divide(Arg, {});
        }
        void operator %= (uint64_t Arg)
        {
            *this = Mod(Arg);
        }
        void operator %= (Uint2048 Arg)
        {
            *this = Mod(Arg, {});
        }

        Uint2048 operator ++ (int)
        {
            *this = Add(1);
            return Subtract(1);
        }
        Uint2048 operator -- (int)
        {
            *this = Subtract(1);
            return Add(1);
        }

        bool operator == (Uint2048 Arg)
        {
            if (Data == Arg.Data)
            {
                return true;
            }
            return false;
        }
        bool operator != (Uint2048 Arg)
        {
            if (Data == Arg.Data)
            {
                return false;
            }
            return true;
        }
        bool operator < (Uint2048 Arg)
        {
            return FirstIsSmaller((*this).Data, Arg.Data);
        }
        bool operator > (Uint2048 Arg)
        {
            return FirstIsSmaller(Arg.Data, (*this).Data);
        }
        bool operator <= (Uint2048 Arg)
        {
            return !FirstIsSmaller(Arg.Data, (*this).Data);
        }
        bool operator >= (Uint2048 Arg)
        {
            return !FirstIsSmaller((*this).Data, Arg.Data);
        }
   
        #define UINT_2048_MIN std::bitset<2048>(0)
        #define UINT_2048_MAX std::bitset<2048>(0).set()

        friend std::ostream& operator << (std::ostream&, Uint2048);
   };

   std::ostream& operator << (std::ostream& os, Uint2048 Arg)
   {
       return os << Arg.Data;
   }
}