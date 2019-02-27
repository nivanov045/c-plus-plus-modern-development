#include "phone_number.h"
#include <sstream>

PhoneNumber::PhoneNumber(const string & international_number)
{
  stringstream ss(international_number);
  char symb;
  if (ss.peek() != '+')
    throw invalid_argument("First symbol is not +");
  ss.ignore(1);
  stringstream tmp;
  while (ss.peek() != '-' && ss.peek() != EOF) {
    char s;
    ss >> s;
    tmp << s;
  }
  if (ss.peek() != '-')
    throw invalid_argument("No city code!");
  country_code_ = tmp.str();
  if (country_code_.length() == 0)
    throw invalid_argument("No country code!");
  tmp.str(string());
  ss.ignore(1);
  while (ss.peek() != '-' && ss.peek() != EOF) {
    char s;
    ss >> s;
    tmp << s;
  }
  if (ss.peek() != '-')
    throw invalid_argument("No local number!");
  city_code_= tmp.str();
  if (city_code_.length() == 0)
    throw invalid_argument("No city code!");
  tmp.str(string());
  ss.ignore(1);
  while (ss.peek() != EOF) {
    char s;
    ss >> s;
    tmp << s;
  }
  local_number_= tmp.str();
  if (local_number_.length() == 0)
    throw invalid_argument("No local number!");
}

string PhoneNumber::GetCountryCode() const
{
  return country_code_;
}

string PhoneNumber::GetCityCode() const
{
  return city_code_;
}

string PhoneNumber::GetLocalNumber() const
{
  return local_number_;
}

string PhoneNumber::GetInternationalNumber() const
{
  stringstream ss;
  ss << "+" << country_code_ << "-" << city_code_ << "-" << local_number_;
  return ss.str();
}
