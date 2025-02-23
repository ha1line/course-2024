#include <iostream>

int main()
{
    const int size = 10;
    std::cout << "Start" << std::endl;
    int* p = new int(size);
    if (p)
    {
        std::cout << "===============" << std::endl;
        std::cout << "allocated " << size << " bytes at addr: " << p << std::endl;
        delete p;
    }
    return 0;
}
