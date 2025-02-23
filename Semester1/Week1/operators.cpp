#include <iostream>

// Operators
// + - * / % << >>
// Only with integral types | & ^ ~
// == < > <= >=
// <=> — spaceship operator (Since C++20)
// && || (Lazy)
// = += -= /= *= %= 
// ++(prefix), ++(postfix), --(prefix), --(postfix)

int main()
{
    int foo = 5;
    std::cout << foo++ << std::endl;
    std::cout << foo << std::endl;
    std::cout << ++foo << std::endl;
    int div = 5 / 2;
    int mod = 5 % 2;
    std::cout << "div: " << div << " mod: " << mod << std::endl;
}