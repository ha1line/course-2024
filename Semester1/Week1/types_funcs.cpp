#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <array>
#include <map>

// Объявление — Declaration
// Определение — Definition

// функция 
// возращаемое значение имя (список аргументов)
// Объявление функции
int foo(double d);
// Определение функции
int foo(double d)
{
    return 5.6;
}

// Фундоментальные типы (Integral types)
// Целочисленные типы: int, long, long long, char
// size_t — беззнаковый
// unsigned
//
// Числа с плавающей точкой: float, double
// целочисленная часть + мантиса

// Булевый тип: bool

// Идентификаторы все типы + 
// Литералы: 5, true, 'a', "str", 0.7, 0.5f

// Неявные касты

void print_vector(std::vector<int> vec)
{
    for (int v : vec)
    {
        std::cout << v << ' ';
    }
    std::cout << std::endl;
}

int main()
{
    // Integral types
    // от -2^32 до 2^32 - 1
    int x = 5;
    std::cout << sizeof(x) << std::endl;
    long l = 6;
    std::cout << sizeof(l) << std::endl;
    long long ll = 10;
    std::cout << sizeof(ll) << std::endl;
    // 0 255
    char c = 'A';
    std::cout << sizeof(c) << std::endl;

    // 2^64 - 1
    unsigned int ux = -1;
    std::cout << "unsigned: " << ux << std::endl;

    size_t st = 5;
    std::cout << sizeof(st) << std::endl;

    // Floating types
    float f = 4.0;
    std::cout << sizeof(f) << std::endl;
    double d = 4.0;
    std::cout << sizeof(d) << std::endl;

    bool b = false;
    std::cout << sizeof(b) << "bool:" << b << std::endl;

    // double -> long
    long l1 = 1.67;
    std::cout << l1 << std::endl;
    // long -> double
    double d1 = 2237273;
    // int -> bool
    bool b1 = 12;

    std::cout << foo(4) << std::endl;

    // Compound types (сложные типы)
    // "abc\0"
    std::string str = "abc";
    // std::string
    std::cout << str << std::endl;
    // char
    std::cout << str[0] << std::endl;

    std::string strSecond = "bcd";
    // strSecond = std::string(strSecond + str)
    strSecond = strSecond + str; // extra copy
    strSecond += str; // non extra copy
    std::cout << strSecond << std::endl;

    strSecond.push_back('H');
    std::cout << strSecond << std::endl;
    strSecond.pop_back();
    std::cout << strSecond << std::endl;

    strSecond.insert(0, "Hello, World!");
    std::cout << strSecond << std::endl;
    std::cout << strSecond.erase(0, 13) << std::endl;

    std::cout << strSecond.front() << " " << strSecond.back() << std::endl;
    std::cout << strSecond.size() << std::endl;

    // std::vector
    std::vector<int> vec {1, 2, 3}; // Since C++11
    vec.resize(4);
    std::cout << vec.size() << std::endl;
    // unsafe get, safe get
    std::cout << vec[2] << vec.at(2) << std::endl;

    // Old school for
    for (size_t i = 0; i < vec.size(); ++i)
    {
        std::cout << vec[i] << ' ';
    }
    std::cout << std::endl;

    // Since C++11
    // v — element
    for (int v : vec)
    {
        std::cout << v << ' ';
    }
    std::cout << std::endl;

    vec.push_back(5);
    std::cout << vec.front() << " " << vec.back() << std::endl;
    vec.pop_back();
    std::cout << vec.front() << " " << vec.back() << std::endl;

    vec.clear(); // Delete all elements
    std::cout << "vec" << vec.size() << std::endl;
    print_vector(vec);
    std::vector<int> vecSecond = vec;
    vecSecond.push_back(0);
    print_vector(vecSecond);

    // C-style array
    int mass[10];
    int mass2[10];
    std::cout << mass[-1] << std::endl; // UB

    // std::array
    std::array<int, 5> arr {1, 2, 3, 4, 5};
    std::cout << arr[0] << arr.at(4) << std::endl;
    std::cout << arr.front() << " " << arr.back() << std::endl;
    std::cout << "array: ";
    size_t idx = 0;
    while (idx != arr.size())
    {
        std::cout << arr[idx] << ' ';
        ++idx;
    }
    std::cout << std::endl;
    // break, continue
    /*
    do
    {
    } while ()
    */
    // std::map
    std::map<size_t, std::string> dict {{1, "Abc"}, {2, "Bcd"}};
    // Since C++ 14 [key, value]
    for (auto [key, value] : dict)
    {
        std::cout << key << " " << value << " ";
    }

    if (int var = 5; var == 5)
    {
        std::cout << var;
    }
}
