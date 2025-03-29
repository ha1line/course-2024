#include <iostream>
#include <iterator>
#include <vector>
#include <istream>

int main()
{
    std::vector<int> vec;
    std::istream_iterator<int> it(std::cin);

    std::istream_iterator<int> end;
    while (it != end)
    {
        vec.push_back(*it);
        ++it;
    }
    for (int elem : vec)
    {
         std::cout << elem << ' ';
    }
    return 0;
}
