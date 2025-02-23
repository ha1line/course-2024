#include <iostream>

int main()
{
    int* ptr = new int(5);
    int* arr = new int[5];
    std::cout << "Single int: " << *ptr << std::endl;
    std::cout << "Array : " << *arr << std::endl;
    delete ptr;
    delete []arr;
}
