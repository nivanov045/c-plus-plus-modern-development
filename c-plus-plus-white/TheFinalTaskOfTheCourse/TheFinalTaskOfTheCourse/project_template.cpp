// Реализуйте функции и методы классов и при необходимости добавьте свои

#include <string>
#include <iostream>
#include <map>
#include <set>
#include <iomanip>
#include <sstream>

using namespace std;

class Date {
public:
  Date(int iYear, int iMonth, int iDay) :
  _year(iYear), _month(iMonth), _day(iDay)
  {
    if (iMonth > 12 || iMonth < 1)
      throw invalid_argument("Month value is invalid: " + to_string(iMonth));
    if (iDay > 31 || iDay < 1)
      throw invalid_argument("Day value is invalid: " + to_string(iDay));
  }
  ~Date() = default;

  int GetYear() const { return _year; }
  int GetMonth() const { return _month; }
  int GetDay() const { return _day; }

private:
  int _year;
  int _month;
  int _day;
};

bool operator<(const Date& lhs, const Date& rhs)
{
  if (lhs.GetYear() < rhs.GetYear())
    return true;
  if (lhs.GetYear() > rhs.GetYear())
    return false;
  if (lhs.GetMonth() < rhs.GetMonth())
    return true;
  if (lhs.GetMonth() > rhs.GetMonth())
    return false;
  if (lhs.GetDay() < rhs.GetDay())
    return true;
  return false;
}

class Database {
public:
  Database() = default;
  ~Database() = default;

  void AddEvent(const Date& date, const string& event)
  {
    /*if (_dataBase.count(date))*/
    _dataBase[date].emplace(event);
  }

  bool DeleteEvent(const Date& date, const string& event)
  {
    if (_dataBase.count(date))
      if (_dataBase.at(date).count(event)) {
        _dataBase.at(date).erase(event);
        cout << "Deleted successfully" << endl;
        return true;
      }
    cout << "Event not found" << endl;
    return false;
  }

  int  DeleteDate(const Date& date)
  {
    int tmp = 0;
    if (_dataBase.count(date)) {
      tmp = _dataBase.at(date).size();
      _dataBase.erase(date);
    }
    cout << "Deleted " << tmp << " events" << endl;
    return tmp;
  }

  void Find(const Date& date) const
  {
    if (_dataBase.count(date))
      for (auto& e : _dataBase.at(date))
        cout << e << endl;
  }

  void Print() const
  {
    for (auto& d : _dataBase)
      for (auto& e : d.second)
        cout << setw(4) << setfill('0') << d.first.GetYear() << "-" << setw(2) << setfill('0') << d.first.GetMonth() <<
          "-" << setw(2) << setfill('0') << d.first.GetDay() << " " << e << endl;
  }

private:
	map<Date, set<string>> _dataBase;
};

Date ParseDate(const string& s) {
  stringstream stream(s);
  int year = 0, month = 0, day = 0;
  if (!(stream >> year))
    throw invalid_argument("Wrong date format: " + s);
  if (stream.peek() != '-')
    throw invalid_argument("Wrong date format: " + s);
  stream.ignore(1);
  if(!(stream >> month))
    throw invalid_argument("Wrong date format: " + s);
  if (stream.peek() != '-')
    throw invalid_argument("Wrong date format: " + s);
  stream.ignore(1);
  if(!(stream >> day))
    throw invalid_argument("Wrong date format: " + s);
  if (stream.peek() != EOF)
    throw invalid_argument("Wrong date format: " + s);
  return {year, month, day};
}

int main() {
  Database db;

	string command;
  while (getline(cin, command)) {
    try {
      stringstream stream(command);
      string task;
      getline(stream, task, ' ');
      if (task == "Add") {
        string strDate;
        getline(stream, strDate, ' ');
        auto date = ParseDate(strDate);
        string event;
        getline(stream, event);
        if (!event.empty())
          db.AddEvent(date, event);
      }
      else if (task == "Del") {
        string strDate;
        getline(stream, strDate, ' ');
        auto date = ParseDate(strDate);
        string event;
        getline(stream, event);
        if (!event.empty())
          db.DeleteEvent(date, event);
        else
          db.DeleteDate(date);
      }
      else if (task == "Find") {
        string strDate;
        getline(stream, strDate, ' ');
        auto date = ParseDate(strDate);
        db.Find(date);
      }
      else if (task == "Print")
        db.Print();
      else if (!task.empty())
        cout << "Unknown command: " << task << endl;
    }
    catch (invalid_argument& ex) {
      cout << ex.what() << endl;
      return 1;
    }
    catch (exception&) {
      return 2;
    }
  }
  return 0;
}
