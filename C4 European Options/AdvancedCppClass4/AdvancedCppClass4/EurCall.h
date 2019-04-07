#ifndef EurCall_h
#define EurCall_h
#include "Options.h"

class EurCall: public EurOption
{
   public:     
	  EurCall(double T_, double K_) : EurOption(T_, K_) {};
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
