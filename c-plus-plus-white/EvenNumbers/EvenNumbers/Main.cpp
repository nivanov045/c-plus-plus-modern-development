#include <iostream>

int main()
{
	int a = 1, b = 1;
	std::cin >> a >> b;
	auto lBound = a;
	if (a % 2 != 0)
		lBound++;
	for (auto it = lBound; it <= b; it += 2)
		std::cout << it << " ";
	system("pause");
	return 0;
}
