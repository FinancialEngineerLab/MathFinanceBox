#include "UpAndOutEurCall.h"
#include <iostream>
#include <cmath>

using namespace std;

int main()
{

	double r = 0.05;
	double sigma = 0.2;
	double Time = 1;
	int N = 50000;
	double delta = Time / N;
	double S0 = 98;
	double K = 100;
	double B = 130;
	long double R = exp(r*delta);
	double U = exp(sigma*sqrt(delta));
//	double U = exp((r - 0.5*pow(sigma, 2))*delta + sigma*sqrt(delta));
	cout << "The U is: " << U << endl;
	double D = exp(-sigma * sqrt(delta));
//	double D = exp((r - 0.5*pow(sigma, 2))*delta - sigma*sqrt(delta));
	cout << "The D is: " << D << endl;
	cout << "The R is: " << R << endl;
	system("pause");

	//and object of the Up and out Call option class. Arguments in order of: B, S0, K, r, sigma, T
	UpAndOutEurCall CallObj(B, S0, K, r, sigma, Time);
	CallObj.SetN(N);
	//object of binmodel class. arguments in order of:double S0, double U, double D, double R
	BinModel Model(S0, U-1, D-1, R-1);
	cout << "The price of the option is: " << CallObj.PriceByBSFormula() << endl;
	cout << "The price of the option is: " << CallObj.PriceByCRR(Model);
	system("pause");
}