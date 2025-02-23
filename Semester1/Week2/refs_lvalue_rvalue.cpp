#include <iostream>
#include <vector>

int bar()
{
    int bar = 5;
    return bar;
}

namespace global
{
    double pi = 3.14;
}

// ref = lvalue
double& get_pi()
{
    return global::pi;
}

// UB
// inside print_size str = lvalue
// 2 раза жизнь продлеваться не будет
void print_size(const std::string& str)
{
    std::cout << str.size() << std::endl;
}

// inside print str = lvalue
void print(const std::string& str)
{
    std::cout << str << std::endl;
    print_size(str);
}

int main()
{
    std::cout << bar() << std::endl;
    //foo() = 4;

    {
        // c1 - lvalue, 5 - rvalue (литерал)
        int c1 = 5;
        // c2 - lvalue
        int c2;
        // 10 - rvalue
        c2 = 10;
        // operator= (lvalue) = lvalue/rvalue
        // rvalue = lvalue
        //10 = c2;
        // rvalue = lvalue
        //(10 + c1) = c2;
        // rvalue = lvalue
        // foo() = 5;
        // c3 = (c1 + c2) - copy rvalue
        const int c3 = c1 + c2;
    }

    {
        get_pi() = 10;
        std::cout << global::pi << std::endl;
    }

    {
        std::vector<int> vec {1, 2, 3};
        // lvalue ref
        vec[0] = 5;
    }

    {
        const int& cref = 5;
        const int& cref1 = cref;
        // std::string("abc") - rvalue
        print(std::string("abc"));
    }


}
