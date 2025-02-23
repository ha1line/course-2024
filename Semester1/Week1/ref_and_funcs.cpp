#include <iostream>
#include <string>

namespace function
{
    // Declaration
    void foo();

    // Definition
    void foo()
    {
        std::cout << "foo" << std::endl;
    }

    // Definition
    // Overloading
    void foo(int i)
    {
        std::cout << "int" << i << std::endl;
    }

    // Definition
    // Overloading
    void foo(char i)
    {
        std::cout << "char" << i << std::endl;
    }

    // Definition
    // Overloading
    void foo(float f)
    {
        std::cout << "float" << f << std::endl;
    }

    // Definition
    // Overloading
    void foo(double d)
    {
        std::cout << "double" << d << std::endl;
    }

    void foo(std::string s)
    {
        std::cout << "string" << s << std::endl;
    }

    // Def argument
    void foo(bool b, double d = 5.0)
    {
        std::cout << "bool" << b << "double" << d << std::endl;
    }
}

// Copy
void printStr(std::string str)
{
    str.push_back('A');
    std::cout << "printStr " << str << std::endl;
}

// std::string &str;
// std::string & str;
// std::string& str; type — std::string&
void printStrRef(std::string& str)
{
    str.push_back('B');
}

int main()
{
    {
        using namespace function;
        foo();
        foo(5);
        foo('A');
        foo(2.5);
        // const char*
        foo("const char*");
        foo(true);
        foo(5, 6.3);
    }
    {
        std::string str = "ABC";
        std::cout << str << std::endl;
        printStr(str);
        std::cout << str << std::endl;
        printStrRef(str);
        std::cout << str << std::endl;
    }
}