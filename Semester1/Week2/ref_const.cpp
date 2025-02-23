#include <iostream>
#include <string>
#include <vector>

void foo(std::string str)
{
    str.append(", ABC");
    std::cout << &str << " " << str << std::endl;
}

// UB
// std::string&
// const std::string&
// No effect
// const std::string
std::string bar()
{
    std::string str = "bar";
    return str;
}

void fooRef(const std::string& str)
{
    std::cout << &str << std::endl;
    std::cout << str << std::endl;
}

// 1. Я хочу скопировать объект и поменять его
// void foo(std::string)

// 2. Я хочу скопировать объект, но не менять его
// void foo(const std::string)

// 3. Я не хочу копировать, но хочу поменять
// void foo(std::string&)

// 4. Я не хочу копировать, не хочу менять
// void foo(const std::string&)

// Все Simple types (int, double, float) дешевле копировать, чем передавать по ссылке

int main()
{
    {
        std::string str = "abc";
        foo(str);
        std::cout << &str << " " << str << std::endl;

        // floating ref, UB
        std::string barRes = bar();
        std::cout << barRes << std::endl;
        std::cout << std::endl;
    }
    {
        std::string s1 = "Hello, World!";
        std::string s2 = s1;
        s1.clear();
        std::cout << s1.empty() << " " << s2 << std::endl; //  s1 = empty
        std::cout << &s1 << " " << &s2 << std::endl;

        int x = 42;
        int& ref = x;
        ++x;
        std::cout << ref << std::endl;

        ++ref;
        std::cout << x << std::endl;

        int z = 42; // z = 42
        int y = 13; // y = 13
        int& ref1 = z; // OK, ref1 = 42, same as z
        ref1 = y; // ref1 same as y
        std::cout << z << " " << y << " " << ref1 << std::endl;
    }
    // const
    {
        const int c1 = 42; // известно на этапе компиляции
        // const int c2;
        int x;
        std::cin >> x;
        const int c2 = 5 * x;
        std::cout << x << " " << c2 << std::endl;
        // c2 = 0; CE
    }
    {
        const std::vector<int> v = {1, 2, 3};
        std::cout << v.size() << std::endl;
        // v.clear(); // CE
        // v[0] = 2; // CE
        std::cout << v[0] << std::endl;
    }
    // const ref
    {
        int x = 42;
        int& ref = x; // новое имя для x
        const int& cref = x; // константное новое имя для x
        ++x;
        ++ref;
        std::cout << ref << " " << cref << std::endl;
    }
    // const ref
    {
        std::string str = "sahjhjadsghjadsghjasdghjdjgasjhgdghashjdjghashjdhgjashgjjdhgasjhdgasjhdghsahjhjadsghjadsghjasdghjdjgasjhgdghashjdjghashjdhgjashgjjdhgasjhdgasjhdghsahjhjadsghjadsghjasdghjdjgasjhgdghashjdjghashjdhgjashgjjdhgasjhdgasjhdghsahjhjadsghjadsghjasdghjdjgasjhgdghashjdjghashjdhgjashgjjdhgasjhdgasjhdghsahjhjadsghjadsghjasdghjdjgasjhgdghashjdjghashjdhgjashgjjdhgasjhdgasjhdghsahjhjadsghjadsghjasdghjdjgasjhgdghashjdjghashjdhgjashgjjdhgasjhdgasjhdghsahjhjadsghjadsghjasdghjdjgasjhgdghashjdjghashjdhgjashgjjdhgasjhdgasjhdghsahjhjadsghjadsghjasdghjdjgasjhgdghashjdjghashjdhgjashgjjdhgasjhdgasjhdghsahjhjadsghjadsghjasdghjdjgasjhgdghashjdjghashjdhgjashgjjdhgasjhdgasjhdghsahjhjadsghjadsghjasdghjdjgasjhgdghashjdjghashjdhgjashgjjdhgasjhdgasjhdghsahjhjadsghjadsghjasdghjdjgasjhgdghashjdjghashjdhgjashgjjdhgasjhdgasjhdghsahjhjadsghjadsghjasdghjdjgasjhgdghashjdjghashjdhgjashgjjdhgasjhdgasjhdgh";
        fooRef(str);
        std::cout << &str << std::endl;
    }
    // ref in for
    {
        const size_t sz1 = 10'000;
        const size_t sz2 = 1000;
        std::vector<std::string> v(sz1);
        // в каждом элементе вектора будет строка размером 1000
        for (size_t i = 0; i < v.size(); ++i)
        {
            v[i].resize(sz2);
        }
        size_t sum = 0;
        // C++11, 4 случая также работают см. пример с функциями
        for (const std::string& s : v)
        {
            sum += s.size();
        }
        std::cout << sum << std::endl;
    }
    {
        std::vector<std::string> v {"one", "two", "three"};
        std::string& str = v[0]; // OK std::string exist
        std::cout << str << std::endl;
        v.clear();
        std::cout << str << std::endl; // UB, std::string doesn't exist
    }
}
