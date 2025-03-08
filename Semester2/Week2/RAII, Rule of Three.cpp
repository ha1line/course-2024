#include <iostream>
#include <vector>

// Rule of Three
    //Правило трех Конструктор сделали сами -> извольте сделать все сами и остальное.

/// @brief Resource Acquisition Is Initialization
struct NotSmarPointer
{
    //Констурктор
    NotSmarPointer(const int& incoming)
    : ptr(new int(incoming))
    {
    }
    //Конструктор Копирования
    NotSmarPointer(const NotSmarPointer& other) :
    ptr(new int(*other.ptr))
    {
    }
    //Оператор присваивания
    NotSmarPointer& operator= (const NotSmarPointer& other)
    {
        // * - разыменовать
        // int* - указатель
        // & - взять адрес
        // int& - ссылка
        if (this != &other)
        {
            // Идиома copy && swap
            NotSmarPointer copy(other);
            std::swap(ptr, copy.ptr);
        }
        return *this;
    }
    ~NotSmarPointer()
    {
        delete ptr;
        std::cout<<"EEEE we gonna clean our memory"<<std::endl;
    }
    int* ptr = nullptr;
};


int main()
{
    NotSmarPointer n(228);
    std::cout<<*n.ptr<<std::endl;
    NotSmarPointer p(337);
    std::cout<<sizeof(p)<<std::endl;
    p = n;
    std::cout<<*p.ptr<<std::endl;
}