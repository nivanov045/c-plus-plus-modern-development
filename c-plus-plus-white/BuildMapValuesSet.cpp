#include <string>
#include <map>
#include <set>
#include <iostream>

std::set<std::string> BuildMapValuesSet(const std::map<int, std::string>& m) {
	std::set<std::string> result;
	for (const auto& v : m)
		result.emplace(v.second);
	return result;
}
