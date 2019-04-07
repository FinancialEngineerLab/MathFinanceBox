#include <iostream>
#include <cmath>
#include "Functions.h"
#include "DefInt.h"
using namespace std;

int main()
{
	int N = 10000;
	//S0, sigma, r, t, K.
	EurCallOption CallOption(80.0, 0.1,
		0.06, 1.0, 100);
	// integral from and to, from cannot be 0. And object of class which we wish to integrate.
	DefInt CallInt(0.0001, 500.0, CallOption);
	cout << "The approximate value of the call option is: " << CallInt.ByTrapezoid(N) << endl;
	EurPutOption PutOption(80.0, 0.1,
		0.06, 1.0, 100);
	DefInt PutInt(0.0001, 500.0, PutOption);
	cout << "The approximate value of the put option is: " << PutInt.ByTrapezoid(N) << endl;
	system ("pause");
}