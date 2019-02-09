#include <fstream>
#include <iomanip>
#include <iostream>

int main(int argc, char* argv[])
{
	std::ifstream input("input.txt");
	//std::ofstream output("output.txt");
	int N = 0, M = 0;
	if (!input)
		return 0;
	input >> N >> M;
	for (int i = 0; i < N; ++i) {
		int tmp = 0;
		for (int j = 0; j < M - 1; ++j) {
			input >> tmp;
			input.ignore(1);
			std::cout << std::setw(10) << tmp << " ";
		}
		input >> tmp;
		std::cout << std::setw(10) << tmp;
		if (i != N - 1)
			std::cout << std::endl;
	}
	return 0;
}
