#include <iostream>
#include <string>

/*� ����������� ������ ���� ��� ������, ���������� ��������. ������ ������ ������� 
 *�� �������� ��������� ���� � ����� ����� �� ����� 30 ��������. �������� � ����������� 
 *����� ����������������� ����������� �� ���.*/

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
