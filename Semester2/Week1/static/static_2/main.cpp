#include <iostream>

int main ()
{
    int number = 1;
    int* abc = new int(5);
    std::cout << "address: " << abc << std::endl;
    std::cout << "value: " << *abc << std::endl;
    delete abc;
    return 0;
}
