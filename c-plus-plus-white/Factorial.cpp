//#include <iostream>
//
//int Factorial(int x);
//
//int main()
//{
//	std::cout << Factorial(5);
//	system("pause");
//	return 0;
//}

int Factorial(int x) {
	if (x <= 0)
		return 1;
	return x * Factorial(x - 1);
}
