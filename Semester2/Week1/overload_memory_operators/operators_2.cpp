#include <iostream>

class Test
{
public:
    void* operator new(size_t size)
    {
        std::cout << "Create new Test object" << std::endl;
        return ::operator new(size);
    }

    void operator delete(void* p)
    {
        std::cout << "Delete single Test" << std::endl;
        ::operator delete(p);
    }

    void* operator new[](size_t size)
    {
        std::cout << "Create Test objects, size: " << size << std::endl;
        return ::operator new[](size);
    }

    void operator delete[](void* p)
    {
        std::cout << "Delete Test objects" << std::endl;
        ::operator delete[](p);
    }
};


int main()
{
    Test* c = new Test();
    delete c;
    Test* ptr = new Test[5];
    delete [] ptr;
    return 0;
}
