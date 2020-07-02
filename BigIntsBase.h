#pragma once

#include <string>
#include <bitset>
#include <stdexcept>
#include <initializer_list>
#include <vector>

template<typename T, int Length>
class BigIntsBase
{
private:
	std::bitset<Length> Data;

	static std::bitset<Length> StringToBitset(std::string);
    static uint64_t TryToUlong_(std::bitset<Length>);
    static bool FirstIsSmaller(std::bitset<Length>, std::bitset<Length>);

    static std::bitset<Length> Internal_Add(std::bitset<Length>, std::bitset<Length>);
    static std::bitset<Length> Internal_Subtract(std::bitset<Length>, std::bitset<Length>);
    static std::bitset<Length> Internal_Multiply(std::bitset<Length>, std::bitset<Length>);
    static std::bitset<Length> Internal_Divide(std::bitset<Length>, std::bitset<Length>);
    static std::bitset<Length> Internal_Pow(std::bitset<Length>, std::bitset<Length>);
    static std::bitset<Length> Internal_Mod(std::bitset<Length>, std::bitset<Length>);
    static std::bitset<Length> Internal_Log(std::bitset<Length>, std::bitset<Length>);
    static std::bitset<Length> Internal_Sqrt(std::bitset<Length>);
    static std::bitset<Length> Internal_Factorial(std::bitset<Length>);
public:
	BigIntsBase();
	BigIntsBase(std::string);
	BigIntsBase(std::bitset<Length>);
	BigIntsBase(int);
	BigIntsBase(uint64_t);

    T Add(uint64_t);
    T Add(std::initializer_list<BigIntsBase<T, Length>>);

    T Subtract(uint64_t);
    T Subtract(std::initializer_list<BigIntsBase<T, Length>>);

    T Multiply(uint64_t);
    T Multiply(std::initializer_list<BigIntsBase<T, Length>>);

    T Divide(uint64_t);
    T Divide(std::initializer_list<BigIntsBase<T, Length>>);

    T Pow(uint64_t);
    T Pow(std::initializer_list<BigIntsBase<T, Length>>);

    T Mod(uint64_t);
    T Mod(std::initializer_list<BigIntsBase<T, Length>>);

    T Log2();
    T Log10();
    T Log(uint64_t);
    T Log(BigIntsBase<T, Length>);

    T Sqrt();

    T Factorial();

    int TryToInt();

    uint64_t TryToUint64();

    std::bitset<Length> GetBinaryRepresentation();

    std::string ToString();

    T operator +(uint64_t);
    T operator +(std::initializer_list<BigIntsBase<T, Length>>);

    T operator -(uint64_t);
    T operator -(std::initializer_list<BigIntsBase<T, Length>>);

    T operator *(uint64_t);
    T operator *(std::initializer_list<BigIntsBase<T, Length>>);

    T operator /(uint64_t);
    T operator /(std::initializer_list<BigIntsBase<T, Length>>);

    T operator %(uint64_t);
    T operator %(std::initializer_list<BigIntsBase<T, Length>>);

    T operator ++();
    T operator --();

    void operator += (uint64_t);
    void operator += (std::initializer_list<BigIntsBase<T, Length>>);

    void operator -= (uint64_t);
    void operator -= (std::initializer_list<BigIntsBase<T, Length>>);

    void operator *= (uint64_t);
    void operator *= (std::initializer_list<BigIntsBase<T, Length>>);

    void operator /= (uint64_t);
    void operator /= (std::initializer_list<BigIntsBase<T, Length>>);

    void operator %= (uint64_t);
    void operator %= (std::initializer_list<BigIntsBase<T, Length>>);

    bool operator == (BigIntsBase<T, Length>);
    bool operator != (BigIntsBase<T, Length>);
    bool operator < (BigIntsBase<T, Length>);
    bool operator > (BigIntsBase<T, Length>);
    bool operator <= (BigIntsBase<T, Length>);
    bool operator >= (BigIntsBase<T, Length>);
};

