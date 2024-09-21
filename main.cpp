#include <iostream>
#include <string>

// возвращаемое значение имя (аргументы)
void foo(int f)
{
    std::cout << "f" << f << '\n';
}

int main()
{
    std::cout << "Hello, World!";
    foo(5);

    // тип переменной, = значение
    int x;
    int y = 5;
    // console output
    std::cout << x << std::endl;
    return 0;
}
