#include "EurCall.h"
#include <cmath>
#include "Options.h"

double N(double x);
double Phi(double d);
double EurCall::PriceByBSFormula(double S0,
   double sigma, double r)
{
	if (S0 < 0 || sigma <= 0) exit(EXIT_FAILURE);

   return S0*N(d_plus(S0,sigma,r))
      -m_K*exp(-r*m_T)*N(d_minus(S0,sigma,r));
}

double EurCall::DeltaByBSFormula(double S0,
	double sigma, double r)
{
	return N(d_plus(S0, sigma, r));
}
double EurCall::GammaByBSFormula(double S0,
	double sigma, double r)
{
	return Phi(d_plus(S0, sigma, r)) / (S0*sigma*sqrt(m_T));
}
double EurCall::ThetaByBSFormula(double S0,
	double sigma, double r)
{
	return -(S0*Phi(d_plus(S0, sigma, r))*sigma) / (2 * sqrt(m_T)) 
		- r*m_K*exp(-r*m_T)*N(d_minus(S0, sigma, r));
}