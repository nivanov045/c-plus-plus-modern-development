#include <iostream>
#include <exception>
using namespace std;

class Rational
{
public:
	Rational() : _numerator(0), _denominator(1)
	{
	}

	Rational(const int numerator, const int denominator)
	{
		if (denominator == 0)
			throw invalid_argument("Denominator is zero!");
		const auto divisor = FindGreatestCommonDivisor(abs(numerator), abs(denominator));
		const bool isPositive = (numerator > 0 && denominator > 0) || (numerator < 0 && denominator < 0);
		_numerator = abs(numerator) / divisor;
		_numerator *= isPositive ? 1 : -1;
		_denominator = abs(denominator) / divisor;
	}

	int Numerator() const
	{
		return _numerator;
	}

	void setNumerator(int numerator) { _numerator = numerator; }

	int Denominator() const
	{
		return _denominator;
	}

	void setDenominator(int denominator) { _denominator = denominator; }

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

Rational operator*(const Rational& lhs, const Rational& rhs)
{
	return Rational(lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator());
}

Rational operator/(const Rational& lhs, const Rational& rhs)
{
	if (rhs.Numerator() == 0)
		throw domain_error("Divided by zero!");
	return lhs * Rational(rhs.Denominator(), rhs.Numerator());
}


int main() {
    try {
        Rational r(1, 0);
        cout << "Doesn't throw in case of zero denominator" << endl;
        return 1;
    } catch (invalid_argument&) {
    }

    try {
        auto x = Rational(1, 2) / Rational(0, 1);
        cout << "Doesn't throw in case of division by zero" << endl;
        return 2;
    } catch (domain_error&) {
    }

    cout << "OK" << endl;
    return 0;
}
