#include <iostream>
#include <sstream>

#include "database.h"


void Database::Add(const Date& date, const string& event)
{
  if(_dataBaseSet[date].emplace(event).second)
    _dataBaseVector[date].emplace_back(event);
}

bool Database::deleteEvent(const Date& date, const string& event)
{
  if (!_dataBaseVector.count(date))
    return false;
  auto it = find(_dataBaseVector.at(date).begin(), _dataBaseVector.at(date).end(), event);
  if (it != _dataBaseVector.at(date).end()) {
    _dataBaseVector.at(date).erase(it);
    if (_dataBaseVector.at(date).empty())
      _dataBaseVector.erase(date);
    return true;
  }
  return false;
}

void Database::findByDate(const Date& date) const
{
  if (_dataBaseVector.count(date))
    for (auto& e : _dataBaseVector.at(date))
      cout << e << endl;
}

void Database::Print(ostream& stream) const
{
  for (auto& d : _dataBaseVector)
    for (auto& e : d.second)
      stream << d.first << " " << e << endl;
}

vector<string> Database::FindIf(std::function<bool(const Date&, const string&)> isCorresponding) const
{
  vector<string> forPrint;
  for (auto& date : _dataBaseVector) {
    for (auto& event : date.second)
      if (isCorresponding(date.first, event)) {
        stringstream ss;
        ss << date.first << ' ' << event;
        forPrint.emplace_back(ss.str());
      }
  }
  return forPrint;
}

int Database::RemoveIf(std::function<bool(const Date&, const string&)> isCorresponding)
{
  int counter = 0;
  vector<Date> forDelete;
  for (auto& date : _dataBaseVector) {
    auto it = stable_partition(date.second.begin(), date.second.end(), [date, isCorresponding](const string& event)
    {
      return !isCorresponding(date.first, event);
    });
    if (it == date.second.end())
      continue;
    counter += date.second.end() - it;
    for (auto iter = it; iter != date.second.end(); ++iter)
      _dataBaseSet[date.first].erase(*iter);
    date.second.erase(it, date.second.end());
    if (date.second.empty())
      forDelete.emplace_back(date.first);
  }
  for (auto& dateIt : forDelete) {
    _dataBaseVector.erase(dateIt);
    _dataBaseSet.erase(dateIt);
  }
  return counter;
}

string Database::Last(const Date & date) const
{
  auto ubIt = _dataBaseVector.upper_bound(date);
  if (ubIt == _dataBaseVector.begin())
    throw invalid_argument("No such date");
  --ubIt;
  stringstream ss;
  ss << ubIt->first << ' ' << *(ubIt->second.rbegin());
  return ss.str();
}
