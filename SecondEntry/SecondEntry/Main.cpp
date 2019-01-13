#include <string>
#include <iostream>

int main()
{
	int firstIdx = -1, secondIdx = -1;
	std::string str;
	std::cin >> str;
	firstIdx = str.find('f');
	if (firstIdx == -1)
		std::cout << -2 << std::endl;
	else {
		secondIdx = str.find('f', firstIdx + 1);
		if (secondIdx == -1)
			std::cout << -1 << std::endl;
		else {
			std::cout << secondIdx << std::endl;
		}
	}
	//system("pause");
	return 0;
}
