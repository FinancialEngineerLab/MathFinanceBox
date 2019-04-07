//********************************************************
//
//	Michael J Phillips
//	Copyright 2015
//	All rights reserved.
//	Based on original file by Capinski and Zastawniak.
//
//********************************************************

#include <cmath>
#include "EurOption.h"

double EurOption::cumNorm(double x) const
{
	const double gamma = 0.2316419;
	const double a1 = 0.319381530;
	const double a2 = -0.356563782;
	const double a3 = 1.781477937;
	const double a4 = -1.821255978;
	const double a5 = 1.330274429;
	const double k  = 1.0 / (1.0 + gamma * x);
	if (x >= 0.0)
	{
		return 1.0 - ((((a5 * k + a4) * k + a3) * k + a2) * k + a1)
			* k *exp(-x * x / 2.0) / sqrt(2.0 * PI);
	}
	else
	{
		return 1.0 - cumNorm(-x);
	}
}

double EurOption::d_plus(double S0, double sigma, double r) const
{
	return (log(S0 / mK) + (r + 0.5 * pow(sigma, 2.0)) * mT) / (sigma * sqrt(mT));
}

double EurOption::d_minus(double S0, double sigma, double r) const
{
	return d_plus(S0, sigma, r) - sigma * sqrt(mT);
}
