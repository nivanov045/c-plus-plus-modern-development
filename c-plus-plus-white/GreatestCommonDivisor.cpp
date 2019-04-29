#include <iostream>

int main()
{
	int a = 0, b = 0;
	std::cin >> a >> b;
	while ((a > 0) && (b > 0)) {
		if (a > b)
			a %= b;
		else
			b %= a;
	}
	std::cout << a + b << std::endl;
	//system("pause");
	return 0;
}
