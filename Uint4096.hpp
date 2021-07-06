#pragma once

#include <initializer_list>
#include <iostream>
#include <string>

#include "BigIntsBase.hpp"

namespace BigInts
{
    class Uint4096 : public BigInts::BigIntsBase<4096>
    {
    private:
        
    public:
        Uint4096() : BigIntsBase() {}
        Uint4096(std::string Arg) : BigIntsBase(Arg) {}
        Uint4096(std::bitset<4096> Arg) : BigIntsBase(Arg) {}
        Uint4096(int Arg) : BigIntsBase(Arg) {}
        Uint4096(uint64_t Arg) : BigIntsBase(Arg) {}

        Uint4096 Add(uint64_t Arg)
        {
            return Uint4096(Internal_Add(Data, std::bitset<4096>(Arg)));
        }
        Uint4096 Add(Uint4096 Arg, std::initializer_list<Uint4096> Il)
        {
            Uint4096 result(Internal_Add(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Add(result.Data, element.Data);
            }
            return result;
        }
        Uint4096 Subtract(uint64_t Arg)
        {
            return Uint4096(Internal_Subtract(Data, std::bitset<4096>(Arg)));
        }
        Uint4096 Subtract(Uint4096 Arg, std::initializer_list<Uint4096> Il)
        {
            Uint4096 result(Internal_Subtract(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Subtract(result.Data, element.Data);
            }
            return result;
        }
        Uint4096 Multiply(uint64_t Arg)
        {
            return Uint4096(Internal_Multiply(Data, std::bitset<4096>(Arg)));
        }
        Uint4096 Multiply(Uint4096 Arg, std::initializer_list<Uint4096> Il)
        {
            Uint4096 result(Internal_Multiply(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Multiply(result.Data, element.Data);
            }
            return result;            
        }
        Uint4096 Divide(uint64_t Arg)
        {
            return Internal_Divide(Data, std::bitset<4096>(Arg));
        }
        Uint4096 Divide(Uint4096 Arg, std::initializer_list<Uint4096> Il)
        {
            Uint4096 result(Internal_Divide(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Divide(result.Data, element.Data);
            }
            return result;
        }   
        Uint4096 Pow(uint64_t Arg)
        {
            return Internal_Pow(Data, std::bitset<4096>(Arg));
        }
        Uint4096 Pow(Uint4096 Arg, std::initializer_list<Uint4096> Il)
        {
            Uint4096 result(Internal_Pow(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Pow(result.Data, element.Data);
            }
            return result;
        }
        Uint4096 Mod(uint64_t Arg)
        {
            return Internal_Mod(Data, std::bitset<4096>(Arg));
        }
        Uint4096 Mod(Uint4096 Arg, std::initializer_list<Uint4096> Il)
        {
            Uint4096 result(Internal_Mod(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Mod(result.Data, element.Data);
            }
            return result;
        }
        Uint4096 Log2()
        {
            return Internal_Log(Data, std::bitset<4096>(2));
        }
        Uint4096 Log10()
        {
            return Internal_Log(Data, std::bitset<4096>(10));
        }
        Uint4096	Log(uint64_t Arg)
        {
            return Internal_Log(Data, std::bitset<4096>(Arg));
        }
        Uint4096 Log(Uint4096 Arg)
        {
            return Internal_Log(Data, Arg.Data);
        }
        Uint4096 Sqrt()
        {
            return Internal_Sqrt(Data);
        }
        Uint4096 Factorial()
        {
            return Internal_Factorial(Data);
        }
   
        //Operators
        Uint4096 operator + (uint64_t Arg)
        {
            return Add(Arg);
        }
        Uint4096 operator + (Uint4096 Arg)
        {
            return Add(Arg, {});
        }
        Uint4096 operator - (uint64_t Arg)
        {
            return Subtract(Arg);
        }
        Uint4096 operator - (Uint4096 Arg)
        {
            return Subtract(Arg, {});
        }
        Uint4096 operator * (uint64_t Arg)
        {
            return Multiply(Arg);
        }
        Uint4096 operator * (Uint4096 Arg)
        {
            return Multiply(Arg, {});
        }
        Uint4096 operator / (uint64_t Arg)
        {
            return Divide(Arg);
        }
        Uint4096 operator / (Uint4096 Arg)
        {
            return Divide(Arg, {});
        }
        Uint4096 operator % (uint64_t Arg)
        {
            return Mod(Arg);
        }
        Uint4096 operator % (Uint4096 Arg)
        {
            return Mod(Arg, {});
        }

        void operator += (uint64_t Arg)
        {
            *this = Add(Arg);
        }
        void operator += (Uint4096 Arg)
        {
            *this = Add(Arg, {});
        }
        void operator -= (uint64_t Arg)
        {
            *this = Subtract(Arg);
        }
        void operator -= (Uint4096 Arg)
        {
            *this = Subtract(Arg, {});
        }
        void operator *= (uint64_t Arg)
        {
            *this = Multiply(Arg);
        }
        void operator *= (Uint4096 Arg)
        {
            *this = Multiply(Arg, {});
        }
        void operator /= (uint64_t Arg)
        {
            *this = Divide(Arg);
        }
        void operator /= (Uint4096 Arg)
        {
            *this = Divide(Arg, {});
        }
        void operator %= (uint64_t Arg)
        {
            *this = Mod(Arg);
        }
        void operator %= (Uint4096 Arg)
        {
            *this = Mod(Arg, {});
        }

        Uint4096 operator ++ (int)
        {
            *this = Add(1);
            return Subtract(1);
        }
        Uint4096 operator -- (int)
        {
            *this = Subtract(1);
            return Add(1);
        }

        bool operator == (Uint4096 Arg)
        {
            if (Data == Arg.Data)
            {
                return true;
            }
            return false;
        }
        bool operator != (Uint4096 Arg)
        {
            if (Data == Arg.Data)
            {
                return false;
            }
            return true;
        }
        bool operator < (Uint4096 Arg)
        {
            return FirstIsSmaller((*this).Data, Arg.Data);
        }
        bool operator > (Uint4096 Arg)
        {
            return FirstIsSmaller(Arg.Data, (*this).Data);
        }
        bool operator <= (Uint4096 Arg)
        {
            return !FirstIsSmaller(Arg.Data, (*this).Data);
        }
        bool operator >= (Uint4096 Arg)
        {
            return !FirstIsSmaller((*this).Data, Arg.Data);
        }
   
        #define UINT_4096_MIN std::bitset<4096>(0)
        #define UINT_4096_MAX std::bitset<4096>(0).set()

        friend std::ostream& operator << (std::ostream&, Uint4096);
   };

   std::ostream& operator << (std::ostream& os, Uint4096 Arg)
   {
       return os << Arg.Data;
   }
}
