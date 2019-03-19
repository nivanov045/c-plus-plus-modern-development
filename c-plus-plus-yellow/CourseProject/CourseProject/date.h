#pragma once
#include <string>

using namespace std;

class Date
{
public:
  Date(int iYear, int iMonth, int iDay);
  ~Date() = default;

  int GetYear() const { return _year; }
  int GetMonth() const { return _month; }
  int GetDay() const { return _day; }

private:
  int _year;
  int _month;
  int _day;
};

ostream& operator<< (ostream& stream, const Date& date);


bool operator<(const Date& lhs, const Date& rhs);