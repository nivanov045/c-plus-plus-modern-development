#include "date.h"

#include <iomanip>

Date::Date(int iYear, int iMonth, int iDay) :
  _year(iYear), _month(iMonth), _day(iDay)
{
  if (iMonth > 12 || iMonth < 1)
    throw invalid_argument("Month value is invalid: " + to_string(iMonth));
  if (iDay > 31 || iDay < 1)
    throw invalid_argument("Day value is invalid: " + to_string(iDay));
}



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

ostream& operator<<(ostream& stream, const Date& d)
{
  stream << setw(4) << setfill('0') << d.GetYear() << "-" << setw(2) << setfill('0') << d.GetMonth() <<
    "-" << setw(2) << setfill('0') << d.GetDay();
  return stream;
}
