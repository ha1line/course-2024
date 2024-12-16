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
  int __year, __month, __day;
public:
  Date(int y, int m, int d): __year(y), __month(m), __day(d) {}
  ~Date() = default;
  int GetYear() const
  {
    return __year;
  }
  int GetMonth() const
  {
    return __month;
  }
  int GetDay() const
  {
    return __day;
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
  Database() = default;
  ~Database() = default;
  void AddEvent(const Date& date, const std::string& event)
  {
      __db[date].insert(event);
  }

  bool DeleteEvent(const Date& date, const std::string& event)
  {
    if (__db.count(date) && __db[date].count(event))
    {
      __db[date].erase(event);
      return true;
    }
    return false;
  }

  int DeleteDate(const Date& date)
  {
    int n = __db[date].size();
    __db.erase(date);
    return n;
  }

  // будет зависеть от контейнера, который вы выберете
  std::set<std::string> Find(const Date& date) const
  {
    if (__db.count(date))
    {
      return __db.at(date);
    }
    
    return std::set<std::string>();
  }
  
  void Print() const
  {
    for (const auto& [date, events] : __db)
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
  std::map<Date, std::set<std::string>> __db;
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
    std::string month_error = std::to_string(month);
    throw std::invalid_argument("Month value is invalid: " + month_error);
  }
  if (day < 1 || day > 31)
  {
    std::string day_error = std::to_string(day);
    throw std::invalid_argument("Day value is invalid: " + day_error);
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
