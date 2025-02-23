#include <iostream>
#include <vector>

void* operator new(std::size_t size)
{
    if (0 == size)
    {
        ++size;
    }
    std::cout << "Allocated " << size << " bytes" << std::endl;
    void* ptr = std::malloc(size);
    if (ptr)
    {
        return ptr;
    }
    throw std::bad_alloc{};
}

void* operator new[](std::size_t size)
{
    if (0 == size)
    {
        ++size;
    }
    std::cout << "Allocated " << size << " bytes" << std::endl;
    void* ptr = std::malloc(size);
    if (ptr)
    {
        return ptr;
    }
    throw std::bad_alloc{};
}

void operator delete(void* ptr)
{
    std::cout << "Destroy allocated memory" << std::endl;
    free(ptr);
}

void operator delete[](void* ptr)
{
    std::cout << "Destroy allocated memory" << std::endl;
    free(ptr);
}

int main()
{
    std::cout << "Start" << std::endl;
    std::vector<std::string> vec = {"one", "two", "three", "four"};
    std::cout << "End" << std::endl;
    return 0;
}
