#include "EurPut.h"
#include <cmath>
using namespace std;
#include <iostream>

double N(double x);
double Phi(double d);
double normalCDF(double x);
double EurPut::PriceByBSFormula(double S0,
	double sigma, double r)
{
	if (S0 < 0 || sigma <= 0) exit(EXIT_FAILURE);
	
	return -S0*N(-d_plus(S0, sigma, r))
		+ m_K*exp(-r*m_T)*N(-d_minus(S0, sigma, r));
}

double EurPut::DeltaByBSFormula(double S0,
	double sigma, double r)
{
	return N(d_plus(S0, sigma, r)) - 1;
}
double EurPut::GammaByBSFormula(double S0,
	double sigma, double r)
{
	return Phi(d_plus(S0, sigma, r)) / (S0*sigma*sqrt(m_T));
}
double EurPut::ThetaByBSFormula(double S0,
	double sigma, double r)
{
	return -(S0*Phi(d_plus(S0, sigma, r))*sigma) / (2 * sqrt(m_T)) +
		(r*m_K*exp(-r * m_T)*normalCDF(-d_minus(S0, sigma, r)));
}
