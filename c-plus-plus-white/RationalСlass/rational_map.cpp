#include <iostream>
#include <map>
#include <set>
#include <vector>
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
    {
        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            v.push_back(x);
        }
        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}
