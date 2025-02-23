#include <iostream>

int main()
{
    size_t size = -1;
    int* ptr = new int[size];
    std::cout << "Ptr: " << *ptr << std::endl;
    delete []ptr;
}
