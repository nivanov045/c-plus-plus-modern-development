#include <iostream>
#include <string>
#include <ctime>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <vector>

using namespace std;

class Date
{
public:
  Date(int iYear, int iMonth, int iDay) : _day(iDay), _month(iMonth), _year(iYear) {}
  Date() = default;
  bool operator< (const Date& other) const
  {
    if (_year == other._year) {
      if (_month == other._month) {
        return _day < other._day;
      }
      return _month < other._month;
    }
    return _year < other._year;
  }
  
  bool operator== (const Date& other) const
  {
    return !(*this < other) && !(other < *this);
  }
  
  bool operator<= (const Date& other) const
  {
    return (*this < other) || (*this == other);
  }
  
  Date& operator++ ()
  {
    if (_month == 12 && _day == 31) {
      _month = 1;
      _day = 1;
      ++_year;
    } 
    else if (getCurMonthLength() == _day) {
      ++_month;
      _day = 1;
    } else {
      ++_day;
    }
    return *this;
  }
  
  time_t AsTimestamp() const
  {
    std::tm t;
    t.tm_sec = 0;
    t.tm_min = 0;
    t.tm_hour = 0;
    t.tm_mday = _day;
    t.tm_mon = _month - 1;
    t.tm_year = _year - 1900;
    t.tm_isdst = 0;
    return mktime(&t);
  }
  friend istream& operator>>(istream& iStream, Date& date);

private:
  int _day = 1;
  int _month = 1;
  int _year = 2000;

  bool isLeapYear() const {
    return ((_year % 4 == 0) && (!(_year % 100 == 0) && (_year % 400 != 0)));
  }

  int getCurMonthLength() {
    switch (_month) {
    case 1:
      return 31;
    case 2:
      return (28 + isLeapYear());
    case 3:
      return 31;
    case 4:
      return 30;
    case 5:
      return 31;
    case 6:
      return 30;
    case 7:
      return 31;
    case 8:
      return 31;
    case 9:
      return 30;
    case 10:
      return 31;
    case 11:
      return 30;
    case 12:
      return 31;
    default:
      return 0;
    }
  }
};

istream& operator>>(istream& iStream, Date& date)
{
  iStream >> date._year;
  iStream.ignore(1);
  iStream >> date._month;
  iStream.ignore(1);
  iStream >> date._day;
  return iStream;
}

int ComputeDaysDiff(const Date& date_to, const Date& date_from) {
  const time_t timestamp_to = date_to.AsTimestamp();
  const time_t timestamp_from = date_from.AsTimestamp();
  static const int SECONDS_IN_DAY = 60 * 60 * 24;
  return (timestamp_to - timestamp_from) / SECONDS_IN_DAY;
}

class Budget
{
public:
  Budget()
  {
    auto maxSize = ComputeDaysDiff({ 2099, 12, 31 }, { 2000, 01, 01 });
    _income.resize(maxSize, 0.0);
    _spending.resize(maxSize, 0.0);
    _newIncome.resize(maxSize, 0.0);
    resetNewIndexBoundary();
  }
  void Earn(const Date& iFrom, const Date& iTo, int iValue)
  {
    auto valToAdd = static_cast<double>(iValue) / (ComputeDaysDiff(iTo, iFrom) + 1);
    _firstIncome = std::min(_firstIncome, getIdxByDate(iFrom));
    _lastIncome= std::max(_lastIncome, getIdxByDate(iTo) + 1);
    _newIncome[getIdxByDate(iFrom)] += valToAdd;
    _newIncome[getIdxByDate(iTo) + 1] -= valToAdd;
    _hasNewIncoming = true;
    _wasFirstIncome = true;
  }
  void Spend(const Date& iFrom, const Date& iTo, int iValue)
  {
    auto valToAdd = static_cast<double>(iValue) / (ComputeDaysDiff(iTo, iFrom) + 1);
    std::transform(&_spending[getIdxByDate(iFrom)], &_spending[getIdxByDate(iTo) + 1], &_spending[getIdxByDate(iFrom)],
      [valToAdd](const double& el) {return el + valToAdd; });
  }

  double ComputeIncome(const Date& iFrom, const Date& iTo)
  { 
    perfomeIncoming();
    auto first = _wasFirstIncome ? std::accumulate(&_income[getIdxByDate(iFrom)], &_income[getIdxByDate(iTo) + 1], 0.0) :
      0.0;
    auto second = std::accumulate(&_spending[getIdxByDate(iFrom)], &_spending[getIdxByDate(iTo) + 1], 0.0);
    return first - second;
  }

  void PayTax(const Date& iFrom, const Date& iTo, int iPercentage = 13)
  { 
    perfomeIncoming();
    std::transform(&_income[getIdxByDate(iFrom)], &_income[getIdxByDate(iTo) + 1], &_income[getIdxByDate(iFrom)],
      [iPercentage](const double& el) {return el * (100 - iPercentage) * 0.01; });
  }

private:
  vector<double> _income;
  vector<double> _spending;

  vector<double> _newIncome;
  int _firstIncome;
  int _lastIncome;
  bool _hasNewIncoming = false;

  bool _wasFirstIncome = false;

  static int getIdxByDate(const Date& iDate)
  {
    Date firstDate(2000, 01, 01);
    return ComputeDaysDiff(iDate, firstDate);
  }

  void resetNewIndexBoundary() {
    _firstIncome = _newIncome.size() - 1;
    _lastIncome = 0;
  }

  void perfomeIncoming() {
    if (!_hasNewIncoming)
      return;
    auto sum = 0.0;
    for (auto idx = _firstIncome; idx <= _lastIncome; ++idx) {
      sum += _newIncome[idx];
      _newIncome[idx] = 0;
      _income[idx] += sum;
    }
    resetNewIndexBoundary();
  }
};

int main(int argc, char* argv[])
{
  auto numOfQueries = 0;
  cin >> numOfQueries;
  Budget budget;
  for (int i = 0; i < numOfQueries; ++i) {
    string comand;
    cin >> comand;
    Date from, to;
    cin >> from >> to;
    if (comand == "Earn") {
      int value;
      cin >> value;
      budget.Earn(from, to, value);
    }
    else if (comand == "Spend") {
      int value;
      cin >> value;
      budget.Spend(from, to, value);
    }
    else if (comand == "ComputeIncome") {
      cout << setprecision(25) << budget.ComputeIncome(from, to) << endl;
    }
    else if (comand == "PayTax") {
      int percentage;
      cin >> percentage;
      budget.PayTax(from, to, percentage);
    }
    else
      break;
  }
  system("pause");
  return 0;
}
