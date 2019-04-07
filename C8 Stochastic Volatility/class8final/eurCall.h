//********************************************************
//
//	Michael J Phillips
//	Copyright 2015
//	All rights reserved.
//	Based on original file by Capinski and Zastawniak.
//
//********************************************************

#ifndef _EURCALL_H_
#define _EURCALL_H_

#include "Solver02.h"
#include "eurOption.h"



class EurCall : public EurOption
{
public:
	EurCall(double T, double K) : EurOption(T, K) {}
	virtual ~EurCall() {}

	virtual double PriceByJumpDiffusion(double S0, double Sigma, double Lambda, double r, double s, double m, int N)const;

	virtual double priceByBSFormula(double S0, double sigma, double r) const;
	virtual double deltaByBSFormula(double S0, double sigma, double r) const;
	virtual double gammaByBSFormula(double S0, double sigma, double r) const;
	virtual double thetaByBSFormula(double S0, double sigma, double r) const;
	double CalcImpliedVolatility(double S0, double r, double Price)const;
private:
	double ForwardSigma(double Sigma, int n, double s)const;
	double Forwardr(double r, double Lambda, int n, double k)const;
};

class BSWrapper : public Function, public EurCall
{
public:
	BSWrapper(double S0, double r, double K, double T) : mS0(S0), mr(r), EurCall(T, K) {}
	double Value(double Sigma);

private:
	double mS0, mr;

};

#endif
