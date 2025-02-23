#include "lib_with_side_effect.h"
#include <stdexcept>

std::string get_username(int userId)
{
    if (userId < 0)
    {
        throw std::invalid_argument("Incorrect User ID");
    }
    return "John";
}
