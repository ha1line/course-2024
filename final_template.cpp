// вы можете подключить все необходимые вам библиотеки из стандарта
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <iomanip>
#include <sstream>

// нужно заполнить методы и перегрузить нужные операторы
class Date
{
private:
  int m_year, m_month, m_day;
public:
  Date(int y, int m, int d): m_year(y), m_month(m), m_day(d) {}
  int GetYear() const
  {
    return m_year;
  }
  int GetMonth() const
  {
    return m_month;
  }
  int GetDay() const
  {
    return m_day;
  }
};

// здесь советую воспользоваться трюком с вектором из лекции, либо std::tie
bool operator<(const Date& lhs, const Date& rhs)
{
  return std::vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()}
         < std::vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

class Database
{
public:
  void AddEvent(const Date& date, const std::string& event)
  {
      m_db[date].insert(event);
  }

  bool DeleteEvent(const Date& date, const std::string& event)
  {
    if (m_db.count(date) && m_db[date].count(event))
    {
      m_db[date].erase(event);
      return true;
    }
    return false;
  }

  int DeleteDate(const Date& date)
  {
    int n = m_db[date].size();
    m_db.erase(date);
    return n;
  }

  // будет зависеть от контейнера, который вы выберете
  std::set<std::string> Find(const Date& date) const
  {
    auto today = m_db.find(date);
    if (today != m_db.end())
    {
      return today->second;
    }
    
    return {};
  }
  
  void Print() const
  {
    for (const auto& [date, events] : m_db)
    {
      if (date.GetYear() < 0) {continue;}
      for (const auto& event : events)
      {
        std::cout << std::setfill('0');
        std::cout << std::setw(4) << date.GetYear() << '-' << std::setw(2) << date.GetMonth() << 
        '-' << std::setw(2) << date.GetDay() << ' ' << event << std::endl;
      }
    }
  }
private:
  std::map<Date, std::set<std::string>> m_db;
};

Date GetDate(const std::string& date_str)
{
  int year, month, day;
  char delimeter;
  std::istringstream input(date_str); 

  if (!(input >> year >> delimeter >> month >> delimeter >> day) || delimeter != '-')
  {
    throw std::invalid_argument("Wrong date format: " + date_str);
  }
  if (input.peek() != EOF)
  {
    throw std::invalid_argument("Wrong date format: " + date_str);
  }
  if (month < 1 || month > 12)
  {
    throw std::invalid_argument("Month value is invalid: " + std::to_string(month));
  }
  if (day < 1 || day > 31)
  {
    throw std::invalid_argument("Day value is invalid: " + std::to_string(day));
  }

  return Date(year, month, day);
}

int main()
{
  Database db;

  std::string commandLine;
  std::string command, date_str, event;

  try
  {
    while (std::getline(std::cin, commandLine))
    {
      if (commandLine.empty()) {continue;}
      std::istringstream streamLine(commandLine);
      streamLine >> command;
      if (command == "Add")
      {
        streamLine >> date_str >> event;
        Date date = GetDate(date_str);
        db.AddEvent(date, event);
      }
      else if (command == "Del")
      {
        streamLine >> date_str;
        Date date = GetDate(date_str);
        if (streamLine >> event)
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
        else
        {
          int n = db.DeleteDate(date);
          std::cout << "Deleted " << n << " events" << std::endl;
        }
      }
      else if (command == "Find")
      {
        streamLine >> date_str;
        Date date = GetDate(date_str);
        for (const auto& event : db.Find(date))
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
        std::cout << "Unknown command: " << command << std::endl;
      }
    }
  }
  catch (const std::invalid_argument& e)
  {
    std::cout << e.what() << std::endl;
  }
  return 0;
}
