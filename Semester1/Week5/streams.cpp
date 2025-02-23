#include <iostream>
#include <sstream>
#include <iomanip>

struct Duration
{
    int hour;
    int min;
};

// std::istream (Base) -> std::stringstream 

// std::cin, std::fstream, std::stringstream
Duration read_duration(std::istream& stream)
{
    int h = 0;
    int m = 0;
    // 01
    stream >> h;
    //check :
    if (stream.peek() != ':')
    {
        throw std::invalid_argument("Invalid duration format");
    }
    // skip :
    stream.ignore(1);
    // 20
    stream >> m;

    return {h, m};
}

// print_duration with format XX:XX, X - can be 0
void print_duration(std::ostream& stream, const Duration& duration)
{
    stream << std::setfill('0');
    stream << std::setw(2) << duration.hour << ':' << std::setw(2) << duration.min;
}

int main()
{
    // std::cin std::stringstream
    Duration dur = read_duration(std::cin);
    print_duration(std::cout, dur);
    std::cout << std::endl;
    std::string rawDuration = {"01:20"};
    std::stringstream sstream(rawDuration);

    Duration durString = read_duration(sstream);
    print_duration(std::cout, durString);
}
