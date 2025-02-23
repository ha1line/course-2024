#include <iostream>

int main()
{
    int* p = new int(10);
    std::cout << p << " " << *p << std::endl;

    bool error = true;

    if (error)
    {
        delete p;
        p = nullptr;
    }

    // ...
    delete p;
    p = nullptr;
}
