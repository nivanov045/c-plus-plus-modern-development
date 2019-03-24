#include "airline_ticket.h"
#include "test_runner.h"
#include <map>
#include <iomanip>

using namespace std;

#define UPDATE_FIELD(ticket, field, values){ \
  map<string, string>::const_iterator it; \
  it = values.find(#field);  \
  if (it != values.end()){  \
    istringstream is(it->second); \
    is >> ticket.field; \
  } \
}

bool operator< (const Date& lDate, const Date& rDate) {
  return  lDate.year < rDate.year ||
    lDate.year == rDate.year && (lDate.month < rDate.month ||
      lDate.month == rDate.month && lDate.day < rDate.day);
}

bool operator== (const Date& lDate, const Date& rDate) {
  return !(lDate < rDate) && !(rDate < lDate);
}

ostream& operator<<(ostream& stream, const Date& d)
{
  stream << d.year << "-" << d.month << "-" << d.day;
  return stream;
}

Date ParseDate(istream& stream) {
  int year = 0, month = 0, day = 0;
  if (!(stream >> year))
    throw invalid_argument("Wrong date format");
  if (stream.peek() != '-')
    throw invalid_argument("Wrong date format");
  stream.ignore(1);
  if (!(stream >> month))
    throw invalid_argument("Wrong date format");
  if (stream.peek() != '-')
    throw invalid_argument("Wrong date format");
  stream.ignore(1);
  if (!(stream >> day))
    throw invalid_argument("Wrong date format");
  return { year, month, day };
}

istream& operator>>(istream& stream, Date& d)
{
  d = ParseDate(stream);
  return stream;
}

bool operator< (const Time& lTime, const Time& rTime)
{
  return  lTime.hours < rTime.hours ||
    lTime.hours == rTime.hours && lTime.minutes < rTime.minutes;
}

bool operator== (const Time& lTime, const Time& rTime)
{
  return !(lTime < rTime) && !(rTime < lTime);
}


ostream& operator<<(ostream& stream, const Time& t)
{
  stream << t.hours << ":" << t.minutes;
  return stream;
}

Time ParseTime(istream& stream) {
  int hours = 0, minutes = 0;
  if (!(stream >> hours))
    throw invalid_argument("Wrong date format");
  if (stream.peek() != ':')
    throw invalid_argument("Wrong date format");
  stream.ignore(1);
  if (!(stream >> minutes))
    throw invalid_argument("Wrong date format");
  return { hours, minutes };
}

istream& operator>>(istream& stream, Time& t)
{
  t = ParseTime(stream);
  return stream;
}

void TestUpdate() {
  AirlineTicket t;
  t.price = 0;

  const map<string, string> updates1 = {
    {"departure_date", "2018-2-28"},
    {"departure_time", "17:40"},
  };
  UPDATE_FIELD(t, departure_date, updates1);
  UPDATE_FIELD(t, departure_time, updates1);
  UPDATE_FIELD(t, price, updates1);

  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 0);

  const map<string, string> updates2 = {
    {"price", "12550"},
    {"arrival_time", "20:33"},
  };
  UPDATE_FIELD(t, departure_date, updates2);
  UPDATE_FIELD(t, departure_time, updates2);
  UPDATE_FIELD(t, arrival_time, updates2);
  UPDATE_FIELD(t, price, updates2);

  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 12550);
  ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestUpdate);
}
