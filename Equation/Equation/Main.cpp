#include <iostream>
#include <cmath>

int main()
{
	double A = 0, B = 0, C = 0;
	std::cin >> A >> B >> C;
	if (A == 0) {
		if (B != 0)
		std::cout << -C / B;
	}
	else {
		const double D = B * B - 4 * A * C;
		if (D < 0)
			return 0;

		std::cout << (-B - sqrt(D)) / (2 * A);
		if (D != 0)
			std::cout << " " << (-B + sqrt(D)) / (2 * A);
	}
	return 0;
}
