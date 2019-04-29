#include <iostream>
#include <string>
#include <map>
#include <vector>

int main(int argc, char* argv[])
{
	int Q = 0;
	std::cin >> Q;
	std::map<std::string, std::vector<std::string>> buses;
	std::map<std::string, std::vector<std::string>> stops;
	for (int i = 0; i < Q; ++i) {
		std::string command;
		std::cin >> command;
		if (command == "NEW_BUS") {
			std::string bus;
			std::cin >> bus;
			int stopCount = 0;
			std::cin >> stopCount;
			std::vector<std::string> stopsForCurBus;
			for (int j = 0; j < stopCount; j++) {
				std::string stop;
				std::cin >> stop;
				stopsForCurBus.emplace_back(stop);
				if (!stops.count(stop))
					stops[stop] = std::vector<std::string>(1, bus);
				else
					stops[stop].emplace_back(bus);
			}
			buses[bus] = stopsForCurBus;
		}
		else if (command == "BUSES_FOR_STOP") {
			std::string stop;
			std::cin >> stop;
			if(!stops.count(stop))
				std::cout << "No stop" << std::endl;
			else {
				for (const auto& b : stops.at(stop)) {
					std::cout << b << " ";
				}
				std::cout << std::endl;
			}
		}
		else if (command == "STOPS_FOR_BUS") {
			std::string bus;
			std::cin >> bus;
			if (!buses.count(bus))
				std::cout << "No bus" << std::endl;
			else {
				for (const auto& s : buses.at(bus)) {
					std::cout << "Stop " << s << ": ";
					if (stops.at(s).size() == 1)
						std::cout << "no interchange" << std::endl;
					else {
						for (const auto& b : stops.at(s)) {
							if (b != bus)
								std::cout << b << " ";
						}
						std::cout << std::endl;
					}
				}
			}
		}
		else {	//command == "ALL_BUSES"
			if (buses.empty()) {
				std::cout << "No buses" << std::endl;
			}
			else
				for (const auto& b : buses) {
					std::cout << "Bus " << b.first <<": ";
					for (const auto& s : b.second)
						std::cout << s << " ";
					std::cout << std::endl;
				}
		}
	}
	system("pause");
	return 0;
}
