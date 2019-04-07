#include <iostream>
#include <cmath>
#include "BSModel.h"
#include "RangeAccruals.h"
#include <iomanip>
using namespace std;

int main()
{
	double SMin = 100;
	double SMax = 110;
	int M = 1000000;
	int D = 252;
	double S0 = 105;
	double Sigma = 0.25;
	double r = 0.05;
	long N = 10;

	RangeAccrualOption OptionA(D, SMin, SMax, M);
	
	// Issue, the same rand is being called in the monte carlo, so its just one path over and over,.
	cout << fixed << setprecision(2);
	cout << "The value of the option is: " << OptionA.PriceByMonteCarlo(N, r, Sigma, S0) << endl;
	system("pause");

}