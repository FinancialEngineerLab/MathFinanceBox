//********************************************************
//
//	Michael J Phillips
//	Copyright 2015
//	All rights reserved.
//
//********************************************************

#ifndef _EUROPTION_H_
#define _EUROPTION_H_

#include <cmath>

static const double PI = 4.0 * std::atan(1.0);

class EurOption
{
public:
	EurOption(double T, double K) : mT(T), mK(K) {};
	virtual ~EurOption() {}

	virtual double PriceByJumpDiffusion(double S0, double Sigma, double Lambda, double r, double s, double m, int N) const = 0;

	virtual double priceByBSFormula(double S0, double sigma, double r) const = 0;
	virtual double deltaByBSFormula(double S0, double sigma, double r) const = 0;
	virtual double gammaByBSFormula(double S0, double sigma, double r) const = 0;
	virtual double thetaByBSFormula(double S0, double sigma, double r) const = 0;

	double crossCheck(double S0, double sigma, double r) const
	{
		//	Check against BS PDE
		const double p = priceByBSFormula(S0, sigma, r);
		const double d = deltaByBSFormula(S0, sigma, r);
		const double g = gammaByBSFormula(S0, sigma, r);
		const double t = thetaByBSFormula(S0, sigma, r);
			
		return t + sigma*sigma*S0*S0 * g/2.0 + r*S0*d - r*p;
	}

protected:
	double d_plus(double S0, double sigma, double r) const;
	double d_minus(double S0, double sigma, double r) const;
	double cumNorm(double x) const;

	const double mT;
	const double mK;
};

#endif
