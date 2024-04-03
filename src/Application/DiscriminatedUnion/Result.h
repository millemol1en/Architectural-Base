#pragma once
#ifndef RESULT_H
#define RESULT_H

template<typename T>
struct Result
{
	bool has_value;
	T value;

    Result(bool has_value, T value) : has_value(has_value), value(value) {}

    static Result<T> Success(const T& value)
    {
        return Result<T>(true, value);
    }

    static Result<T> Failure()
    {
        return Result<T>(false, T());
    }
};

#endif 

/*
    Implement a try-catch instead to incorporate the method
    Right now, this method can't be used for methods which are overriden. 

*/




/*
#pragma once
#ifndef RESULT_H
#define RESULT_H

#include <functional>

template<typename T>
struct Result
{
    bool has_value;
    T value;

    Result(bool has_value, T value) : has_value(has_value), value(value) {}

    static Result<T> Try(std::function<T()> func)
    {
        try
        {
            return Success(func());
        }
        catch (...)
        {
            return Failure();
        }
    }

    static Result<T> Success(const T& value)
    {
        return Result<T>(true, value);
    }

    static Result<T> Failure()
    {
        return Result<T>(false, T());
    }
};

#endif

*/