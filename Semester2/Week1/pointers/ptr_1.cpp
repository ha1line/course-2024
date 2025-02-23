#include <iostream>

int main()
{
    int* p = new int(10);
    int* p2 = p;

    if (p != nullptr)
    {
      std::cout << p << " " << *p << std::endl;
    }

    delete p;
    p = nullptr;
    p2 = nullptr;

    if (p != nullptr)
    {
        std::cout << p << " " << *p << std::endl;
    }

    // oops
    if (p2 != nullptr)
    {
        std::cout << p2 << " " << *p2 << std::endl;
    }
}
