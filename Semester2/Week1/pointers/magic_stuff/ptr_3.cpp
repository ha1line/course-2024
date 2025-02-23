#include <iostream>
#include <functional>

// Функция, которую мы будем передавать в другую функцию
void sayHello()
{
    std::cout << "Привет, мир!" << std::endl;
}

void sayGoodbye()
{
    std::cout << "Пока, мир!" << std::endl;
}

// Функция, которая принимает указатель на функцию и вызывает её
void executeFunction(void (*funcPtr)())
{
    std::cout << "Собираемся выполнить функцию..." << std::endl;
    funcPtr(); // Вызываем функцию, на которую указывает funcPtr
    std::cout << "Функция выполнена." << std::endl;
}

int main()
{
    // Объявляем указатель на функцию, которая не принимает аргументов и не возвращает значения
    void (*myFuncPtr)() = sayHello;

    // Вызываем функцию executeFunction, передавая ей указатель на функцию sayHello
    executeFunction(myFuncPtr);

    // Присваиваем указателю адрес функции sayGoodbye
    myFuncPtr = sayGoodbye;

    // Вызываем функцию executeFunction, передавая ей указатель на функцию sayGoodbye
    executeFunction(myFuncPtr);

    return 0;
}
