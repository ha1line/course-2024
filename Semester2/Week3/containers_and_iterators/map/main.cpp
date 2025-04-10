#include <map>
#include <string>

int main()
{
    std::map<std::string, int> map = { {"fisrt", 1} };
    auto it = map.find("first");
    if (it != map.end())
    {
        // Bad pattern (2 operations vs 1 operation)
        map["first"] = 2;
        // Good variant
        it->second = 2;
    }
}
