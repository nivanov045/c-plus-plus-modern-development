#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

int main(int argc, char* argv[])
{
	int N = 0;
	std::cin >> N;
	std::vector<std::string> S;
	for (int i = 0; i < N; i++) {
		std::string tmp;
		std::cin >> tmp;
		S.emplace_back(tmp);
	}
	std::sort(S.begin(), S.end(), [](std::string first, std::string second)
	{
		std::transform(first.begin(), first.end(), first.begin(), ::tolower);
		std::transform(second.begin(), second.end(), second.begin(), ::tolower);
		return first<  second ? 1 : 0;
	});
	for (const auto& v : S) {
		std::cout << v << " ";
	}
	return 0;
}
