#include <iostream>
#include <exception>
#include <tuple>
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
			throw invalid_argument("Invalid argument");
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

bool operator==(const Rational& lhs, const Rational& rhs)
{
	return lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator();
}

bool operator<(const Rational& lhs, const Rational& rhs)
{
	return lhs.Numerator()*rhs.Denominator() < rhs.Numerator()*lhs.Denominator();
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
	if (rhs.Numerator() == 0)
		throw domain_error("Division by zero");
	return lhs * Rational(rhs.Denominator(), rhs.Numerator());
}

ostream& operator<<(ostream& stream, const Rational& rational)
{
	stream << rational.Numerator() << "/" << rational.Denominator();
	return stream;
}

istream& operator>>(istream& stream, Rational& rational)
{
	int numerator = rational.Numerator();
	int denominator = rational.Denominator();
	stream >> numerator;
	stream.ignore(1);
	stream >> denominator;
	rational = { numerator, denominator };
	return stream;
}

int main() {
	try {
		Rational firstRational, secondRational;
		cin >> firstRational;
		cin.ignore(1);
		char operation;
		cin >> operation;
		cin.ignore(1);
		cin >> secondRational;
		if (operation == '+')
			cout << firstRational + secondRational << endl;
		else if(operation == '-')
			cout << firstRational - secondRational << endl;
		else if(operation == '*')
			cout << firstRational * secondRational << endl;
		else
			cout << firstRational / secondRational << endl;
	}
	catch (invalid_argument& ex) {
		cout << ex.what() << endl;;
	}
	catch (domain_error& ex) {
		cout << ex.what() << endl;;
	}
	return 0;
}
