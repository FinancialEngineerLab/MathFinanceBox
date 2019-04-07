#pragma once

class FunctionsToIntegrate
{
public:
	FunctionsToIntegrate(double S0_, double sigma_, double r_, double T_, double K_)
	{
		m_S0 = S0_;
		m_sigma = sigma_;
		m_r = r_;
		m_T = T_;
		m_K = K_;
	}
	double UserFunction(double x);
	double PDFofStockPrice(double ST);
	virtual double PayOff(double ST) = 0;
	


protected:
	double m_S0, m_sigma, m_r, m_T, m_K;
	const double Pi = 3.14159265359;
};

class EurCallOption : public FunctionsToIntegrate
{
public:

	EurCallOption(double S0_, double sigma_, double r_, double T_, double K_) :FunctionsToIntegrate(S0_, sigma_, r_, T_, K_) { ; }
	double PayOff(double ST);
};
class EurPutOption : public FunctionsToIntegrate
{
public:

	EurPutOption(double S0_, double sigma_, double r_, double T_, double K_) :FunctionsToIntegrate(S0_, sigma_, r_, T_, K_) { ; }
	double PayOff(double ST);
};

