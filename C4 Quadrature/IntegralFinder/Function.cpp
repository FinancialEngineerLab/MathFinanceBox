
#include "Functions.h"
#include <cmath>


double FunctionsToIntegrate::UserFunction(double ST)
{
	return PDFofStockPrice(ST)*PayOff(ST);
}

double FunctionsToIntegrate::PDFofStockPrice(double ST)
{
	double s = m_sigma * sqrt(m_T);
	double m = log(m_S0) + (m_r - 0.5*m_sigma*m_sigma)*m_T;
	return (1 / (ST*s*sqrt(2 * Pi)))*exp(-pow((log(ST) - m), 2) / (2 * s*s));
}

double EurCallOption::PayOff(double ST)
{
	if (ST >= m_K)
	{
		return ST - m_K;
	}
	else return 0;
}
double EurPutOption::PayOff(double ST)
{
	if (ST <= m_K)
	{
		return m_K - ST;
	}
	else return 0;
}
