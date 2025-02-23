#include <iostream>

int main()
{
    int value = 10;
    void* ptr = &value;
    // Ошибка!
    std::cout << *ptr << std::endl;
    // Приведение к int*
    int* intPtr = static_cast<int*>(ptr);
    std::cout << *intPtr << std::endl; // Теперь это работает
    return 0;
}
