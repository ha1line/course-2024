#include <iostream>

class Object
{
public:
    Object()
    {
        std::cout << "Create object with default constructor" << std::endl;
    }

    Object(int number) : m_number(number)
    {
        std::cout << "Create object with number: " << number << std::endl;
    }

    int Get() const
    {
        return m_number;
    }

    ~Object()
    {
        std::cout << "Call destructor" << std::endl;
    }
private:
    int m_number = 0;
};


int main()
{
    Object* obj_1 = new Object();
    Object* obj_2 = new Object(2);
    std::cout << "Obj1: " << obj_1->Get() << std::endl;
    std::cout << "Obj2: " << obj_2->Get() << std::endl;
    delete obj_1;
    delete obj_2;
}
