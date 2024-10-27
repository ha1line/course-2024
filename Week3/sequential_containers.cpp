#include <iostream>
#include <limits>
#include <vector>
#include <list>
#include <forward_list>
#include <string>
#include "common/log_duration.h"

int main()
{
    {
        const size_t max = std::numeric_limits<size_t>::max();
        const size_t min = std::numeric_limits<size_t>::min();
        std::cout << "-------------------------" << std::endl;
        std::cout << "min: " << min << std::endl;
        std::cout << "max: " << max << std::endl;
        // std::string::size_type = size_t
        std::cout << "npos: " << std::string::npos << std::endl;
        std::cout << "-------------------------" << std::endl;
    }
    {
        std::string str = "Hello, World!";
        // O(N)
        size_t pos = str.find("Hello");
        if (pos == std::string::npos)
        {
            std::cout << "not found" << std::endl;
        }
        else
        {
            std::cout << "found pos - " << pos << std::endl;
        }

        // since C++20, O(N)
        if (str.contains("Hello"))
        {
            std::cout << "found Hello" << std::endl;
        }

        // O(N)
        pos = str.rfind("World");
        // O(N)
        std::string newStr = str.substr(0, pos);
        std::cout << newStr << std::endl;
        // O(1), if size < capacity
        str.resize(pos);
        std::cout << "New str: " << str << std::endl;
        std::cout << "-------------------------" << std::endl;
    }
    {
        std::string str = "aaabbc";
        // O(N * X)
        auto pos = str.find_first_of("b");
        std::cout << "Position: " << pos << std::endl;
        std::cout << "-------------------------" << std::endl;
    }
    {
        std::string str = "Hello, World!";
        // Since C++23, O(N)
        if (str.starts_with("Hello"))
        {
            std::cout << "start with" << std::endl;
        }
        // Since C++23, O(N)
        if (str.ends_with("World!"))
        {
            std::cout << "end with" << std::endl;
        }
        std::cout << "-------------------------" << std::endl;
    }
    {
        std::string str = "1 is ";
        std::vector<char> vec = { 'i', 'n', 't'};
        // O(N)
        str.append(vec.begin(), vec.end());
        // str.append_range(vec)
        std::cout << str << std::endl;
        std::cout << "-------------------------" << std::endl;
    }
    {
        std::string str1 = "Hello";
        std::string str2 = "Bye";
        std::cout << "str1: " << str1 << std::endl;
        std::cout << "str2: " << str2 << std::endl;
        std::cout << "after swap" << std::endl;
        // O(1) - very fast
        str1.swap(str2);
        std::cout << "str1: " << str1 << std::endl;
        std::cout << "str2: " << str2 << std::endl;
        std::cout << "-------------------------" << std::endl;
    }
    {
        std::string str;
        // O(1)
        if (str.empty())
        {
            std::cout << "wow empty" << std::endl;
        }
        std::cout << "-------------------------" << std::endl;
    }
    {
        // constructor with 1 parameter
        std::vector<int> vec(10);
        // O(1)
        std::cout << vec.size() << std::endl;
        // O(1)
        std::cout << vec.capacity() << std::endl;
        std::cout << "-------------------------" << std::endl;
    }
    {
        // constructor with 2 parameters
        std::vector<int> vec(10, 2);
        std::cout << vec[4] << std::endl;
        std::cout << "-------------------------" << std::endl;
    }
    {
        std::vector<int> vec;
        // UB!
        vec.pop_back();
        std::cout << vec.size() << std::endl;
        std::cout << "-------------------------" << std::endl;
    }
    // {
    //     LOG_DURATION("reserve + push_back");
    //     std::vector<size_t> vec;
    //     vec.reserve(1000000);
    //     for (size_t i = 0; i < 1'000'000'000; ++i)
    //     {
    //         vec.push_back(i);
    //     }
    // }
    // {
    //     LOG_DURATION("push_back");
    //     std::vector<size_t> vec;
    //     for (size_t i = 0; i < 1'000'000'000; ++i)
    //     {
    //         vec.push_back(i);
    //     }
    // }
    {
        std::cout << "-------------------------" << std::endl;
        std::vector<int> vec(10);
        std::cout << vec.size() << std::endl;
        vec.clear();
        // O(N)
        vec.resize(6);
        std::cout << vec.size() << ' ' << vec.capacity() << std::endl;
        // O(N)
        vec.shrink_to_fit();
        std::cout << vec.size() << ' ' << vec.capacity() << std::endl;
        std::cout << "-------------------------" << std::endl;
    }
    {
        std::vector<int> vec = {1, 2};
        const auto& number = vec[0];
        std::cout << number << std::endl;
        // size == capacity
        vec.push_back(123);
        // UB!
        std::cout << number << std::endl;
        std::cout << "-------------------------" << std::endl;
    }
    {
        std::list<int> list = {1, 2, 3};
        // auto since C++11
        list.erase(std::next(list.begin(), 1));
        for (const auto& it : list)
        {
             std::cout << it << " ";
        }
        std::cout << std::endl;
        std::cout << "-------------------------" << std::endl;
    }
    {
        std::list<int> list = {1, 2, 3};
        // O(1)
        list.push_back(5);
        // O(1)
        list.push_front(4);
        for (const auto& it : list)
        {
            std::cout << it << " ";
        }
        std::cout << std::endl;
        std::cout << "-------------------------" << std::endl;
    }
    {
        std::list<int> list = {3, 2, 5};
        // since C++20, O(N) * log(N)
        std::cout << "before sort" << std::endl;
        for (const auto& it : list)
        {
             std::cout << it << " ";
        }
        std::cout << std::endl;
        std::cout << "after sort" << std::endl;
        // N * log(N)
        list.sort();
        for (const auto& it : list)
        {
             std::cout << it << " ";
        }
        std::cout << std::endl;
        std::cout << "-------------------------" << std::endl;
    }
    {
        std::list<int> list = {3, 5, 5, 2, 2};
        std::cout << "before unique" << std::endl;
        for (const auto& it : list)
        {
             std::cout << it << " ";
        }
        std::cout << std::endl;
        std::cout << "after unique" << std::endl;
        // since C++20, O(N) * log(N)
        list.unique();
        for (const auto& it : list)
        {
             std::cout << it << " ";
        }
        std::cout << std::endl;
        std::cout << "-------------------------" << std::endl;
    }
    {
        // Since C++11
        std::forward_list<int> list = {1, 2, 3};
        // O(1)
        list.insert_after(list.end(), 4);
        // O(1)
        // list.erase_after(std::prev(list.end()));
        for (const auto& it : list)
        {
             std::cout << it << std::endl;
        }
    }
    {
        // std::deque ~ std::vector
        // except push_front O(1), push_back O(1), not invalidate ref/ptr, invalidate it
        // std::deque * 2 > std::vector
        // std::deque = vec[0] -> vec[2]
    }
    return 0;
}
