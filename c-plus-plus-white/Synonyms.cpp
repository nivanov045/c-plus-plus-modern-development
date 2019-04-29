#include <iostream>
#include <string>
#include <set>
#include <mutex>
#include <map>
#include <vector>
#include <algorithm>

int main(int argc, char* argv[])
{
	int Q = 0;
	std::cin >> Q;
	std::map<std::string, std::set<std::string>> dict;
	for (int i = 0; i < Q; i++) {
		std::string command;
		std::cin >> command;
		if (command == "ADD") {
			std::string word1, word2;
			std::cin >> word1 >> word2;
			dict[word1].emplace(word2);
			dict[word2].emplace(word1);
		}
		else if (command == "COUNT") {
			std::string word;
			std::cin >> word;
			std::cout << dict[word].size() << std::endl;
		}
		else {	//command == CHECK
			std::string word1, word2;
			std::cin >> word1 >> word2;
			if (dict[word1].find(word2) == dict[word1].end())
				std::cout << "NO" << std::endl;
			else {
				std::cout << "YES" << std::endl;
			}
		}
	}
	return 0;
}
