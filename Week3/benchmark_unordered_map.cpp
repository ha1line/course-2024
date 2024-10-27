#include <iostream>
#include <unordered_map>

int main()
{
    std::unordered_map<std::string, int> map;
    map.reserve(1'000'000);
    std::string temp;
    while (std::cin >> temp)
    {
        ++map[temp];
    }
}
