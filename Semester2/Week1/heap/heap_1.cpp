#include <iostream>

int* alloc_single()
{
    int* ptr = new int(5);
    return ptr;
}

int* alloc_array()
{
    int* ptr = new int[5];
    ptr[0] = 3;
    return ptr;
}

int main()
{
    // Single allocation
    auto ptr = alloc_single();
    std::cout << "Ptr: " << *ptr << std::endl;
    delete ptr;

    // Array allocation
    auto arr = alloc_array();
    std::cout << "Ptr: " << arr[0] << std::endl;
    delete [] arr;
}
