#include <iostream>

int main()
{
	double N = 0, A = 0, B = 0, X = 0, Y = 0;
	std::cin >> N >> A >> B >> X >> Y;
	double discount = 0;
	if ((N > A) && (N <= B))
		discount = X;
	else if (N > B)
		discount = Y;
	std::cout << N / 100 * (100 - discount) << std::endl;
	return 0;
}
