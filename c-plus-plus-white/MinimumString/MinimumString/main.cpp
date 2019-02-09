#include <iostream>
#include <string>

/*В стандартном потоке даны три строки, разделённые пробелом. Каждая строка состоит 
 *из строчных латинских букв и имеет длину не более 30 символов. Выведите в стандартный 
 *вывод лексикографически минимальную из них.*/

int main()
{
	std::string str1, str2, str3;
	std::cin >> str1 >> str2 >> str3;
	std::string min = str1;
	if (str2 < min)
		min = str2;
	if (str3 < min)
		min = str3;
	std::cout << min;
	return 0;
}
