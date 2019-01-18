#include <iostream>
#include <string>
#include <map>

int main(int argc, char* argv[])
{
	int Q = 0;
	std::cin >> Q;
	std::map<std::string, std::string> directory;
	for (int i = 0; i < Q; ++i) {
		std::string command;
		std::cin >> command;
		if (command == "CHANGE_CAPITAL") {
			std::string country;
			std::string newCapital;
			std::cin >> country >> newCapital;
			if (!directory.count(country)) {
				std::cout << "Introduce new country " << country << " with capital " << newCapital << std::endl;
				directory[country] = newCapital;
			}
			else if (directory.at(country) == newCapital)
				std::cout << "Country " << country << " hasn't changed its capital" << std::endl;
			else {
				std::cout << "Country " << country << " has changed its capital from " << directory.at(country) 
				<< " to " << newCapital << std::endl;
				directory.at(country) = newCapital;
			}
		}
		else if (command == "RENAME") {
			std::string oldCountryName;
			std::string newCountryName;
			std::cin >> oldCountryName >> newCountryName;
			if (!directory.count(oldCountryName) || (oldCountryName == newCountryName) || directory.count(newCountryName)) {
				std::cout << "Incorrect rename, skip" << std::endl;
			}
			else {
				std::cout << "Country " << oldCountryName << " with capital " << directory.at(oldCountryName)
					<< " has been renamed to " << newCountryName << std::endl;
				directory[newCountryName] = directory.at(oldCountryName);
				directory.erase(oldCountryName);
			}
		}
		else if (command == "ABOUT") {
			std::string country;
			std::cin >> country;
			if (!directory.count(country))
				std::cout << "Country " << country << " doesn't exist" << std::endl;
			else {
				std::cout << "Country " << country << " has capital " << directory.at(country) << std::endl;
			}
		}
		else { //command == "DUMP"
			if (directory.empty())
				std::cout << "There are no countries in the world" << std::endl;
			else {
				for (const auto& c : directory) {
					std::cout << c.first << "/" << c.second << " ";
				}
				std::cout << std::endl;
			}
		}
	}
	system("pause");
	return 0;
}
