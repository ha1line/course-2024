#include <iostream>
#include <memory>

int main()
{
    {
        int* ptr = new int(5);
        delete ptr;
    }
    {
        int* ptr = new int(5);
        delete ptr; // Первый вызов delete
    }
    {
        int* arr = new int[10];
        delete []arr; // Ошибка: должен быть вызван delete[]
    }
    {
        int* ptr = new int(5);
        delete ptr;
    }
    {
        auto ptr = std::make_unique<int>(5);
        throw std::runtime_error("unexpected error");
    }
}
