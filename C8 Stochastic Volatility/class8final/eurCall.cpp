//********************************************************
//
//	Michael J Phillips
//	Copyright 2015
//	All rights reserved.
//	Based on original file by Capinski and Zastawniak.
//
//********************************************************

#include <cmath>
#include "eurCall.h"
#include <iostream>

using namespace std;
double Factorial(int Number);

double BSWrapper::Value(double SigmaFind)
{
	
	return priceByBSFormula(mS0, SigmaFind, mr);
}

double EurCall::PriceByJumpDiffusion(double S0, double Sigma, double Lambda, double r, double s, double m, int N)const
{
	double k = exp(m + pow(s, 2) / 2) - 1;
	double Lambda2 = Lambda*(1 + k);
	double Sum = 0;
	for (int n = 0; n <= N; ++n)
	{
		Sum += ((exp(-Lambda2*mT)*pow(Lambda2*mT, n)) / Factorial(n))*priceByBSFormula(S0, ForwardSigma(Sigma, n, s), Forwardr(r, Lambda, n, k));

	}
	return Sum;
}

double EurCall::CalcImpliedVolatility(double S0, double r, double Price)const
{
	double LEnd = 0;
	double REnd = 1;
	double Acc = 0.001;
	BSWrapper CallOption(S0, r, mK, mT);
	return SolveByBisect(&CallOption, Price, LEnd, REnd, Acc);
}

double EurCall::ForwardSigma(double Sigma, int n, double s)const
{
	return sqrt(pow(Sigma, 2) + (n*pow(s, 2)) / mT);
}

double EurCall::Forwardr(double r, double Lambda, int n, double k)const
{
	return r - Lambda*k + (n*log(1 + k)) / mT;
}

double Factorial(int Number)
{
	if (Number == 0 || Number == 1) return 1;
	else if (Number < 0)
	{
		cout << "Negative number in factorial finder";
		exit(EXIT_FAILURE);
	}
	else
	{
		int Fact = Number;
		for (int i = Number - 1; i > 0; --i)
		{
			Fact = Fact*i;
		}
		return Fact;
	}
}

double EurCall::priceByBSFormula(double S0, double sigma, double r) const
{
	return S0 * cumNorm(d_plus(S0, sigma, r))
		- mK * exp(-r * mT) * cumNorm(d_minus(S0, sigma, r));
}

double EurCall::deltaByBSFormula(double S0, double sigma, double r) const
{
	return cumNorm(d_plus(S0, sigma, r));
}

double EurCall::gammaByBSFormula(double S0, double sigma, double r) const
{
	return exp(-pow(d_plus(S0, sigma, r), 2.0) / 2.0) / S0 / sigma / sqrt(mT) / sqrt(2*PI);
}

double EurCall::thetaByBSFormula(double S0, double sigma, double r) const
{
	return -S0 * exp(-pow(d_plus(S0, sigma, r), 2.0) / 2.0) * sigma / 2.0 / sqrt(mT) / sqrt(2*PI) - r * mK *exp(-r*mT) * cumNorm(d_minus(S0, sigma, r));
}
