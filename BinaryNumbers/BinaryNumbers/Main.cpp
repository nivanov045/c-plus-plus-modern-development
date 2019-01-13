#include <iostream>
#include <vector>

int main()
{
	int n = 1;
	std::cin >> n;
	std::vector<bool> revBinNum;
	while (n > 1) {
		revBinNum.emplace_back(n % 2);
		n /= 2;
	};
	for (auto it = revBinNum.rbegin(); it > = revBinNum.begin(); --it) {
		
	}
	system("pause");
	return 0;
}
