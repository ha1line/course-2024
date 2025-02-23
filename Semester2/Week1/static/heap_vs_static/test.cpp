#include <iostream>
#include <vector>
#include <chrono>

std::vector<std::string> get_default_values_v1()
{
    const std::vector<std::string> values = {"one", "two", "three", "four", "five"};
    return values;
}

const std::vector<std::string>& get_default_values_v2()
{
    static const std::vector<std::string> values = {"one", "two", "three", "four", "five"};
    return values;
}

template <typename T>
void start_benchmark(const std::string_view name, T& func, long long count)
{
    std::cout << "Start test for " << name << " with count " << count << std::endl;
    std::chrono::time_point start = std::chrono::steady_clock::now();
    for (long long i = 0; i < count; ++i)
    {
        func();
    }
    std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::steady_clock::now();
    auto elapsed = end - start;
    std::cout << "Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count() << " ms\n";
}

int main()
{
    start_benchmark("dynamic allocation", get_default_values_v1, 10000000);
    start_benchmark("static memory", get_default_values_v2, 10000000);
    return 0;
}
