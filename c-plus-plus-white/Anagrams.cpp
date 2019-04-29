#include <iostream>
#include <map>
#include <string>

std::map<char, int> BuildCharCounters(const std::string& iS)
{
	std::map<char, int> result;
	for (const auto& s : iS)
		result[s]++;
	return result;
}

int main(int argc, char* argv[])
{
	int N = 0;
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::string	s1, s2;
		std::cin >> s1 >> s2;
		if (BuildCharCounters(s1) == BuildCharCounters(s2))
			std::cout << "YES";
		else
			std::cout << "NO";
		std::cout << std::endl;
	}
	system("pause");
	return 0;
}
