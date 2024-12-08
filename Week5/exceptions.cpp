#include <iostream>
#include <stdio.h>
#include <exception>
#include <sstream>

int third(int num)
{
    if (num == 2)
    {
        return -1;
    }
    //return fourth()
    return 0;
}

int second(int num)
{
    num += 2;
    const int ret = third(num);
    if (ret < 0)
    {
        return ret;
    }
    return num;
}

int first(int num)
{
    num += 1;
    const int ret = second(num);
    if (ret < 0)
    {
        return 0;
    }
    return 1;
}

int int_from_str(const std::string& str, int& ret)
{
    // if str -> valid ->return int;
    // if str -> not valid 
    ret = -1;
    return 5;
}

void thrower()
{
    throw std::invalid_argument("haha");
}


class Thrower
{
public:
    Thrower()
    {
        std::cout << "thrower" << std::endl;
    }

    ~Thrower() noexcept
    {
        std::cout << "~thrower" << std::endl;
    }
};

class Fraction
{
public:
    Fraction(const int num, const int den)
    {
        if (den == 0)
        {
            // это ошибка, дробь невалидная, надо как-то сообщить
            throw std::invalid_argument("_denominater can't be 0");
        }
    }

    ~Fraction()
    {
        std::cout << "~Fraction" << std::endl;
    }

    void Get() const noexcept
    {
        // std::terminate() -> std::abort()
    }

    Fraction& operator/=(const Fraction& other)
    {
        // делим одну дробь из другой
        // получить 0
        return *this;
    }
private:
    int _numerator; // числитель
    int _denominater; // знаменатель
    Thrower _thrower;
};

class exception
{
public:
    exception() noexcept = default;
    // some standatrs operators
    virtual ~exception() noexcept = default;

    virtual const char* what() const noexcept;
};

int main()
{
    //const int ret = printf("Hello World!\n");
    //if (ret < 0)
    //{
    //    // some code
    //    return 1;
    //}

    {
        try
        {
            //Fraction fraction(0, 0);
            //fraction.Get();
        }
        catch(const std::invalid_argument& e)
        {
            std::cerr << e.what() << '\n';
        }
        catch(const std::runtime_error& e)
        {
            std::cerr << e.what() << '\n';
        }
        catch(const std::exception&)
        {
            std::cout << "other" << std::endl;
        }
    }
    {
        std::string str {"Hello, wordl!"};
        std::string date {"29:01:2001"};
        std::stringstream stream(date);
        if (stream)
        {
            stream << "abc";
            stream << "bcd";
        }
    }
    return 0;
}
