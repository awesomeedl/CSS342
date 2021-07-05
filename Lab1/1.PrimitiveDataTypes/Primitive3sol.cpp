/*
*  Primitive3.cpp
*
*  Created by Yang Peng
*
*/

#include <iostream>
#include <cmath>
using namespace std;

int roundUp(double f) {
	int roudupValue = static_cast<int>(f + 0.5);
	int convertedIntValue = static_cast<int>(f);
	if (roudupValue > convertedIntValue) {
		return roudupValue;
	}
	return convertedIntValue;
}

int main()
{
	double a, b, c;

	a = 0.4;
	b = 0.5;
	c = 0.6;
	cout << "double(" << a <<") is rounded up to " << round(a) << " using cmath::round()" << endl;
	cout << "double(" << b << ") is rounded up to " << round(b) << " using cmath::round()" << endl;
	cout << "double(" << c << ") is rounded up to " << round(c) << " using cmath::round()" << endl;
	cout << "double(" << a << ") is rounded up to " << roundUp(a) << " using roundUp()" << endl;
	cout << "double(" << b << ") is rounded up to " << roundUp(b) << " using roundUp()" << endl;
	cout << "double(" << c << ") is rounded up to " << roundUp(c) << " using roundUp()" << endl;

	a = 1.4;
	b = 2.5;
	c = 3.6;
	cout << "double(" << a << ") is rounded up to " << round(a) << " using cmath::round()" << endl;
	cout << "double(" << b << ") is rounded up to " << round(b) << " using cmath::round()" << endl;
	cout << "double(" << c << ") is rounded up to " << round(c) << " using cmath::round()" << endl;
	cout << "double(" << a << ") is rounded up to " << roundUp(a) << " using roundUp()" << endl;
	cout << "double(" << b << ") is rounded up to " << roundUp(b) << " using roundUp()" << endl;
	cout << "double(" << c << ") is rounded up to " << roundUp(c) << " using roundUp()" << endl;

    return 0;

}