template<typename T, int Length>
inline std::bitset<Length> BigIntsBase<T, Length>::StringToBitset(std::string Arg)
{
    std::bitset<Length> Result = std::bitset<Length>(0);

    if (Arg.size() != 0)
    {
        while (Arg.at(0) == '0')
        {
            Arg = Arg.erase(0, 1);
            if (Arg.size() == 0)
            {
                break;
            }
        }
    }

    if (Arg.size() >= Length)
    {
        throw std::invalid_argument{ "The method received more than digits than bits provided" };
    }

    for (size_t i = 0; i < Arg.size(); i++)
    {
        if (Arg[Arg.size() - 1 - i] == '1')
        {
            Result[i] = true;
        }
        else if (Arg[Arg.size() - 1 - i] == '0')
        {
            Result[i] = false;
        }
        else
        {
            throw std::invalid_argument{ "The provided argument included characters which were not either '0' or '1'" };
        }
    }

    return Result;
}

template<typename T, int Length>
inline uint64_t BigIntsBase<T, Length>::TryToUlong_(std::bitset<Length> Arg)
{
    uint64_t result = 0;

    if (FirstIsSmaller(std::bitset<Arg.size()>(UINT64_MAX), Arg))
    {
        throw std::invalid_argument{ "Can not convert value into uint64" };
    }

    for (int i = 0; i < 64; i++)
    {
        if (Arg[i] == true)
        {
            result += (uint64_t)pow(2, i);
        }
    }

    return result;
}

template<typename T, int Length>
inline bool BigIntsBase<T, Length>::FirstIsSmaller(std::bitset<Length> First, std::bitset<Length> Second)
{
    for (size_t i = 0; i < First.size(); i++)
    {
        if (First[First.size() - 1 - i] && !Second[Second.size() - 1 - i])
        {
            return false;
        }
        else if (!First[First.size() - 1 - i] && Second[Second.size() - 1 - i])
        {
            return true;
        }
    }

    return false;
}

