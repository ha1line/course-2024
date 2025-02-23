#include <iostream>
#include "lib_with_side_effect.h"

int main()
{
    int* id = new int(5);
    std::cout << *id << std::endl;
    std::cout << get_username(*id) << std::endl;
    *id = -1;
    // throw exception
    std::cout << get_username(*id) << std::endl;
    delete id;
}
