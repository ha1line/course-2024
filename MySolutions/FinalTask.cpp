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

    bool IsYearNegative() const noexcept
    {
        return m_year < 0;
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

Date CreateDateFromString(std::string stringDate)
{
    int year;
    int month;
    int day;
    
    std::istringstream dateIS(stringDate);

    dateIS >> year;
    if (!dateIS || !(year >= -9999 && year <= 9999) || dateIS.peek() != '-')
    {
        throw std::runtime_error("Wrong date format: " + stringDate);
    }
    dateIS.ignore(1);
    dateIS >> month;
    if (!dateIS || !(month >= -99 && month <= 99) || dateIS.peek() != '-')
    {
        throw std::runtime_error("Wrong date format: " + stringDate);
    }
    dateIS.ignore(1);
    dateIS >> day;
    if (!dateIS || !(day >= -99 && day <= 99) || dateIS.peek() != -1)
    {
        throw std::runtime_error("Wrong date format: " + stringDate);
    }

    if (!(month > 0 && month < 13))
    {
        throw std::runtime_error("Month value is invalid: " + std::to_string(month));
    }
    if (!(day > 0 && day < 32))
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
        if (!m_base.count(date) > 0)
        {
            m_base[date] = { event };
            return;
        }
        m_base[date].insert(event);
    }

    bool DeleteEvent(const Date& date, const std::string& event) noexcept
    {
        if (m_base.count(date) > 0 && m_base[date].count(event) > 0)
        {
            m_base[date].erase(event);
            return true;
        }
        return false;
    }

    int DeleteDate(const Date& date) noexcept
    {
        if (m_base.count(date) > 0)
        {
            size_t eventsCount = m_base[date].size();
            m_base[date].clear();
            return eventsCount;
        }
        return 0;
    }

    std::set<std::string> Find(const Date& date) const noexcept
    {
        if (m_base.count(date) > 0)
        {
            return m_base.at(date);
        }
        return {};
    }
    
    void Print() const noexcept
    {
        for (const auto& [date, eventsSet] : m_base)
        {
          if (date.IsYearNegative())
          {
              continue;
          }
          for (std::string event : eventsSet)
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
            if (db.DeleteEvent(date, event))
            {
                std::cout << "Deleted successfully" << std::endl;
            }
            else
            {
                std::cout << "Event not found" << std::endl;
            }
        }
    }
    else if (command == "Find")
    {
        std::string stringDate;
        is >> stringDate;
        Date date = CreateDateFromString(stringDate);
        std::set<std::string> dateEvents = db.Find(date);
        for (std::string event : dateEvents)
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