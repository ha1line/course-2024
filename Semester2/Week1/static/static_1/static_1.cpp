#include <iostream>
#include "user.h"

static int number = 1;

int main()
{
    UserId& id = UserId::instance();
    std::cout << "Start" << std::endl;
    std::cout << "End" << std::endl;
    return 0;
}
