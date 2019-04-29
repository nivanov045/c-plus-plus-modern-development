#include <iostream>
using namespace std;

class Rational
{
public:
	Rational() : _numerator(0), _denominator(1)
	{
	}

	Rational(int numerator, int denominator)
	{
		const auto divisor = FindGreatestCommonDivisor(abs(numerator), abs(denominator));
		bool isPositive = false;
		isPositive = (numerator > 0 && denominator > 0) || (numerator < 0 && denominator < 0);
		_numerator = abs(numerator) / divisor;
		_numerator *= isPositive ? 1 : -1;
		_denominator = abs(denominator) / divisor;
	}

	int Numerator() const
	{
		return _numerator;
	}

	int Denominator() const
	{
		return _denominator;
	}

private:
	static int FindGreatestCommonDivisor(int lhs, int rhs)
	{
		while ((lhs > 0) && (rhs > 0)) {
			if (lhs > rhs)
				lhs %= rhs;
			else
				rhs %= lhs;
		}
		return lhs + rhs;
	}

	int _numerator;
	int _denominator;
};

bool operator==(const Rational& lhs, const Rational& rhs)
{
	return lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator();
}

Rational operator+(const Rational& lhs, const Rational& rhs)
{
	return Rational(lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator(),
		lhs.Denominator() * rhs.Denominator());
}

Rational operator-(const Rational& lhs, const Rational& rhs)
{
	return lhs + Rational(-rhs.Numerator(), rhs.Denominator());
}

Rational operator*(const Rational& lhs, const Rational& rhs)
{
	return Rational(lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator());
}

Rational operator/(const Rational& lhs, const Rational& rhs)
{
	return lhs * Rational(rhs.Denominator(), rhs.Numerator());
}

int main() {
    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a * b;
        bool equal = c == Rational(8, 9);
        if (!equal) {
            cout << "2/3 * 4/3 != 8/9" << endl;
            return 1;
        }
    }

    {
        Rational a(5, 4);
        Rational b(15, 8);
        Rational c = a / b;
        bool equal = c == Rational(2, 3);
        if (!equal) {
            cout << "5/4 / 15/8 != 2/3" << endl;
            return 2;
        }
    }

    cout << "OK" << endl;
    return 0;
}
