#include <string>
#include <map>
#include <iostream>

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

	//TODO: Refactor 2 next methods
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

	std::string GetFullNameWithHistory(int year) {
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

	std::string findName(int iDate, const std::map<int, std::string>& iMap) const
	{
		std::string candidate;
		for (const auto& it : iMap) {
			if (it.first > iDate)
				return candidate;
			candidate = it.second;
		}
		return candidate;
	}
	std::string findNameHistory(int iDate, const std::map<int, std::string>& iMap) const
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

//int main() {
//	Person person;
//
//	person.ChangeFirstName(1900, "Eugene");
//	person.ChangeLastName(1900, "Sokolov");
//	person.ChangeLastName(1910, "Sokolov");
//	person.ChangeFirstName(1920, "Evgeny");
//	person.ChangeLastName(1930, "Sokolov");
//	std::cout << person.GetFullNameWithHistory(1940) << std::endl;
//
//	system("pause");
//	return 0;
//}

//int main() {
//	Person person;
//
//	person.ChangeFirstName(1965, "Polina");
//	person.ChangeLastName(1967, "Sergeeva");
//	for (int year : {1900, 1965, 1990}) {
//		std::cout << person.GetFullNameWithHistory(year) << std::endl;
//	}
//
//	person.ChangeFirstName(1970, "Appolinaria");
//	for (int year : {1969, 1970}) {
//		std::cout << person.GetFullNameWithHistory(year) << std::endl;
//	}
//
//	person.ChangeLastName(1968, "Volkova");
//	for (int year : {1969, 1970}) {
//		std::cout << person.GetFullNameWithHistory(year) << std::endl;
//	}
//
//	person.ChangeFirstName(1990, "Polina");
//	person.ChangeLastName(1990, "Volkova-Sergeeva");
//	std::cout << person.GetFullNameWithHistory(1990) << std::endl;
//
//	person.ChangeFirstName(1966, "Pauline");
//	std::cout << person.GetFullNameWithHistory(1966) << std::endl;
//
//	person.ChangeLastName(1960, "Sergeeva");
//	for (int year : {1960, 1967}) {
//		std::cout << person.GetFullNameWithHistory(year) << std::endl;
//	}
//
//	person.ChangeLastName(1961, "Ivanova");
//	std::cout << person.GetFullNameWithHistory(1967) << std::endl;
//	system("pause");
//
//	return 0;
//}