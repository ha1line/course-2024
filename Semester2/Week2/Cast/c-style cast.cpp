#include <iostream>
#include <vector>
void foo(const long& i)
{
    long& c = (long&)(i);
    c = 339;
}

int main()
{
    int i = 5;
    double d = (int&)i;
    std::cout<<d<<std::endl;
    const long l = 228;
    foo(l);
    std::cout<<l<<std::endl;
    struct Computer
    {
        Computer(double cpu, int ram) :
        cpu(cpu), ram(ram)
        {

        }
        double cpu;
        int ram;
    };

    struct Laptop
    {
        double cpu;
        int ram;
    };
    Computer comp(3.3,8);
    Laptop& lap = (Laptop&)(comp);
    std::cout<<lap.cpu<<" "<<lap.ram<<std::endl;
    {
        int ii = -288;
        unsigned int dd = (int)ii;
        std::cout<<dd<<std::endl;
    }
}