#include <iostream>
#include <vector>

void foo(const long& i)
{
    long& c = const_cast<long&>(i);
    c = 339;
}

int main()
{
    const long i = 228;
    foo(i);
    std::cout<<i<<std::endl;
{
    std::string s = "aboba";
    char* c = const_cast<char*>(s.c_str());
    
}
}