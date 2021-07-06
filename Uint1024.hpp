

#include <initializer_list>
#include <iostream>
#include <string>

#include "BigIntsBase.hpp"

namespace BigInts
{
    class Uint1024 : public BigInts::BigIntsBase<1024>
    {
    private:
        
    public:
        Uint1024() : BigIntsBase() {}
        Uint1024(std::string Arg) : BigIntsBase(Arg) {}
        Uint1024(std::bitset<1024> Arg) : BigIntsBase(Arg) {}
        Uint1024(int Arg) : BigIntsBase(Arg) {}
        Uint1024(uint64_t Arg) : BigIntsBase(Arg) {}

        Uint1024 Add(uint64_t Arg)
        {
            return Uint1024(Internal_Add(Data, std::bitset<1024>(Arg)));
        }
        Uint1024 Add(Uint1024 Arg, std::initializer_list<Uint1024> Il)
        {
            Uint1024 result(Internal_Add(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Add(result.Data, element.Data);
            }
            return result;
        }
        Uint1024 Subtract(uint64_t Arg)
        {
            return Uint1024(Internal_Subtract(Data, std::bitset<1024>(Arg)));
        }
        Uint1024 Subtract(Uint1024 Arg, std::initializer_list<Uint1024> Il)
        {
            Uint1024 result(Internal_Subtract(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Subtract(result.Data, element.Data);
            }
            return result;
        }
        Uint1024 Multiply(uint64_t Arg)
        {
            return Uint1024(Internal_Multiply(Data, std::bitset<1024>(Arg)));
        }
        Uint1024 Multiply(Uint1024 Arg, std::initializer_list<Uint1024> Il)
        {
            Uint1024 result(Internal_Multiply(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Multiply(result.Data, element.Data);
            }
            return result;            
        }
        Uint1024 Divide(uint64_t Arg)
        {
            return Internal_Divide(Data, std::bitset<1024>(Arg));
        }
        Uint1024 Divide(Uint1024 Arg, std::initializer_list<Uint1024> Il)
        {
            Uint1024 result(Internal_Divide(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Divide(result.Data, element.Data);
            }
            return result;
        }   
        Uint1024 Pow(uint64_t Arg)
        {
            return Internal_Pow(Data, std::bitset<1024>(Arg));
        }
        Uint1024 Pow(Uint1024 Arg, std::initializer_list<Uint1024> Il)
        {
            Uint1024 result(Internal_Pow(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Pow(result.Data, element.Data);
            }
            return result;
        }
        Uint1024 Mod(uint64_t Arg)
        {
            return Internal_Mod(Data, std::bitset<1024>(Arg));
        }
        Uint1024 Mod(Uint1024 Arg, std::initializer_list<Uint1024> Il)
        {
            Uint1024 result(Internal_Mod(Data, Arg.Data));
            for (auto element : Il)
            {
                result = Internal_Mod(result.Data, element.Data);
            }
            return result;
        }
        Uint1024 Log2()
        {
            return Internal_Log(Data, std::bitset<1024>(2));
        }
        Uint1024 Log10()
        {
            return Internal_Log(Data, std::bitset<1024>(10));
        }
        Uint1024	Log(uint64_t Arg)
        {
            return Internal_Log(Data, std::bitset<1024>(Arg));
        }
        Uint1024 Log(Uint1024 Arg)
        {
            return Internal_Log(Data, Arg.Data);
        }
        Uint1024 Sqrt()
        {
            return Internal_Sqrt(Data);
        }
        Uint1024 Factorial()
        {
            return Internal_Factorial(Data);
        }
   
        //Operators
        Uint1024 operator + (uint64_t Arg)
        {
            return Add(Arg);
        }
        Uint1024 operator + (Uint1024 Arg)
        {
            return Add(Arg, {});
        }
        Uint1024 operator - (uint64_t Arg)
        {
            return Subtract(Arg);
        }
        Uint1024 operator - (Uint1024 Arg)
        {
            return Subtract(Arg, {});
        }
        Uint1024 operator * (uint64_t Arg)
        {
            return Multiply(Arg);
        }
        Uint1024 operator * (Uint1024 Arg)
        {
            return Multiply(Arg, {});
        }
        Uint1024 operator / (uint64_t Arg)
        {
            return Divide(Arg);
        }
        Uint1024 operator / (Uint1024 Arg)
        {
            return Divide(Arg, {});
        }
        Uint1024 operator % (uint64_t Arg)
        {
            return Mod(Arg);
        }
        Uint1024 operator % (Uint1024 Arg)
        {
            return Mod(Arg, {});
        }

        void operator += (uint64_t Arg)
        {
            *this = Add(Arg);
        }
        void operator += (Uint1024 Arg)
        {
            *this = Add(Arg, {});
        }
        void operator -= (uint64_t Arg)
        {
            *this = Subtract(Arg);
        }
        void operator -= (Uint1024 Arg)
        {
            *this = Subtract(Arg, {});
        }
        void operator *= (uint64_t Arg)
        {
            *this = Multiply(Arg);
        }
        void operator *= (Uint1024 Arg)
        {
            *this = Multiply(Arg, {});
        }
        void operator /= (uint64_t Arg)
        {
            *this = Divide(Arg);
        }
        void operator /= (Uint1024 Arg)
        {
            *this = Divide(Arg, {});
        }
        void operator %= (uint64_t Arg)
        {
            *this = Mod(Arg);
        }
        void operator %= (Uint1024 Arg)
        {
            *this = Mod(Arg, {});
        }

        Uint1024 operator ++ (int)
        {
            *this = Add(1);
            return Subtract(1);
        }
        Uint1024 operator -- (int)
        {
            *this = Subtract(1);
            return Add(1);
        }

        bool operator == (Uint1024 Arg)
        {
            if (Data == Arg.Data)
            {
                return true;
            }
            return false;
        }
        bool operator != (Uint1024 Arg)
        {
            if (Data == Arg.Data)
            {
                return false;
            }
            return true;
        }
        bool operator < (Uint1024 Arg)
        {
            return FirstIsSmaller((*this).Data, Arg.Data);
        }
        bool operator > (Uint1024 Arg)
        {
            return FirstIsSmaller(Arg.Data, (*this).Data);
        }
        bool operator <= (Uint1024 Arg)
        {
            return !FirstIsSmaller(Arg.Data, (*this).Data);
        }
        bool operator >= (Uint1024 Arg)
        {
            return !FirstIsSmaller((*this).Data, Arg.Data);
        }
   
        #define UINT_1024_MIN std::bitset<1024>(0)
        #define UINT_1024_MAX std::bitset<1024>(0).set()

        friend std::ostream& operator << (std::ostream&, Uint1024);
   };

   std::ostream& operator << (std::ostream& os, Uint1024 Arg)
   {
       return os << Arg.Data;
   }
}