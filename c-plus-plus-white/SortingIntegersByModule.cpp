#include <iostream>
#include <vector>
#include <algorithm>
#include <valarray>

int main(int argc, char* argv[])
{
	int N = 0;
	std::cin >> N;
	std::vector<int> A;
	for (int i = 0; i < N; i++) {
		int tmp = 0;
		std::cin >> tmp;
		A.emplace_back(tmp);
	}
	std::sort(A.begin(), A.end(), [](int first, int second)
	{
		return std::abs(first) < std::abs(second) ? 1 : 0;
	});
	for (const auto v : A) {
		std::cout << v << " ";
	}
	return 0;
}
