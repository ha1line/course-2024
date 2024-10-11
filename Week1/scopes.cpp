#include <iostream>

double global = 5.932;

namespace local
{
    int localVar = 10;
    double global = 6.2;
}

int main()
{
    // Let's create a scope
    {
        using namespace local;
        int foo = 5;
        std::cout << foo << std::endl;
        std::cout << localVar << std::endl;
        std::cout << ::global << std::endl;
    }
    {
        using local::localVar;
        using std::cout;
        cout << localVar << std::endl;
    }
}
