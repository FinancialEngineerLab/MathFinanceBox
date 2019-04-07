#include <iostream>
#include "Header.h"
#include <iomanip>
#include <fstream>
using namespace std;

int main()
{
	double a = 0.25; //Rate of mean reversion
	double b = 0.1; // mean reversion level
	double Sigma = 0.02; //volatility of interest rate
	double r0 = 0.07; // Initial interest rate.
	
	double epsilon = 0.0000001;
	double Time = 5.0;
	int Steps = 50;
	int N = 7000;
	double DFError = 0;
	VasicekModel ZeroCouponBondA(a, b, Sigma, r0);
	cout << "Disocunt Factor: " << ZeroCouponBondA.DiscountFactor(Time) << endl;

	/*cout << setprecision(4);
	double Time = 5.0;
	cout << "Information on zero coupon bond at time 5:" << endl;
	cout << "Disocunt Factor: " << ZeroCouponBondA.DiscountFactor(Time) << endl;
	cout << "Continuously compounded deposit rate: " << ZeroCouponBondA.Rcc(Time) << endl;
	cout << "Foward rate: " << ZeroCouponBondA.Fcc(Time, epsilon) << endl;
	system("pause");


	ofstream ZeroCouponBondFile("ZeroCouponBon.csv");
	ZeroCouponBondFile << "Time" << "," << "Discount factor" << "," << "Continously compounded deposit rate" << "," << "Forward rate" << endl;
	for (double Time = 0; Time <= 15; ++Time)
	{
		ZeroCouponBondFile << Time << "," << ZeroCouponBondA.DiscountFactor(Time) << "," 
			<< ZeroCouponBondA.Rcc(Time) << "," << ZeroCouponBondA.Fcc(Time, epsilon) << endl;
	}*/
	
	
	cout << "PathDepDF is: " << ZeroCouponBondA.MCDF(Time, Steps, N, DFError) << "+/- " << DFError << endl;
	
	system("pause");
}