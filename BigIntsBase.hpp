#pragma once

#include <bitset>
#include <string>
#include <exception>
#include <math.h>
#include <vector>

namespace BigInts
{
    template<size_t Length>
    class BigIntsBase
    {
    protected:
        std::bitset<Length> Data;
        //Arithmetics
        static std::bitset<Length> Internal_Add(std::bitset<Length> Arg1, std::bitset<Length> Arg2)
        {
            std::bitset<Length> result(0);
            size_t Reminder = 0;

            for (size_t i = 0; i < Length; i++)
            {
                if (Arg1[i] == 1 && Arg2[i] == 1 && Reminder == 1)
                {
                    result[i] = 1;
                    if (i == Length - 1)
                    {
                        throw std::logic_error("The result will exceed the max value of this type");
                    }
                    Reminder = 1;
                    continue;
                }
                if ((Arg1[i] == 1 && Arg2[i] == 1 && Reminder == 0) ||
                    (Arg1[i] == 1 && Arg2[i] == 0 && Reminder == 1) ||
                    (Arg1[i] == 0 && Arg2[i] == 1 && Reminder == 1))
                {
                    result[i] = 0;
                    if (i == Length - 1)
                    {
                        throw std::logic_error("The result will exceed the max value of this type");
                    }
                    Reminder =  1;
                    continue;
                }
                if ((Arg1[i] == 1 && Arg2[i] == 0 && Reminder == 0) ||
                    (Arg1[i] == 0 && Arg2[i] == 1 && Reminder == 0) ||
                    (Arg1[i] == 0 && Arg2[i] == 0 && Reminder == 1))
                {
                    result[i] = 1;
                    Reminder = 0;
                    continue;
                }
                else
                {
                    result[i] = 0;
                    Reminder = 0;
                    continue;
                }               
            }            

            return result;
        }
        static std::bitset<Length> Internal_Subtract(std::bitset<Length> Arg1, std::bitset<Length> Arg2)
        {
            std::bitset<Length> result(0);
            size_t Reminder = 0;

            if (FirstIsSmaller(Arg1, Arg2))
            {
                throw std::logic_error("This type can't store any negative values");
            }

            for (size_t i = 0; i < Length; i++)
            {
                if ((Arg1[i] == 1 && Arg2[i] == 1 && Reminder == 1) ||
                    (Arg1[i] == 0 && Arg2[i] == 1 && Reminder == 0) ||
                    (Arg1[i] == 0 && Arg2[i] == 0 && Reminder == 1))
                {
                    result[i] = 1;
                    Reminder = 1;
                    continue;
                }
                if ((Arg1[i] == 1 && Arg2[i] == 1 && Reminder == 0) ||
                    (Arg1[i] == 1 && Arg2[i] == 0 && Reminder == 1) ||
                    (Arg1[i] == 0 && Arg2[i] == 0 && Reminder == 0))
                {
                    result[i] = 0;
                    Reminder = 0;
                    continue;
                }
                if (Arg1[i] == 0 && Arg2[i] == 1 && Reminder == 1)
                {
                    result[i] = 0;
                    Reminder = 1;
                    continue;
                }
                else
                {
                    result[i] = 1;
                    Reminder = 0;
                }
            }
            
            return result;
        }  
        static std::bitset<Length> Internal_Multiply(std::bitset<Length> Arg1, std::bitset<Length> Arg2)
        {
            std::vector<std::bitset<Length>> ItemsToAdd = std::vector<std::bitset<Length>>();
            ItemsToAdd.reserve(128);

            size_t ThisLength = 0;
            size_t InitLength = 0;
            bool ThisLengthFound = false;
            bool InitLengthFound = false;

            for (size_t i = 0; i < Length; i++)
            {
                if (Arg1[Length - 1 - i] == 1 && ThisLengthFound == false)
                {
                    ThisLength = Length - i;
                    ThisLengthFound = 1;
                }
                if (Arg2[Length - 1 - i] == 1 && InitLengthFound == false)
                {
                    InitLength = Length - i;
                    InitLengthFound = true;
                }
                if (ThisLengthFound && InitLengthFound)
                {
                    if (ThisLength + InitLength - 1 > Length)
                    {
                        throw std::logic_error("The result will exceed the max value of this type");
                    }
                }
            }

            for (size_t i = 0; i < Length; i++)
            {
               if (Arg2[i] == 1)
               {
                   std::bitset<Length> item(0);
                   for (size_t x = 0; x < Length; x++)
                   {
                       if (x < i)
                       {
                           item[x] = 0;
                       }
                       else
                       {
                           item[x] = Arg1[x - i];
                       }
                   }
                   
                   ItemsToAdd.push_back(item);
               }
               
            }
            
            std::bitset<128> result(0);

            for (auto element : ItemsToAdd)
            {
                result = Internal_Add(result, element);
            }
            
            return result;
        }    
        static std::bitset<Length> Internal_Divide(std::bitset<Length> Arg1, std::bitset<Length> Arg2)
        {
            if (Arg2 == std::bitset<Length>(0))
            {
                throw std::logic_error("Division by 0 is not defined");
            }

            if (FirstIsSmaller(Arg1, Arg2))
            {
                return std::bitset<Length>(0);
            }

            std::string ThisStream = "";
            ThisStream.reserve(Length);
            std::string InitStream = "";
            InitStream.reserve(Length);
            std::string ThisCurrentStream = "1";
            ThisCurrentStream.reserve(Length);
            std::string ResultStream = "";
            ResultStream.reserve(Length);
            bool StartRecordingThis = false;
            bool StartRecordingInit = false;

            for (size_t i = 0; i < Length; i++)
            {
                if (Arg1[Length - 1 - i] == 1)
                {
                    ThisStream += "1";
                    StartRecordingThis = true;
                }
                else if (StartRecordingThis == true)
                {
                    ThisStream += "0";
                }
                
                if(Arg2[Length - 1 - i] == 1)
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

            while (ThisStream.length() > 0)
            {
                if (FirstIsSmaller(std::bitset<Length>(ThisCurrentStream), std::bitset<Length>(InitStream)))
                {
                    ThisCurrentStream += *ThisStream.begin();
                    ThisStream.erase(ThisStream.begin());
                    ResultStream += "0";
                }
                else
                {
                    std::bitset<Length> CThis = std::bitset<Length>(ThisCurrentStream);
                    std::bitset<Length> CInit = std::bitset<Length>(InitStream);

                    std::bitset<Length> RawResult = Internal_Subtract(CThis, CInit);

                    std::string result = "";
                    result.reserve(Length);
                    bool StartWritingZeros = false;

                    for (size_t i = 0; i < Length; i++)
                    {
                        if (RawResult[Length - 1 - i] == 1)
                        {
                            result += "1";
                            StartWritingZeros = true;
                        }
                        if (RawResult[Length - 1 - i] == 0 && StartWritingZeros == true)
                        {
                            result += "0";
                        }
                    }
                    
                    ThisCurrentStream = result;
                    ThisCurrentStream += *ThisStream.begin();
                    ThisStream.erase(ThisStream.begin());
                    ResultStream += "1";
                }
            }
            
            if (FirstIsSmaller(std::bitset<Length>(ThisCurrentStream), std::bitset<Length>(InitStream)))
            {
                ResultStream += "0";
            }
            else
            {
                ResultStream += "1";
            }
            
            while (*ResultStream.begin() == '0')
            {
                ResultStream.erase(ResultStream.begin());
            }
            
            return std::bitset<Length>(ResultStream);
        }
        static std::bitset<Length> Internal_Pow(std::bitset<Length> Arg1, std::bitset<Length> Arg2)
        {
            std::bitset<Length> result(1);
            if (Arg2 == std::bitset<Length>(0))
            {
                return result;
            }

            for (std::bitset<Length> i(0); FirstIsSmaller(i, Arg2); i = Internal_Add(i, std::bitset<Length>(1)))
            {
                result = Internal_Multiply(result, Arg1);
            }
            
            return result;
        }
        static std::bitset<Length> Internal_Mod(std::bitset<Length> Arg1, std::bitset<Length> Arg2)
        {
            return Internal_Subtract(Arg1, Internal_Multiply(Internal_Divide(Arg1, Arg2), Arg2));
        }
        static std::bitset<Length> Internal_Log(std::bitset<Length> Powres, std::bitset<Length> Base)
        {
            if (Base == std::bitset<Length>(0))
            {
                throw std::logic_error("Logarithm on a number with base = 0 is not defined");
            }
            if (Base == std::bitset<Length>(1))
            {
                throw std::logic_error("Logarithm on a number with base = 1 is not defined");
            }
            if (Powres == std::bitset<Length>(0))
            {
                throw std::logic_error("Logarithm on a number = 0 is not defined");
            }

            if (FirstIsSmaller(Powres, Base))
            {
                return std::bitset<Length>(0);
            }
            
            size_t CurrentPosition = Length / 2;
            size_t CurrentOffsetLength = Length / 4;

            while (true)
            {
                try
                {
                    if (Powres == Internal_Pow(Base, std::bitset<Length>(CurrentPosition))
                        || FirstIsSmaller(Internal_Pow(Base, std::bitset<Length>(CurrentPosition)), Powres)
                        && FirstIsSmaller(Powres, Internal_Pow(Base, std::bitset<Length>(CurrentPosition + 1))))
                    {
                        return std::bitset<Length>(CurrentPosition);
                    }
                    if (FirstIsSmaller(Powres, Internal_Pow(Base, std::bitset<Length>(CurrentPosition))))
                    {
                        CurrentPosition -= CurrentOffsetLength;
                        CurrentOffsetLength /= 2;
                        continue;
                    }
                    if (FirstIsSmaller(Internal_Pow(Base, std::bitset<Length>(CurrentPosition)), Powres))
                    {
                        CurrentPosition += CurrentOffsetLength;
                        CurrentOffsetLength /= 2;
                        continue;
                    }
                }
                catch(const std::exception& e)
                {
                    CurrentPosition -= CurrentOffsetLength;
                    CurrentOffsetLength /= 2;
                    continue;
                }               
            }
        }
        static std::bitset<Length> Internal_Sqrt(std::bitset<Length> Arg)
        {
            if (Arg == std::bitset<Length>(0))
            {
                return std::bitset<Length>(0);
            }
            
            std::bitset<Length> result = std::bitset<Length>(0);

            std::bitset<Length> CurrentPosition = std::bitset<Length>(2);
            CurrentPosition = Internal_Pow(CurrentPosition, std::bitset<Length>(Length / 2));
            std::bitset<Length> CurrentOffset = Internal_Divide(CurrentPosition, std::bitset<Length>(2));

            while (true)
            {
                try
                {
                    if ((FirstIsSmaller(Internal_Multiply(CurrentPosition, CurrentPosition), Arg)
                        && FirstIsSmaller(Arg, Internal_Multiply(Internal_Add(CurrentPosition, std::bitset<Length>(1)),
                        Internal_Add(CurrentPosition, std::bitset<Length>(1)))))
                        || Arg == Internal_Multiply(CurrentPosition, CurrentPosition))
                    {
                        return CurrentPosition;
                    }
                    if (FirstIsSmaller(Arg, Internal_Multiply(CurrentPosition, CurrentPosition)))
                    {
                        CurrentPosition = Internal_Subtract(CurrentPosition, CurrentOffset);
                        CurrentOffset = Internal_Divide(CurrentOffset, std::bitset<Length>(2));
                        continue;
                    }
                    if (FirstIsSmaller(Internal_Multiply(CurrentPosition, CurrentPosition), Arg))
                    {
                        CurrentPosition = Internal_Add(CurrentPosition, CurrentOffset);
                        CurrentOffset = Internal_Divide(CurrentOffset, std::bitset<Length>(2));
                        continue;
                    }
                }
                catch(const std::exception& e)
                {
                    CurrentPosition = Internal_Subtract(CurrentPosition, CurrentOffset);
                    CurrentOffset = Internal_Divide(CurrentOffset, std::bitset<Length>(2));
                    continue;
                }               
            }            
        }
        static std::bitset<Length> Internal_Factorial(std::bitset<Length> Arg)
        {
            if (Arg == std::bitset<Length>(0))
            {
                return std::bitset<Length>(1);
            }

            std::bitset<Length> result = Arg;

            for (std::bitset<Length> i(1); FirstIsSmaller(i, Arg);
                 i = Internal_Add(i, std::bitset<Length>(1)))
            {
                result = Internal_Multiply(i, result);
            }
            
            return result;
        }
        
        //Helpers
        static bool FirstIsSmaller(std::bitset<Length> First, std::bitset<Length> Second)
        {
            for (size_t i = 0; i < Length; i++)
            {
                if (First[Length - 1 - i] == 1 && Second[Length - 1 - i] == 0)
                {
                    return false;
                }
                else if (First[Length - 1 - i] == 0 && Second[Length - 1 - i] == 1)
                {
                    return true;
                }
            }
            
            return false;
        }

    public:
        //Constructors
        BigIntsBase()
        {
            this->Data = std::bitset<Length>();
        }
        BigIntsBase(std::string Bits)
        {
            this->Data = std::bitset<Length>(Bits);
        }
        BigIntsBase(std::bitset<Length> Arg)
        {
            this->Data = Arg;
        }
        BigIntsBase(int Arg)
        {
            if (Arg < 0)
            {
                throw std::invalid_argument("Can't store negative values");
            }
            this->Data = std::bitset<Length>(Arg);
        }
        BigIntsBase(uint64_t Arg)
        {
            this->Data = std::bitset<Length>(Arg);
        }

        //Different helpers     
        std::string ToString()
        {
            return Data.to_string();
        }
        std::bitset<Length> GetBinaryRepresentation()
        {
            return Data;
        }        
        //Converters
        uint64_t TryToUint64()
        {
            uint64_t result = 0;

            if (FirstIsSmaller(std::bitset<Length>(UINT64_MAX), Data))
            {
                throw std::bad_cast();
            }

            for (size_t i = 0; i < 64; i++)
            {
                if (Data[i] == 1)
                {
                    result += uint64_t(pow(2 ,i));
                }               
            }
            
            return result;
        }
        int TryToInt()
        {
            int result = 0;

            if (FirstIsSmaller(std::bitset<Length>(INT_MAX), Data))
            {
                throw std::bad_cast();
            }

            for (size_t i = 0; i < 31; i++)
            {
                if (Data[i] == 1)
                {
                    result += int(pow(2 ,i));
                }               
            }
            
            return result;
        }
    };
}
