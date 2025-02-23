#include <iostream>

class Person
{
public:
    Person(const std::string& name) : m_name(name)
    {
    }

    void SayHello() const
    {
        std::cout << "Hello, " << m_name << "!" << std::endl;
    }
private:
    const std::string m_name;
};

void send()
{
    // send *ptr
}

void accept(void* data)
{
    // reinterpret_cast<Package*>(data)
}

void say(void* ptr)
{
    std::cout << "[func]: ";
    Person* new_ptr = reinterpret_cast<Person*>(ptr);
    if (new_ptr != nullptr)
    {
        new_ptr->SayHello();
    }
    else
    {
        std::cout << "nullptr" << std::endl;
    }
}

int main()
{
    Person* ptr = new Person("Jack");
    std::cout << "[main]: ";
    ptr->SayHello();
    std::cout << std::endl;
    say(nullptr);
    say(ptr);

    delete ptr;
    return 0;
}
