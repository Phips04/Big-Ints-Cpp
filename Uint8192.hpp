#pragma once

#include <initializer_list>
#include <iostream>
#include <string>

#include "BigIntsBase.hpp"

namespace BigInts
{
    class Uint8192 : public BigInts::BigIntsBase<8192>
    {
    private:
        
    public:
        Uint8192() : BigIntsBase() {}
        Uint8192(std::string Arg) : BigIntsBase(Arg) {}
        Uint8192(std::bitset<8192> Arg) : BigIntsBase(Arg) {}
        Uint8192(int Arg) : BigIntsBase(Arg) {}
        Uint8192(uint64_t Arg) : BigIntsBase(Arg) {}

        Uint8192 Add(uint64_t Arg)
        {
            return Uint8192(Internal_Add(Data, std::bitset<8192>(Arg)));
        }
        Uint8192 Add(Uint8192 Arg, std::initializer_list<Uint8192> Il)
        {
            Uint8192 result(Internal_Add(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Add(result.Data, element.Data);
            }
            return result;
        }
        Uint8192 Subtract(uint64_t Arg)
        {
            return Uint8192(Internal_Subtract(Data, std::bitset<8192>(Arg)));
        }
        Uint8192 Subtract(Uint8192 Arg, std::initializer_list<Uint8192> Il)
        {
            Uint8192 result(Internal_Subtract(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Subtract(result.Data, element.Data);
            }
            return result;
        }
        Uint8192 Multiply(uint64_t Arg)
        {
            return Uint8192(Internal_Multiply(Data, std::bitset<8192>(Arg)));
        }
        Uint8192 Multiply(Uint8192 Arg, std::initializer_list<Uint8192> Il)
        {
            Uint8192 result(Internal_Multiply(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Multiply(result.Data, element.Data);
            }
            return result;            
        }
        Uint8192 Divide(uint64_t Arg)
        {
            return Internal_Divide(Data, std::bitset<8192>(Arg));
        }
        Uint8192 Divide(Uint8192 Arg, std::initializer_list<Uint8192> Il)
        {
            Uint8192 result(Internal_Divide(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Divide(result.Data, element.Data);
            }
            return result;
        }   
        Uint8192 Pow(uint64_t Arg)
        {
            return Internal_Pow(Data, std::bitset<8192>(Arg));
        }
        Uint8192 Pow(Uint8192 Arg, std::initializer_list<Uint8192> Il)
        {
            Uint8192 result(Internal_Pow(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Pow(result.Data, element.Data);
            }
            return result;
        }
        Uint8192 Mod(uint64_t Arg)
        {
            return Internal_Mod(Data, std::bitset<8192>(Arg));
        }
        Uint8192 Mod(Uint8192 Arg, std::initializer_list<Uint8192> Il)
        {
            Uint8192 result(Internal_Mod(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Mod(result.Data, element.Data);
            }
            return result;
        }
        Uint8192 Log2()
        {
            return Internal_Log(Data, std::bitset<8192>(2));
        }
        Uint8192 Log10()
        {
            return Internal_Log(Data, std::bitset<8192>(10));
        }
        Uint8192	Log(uint64_t Arg)
        {
            return Internal_Log(Data, std::bitset<8192>(Arg));
        }
        Uint8192 Log(Uint8192 Arg)
        {
            return Internal_Log(Data, Arg.Data);
        }
        Uint8192 Sqrt()
        {
            return Internal_Sqrt(Data);
        }
        Uint8192 Factorial()
        {
            return Internal_Factorial(Data);
        }
   
        //Operators
        Uint8192 operator + (uint64_t Arg)
        {
            return Add(Arg);
        }
        Uint8192 operator + (Uint8192 Arg)
        {
            return Add(Arg, {});
        }
        Uint8192 operator - (uint64_t Arg)
        {
            return Subtract(Arg);
        }
        Uint8192 operator - (Uint8192 Arg)
        {
            return Subtract(Arg, {});
        }
        Uint8192 operator * (uint64_t Arg)
        {
            return Multiply(Arg);
        }
        Uint8192 operator * (Uint8192 Arg)
        {
            return Multiply(Arg, {});
        }
        Uint8192 operator / (uint64_t Arg)
        {
            return Divide(Arg);
        }
        Uint8192 operator / (Uint8192 Arg)
        {
            return Divide(Arg, {});
        }
        Uint8192 operator % (uint64_t Arg)
        {
            return Mod(Arg);
        }
        Uint8192 operator % (Uint8192 Arg)
        {
            return Mod(Arg, {});
        }

        void operator += (uint64_t Arg)
        {
            *this = Add(Arg);
        }
        void operator += (Uint8192 Arg)
        {
            *this = Add(Arg, {});
        }
        void operator -= (uint64_t Arg)
        {
            *this = Subtract(Arg);
        }
        void operator -= (Uint8192 Arg)
        {
            *this = Subtract(Arg, {});
        }
        void operator *= (uint64_t Arg)
        {
            *this = Multiply(Arg);
        }
        void operator *= (Uint8192 Arg)
        {
            *this = Multiply(Arg, {});
        }
        void operator /= (uint64_t Arg)
        {
            *this = Divide(Arg);
        }
        void operator /= (Uint8192 Arg)
        {
            *this = Divide(Arg, {});
        }
        void operator %= (uint64_t Arg)
        {
            *this = Mod(Arg);
        }
        void operator %= (Uint8192 Arg)
        {
            *this = Mod(Arg, {});
        }

        Uint8192 operator ++ (int)
        {
            *this = Add(1);
            return Subtract(1);
        }
        Uint8192 operator -- (int)
        {
            *this = Subtract(1);
            return Add(1);
        }

        bool operator == (Uint8192 Arg)
        {
            if (Data == Arg.Data)
            {
                return true;
            }
            return false;
        }
        bool operator != (Uint8192 Arg)
        {
            if (Data == Arg.Data)
            {
                return false;
            }
            return true;
        }
        bool operator < (Uint8192 Arg)
        {
            return FirstIsSmaller((*this).Data, Arg.Data);
        }
        bool operator > (Uint8192 Arg)
        {
            return FirstIsSmaller(Arg.Data, (*this).Data);
        }
        bool operator <= (Uint8192 Arg)
        {
            return !FirstIsSmaller(Arg.Data, (*this).Data);
        }
        bool operator >= (Uint8192 Arg)
        {
            return !FirstIsSmaller((*this).Data, Arg.Data);
        }
   
        #define UINT_8192_MIN std::bitset<8192>(0)
        #define UINT_8192_MAX std::bitset<8192>(0).set()

        friend std::ostream& operator << (std::ostream&, Uint8192);
   };

   std::ostream& operator << (std::ostream& os, Uint8192 Arg)
   {
       return os << Arg.Data;
   }
}
