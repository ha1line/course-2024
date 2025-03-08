#include <iostream>
#include <vector>

int main()
{
    {
        double d = 5.5;
        int& i = reinterpret_cast<int&>(d);
        std::cout<<sizeof(int*)<<std::endl;
        std::cout<<i<<std::endl;
    }
    {
        long long l = 386754;
        double& d = reinterpret_cast<double&>(l);
        std::cout<<d<<std::endl;
    }
//    {
//        int i = 228;
//        double& d = reinterpret_cast<double&>(d);
//        std::cout<<d<<std::endl;
//    }
    {
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
        Laptop& lap = reinterpret_cast<Laptop&>(comp);
        std::cout<<lap.cpu<<" "<<lap.ram<<std::endl;
    }
    {
        std::vector<int> v = {5, 6, 7};
        int& i = reinterpret_cast<int&>(*(v.data()));
        std::cout<<i<<std::endl;
    }
    {
        char* pack = new char[sizeof(int)];
        int& i = reinterpret_cast<int&>(pack);
        std::cout<<i<<std::endl;
    }
}