#pragma once
#include <string>
#include <map>
#include <vector>
#include <functional>
#include <unordered_set>

#include "date.h"
#include <queue>
#include <set>


using namespace std;

class Database
{
public:
  Database() = default;
  ~Database() = default;

  void Add(const Date& date, const string& event);

  void Print(ostream& stream) const;

  //std::function<double(const TransformedTooth&, const Vector3&)> iDistance,
  vector<string> FindIf(std::function<bool(const Date&, const string&)> isCorresponding) const;

  int RemoveIf(std::function<bool(const Date&, const string&)> isCorresponding);

  string Last(const Date& date) const;

private:
  bool deleteEvent(const Date& date, const string& event);

  void findByDate(const Date& date) const;

  map<Date, vector<string>> _dataBaseVector;
  map<Date, set<string>> _dataBaseSet;
};
