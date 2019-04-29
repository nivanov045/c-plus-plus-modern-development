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
};

//int main() {
//	Person person;
//	person.ChangeFirstName(1965, "Polina");
//	person.ChangeLastName(1967, "Sergeeva");
//	for (int year : {1964, 1965, 1966, 1967, 1968}) {
//		std::cout << person.GetFullName(year) << std::endl;
//	}
//
//	Person person2;
//	for (int year : {1964, 1965, 1966, 1967, 1968}) {
//		std::cout << person2.GetFullName(year) << std::endl;
//	}
//
//	Person person3;
//	person3.ChangeLastName(1965, "Sergeeva");
//	person3.ChangeFirstName(1967, "Polina");
//	for (int year : {1964, 1965, 1966, 1967, 1968}) {
//		std::cout << person3.GetFullName(year) << std::endl;
//	}
//	system("pause");
//	return 0;
//}