#include <iostream>
#include <map>
#include <vector>
#include <string>

int main(int argc, char* argv[])
{
	int Q = 0;
	std::cin >> Q;
	std::map<std::vector<std::string>, int> routs;
	int numOfRout = 1;
	for (int i = 0; i < Q; i++) {
		int N = 1;
		std::cin >> N;
		std::string s;
		std::vector<std::string> curRout;
		for (int j = 0; j < N; j++) {
			std::cin >> s;
			curRout.emplace_back(s);
		}
		if (routs.count(curRout)) {
			std::cout << "Already exists for " << routs.at(curRout) << std::endl;
		}
		else {
			routs[curRout] = numOfRout;
			std::cout << "New bus " << numOfRout << std::endl;
			numOfRout++;
		}
	}
	return 0;
}
