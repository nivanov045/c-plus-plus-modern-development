#include <string>
#include <map>
//#include <iostream>

using namespace std;

class Person {
public:
  void ChangeFirstName(int year, const std::string& firstName)
  {
    _changesOfFirstName.emplace(year, firstName);
  }
  void ChangeLastName(int year, const std::string& lastName)
  {
    _changesOfLastName.emplace(year, lastName);
  }

  std::string GetFullName(int year) const
  {
    if (_changesOfFirstName.empty() || _changesOfFirstName.begin()->first > year) {
      if (_changesOfLastName.empty() || _changesOfLastName.begin()->first > year)
        return("Incognito");
      return(findName(year, _changesOfLastName) + " with unknown first name");
    }
    if (_changesOfLastName.empty() || _changesOfLastName.begin()->first > year)
      return(findName(year, _changesOfFirstName) + " with unknown last name");
    return(findName(year, _changesOfFirstName) + " " + findName(year, _changesOfLastName));
  }
private:
  std::map<int, std::string> _changesOfFirstName;
  std::map<int, std::string> _changesOfLastName;

  std::string findName(const int iDate, const std::map<int, std::string>& iMap) const
  {
    auto it = iMap.upper_bound(iDate);
    if (it == iMap.begin())
      return "";
    return (--it)->second;
  }
};

//int main() {
//  Person person;
//
//  person.ChangeFirstName(1965, "Polina");
//  person.ChangeLastName(1967, "Sergeeva");
//  for (int year : {1900, 1965, 1990}) {
//    cout << person.GetFullName(year) << endl;
//  }
//
//  person.ChangeFirstName(1970, "Appolinaria");
//  for (int year : {1969, 1970}) {
//    cout << person.GetFullName(year) << endl;
//  }
//
//  person.ChangeLastName(1968, "Volkova");
//  for (int year : {1969, 1970}) {
//    cout << person.GetFullName(year) << endl;
//  }
//  system("pause");
//  return 0;
//}