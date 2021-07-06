#pragma once

#include <initializer_list>
#include <iostream>
#include <string>

#include "BigIntsBase.hpp"

namespace BigInts
{
    class Uint16384 : public BigInts::BigIntsBase<16384>
    {
    private:
        
    public:
        Uint16384() : BigIntsBase() {}
        Uint16384(std::string Arg) : BigIntsBase(Arg) {}
        Uint16384(std::bitset<16384> Arg) : BigIntsBase(Arg) {}
        Uint16384(int Arg) : BigIntsBase(Arg) {}
        Uint16384(uint64_t Arg) : BigIntsBase(Arg) {}

        Uint16384 Add(uint64_t Arg)
        {
            return Uint16384(Internal_Add(Data, std::bitset<16384>(Arg)));
        }
        Uint16384 Add(Uint16384 Arg, std::initializer_list<Uint16384> Il)
        {
            Uint16384 result(Internal_Add(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Add(result.Data, element.Data);
            }
            return result;
        }
        Uint16384 Subtract(uint64_t Arg)
        {
            return Uint16384(Internal_Subtract(Data, std::bitset<16384>(Arg)));
        }
        Uint16384 Subtract(Uint16384 Arg, std::initializer_list<Uint16384> Il)
        {
            Uint16384 result(Internal_Subtract(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Subtract(result.Data, element.Data);
            }
            return result;
        }
        Uint16384 Multiply(uint64_t Arg)
        {
            return Uint16384(Internal_Multiply(Data, std::bitset<16384>(Arg)));
        }
        Uint16384 Multiply(Uint16384 Arg, std::initializer_list<Uint16384> Il)
        {
            Uint16384 result(Internal_Multiply(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Multiply(result.Data, element.Data);
            }
            return result;            
        }
        Uint16384 Divide(uint64_t Arg)
        {
            return Internal_Divide(Data, std::bitset<16384>(Arg));
        }
        Uint16384 Divide(Uint16384 Arg, std::initializer_list<Uint16384> Il)
        {
            Uint16384 result(Internal_Divide(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Divide(result.Data, element.Data);
            }
            return result;
        }   
        Uint16384 Pow(uint64_t Arg)
        {
            return Internal_Pow(Data, std::bitset<16384>(Arg));
        }
        Uint16384 Pow(Uint16384 Arg, std::initializer_list<Uint16384> Il)
        {
            Uint16384 result(Internal_Pow(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Pow(result.Data, element.Data);
            }
            return result;
        }
        Uint16384 Mod(uint64_t Arg)
        {
            return Internal_Mod(Data, std::bitset<16384>(Arg));
        }
        Uint16384 Mod(Uint16384 Arg, std::initializer_list<Uint16384> Il)
        {
            Uint16384 result(Internal_Mod(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Mod(result.Data, element.Data);
            }
            return result;
        }
        Uint16384 Log2()
        {
            return Internal_Log(Data, std::bitset<16384>(2));
        }
        Uint16384 Log10()
        {
            return Internal_Log(Data, std::bitset<16384>(10));
        }
        Uint16384	Log(uint64_t Arg)
        {
            return Internal_Log(Data, std::bitset<16384>(Arg));
        }
        Uint16384 Log(Uint16384 Arg)
        {
            return Internal_Log(Data, Arg.Data);
        }
        Uint16384 Sqrt()
        {
            return Internal_Sqrt(Data);
        }
        Uint16384 Factorial()
        {
            return Internal_Factorial(Data);
        }
   
        //Operators
        Uint16384 operator + (uint64_t Arg)
        {
            return Add(Arg);
        }
        Uint16384 operator + (Uint16384 Arg)
        {
            return Add(Arg, {});
        }
        Uint16384 operator - (uint64_t Arg)
        {
            return Subtract(Arg);
        }
        Uint16384 operator - (Uint16384 Arg)
        {
            return Subtract(Arg, {});
        }
        Uint16384 operator * (uint64_t Arg)
        {
            return Multiply(Arg);
        }
        Uint16384 operator * (Uint16384 Arg)
        {
            return Multiply(Arg, {});
        }
        Uint16384 operator / (uint64_t Arg)
        {
            return Divide(Arg);
        }
        Uint16384 operator / (Uint16384 Arg)
        {
            return Divide(Arg, {});
        }
        Uint16384 operator % (uint64_t Arg)
        {
            return Mod(Arg);
        }
        Uint16384 operator % (Uint16384 Arg)
        {
            return Mod(Arg, {});
        }

        void operator += (uint64_t Arg)
        {
            *this = Add(Arg);
        }
        void operator += (Uint16384 Arg)
        {
            *this = Add(Arg, {});
        }
        void operator -= (uint64_t Arg)
        {
            *this = Subtract(Arg);
        }
        void operator -= (Uint16384 Arg)
        {
            *this = Subtract(Arg, {});
        }
        void operator *= (uint64_t Arg)
        {
            *this = Multiply(Arg);
        }
        void operator *= (Uint16384 Arg)
        {
            *this = Multiply(Arg, {});
        }
        void operator /= (uint64_t Arg)
        {
            *this = Divide(Arg);
        }
        void operator /= (Uint16384 Arg)
        {
            *this = Divide(Arg, {});
        }
        void operator %= (uint64_t Arg)
        {
            *this = Mod(Arg);
        }
        void operator %= (Uint16384 Arg)
        {
            *this = Mod(Arg, {});
        }

        Uint16384 operator ++ (int)
        {
            *this = Add(1);
            return Subtract(1);
        }
        Uint16384 operator -- (int)
        {
            *this = Subtract(1);
            return Add(1);
        }

        bool operator == (Uint16384 Arg)
        {
            if (Data == Arg.Data)
            {
                return true;
            }
            return false;
        }
        bool operator != (Uint16384 Arg)
        {
            if (Data == Arg.Data)
            {
                return false;
            }
            return true;
        }
        bool operator < (Uint16384 Arg)
        {
            return FirstIsSmaller((*this).Data, Arg.Data);
        }
        bool operator > (Uint16384 Arg)
        {
            return FirstIsSmaller(Arg.Data, (*this).Data);
        }
        bool operator <= (Uint16384 Arg)
        {
            return !FirstIsSmaller(Arg.Data, (*this).Data);
        }
        bool operator >= (Uint16384 Arg)
        {
            return !FirstIsSmaller((*this).Data, Arg.Data);
        }
   
        #define UINT_16384_MIN std::bitset<16384>(0)
        #define UINT_16384_MAX std::bitset<16384>(0).set()

        friend std::ostream& operator << (std::ostream&, Uint16384);
   };

   std::ostream& operator << (std::ostream& os, Uint16384 Arg)
   {
       return os << Arg.Data;
   }
}
