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
	if (n == 1)
		revBinNum.emplace_back(1);
	for (auto it = revBinNum.rbegin(); it != revBinNum.rend(); ++it) {
		std::cout << static_cast<int>(*it);
	}
	/*system("pause");*/
	return 0;
}
