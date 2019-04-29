#include <iostream>
#include <set>
#include <string>

int main(int argc, char* argv[])
{
	int N = 0;
	std::cin >> N;
	std::set<std::string> uniqStrings;
	for (int i = 0; i < N; i++) {
		std::string s;
		std::cin >> s;
		uniqStrings.emplace(s);
	}
	std::cout << uniqStrings.size();
	return 0;
}
