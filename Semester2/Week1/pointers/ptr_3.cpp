#include <iostream>

int main()
{
    int numbers[5] = {1, 2, 3, 4, 5};
    int* p = numbers;

    std::cout << "Forward:" << std::endl;
    for (size_t i = 0; i < 5; ++i)
    {
        std::cout << *p++ << std::endl;
    }
    std::cout << "Reverse:" << std::endl;
    for (size_t i = 0; i < 5; ++i)
    {
        std::cout << *--p << std::endl;
    }

    std::cout << "Direct access:" << std::endl;
    std::cout << *(p + 3) << std::endl;
}
