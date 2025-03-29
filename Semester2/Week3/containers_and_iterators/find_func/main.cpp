#include <algorithm>
#include <iostream>
#include <vector>
#include <list>
#include <forward_list>
#include <set>
#include <map>

// 1 2 3
template <typename Container, typename Value>
int dummy_find(const Container& container, const Value& value)
{
    typename Container::const_iterator begin = container.begin();
    typename Container::const_iterator end = container.end();
    int position = 0;
    while (begin != end)
    {
        if (*begin == value)
        {
            return position;
        }
        ++begin;
        ++position;
    }
    return -1;
}

template <typename Key, typename Value>
int dummy_find(const std::map<Key, Value>& container, const Key& value)
{
    typename std::map<Key,Value>::const_iterator it = container.find(value);
    if (it != container.end())
    {
        return std::distance(container.begin(), it);
    }
    return -1;
}


int main()
{
    {
        std::vector<int> vec = {1, 2, 3};
        std::cout << "Position: " << dummy_find(vec, 10) << std::endl;
        std::cout << "Position: " << dummy_find(vec, 2) << std::endl;
    }
    {
        std::list<int> list = {1, 2, 3};
        std::cout << "Position: " << dummy_find(list, 10) << std::endl;
        std::cout << "Position: " << dummy_find(list, 2) << std::endl;
    }
    {
        std::forward_list<int> flist = {1, 2, 3};
        std::cout << "Position: " << dummy_find(flist, 10) << std::endl;
        std::cout << "Position: " << dummy_find(flist, 2) << std::endl;
    }
    {
        std::set<int> set = {1, 2, 3};
        std::cout << "Position: " << dummy_find(set, 10) << std::endl;
        std::cout << "Position: " << dummy_find(set, 2) << std::endl;
    }
    {
        std::map<int, int> map = {{1, 2}, {3, 4}};
        std::cout << "Position: " << dummy_find(map, 10) << std::endl;
        std::cout << "Position: " << dummy_find(map, 1) << std::endl;
    }
    return 0;
}
