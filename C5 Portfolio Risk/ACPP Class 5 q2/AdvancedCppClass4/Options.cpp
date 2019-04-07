#include "Options.h"
#include <cmath>
#include <iostream>


using namespace std;
double normalCDF(double x)
{
	return 0.5*erfc(-x * sqrt(0.5));
}
double Phi(double d)
{
	const double Pi = 3.1415926535;
	return exp(-d*d / 2) / sqrt(2 * Pi);
}
double N(double x)
{
	double gamma = 0.2316419;     double a1 = 0.319381530;
	double a2 = -0.356563782;   double a3 = 1.781477937;
	double a4 = -1.821255978;   double a5 = 1.330274429;
	double pi = 4.0*atan(1.0); double k = 1.0 / (1.0 + gamma*x);
	if (x >= 0.0)
	{
		return 1.0 - ((((a5*k + a4)*k + a3)*k + a2)*k + a1)
			*k*exp(-x*x / 2.0) / sqrt(2.0*pi);
	}
	else return 1.0 - N(-x);
}

double EurOption::d_plus(double S0, double sigma, double r)
{
	return (log(S0 / m_K) +
		(r + 0.5*pow(sigma, 2.0))*m_T)
		/ (sigma*sqrt(m_T));
}

double EurOption::d_minus(double S0, double sigma, double r)
{
	return d_plus(S0, sigma, r) - sigma*sqrt(m_T);
}

EurOption::EurOption(double T_, double K_)
{
	m_T = T_; m_K = K_;
}

void MarketData::GetMarketData()
{
	cout << "Enter spot price: ";
	cin >> S0;
	cout << "Enter volatility: ";
	cin >> sigma;
	cout << "Enter interest rate: ";
	cin >> r;
	
	
}
/*
ostream EurOption::PrintData(ostream &stream, MarketData &object, EurOption* p)
{
	stream << "The price is: " << p->PriceByBSFormula(object.GetS0(), object.Getsigma(), object.Getr()) << endl;
	stream << "The Delta is: " << p->DeltaByBSFormula(object.GetS0(), object.Getsigma(), object.Getr()) << endl;
	stream << "The Gamma is: " << p->GammaByBSFormula(object.GetS0(), object.Getsigma(), object.Getr()) << endl;
	stream << "The Theta is: " << p->ThetaByBSFormula(object.GetS0(), object.Getsigma(), object.Getr()) << endl;
	return stream;
}*/
/*ostream &operator<< (ostream &stream, MarketData &object)
{
	EurOption* p;
	stream << "The price is: " << p->PriceByBSFormula(object.GetS0(), object.Getsigma(), object.Getr()) << endl;
	stream << "The Delta is: " << p->DeltaByBSFormula(object.GetS0(), object.Getsigma(), object.Getr()) << endl;
	stream << "The Gamma is: " << p->GammaByBSFormula(object.GetS0(), object.Getsigma(), object.Getr()) << endl;
	stream << "The Theta is: " << p->ThetaByBSFormula(object.GetS0(), object.Getsigma(), object.Getr()) << endl;
	return stream;
}*/