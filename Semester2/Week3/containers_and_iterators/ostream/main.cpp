#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

int main()
{
    std::vector<int> vec = {1, 2, 3};
    std::ostream_iterator<int> it(std::cout);
    std::copy(vec.begin(), vec.end(), it);
    return 0;
}
