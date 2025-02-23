#include <iostream>

int main()
{
    int value = 7;

    int* ptr = &value;
    std::cout << *ptr << std::endl; // разыменовываем указатель, чтобы получить значение типа int

    int **ptrptr = &ptr;
    std::cout << **ptrptr << std::endl;

    return 0;
}
