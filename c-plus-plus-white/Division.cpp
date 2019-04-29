#include <iostream>

int  main()
{
	int a = 0, b = 0;
	std::cin >> a >> b;
	if (b == 0)
		std::cout << "Impossible";
	else
		std::cout << a / b;
	return 0;
}
