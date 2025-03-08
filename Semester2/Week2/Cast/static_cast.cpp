#include <iostream>
#include <vector>
enum EU
{
    One = 1,
    two = 2
};
void foo(EU e)
{
    std::cout<<"EU"<<std::endl;
}
void bar(double i)
{
    std::cout<<"double bar"<<std::endl;
}
///
void bar(int i)
{
    std::cout<<"int bar"<<std::endl;
}
int main()
{
    {
        double d = 5.5;
        int i = static_cast<int>(d);
        std::cout<<i<<std::endl;
    }
    {
        int* pointerInt = new int(228);
        void* pointer = pointerInt;
        int* pointerInt2 = static_cast<int*>(pointer);
        std::cout<<*pointerInt2<<std::endl;
    }
    {
        EU e = EU::One;
        int i = static_cast<int>(e);
        std::cout<<i<<std::endl;
    }
    {
        double d = 337;
        bar(static_cast<int>(d));
        int i = 2;
        foo(static_cast<EU>(i));
    }
}