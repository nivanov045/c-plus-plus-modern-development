//#include <iostream>
#include <string>
#include <vector>

bool IsPalindrom(std::string s)
{
	if (s.length() == 0)
		return true;
	int i = 0, j = s.length() - 1;
	while (i < j) {
		if (s.at(i) != s.at(j))
			return false;
		++i;
		--j;
	}
	return true;
}

std::vector<std::string> PalindromFilter(std::vector<std::string> words, int minLength)
{
	std::vector<std::string> answer;
	for (const auto& w : words) {
		if ((IsPalindrom(w)) && (w.length() >= minLength))
			answer.emplace_back(w);
	}
	return answer;
}

//int main(int argc, char* argv[])
//{
//	const std::vector<std::string> words = { "weew", "bro", "code" };
//	auto answer = PalindromFilter(words, 4);
//	for (const auto& a : answer) {
//		std::cout << a << ", ";
//	}
//	std::cout << std::endl;
//	
//	system("pause");
//	return 0;
//}
