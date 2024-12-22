// вы можете подключить все необходимые вам библиотеки из стандарта
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <iomanip>
#include <tuple>

// нужно заполнить методы и перегрузить нужные операторы
class Date
{
public:
  Date(int y, int m, int d)
  {
    year = y;
    month = m;
    day = d;
  }
  int GetYear() const
  {
    return year;
  }
  int GetMonth() const
  {
    return month;
  }
  int GetDay() const
  {
    return day;
  }

private:
  int year;
  int month;
  int day;
};

// здесь советую воспользоваться трюком с вектором из лекции, либо std::tie
bool operator<(const Date& lhs, const Date& rhs)
{
  std::tuple<int, int, int> left = std::make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay());
  std::tuple<int, int, int> right = std::make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
  return std::tie(left) < std::tie(right);
}

bool operator>(const Date& lhs, const Date& rhs)
{
  return rhs < lhs;
}

bool operator==(const Date& lhs, const Date& rhs)
{
  return !(lhs < rhs) && !(lhs > rhs);
}

class Database
{
public:
  void AddEvent(const Date& date, const std::string& event)
  {
    storage[date].insert(event);
  }
  void DeleteEvent(const Date& date, const std::string& event)
  {
    if (storage[date].erase(event))
      std::cout << "Deleted successfully" << std::endl;
    else
      std::cout << "Event not found" << std::endl;
  }
  void DeleteDate(const Date& date)
  {
    int numberOfEvents = storage[date].size();
    storage[date].clear();
    std::cout << "Deleted " << numberOfEvents << " events" << std::endl;
  }
  void Find(const Date& date, std::ostream& stream) const
  {
    auto events = storage.find(date);
    if (events != storage.end())
    {
      for (const std::string& temp : events->second)
      {
        stream << temp << '\n';
      }
    }
  }
  
  void Print(std::ostream& stream) const
  {
    stream << std::setfill('0');
    for (auto i = storage.begin(); i != storage.end(); ++i)
    {
      std::set<std::string> events = i -> second;
      for (auto j = events.begin(); j != events.end(); ++j)
      {
        stream << std::setw(4) << i -> first.GetYear() << "-" << std::setw(2)
          << i -> first.GetMonth() << "-" << std::setw(2) << i -> first.GetDay() << ' ' << *j << '\n';
      }
    }
  }
private:
  std::map<Date, std::set<std::string>> storage;
};

Date read_date(std::string dateString)
{
  std::stringstream stream(dateString);
  int year;
  int month;
  int day;
  if (!(stream >> year) || stream.get() != '-'
    || !(stream >> month) || stream.get() != '-'
    || !(stream >> day))
    throw std::invalid_argument("Wrong date format: " + dateString);
  char test;
  if (stream >> test)
    throw std::invalid_argument("Wrong date format: " + dateString);
  if (month < 1 || month > 12)
    throw std::invalid_argument("Month value is invalid: " + std::to_string(month));
  if (day < 1 || day > 31)
    throw std::invalid_argument("Day value is invalid: " + std::to_string(day));
  return Date(year, month, day);
}

int main()
{
  Database db;

  std::string commandLine;
  while (std::getline(std::cin, commandLine))
  {
    std::stringstream sstream(commandLine);
    std::string command;
    sstream >> command;
    if (command.empty())
      continue;
    std::string tempDate;
    sstream >> tempDate;
    if (command == "Print")
      db.Print(std::cout);
    else if (command != "Add" && command != "Del" && command != "Find")
    {
      std::cout << "Unknown command: " << command << std::endl;
      return 0;
    }
    if (tempDate == "")
      continue;
    try
    {
      Date date = read_date(tempDate);

      if (command == "Add")
      {
        std::string event;
        sstream >> event;
        db.AddEvent(date, event);
      }
      else if (command == "Del")
      {
        std::string event;
        sstream >> event;
        if (event != "")
          db.DeleteEvent(date, event);
        else
          db.DeleteDate(date);
      }
      else if (command == "Find")
      {
        db.Find(date, std::cout);
      }
    }
    catch(const std::invalid_argument& e)
    {
      std::cout << e.what() << std::endl;
      return 0;
    }
  }
  return 0;
}