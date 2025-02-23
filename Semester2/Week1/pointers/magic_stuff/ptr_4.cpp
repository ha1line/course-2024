#include <iostream>

int main()
{
    // Объявляем размеры двумерного массива
    const int numRows = 3;
    const int numCols = 4;

    // Создаем двумерный массив, используя "сырые" указатели
    int** matrix = new int*[numRows]; // Создаем массив указателей на строки
    for (int i = 0; i < numRows; ++i)
    {
        matrix[i] = new int[numCols]; // Для каждой строки создаем массив целых чисел
    }

    int value = 1;
    for (int i = 0; i < numRows; ++i)
    {
        for (int j = 0; j < numCols; ++j)
        {
            matrix[i][j] = value++; // Присваиваем последовательные значения
        }
    }

    // Выводим элементы массива на экран
    std::cout << "Matrix elements:" << std::endl;
    for (int i = 0; i < numRows; ++i)
    {
        for (int j = 0; j < numCols; ++j)
        {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl; // Переход на новую строку после каждой строки
    }

    // Освобождаем выделенную память
    for (int i = 0; i < numRows; ++i)
    {
        delete[] matrix[i]; // Удаляем каждую строку
    }
    delete[] matrix; // Удаляем массив указателей на строки
    matrix = nullptr; // Обнуляем указатель, чтобы избежать висячих указателей

    return 0;
}
