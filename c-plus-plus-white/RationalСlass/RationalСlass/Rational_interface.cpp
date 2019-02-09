#include <iostream>
using namespace std;

class Rational {
public:
    Rational() :_numerator(0), _denominator(1)
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

	int Numerator() const {
		return _numerator;
    }

    int Denominator() const {
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

int main() {
    {
        const Rational r(3, 10);
        if (r.Numerator() != 3 || r.Denominator() != 10) {
            cout << "Rational(3, 10) != 3/10" << endl;
            return 1;
        }
    }

    {
        const Rational r(8, 12);
        if (r.Numerator() != 2 || r.Denominator() != 3) {
            cout << "Rational(8, 12) != 2/3" << endl;
            return 2;
        }
    }

    {
        const Rational r(-4, 6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(-4, 6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(4, -6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(4, -6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(0, 15);
        if (r.Numerator() != 0 || r.Denominator() != 1) {
            cout << "Rational(0, 15) != 0/1" << endl;
            return 4;
        }
    }

    {
        const Rational defaultConstructed;
        if (defaultConstructed.Numerator() != 0 || defaultConstructed.Denominator() != 1) {
            cout << "Rational() != 0/1" << endl;
            return 5;
        }
    }

    cout << "OK" << endl;
    return 0;
}
