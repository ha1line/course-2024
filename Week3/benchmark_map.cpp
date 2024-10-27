#include <iostream>
#include <map>

int main()
{
    std::map<std::string, int> map;
    std::string temp;
    while (std::cin >> temp)
    {
        ++map[temp];
    }
}
