#include <string>
#include <map>
#include <iostream>

class Person {
public:
	Person(const std::string& iFirstName, const std::string& iLastName, const int iDate) : _yearOfBirth(iDate)
	{
		_changesOfFirstName.emplace(iDate, iFirstName);
		_changesOfLastName.emplace(iDate, iLastName);
	}
	void ChangeFirstName(int year, const std::string& firstName)
	{
		if (year >= _yearOfBirth)
			_changesOfFirstName.emplace(year, firstName);
	}
	void ChangeLastName(int year, const std::string& lastName)
	{
		if (year >= _yearOfBirth)
			_changesOfLastName.emplace(year, lastName);
	}

	//TODO: Refactor 2 next methods
	std::string GetFullName(const int year) const	{
		if (year < _yearOfBirth)
			return ("No person");
		if (_changesOfFirstName.empty() || _changesOfFirstName.begin()->first > year) {
			if (_changesOfLastName.empty() || _changesOfLastName.begin()->first > year)
				return("Incognito");
			return(findName(year, _changesOfLastName) + " with unknown first name");
		}
		if (_changesOfLastName.empty() || _changesOfLastName.begin()->first > year)
			return(findName(year, _changesOfFirstName) + " with unknown last name");
		return(findName(year, _changesOfFirstName) + " " + findName(year, _changesOfLastName));
	}

	std::string GetFullNameWithHistory(const int year) const {
		if (year < _yearOfBirth)
			return ("No person");
		if (_changesOfFirstName.empty() || _changesOfFirstName.begin()->first > year) {
			if (_changesOfLastName.empty() || _changesOfLastName.begin()->first > year)
				return("Incognito");
			return(findNameHistory(year, _changesOfLastName) + " with unknown first name");
		}
		if (_changesOfLastName.empty() || _changesOfLastName.begin()->first > year)
			return(findNameHistory(year, _changesOfFirstName) + " with unknown last name");
		return(findNameHistory(year, _changesOfFirstName) + " " + findNameHistory(year, _changesOfLastName));
	}
private:
	std::map<int, std::string> _changesOfFirstName;
	std::map<int, std::string> _changesOfLastName;
	int _yearOfBirth;
	std::string findName(const int iDate, const std::map<int, std::string>& iMap) const
	{
		std::string candidate;
		for (const auto& it : iMap) {
			if (it.first > iDate)
				return candidate;
			candidate = it.second;
		}
		return candidate;
	}
	std::string findNameHistory(const int iDate, const std::map<int, std::string>& iMap) const
	{
		std::string currentName;
		std::string result;
		bool curNameIsFirstName = true;
		bool curNameIsSecondName = false;
		bool uniqElem = false;
		bool firstBraceAdded = false;
		for (auto it = iMap.rbegin(); it != iMap.rend(); ++it) {
			if (it->first > iDate)
				continue;
			if (currentName == it->second)
				continue;
			if (curNameIsFirstName) {
				if (it == iMap.rend())
					uniqElem = true;
				result = it->second;
				currentName = it->second;
				curNameIsFirstName = false;
				curNameIsSecondName = true;
				continue;
			}
			if (!curNameIsSecondName)
				result += ", ";
			if (curNameIsSecondName) {
				result += " (";
				firstBraceAdded = true;
				curNameIsSecondName = false;
			}
			result += it->second;
			currentName = it->second;
		}
		if (firstBraceAdded)
			result += ")";
		return result;
	}
};
//
//int main() {
//	Person person("Polina", "Sergeeva", 1960);
//	for (int year : {1959, 1960}) {
//		std::cout << person.GetFullNameWithHistory(year) << std::endl;
//	}
//
//	person.ChangeFirstName(1965, "Appolinaria");
//	person.ChangeLastName(1967, "Ivanova");
//	for (int year : {1965, 1967}) {
//		std::cout << person.GetFullNameWithHistory(year) << std::endl;
//	}
//
//	return 0;
//}