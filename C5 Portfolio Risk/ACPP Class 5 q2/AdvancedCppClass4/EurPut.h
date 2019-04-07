#ifndef EurPut_h
#define EurPut_h
#include "Options.h"


class EurPut : public EurOption
{
public:
	EurPut(double T_, double K_) : EurOption(T_, K_) {};
	
	double PriceByBSFormula(double S0,
		double sigma, double r);
	double DeltaByBSFormula(double S0,
		double sigma, double r); // http://www.iotafinance.com/en/Formula-Delta-of-a-Put-Option.html
	double GammaByBSFormula(double S0,
		double sigma, double r);
	double ThetaByBSFormula(double S0,
		double sigma, double r);
private:
	

};

#endif