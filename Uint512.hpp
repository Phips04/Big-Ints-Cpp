#pragma once

#include <initializer_list>
#include <iostream>
#include <string>

#include "BigIntsBase.hpp"

namespace BigInts
{
    class Uint512 : public BigInts::BigIntsBase<512>
    {
    private:
        
    public:
        Uint512() : BigIntsBase() {}
        Uint512(std::string Arg) : BigIntsBase(Arg) {}
        Uint512(std::bitset<512> Arg) : BigIntsBase(Arg) {}
        Uint512(int Arg) : BigIntsBase(Arg) {}
        Uint512(uint64_t Arg) : BigIntsBase(Arg) {}

        Uint512 Add(uint64_t Arg)
        {
            return Uint512(Internal_Add(Data, std::bitset<512>(Arg)));
        }
        Uint512 Add(Uint512 Arg, std::initializer_list<Uint512> Il)
        {
            Uint512 result(Internal_Add(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Add(result.Data, element.Data);
            }
            return result;
        }
        Uint512 Subtract(uint64_t Arg)
        {
            return Uint512(Internal_Subtract(Data, std::bitset<512>(Arg)));
        }
        Uint512 Subtract(Uint512 Arg, std::initializer_list<Uint512> Il)
        {
            Uint512 result(Internal_Subtract(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Subtract(result.Data, element.Data);
            }
            return result;
        }
        Uint512 Multiply(uint64_t Arg)
        {
            return Uint512(Internal_Multiply(Data, std::bitset<512>(Arg)));
        }
        Uint512 Multiply(Uint512 Arg, std::initializer_list<Uint512> Il)
        {
            Uint512 result(Internal_Multiply(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Multiply(result.Data, element.Data);
            }
            return result;            
        }
        Uint512 Divide(uint64_t Arg)
        {
            return Internal_Divide(Data, std::bitset<512>(Arg));
        }
        Uint512 Divide(Uint512 Arg, std::initializer_list<Uint512> Il)
        {
            Uint512 result(Internal_Divide(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Divide(result.Data, element.Data);
            }
            return result;
        }   
        Uint512 Pow(uint64_t Arg)
        {
            return Internal_Pow(Data, std::bitset<512>(Arg));
        }
        Uint512 Pow(Uint512 Arg, std::initializer_list<Uint512> Il)
        {
            Uint512 result(Internal_Pow(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Pow(result.Data, element.Data);
            }
            return result;
        }
        Uint512 Mod(uint64_t Arg)
        {
            return Internal_Mod(Data, std::bitset<512>(Arg));
        }
        Uint512 Mod(Uint512 Arg, std::initializer_list<Uint512> Il)
        {
            Uint512 result(Internal_Mod(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Mod(result.Data, element.Data);
            }
            return result;
        }
        Uint512 Log2()
        {
            return Internal_Log(Data, std::bitset<512>(2));
        }
        Uint512 Log10()
        {
            return Internal_Log(Data, std::bitset<512>(10));
        }
        Uint512	Log(uint64_t Arg)
        {
            return Internal_Log(Data, std::bitset<512>(Arg));
        }
        Uint512 Log(Uint512 Arg)
        {
            return Internal_Log(Data, Arg.Data);
        }
        Uint512 Sqrt()
        {
            return Internal_Sqrt(Data);
        }
        Uint512 Factorial()
        {
            return Internal_Factorial(Data);
        }
   
        //Operators
        Uint512 operator + (uint64_t Arg)
        {
            return Add(Arg);
        }
        Uint512 operator + (Uint512 Arg)
        {
            return Add(Arg, {});
        }
        Uint512 operator - (uint64_t Arg)
        {
            return Subtract(Arg);
        }
        Uint512 operator - (Uint512 Arg)
        {
            return Subtract(Arg, {});
        }
        Uint512 operator * (uint64_t Arg)
        {
            return Multiply(Arg);
        }
        Uint512 operator * (Uint512 Arg)
        {
            return Multiply(Arg, {});
        }
        Uint512 operator / (uint64_t Arg)
        {
            return Divide(Arg);
        }
        Uint512 operator / (Uint512 Arg)
        {
            return Divide(Arg, {});
        }
        Uint512 operator % (uint64_t Arg)
        {
            return Mod(Arg);
        }
        Uint512 operator % (Uint512 Arg)
        {
            return Mod(Arg, {});
        }

        void operator += (uint64_t Arg)
        {
            *this = Add(Arg);
        }
        void operator += (Uint512 Arg)
        {
            *this = Add(Arg, {});
        }
        void operator -= (uint64_t Arg)
        {
            *this = Subtract(Arg);
        }
        void operator -= (Uint512 Arg)
        {
            *this = Subtract(Arg, {});
        }
        void operator *= (uint64_t Arg)
        {
            *this = Multiply(Arg);
        }
        void operator *= (Uint512 Arg)
        {
            *this = Multiply(Arg, {});
        }
        void operator /= (uint64_t Arg)
        {
            *this = Divide(Arg);
        }
        void operator /= (Uint512 Arg)
        {
            *this = Divide(Arg, {});
        }
        void operator %= (uint64_t Arg)
        {
            *this = Mod(Arg);
        }
        void operator %= (Uint512 Arg)
        {
            *this = Mod(Arg, {});
        }

        Uint512 operator ++ (int)
        {
            *this = Add(1);
            return Subtract(1);
        }
        Uint512 operator -- (int)
        {
            *this = Subtract(1);
            return Add(1);
        }

        bool operator == (Uint512 Arg)
        {
            if (Data == Arg.Data)
            {
                return true;
            }
            return false;
        }
        bool operator != (Uint512 Arg)
        {
            if (Data == Arg.Data)
            {
                return false;
            }
            return true;
        }
        bool operator < (Uint512 Arg)
        {
            return FirstIsSmaller((*this).Data, Arg.Data);
        }
        bool operator > (Uint512 Arg)
        {
            return FirstIsSmaller(Arg.Data, (*this).Data);
        }
        bool operator <= (Uint512 Arg)
        {
            return !FirstIsSmaller(Arg.Data, (*this).Data);
        }
        bool operator >= (Uint512 Arg)
        {
            return !FirstIsSmaller((*this).Data, Arg.Data);
        }
   
        #define UINT_512_MIN std::bitset<512>(0)
        #define UINT_512_MAX std::bitset<512>(0).set()

        friend std::ostream& operator << (std::ostream&, Uint512);
   };

   std::ostream& operator << (std::ostream& os, Uint512 Arg)
   {
       return os << Arg.Data;
   }
}
