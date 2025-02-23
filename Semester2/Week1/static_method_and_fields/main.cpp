#include <iostream>

class Person
{
public:
    Person(const std::string& name, size_t age) : m_name(name)
    {
        ++count;
        // если значение не больше максимального
        if (age < maxAge)
        {
            m_age = age;
        }
    }

    ~Person()
    {
        if (count > 0)
        {
            --count;
        }
    }

    // статическая функция
    static void print_count()
    {
        std::cout << count << " objects exists" << std::endl;
    }

    static const size_t maxAge = 120;  // статическая константа
private:
    size_t m_age = 0;
    const std::string m_name;
    static size_t count;              // статическая приватная переменная
};

size_t Person::count = 0;

int main()
{
    {
        Person tom{"Tom", 38};
        Person bob{"Bob", 42};
        std::cout << "Before destroy: " << std::endl;
        // обращаемся к статическим компонентам класса
        Person::print_count();
    }
    std::cout << "After destroy: " << std::endl;
    Person::print_count();
    std::cout << "Max age: " << Person::maxAge << std::endl;
}