template<typename T, int Length>
inline std::bitset<Length> BigIntsBase<T, Length>::Internal_Add(std::bitset<Length> Arg1, std::bitset<Length> Arg2)
{
    std::bitset<Length> result = std::bitset<Length>(0);

    int Reminder = 0;

    for (rsize_t i = 0; i < Arg1.size(); i++)
    {
        if (Arg1[i] == 1 && Arg2[i] == 1 && Reminder == 1)
        {
            result[i] = 1;
            if (i == Arg1.size())
            {
                throw std::exception{ "The result will grow larger than the maximal value of this type" };
            }
            Reminder = 1;
            continue;
        }

        if ((Arg1[i] == 1 && Arg2[i] == 1 && Reminder == 0) ||
            (Arg1[i] == 1 && Arg2[i] == 0 && Reminder == 1) ||
            (Arg1[i] == 0 && Arg2[i] == 1 && Reminder == 1))
        {
            result[i] = 0;
            if (i == Arg1.size() - 1)
            {
                throw std::exception{ "The result will grow larger than the maximal value of this type" };
            }
            Reminder = 1;
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

template<typename T, int Length>
inline std::bitset<Length> BigIntsBase<T, Length>::Internal_Subtract(std::bitset<Length> Arg1, std::bitset<Length> Arg2)
{
    std::bitset<Length> result = std::bitset<Length>(0);

    int Reminder = 0;

    if (FirstIsSmaller(Arg1, Arg2))
    {
        throw std::exception{ "The result will be negative, this type is unsigned" };
    }

    for (size_t i = 0; i < Arg1.size(); i++)
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

        if (Arg1[i] == 1 && Arg2[i] == 0 && Reminder == 0)
        {
            result[i] = 1;
            Reminder = 0;
            continue;
        }
    }

    return result;
}

template<typename T, int Length>
inline std::bitset<Length> BigIntsBase<T, Length>::Internal_Multiply(std::bitset<Length> Arg1, std::bitset<Length> Arg2)
{
    std::vector<std::bitset<Length>> ItemsToAdd;
    ItemsToAdd.reserve(128);

    size_t ThisLength = 0;
    size_t InitLength = 0;
    bool ThisLengthFound = false;
    bool InitLengthFound = false;

    for (size_t i = 0; i < Arg1.size(); i++)
    {
        if (Arg1[Arg1.size() - 1 - i] == 1 && ThisLengthFound == false)
        {
            ThisLength = Arg1.size() - i;
            ThisLengthFound = true;
        }

        if (Arg2[Arg1.size() - 1 - i] == 1 && InitLengthFound == false)
        {
            InitLength = Arg1.size() - i;
            InitLengthFound = true;
        }

        if (ThisLengthFound && InitLengthFound)
        {
            if (ThisLength + InitLength - 1 > Arg1.size())
            {
                throw std::exception{ "The result will grow larger than the maximal value of this type" };
            }
        }
    }

    for (size_t i = 0; i < Arg1.size(); i++)
    {
        if (Arg2[i] == true)
        {
            std::bitset<Arg1.size()> item = std::bitset<Arg1.size()>(0);
            for (size_t x = 0; x < Arg1.size(); x++)
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

    std::bitset<Arg1.size()> result = std::bitset<Arg1.size()>(0);

    for (std::bitset<Length> i : ItemsToAdd)
    {
        result = Internal_Add(result, i);
    }

    return result;
}

template<typename T, int Length>
inline std::bitset<Length> BigIntsBase<T, Length>::Internal_Divide(std::bitset<Length> Arg1, std::bitset<Length> Arg2)
{
    if (Arg2 == std::bitset<Arg2.size()>(0))
    {
        throw std::exception{ "Argument was '0', division by '0' is not defined" };
    }

    if (FirstIsSmaller(Arg1, Arg2))
    {
        return std::bitset<Arg1.size()>(0);
    }

    std::string ThisStream = "";
    std::string InitStream = "";
    std::string ThisCurrentStream = "1";
    std::string ResultStream = "";
    bool StartRecordingThis = false;
    bool StartRecordingInit = false;

    for (size_t i = 0; i < Arg1.size(); i++)
    {
        if (Arg1[Arg1.size() - 1 - i] == 1)
        {
            ThisStream += "1";
            StartRecordingThis = true;
        }
        else if (StartRecordingThis == true)
        {
            ThisStream += "0";
        }

        if (Arg2[Arg1.size() - 1 - i] == 1)
        {
            InitStream += "1";
            StartRecordingInit = true;
        }
        else if (StartRecordingInit == true)
        {
            InitStream += "0";
        }
    }

    ThisStream.erase(0, 1);

    while (ThisStream.length() > 0)
    {
        //Continue working 336
        if (FirstIsSmaller(std::bitset<Arg1.size()>(ThisCurrentStream), std::bitset<Arg1.size()>(InitStream)))
        {
            ThisCurrentStream += ThisStream.at(0);
            ThisStream.erase(0, 1);
            ResultStream += "0";
        }
        else
        {
            std::bitset<Arg1.size()> CThis = std::bitset<Length>(ThisCurrentStream);
            std::bitset<Arg1.size()> CInit = std::bitset<Length>(InitStream);

            std::bitset<Arg1.size()> RawResult = Internal_Subtract(CThis, CInit);

            std::string result = "";
            bool StartWritingZeros = false;

            for (size_t i = 0; i < Arg1.size(); i++)
            {
                if (RawResult[Arg1.size() - 1 - i] == 1)
                {
                    result += "1";
                    StartWritingZeros = true;
                }
                if (RawResult[Arg1.size() - 1 - i] == 0 && StartWritingZeros == true)
                {
                    result += "0";
                }
            }

            ThisCurrentStream = result;
            ThisCurrentStream += ThisStream.at(0);
            ThisStream.erase(0, 1);
            ResultStream += "1";
        }
    }
    if (FirstIsSmaller(std::bitset<Arg1.size()>(ThisCurrentStream), std::bitset<Arg1.size()>(InitStream)))
    {
        ResultStream += "0";
    }
    else
    {
        ResultStream += "1";
    }

    while (ResultStream.at(0) == '0')
    {
        ResultStream.erase(0, 1);
    }

    return std::bitset<Arg1.size()>(ResultStream);
}

template<typename T, int Length>
inline std::bitset<Length> BigIntsBase<T, Length>::Internal_Pow(std::bitset<Length> Base, std::bitset<Length> exp)
{
    std::bitset<Base.size()> result = std::bitset<Base.size()>(1);
    result[0] = 1;

    if (exp == std::bitset<exp.size()>(0))
    {
        return result;
    }



    for (std::bitset<exp.size()> i = std::bitset<exp.size()>(0); FirstIsSmaller(i, exp); i = Internal_Add(i, std::bitset<exp.size()>(1)))
    {
        result = Internal_Multiply(result, Base);
    }

    return result;
}

template<typename T, int Length>
inline std::bitset<Length> BigIntsBase<T, Length>::Internal_Mod(std::bitset<Length> This, std::bitset<Length> Arg)
{
    std::bitset<This.size()> Result = Internal_Subtract(This, Internal_Multiply(Internal_Divide(This, Arg), Arg));
    return Result;
}

template<typename T, int Length>
inline std::bitset<Length> BigIntsBase<T, Length>::Internal_Log(std::bitset<Length> Powres, std::bitset<Length> Base)
{
    if (Base == std::bitset<Base.size()>(0))
    {
        throw std::exception{ "Argument was '0', logarithm which base = '0' is not defined" };
    }

    if (Base == std::bitset<Base.size()>(1))
    {
        throw std::exception{ "Base was '1', logarithm which base is 1 is not defined" };
    }

    if (Powres == std::bitset<Powres.size()>(0))
    {
        throw std::exception{ "The value of the object calling the function 'log(uint128 base)' was '0', logarithm with exponent = '0' is not defined" };
    }

    if (FirstIsSmaller(Powres, Base))
    {
        return std::bitset<Powres.size()>(0);
    }

    int CurrentPosition = Base.size() / (int)TryToUlong_(Base);
    int CurrentOffsetLength = Base.size() / (2 * (int)TryToUlong_(Base)) + 1;

    while (true)
    {
        if (!FirstIsSmaller(Powres, Internal_Pow(Base, std::bitset<Base.size()>(CurrentPosition))) &&
            FirstIsSmaller(Powres, Internal_Pow(Base, std::bitset<Base.size()>((uint64_t)CurrentPosition + 1))))
        {
            return std::bitset<Powres.size()>(CurrentPosition);
        }


        if (!FirstIsSmaller(Powres, Internal_Pow(Base, std::bitset<Base.size()>(CurrentPosition))))
        {
            CurrentPosition += CurrentOffsetLength;
            if (CurrentOffsetLength % 2 != 0)
            {
                CurrentOffsetLength++;
            }
            CurrentOffsetLength /= 2;
            continue;
        }

        if (FirstIsSmaller(Powres, Internal_Pow(Base, std::bitset<Base.size()>(CurrentPosition))))
        {
            CurrentPosition -= CurrentOffsetLength;
            if (CurrentOffsetLength % 2 != 0)
            {
                CurrentOffsetLength++;
            }
            CurrentOffsetLength /= 2;
            continue;
        }
    }
}

template<typename T, int Length>
inline std::bitset<Length> BigIntsBase<T, Length>::Internal_Sqrt(std::bitset<Length> Arg)
{
    if (Arg == std::bitset<Arg.size()>(0))
    {
        return std::bitset<Arg.size()>(0);
    }

    //BitArray CurrentPosition = new BitArray(Arg.Length / 2, true);
    std::bitset<Arg.size()> CurrentPosition = Internal_Divide(Internal_Pow(std::bitset<Arg.size()>(2),
        std::bitset<Arg.size()>((uint64_t)Arg.size() / 2)), std::bitset<Arg.size()>(2));
    //BitArray CurrentOffsetLength(UINT64_MAX / 4 + 1);
    std::bitset<Arg.size()> CurrentOffsetLength = Internal_Add(Internal_Divide(Internal_Pow(std::bitset<Arg.size()>(2),
        std::bitset<Arg.size()>((uint64_t)Arg.size() / 2)), std::bitset<Arg.size()>(4)), std::bitset<Arg.size()>(1));

    while (true)
    {
        if (!FirstIsSmaller(Arg, Internal_Pow(CurrentPosition, std::bitset<CurrentPosition.size()>(2))) &&
            FirstIsSmaller(Arg, Internal_Pow(Internal_Add(CurrentPosition, std::bitset<CurrentPosition.size()>(1)),
                std::bitset<CurrentPosition.size()>(2))))
        {
            return CurrentPosition;
        }

        if (FirstIsSmaller(CurrentPosition, std::bitset<CurrentPosition.size()>(3)))
        {
            return std::bitset<Arg.size()>(1);
        }

        if (!FirstIsSmaller(Arg, Internal_Pow(CurrentPosition, std::bitset<CurrentPosition.size()>(2))))
        {
            CurrentPosition = Internal_Add(CurrentPosition, CurrentOffsetLength);
            CurrentOffsetLength = Internal_Divide(CurrentOffsetLength, std::bitset<CurrentOffsetLength.size()>(2));
            continue;
        }

        if (FirstIsSmaller(Arg, Internal_Pow(CurrentPosition, std::bitset<CurrentPosition.size()>(2))))
        {
            CurrentPosition = Internal_Subtract(CurrentPosition, CurrentOffsetLength);
            CurrentOffsetLength = Internal_Divide(CurrentOffsetLength, std::bitset<CurrentOffsetLength.size()>(2));
            continue;
        }
    }
}

template<typename T, int Length>
inline std::bitset<Length> BigIntsBase<T, Length>::Internal_Factorial(std::bitset<Length> Arg)
{
    if (Arg == std::bitset<Arg.size()>(0))
    {
        return std::bitset<Arg.size()>(1);
    }

    std::bitset<Arg.size()> Result = Arg;

    for (std::bitset<Arg.size()> i = std::bitset<Arg.size()>(1);
        FirstIsSmaller(i, Arg); i = Internal_Add(i, std::bitset<Arg.size()>(1)))
    {
        Result = Internal_Multiply(i, Result);
    }

    return Result;
}

template<typename T, int Length>
inline int BigIntsBase<T, Length>::TryToInt()
{
    int result = 0;

    if (FirstIsSmaller(std::bitset<Length>(INT32_MAX), this->Data))
    {
        throw std::exception{ "Arithmetic overflow" };
    }

    for (int i = 0; i < 31; i++)
    {
        if (Data[i] == 1)
        {
            result += (int)pow(2, i);
        }
    }

    return result;
}

template<typename T, int Length>
inline uint64_t BigIntsBase<T, Length>::TryToUint64()
{
    return TryToUlong_(this->Data);
}

template<typename T, int Length>
inline std::bitset<Length> BigIntsBase<T, Length>::GetBinaryRepresentation()
{
    return this->Data;
}

template<typename T, int Length>
inline std::string BigIntsBase<T, Length>::ToString()
{
    if (this->Data == std::bitset<Length>(0))
    {
        return "0";
    }

    std::string Result = "";
    bool IsSignificant = false;

    for (size_t i = 0; i < Length; i++)
    {
        if (this->Data[Length - 1 - i] == 1)
        {
            Result += '1';
            IsSignificant = true;
        }
        else if (IsSignificant)
        {
            Result += '0';
        }
    }

    return Result;
}

template<typename T, int Length>
inline T BigIntsBase<T, Length>::operator+(uint64_t Arg)
{
    return this->Add(Arg);
}

template<typename T, int Length>
inline T BigIntsBase<T, Length>::operator+(std::initializer_list<BigIntsBase<T, Length>> Args)
{
    return this->Add(Args);
}

template<typename T, int Length>
inline T BigIntsBase<T, Length>::operator-(uint64_t Arg)
{
    return this->Subtract(Arg);
}

template<typename T, int Length>
inline T BigIntsBase<T, Length>::operator-(std::initializer_list<BigIntsBase<T, Length>> Args)
{
    return this->Subtract(Args);
}

template<typename T, int Length>
inline T BigIntsBase<T, Length>::operator*(uint64_t Arg)
{
    return this->Multiply(Arg);
}

template<typename T, int Length>
inline T BigIntsBase<T, Length>::operator*(std::initializer_list<BigIntsBase<T, Length>> Args)
{
    return this->Multiply(Args);
}

template<typename T, int Length>
inline T BigIntsBase<T, Length>::operator/(uint64_t Arg)
{
    return this->Divide(Arg);
}

template<typename T, int Length>
inline T BigIntsBase<T, Length>::operator/(std::initializer_list<BigIntsBase<T, Length>> Args)
{
    return this->Divide(Args);
}

template<typename T, int Length>
inline T BigIntsBase<T, Length>::operator%(uint64_t Arg)
{
    return this->Mod(Arg);
}

template<typename T, int Length>
inline T BigIntsBase<T, Length>::operator%(std::initializer_list<BigIntsBase<T, Length>> Args)
{
    return this->Mod(Args);
}

template<typename T, int Length>
inline T BigIntsBase<T, Length>::operator++()
{
    return this->Add(1);
}

template<typename T, int Length>
inline T BigIntsBase<T, Length>::operator--()
{
    return this->Subtract(1);
}

template<typename T, int Length>
inline void BigIntsBase<T, Length>::operator+=(uint64_t Arg)
{
    this->Data = Internal_Add(this->Data, std::bitset<Length>(Arg));
}

template<typename T, int Length>
inline void BigIntsBase<T, Length>::operator+=(std::initializer_list<BigIntsBase<T, Length>> Args)
{
    for (BigIntsBase<T, Length> i : Args)
    {
        this->Data = Internal_Add(this->Data, i.Data);
    }
}

template<typename T, int Length>
inline void BigIntsBase<T, Length>::operator-=(uint64_t Arg)
{
    this->Data = Internal_Subtract(this->Data, std::bitset<Length>(Arg));
}

template<typename T, int Length>
inline void BigIntsBase<T, Length>::operator-=(std::initializer_list<BigIntsBase<T, Length>> Args)
{
    for (BigIntsBase<T, Length> i : Args)
    {
        this->Data = Internal_Subtract(this->Data, i.Data);
    }
}

template<typename T, int Length>
inline void BigIntsBase<T, Length>::operator*=(uint64_t Arg)
{
    this->Data = Internal_Multiply(this->Data, std::bitset<Length>(Arg));
}

template<typename T, int Length>
inline void BigIntsBase<T, Length>::operator*=(std::initializer_list<BigIntsBase<T, Length>> Args)
{
    for (BigIntsBase<T, Length> i : Args)
    {
        this->Data = Internal_Multiply(this->Data, i.Data);
    }
}

template<typename T, int Length>
inline void BigIntsBase<T, Length>::operator/=(uint64_t Arg)
{
    this->Data = Internal_Divide(this->Data, std::bitset<Length>(Arg));
}

template<typename T, int Length>
inline void BigIntsBase<T, Length>::operator/=(std::initializer_list<BigIntsBase<T, Length>> Args)
{
    for (BigIntsBase<T, Length> i : Args)
    {
        this->Data = Internal_Divide(this->Data, i.Data);
    }
}

template<typename T, int Length>
inline void BigIntsBase<T, Length>::operator%=(uint64_t Arg)
{
    this->Data = Internal_Mod(this->Data, std::bitset<Length>(Arg));
}

template<typename T, int Length>
inline void BigIntsBase<T, Length>::operator%=(std::initializer_list<BigIntsBase<T, Length>> Args)
{
    for (BigIntsBase<T, Length> i : Args)
    {
        this->Data = Internal_Mod(this->Data, i.Data);
    }
}

template<typename T, int Length>
inline bool BigIntsBase<T, Length>::operator==(BigIntsBase<T, Length> Arg)
{
    return this->Data == Arg.Data;
}

template<typename T, int Length>
inline bool BigIntsBase<T, Length>::operator!=(BigIntsBase<T, Length> Arg)
{
    return this->Data != Arg.Data;
}

template<typename T, int Length>
inline bool BigIntsBase<T, Length>::operator<(BigIntsBase<T, Length> Arg)
{
    return FirstIsSmaller(this->Data, Arg.Data)
}

template<typename T, int Length>
inline bool BigIntsBase<T, Length>::operator>(BigIntsBase<T, Length> Arg)
{
    return FirstIsSmaller(Arg.Data, this->Data);
}

template<typename T, int Length>
inline bool BigIntsBase<T, Length>::operator<=(BigIntsBase<T, Length> Arg)
{
    return !FirstIsSmaller(Arg.Data, this->Data);
}

template<typename T, int Length>
inline bool BigIntsBase<T, Length>::operator>=(BigIntsBase<T, Length> Arg)
{
    return !FirstIsSmaller(this->Data, Arg.Data);
}

template<typename T, int Length>
inline BigIntsBase<T, Length>::BigIntsBase()
{
	this->Data = std::bitset<Length>(0);
}

template<typename T, int Length>
inline BigIntsBase<T, Length>::BigIntsBase(std::string Arg)
{
    this->Data = StringToBitset(Arg);
}

template<typename T, int Length>
inline BigIntsBase<T, Length>::BigIntsBase(std::bitset<Length> Arg)
{
    this->Data = Arg;
}

template<typename T, int Length>
inline BigIntsBase<T, Length>::BigIntsBase(int Arg)
{
    this->Data = std::bitset<Length>(Arg);
}

template<typename T, int Length>
inline BigIntsBase<T, Length>::BigIntsBase(uint64_t Arg)
{
    this->Data = std::bitset<Length>(Arg);
}

template<typename T, int Length>
inline T BigIntsBase<T, Length>::Add(uint64_t Arg)
{
    T Result;
    Result.Data = Internal_Add(this->Data, std::bitset<Length>(Arg));
    return Result;
}

template<typename T, int Length>
inline T BigIntsBase<T, Length>::Add(std::initializer_list<BigIntsBase<T, Length>> Args)
{
    T Result;
    Result.Data = this->Data;
    for (BigIntsBase<T, Length> i : Args)
    {
        Result.Data = Internal_Add(Result.Data, i.Data);
    }
    return Result;
}

template<typename T, int Length>
inline T BigIntsBase<T, Length>::Subtract(uint64_t Arg)
{
    T Result;
    Result.Data = Internal_Subtract(this->Data, std::bitset<Length>(Arg));
    return Result;
}

template<typename T, int Length>
inline T BigIntsBase<T, Length>::Subtract(std::initializer_list<BigIntsBase<T, Length>> Args)
{
    T Result;
    Result.Data = this->Data;
    for (BigIntsBase<T, Length> i : Args)
    {
        Result.Data = Internal_Subtract(Result.Data, i.Data);
    }
    return Result;
}

template<typename T, int Length>
inline T BigIntsBase<T, Length>::Multiply(uint64_t Arg)
{
    T Result;
    Result.Data = Internal_Multiply(this->Data, std::bitset<Length>(Arg));
    return Result;
}

template<typename T, int Length>
inline T BigIntsBase<T, Length>::Multiply(std::initializer_list<BigIntsBase<T, Length>> Args)
{
    T Result;
    Result.Data = this->Data;
    for (BigIntsBase<T, Length> i : Args)
    {
        Result.Data = Internal_Multiply(Result.Data, i.Data);
    }
    return Result;
}

template<typename T, int Length>
inline T BigIntsBase<T, Length>::Divide(uint64_t Arg)
{
    T Result;
    Result.Data = Internal_Divide(this->Data, std::bitset<Length>(Arg));
    return Result;
}

template<typename T, int Length>
inline T BigIntsBase<T, Length>::Divide(std::initializer_list<BigIntsBase<T, Length>> Args)
{
    T Result;
    Result.Data = this->Data;
    for (BigIntsBase<T, Length> i : Args)
    {
        Result.Data = Internal_Divide(Result.Data, i.Data);
    }
    return Result;
}

template<typename T, int Length>
inline T BigIntsBase<T, Length>::Pow(uint64_t Arg)
{
    T Result;
    Result.Data = Internal_Pow(this->Data, std::bitset<Length>(Arg));
    return Result;
}

template<typename T, int Length>
inline T BigIntsBase<T, Length>::Pow(std::initializer_list<BigIntsBase<T, Length>> Args)
{
    T Result;
    Result.Data = this->Data;
    for (BigIntsBase<T, Length> i : Args)
    {
        Result.Data = Internal_Pow(Result.Data, i.Data);
    }
    return Result;
}

template<typename T, int Length>
inline T BigIntsBase<T, Length>::Mod(uint64_t Arg)
{
    T Result;
    Result.Data = Internal_Mod(this->Data, std::bitset<Length>(Arg));
    return Result;
}

template<typename T, int Length>
inline T BigIntsBase<T, Length>::Mod(std::initializer_list<BigIntsBase<T, Length>> Args)
{
    T Result;
    Result.Data = this->Data;
    for (BigIntsBase<T, Length> i : Args)
    {
        Result.Data = Internal_Mod(Result.Data, i.Data);
    }
    return Result;
}

template<typename T, int Length>
inline T BigIntsBase<T, Length>::Log2()
{
    T Result;
    Result.Data = Internal_Log(Data, std::bitset<Length>(2));
    return Result;
}

template<typename T, int Length>
inline T BigIntsBase<T, Length>::Log10()
{
    T Result;
    Result.Data = Internal_Log(Data, std::bitset<Length>(10));
    return Result;
}

template<typename T, int Length>
inline T BigIntsBase<T, Length>::Log(uint64_t Arg)
{
    T Result;
    Result.Data = Internal_Log(Data, std::bitset<Length>(Arg));
    return Result;
}

template<typename T, int Length>
inline T BigIntsBase<T, Length>::Log(BigIntsBase<T, Length> Arg)
{
    T Result;
    Result.Data = Internal_Log(Data, Arg.Data);
    return Result;
}

template<typename T, int Length>
inline T BigIntsBase<T, Length>::Sqrt()
{
    return Internal_Sqrt(this->Data);
}

template<typename T, int Length>
inline T BigIntsBase<T, Length>::Factorial()
{
    return Internal_Factorial(this->Data);
}
