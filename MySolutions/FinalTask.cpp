#include <iostream>
#include <string>
#include <map>
#include <set>
#include <sstream>
#include <iomanip>

class Date
{
public:
    Date(int year, int month, int day) :
        m_year(year),
        m_month(month),
        m_day(day)
    {
    } 

    const int& GetYear() const noexcept
    {
        return m_year;
    }
    const int& GetMonth() const noexcept
    {
        return m_month;
    }
    const int& GetDay() const noexcept
    {
        return m_day;
    }

private:
    const int m_year = 0;
    const int m_month = 0;
    const int m_day = 0;
};

bool operator<(const Date& lhs, const Date& rhs)
{
    return std::tie(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) < std::tie(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

std::ostream& operator<<(std::ostream& os, const Date& date)
{
    os << std::setfill('0');
    os << std::setw(4) << date.GetYear() 
        << '-' << std::setw(2) << date.GetMonth() 
        << '-' << std::setw(2) << date.GetDay();
    return os;
}

Date CreateDateFromString(const std::string& stringDate)
{
    int year;
    int month;
    int day;
    
    std::istringstream dateIS(stringDate);
    bool areSeparatorsCorrect = true;
    dateIS >> year;
    areSeparatorsCorrect = dateIS.get() == '-';
    dateIS >> month;
    areSeparatorsCorrect = dateIS.get() == '-';
    dateIS >> day;

    if (!dateIS || !areSeparatorsCorrect || dateIS.peek() != -1)
    {
        throw std::runtime_error("Wrong date format: " + stringDate);
    }

    if (month < 1 || month > 12)
    {
        throw std::runtime_error("Month value is invalid: " + std::to_string(month));
    }
    if (day < 1 || day > 31)
    {
        throw std::runtime_error("Day value is invalid: " + std::to_string(day));
    }

    return {year, month, day};
}

class Database
{
public:
    void AddEvent(const Date& date, const std::string& event) noexcept
    {
        m_base[date].insert(event);
    }

    bool DeleteEvent(const Date& date, const std::string& event) noexcept
    {
        return m_base[date].erase(event) > 0;
    }

    int DeleteDate(const Date& date) noexcept
    {
        const auto it = m_base.find(date);
        int deletedElementsCount = 0;
        if (it != m_base.end())
        {
            deletedElementsCount = (it -> second).size();
            (it -> second).clear();
        }
        return deletedElementsCount;
    }

    std::set<std::string> Find(const Date& date) const noexcept
    {
        const auto it = m_base.find(date);
        return (it == m_base.end()) ? std::set<std::string>() : it -> second;
    }
    
    void Print() const noexcept
    {
        for (const auto& [date, eventsSet] : m_base)
        {
            for (const std::string& event : eventsSet)
            {
                std::cout << date << ' ' << event << std::endl;
            }
        }
    }

private:
    std::map<Date, std::set<std::string>> m_base;
};

void ReadAndExecuteCommand(std::istream& is, Database& db) 
{
    std::string command;
    is >> command;
    if (command == "Add")
    {
        std::string stringDate;
        std::string event;
        is >> stringDate >> event;
        Date date = CreateDateFromString(stringDate);
        db.AddEvent(date, event);
    }
    else if (command == "Del")
    {
        std::string stringDate;
        std::string event;
        is >> stringDate >> event;
        Date date = CreateDateFromString(stringDate);
        if (event.empty())
        {
            std::cout << "Deleted " << db.DeleteDate(date) << " events" << std::endl;
        }
        else
        {
            std::string outputMessage = (db.DeleteEvent(date, event)) ? "Deleted successfully" : "Event not found";
            std::cout << outputMessage << std::endl;
        }
    }
    else if (command == "Find")
    {
        std::string stringDate;
        is >> stringDate;
        Date date = CreateDateFromString(stringDate);
        for (const std::string& event : db.Find(date))
        {
            std::cout << event << std::endl;
        }
    }
    else if (command == "Print")
    {
        db.Print();
    }
    else
    {
        throw std::runtime_error("Unknown command: " + command);
    }
}

int main()
{
    Database db;

    std::string commandLine;
    while (std::getline(std::cin, commandLine))
    {
        if (commandLine.empty()) 
        {
            continue;
        }
        std::istringstream is(commandLine);
        if (!is) 
        {
            continue;
        }
        try
        {
            ReadAndExecuteCommand(is, db);
        }
        catch(const std::runtime_error& e)
        {
            std::cout << e.what() << std::endl;
            return 0;
        }
    }

    return 0;
}