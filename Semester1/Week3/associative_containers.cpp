#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <string>

static std::pair<std::string, int> get()
{
    return {"something", 0};
}

int main ()
{
    {
        const auto [first, second] = get();
        std::cout << "first: " << first << ", second: " << second << std::endl;
        std::cout << "-------------------------" << std::endl;
    }
    {
        std::cout << "work with map" << std::endl;
        std::map<std::string, int> map =
        {
            {"localhost", 32},
            {"host", 24}
        };
        // Since C++11
        for (const auto& it : map)
        {
            std::cout << "key: " << it.first << ", value: " << it.second << std::endl;
        }
        // Since C++17
        // structure binding
        for (const auto& [key, value] : map)
        {
            std::cout << "key: " << key << ", value: " << value << std::endl;
        }
        // original way
        for (std::map<std::string, int>::const_iterator it = map.begin(); it != map.end(); ++it)
        {
            std::cout << "key: " << it->first << ", value: " << it->second << std::endl;
        }
        std::cout << std::endl;
        std::cout << "-------------------------" << std::endl;
    }
    {
        std::map<std::string, int> map =
        {
            {"localhost", 32},
            {"host", 24}
        };
        // O log(N)
        map.insert({"anotherhost", 16});
        for (const auto& [key, value] : map)
        {
            std::cout << "key: " << key << ", value: " << value << std::endl;
        }
        // O log(N)
        map.erase("anotherhost");
        std::cout << std::endl;
        for (const auto& [key, value] : map)
        {
            std::cout << "key: " << key << ", value: " << value << std::endl;
        }
        // O log(N)
        const int value = map["localhost"];
        std::cout << "get value: " << value << std::endl;
        std::cout << std::endl;
        // O log(N)
        const int another_value = map["null"];
        std::cout << "get another value: " << another_value << std::endl;
        std::cout << std::endl;
        // Since C++20, O log(N)
        if (map.contains("localhost"))
        {
            std::cout << "our map contains key = localhost" << std::endl;
        }
        // old way, O log(N)
        if (map.count("localhost") > 0)
        {
            std::cout << "our map contains key = localhost" << std::endl;
        }
        const auto it = map.find("localhost1");
        std::cout << std::endl;
        if (it != map.end())
        {
            std::cout << it->first << ' ' << it->second << std::endl;
        }
        else
        {
            std::cout << "not found" << std::endl;
        }
        std::cout << std::endl;
        // Since C++17, O log(N)
        const auto elem = map.extract("nulllll");
        if (elem.empty())
        {
            std::cout << "can`t extract" << std::endl;
        }
        else
        {
            std::cout << elem.key() << ' ' << elem.mapped() << std::endl;
        }
        std::cout << std::endl;
        std::cout << std::endl;
        map["anotherhost"] = 1;
        map["anotherhost_1"] = 128;
        // Since C++17, O log(N)
        map.insert_or_assign("anotherhost", 2);
        map.insert_or_assign("anotherhost_2", 256);
        for (const auto& [key, value] : map)
        {
            std::cout << "key: " << key << ", value: " << value << std::endl;
        }
        // upper_bound, lower_bound - O log(N)
        // equal_range(key) - O log(N)
        // merge = map1 + map2 => sort => map3
        std::cout << "-------------------------" << std::endl;
    }
    {
        std::map<std::string, std::string> map;
        std::cout << "get from map: " << map["null"] << std::endl;
        std::cout << "-------------------------" << std::endl;
    }
    {
        std::cout << "work with set" << std::endl;
        std::set<int> my_set = {1, 2, 3};
        // O log(N)
        my_set.insert(5);
        // O log(N)
        my_set.erase(2);
        for (const auto& it : my_set)
        {
             std::cout << it << ' ';
        }
        std::cout << std::endl;
        std::cout << "-------------------------" << std::endl;
    }
    {
        std::cout << "work with unordered_map" << std::endl;
        std::unordered_map<std::string, int> map =
        {
            {"localhost", 32},
            {"host", 24}
        };
        map.reserve(100);
        // average case - O(1), worst case - O(N)
        map.insert({"another", 16});
        for (const auto& [key, value] : map)
        {
             std::cout << key << ' ' << value << std::endl;
        }
        // average case - O(1), worst case - O(N)
        map.erase("host");
        std::cout << std::endl;
        for (const auto& [key, value] : map)
        {
             std::cout << key << ' ' << value << std::endl;
        }
        // operator[], average case - O(1), worst case - O(N)
        const int value = map["null"];
        std::cout << "value: " << value << std::endl;
        // Since C++17, average case - O(1), worst case - O(N)
        const auto elem = map.extract("nulllll");
        if (elem.empty())
        {
            std::cout << "can`t extract" << std::endl;
        }
        else
        {
            std::cout << elem.key() << std::endl;
        }
        // std::hash(key) -> (bucket > 1 key) -> key
        // Since C++17, average case - O(1), worst case - O(N)
        map.insert_or_assign("null", 128);
        std::cout << std::endl;
        for (const auto& [key, value] : map)
        {
             std::cout << key << ' ' << value << std::endl;
        }
        std::cout << "-------------------------" << std::endl;
    }
    {
        std::cout << "work with unordered_set" << std::endl;
        std::unordered_set<int> set = {1, 2, 3};
        set.insert(5);
        set.erase(2);
        for (const auto& it : set)
        {
             std::cout << it << ' ';
        }
        std::cout << std::endl;
        std::cout << "-------------------------" << std::endl;
    }
    {
        std::cout << "work with multimap" << std::endl;
        // minus vibe container
        std::multimap<std::string, int> map =
        {
            {"localhost", 16},
            {"localhost", 32}
        };
        // O log(N)
        const auto elem = map.find("localhost");
        std::cout << elem->first << ' ' << elem->second << std::endl;
        // O log(N) + O(K)
        std::cout << "count: " << map.count("localhost") << std::endl;
        const auto it = map.equal_range("localhost");
        std::cout << std::endl;
        for (auto begin = it.first; begin != it.second; ++begin)
        {
             std::cout << begin->first << ' ' << begin->second << std::endl;
        }
        std::cout << "-------------------------" << std::endl;
        // multiset, unordered_multimap, unordered_multiset
    }
    // std::vector - best seq, std::unordered_map - best associative
    {
        // Since C++23
        // flat_map, flat_set
        // N = [10:50], insert - O(N), >>> Cache Friendly
    }
    return 0;
}
