#pragma once
#include "BSModel.h"

class PathDepOption
{
public:
	PathDepOption(int M, double T) : mT(T), mM(M) {}
	double PriceByMonteCarlo(long N, double r, double Sigma, double S0);
	virtual double Payoff(SamplePath &S) = 0;

protected:
	double mT; //Time in years.
	double mM; //Notional
};

class RangeAccrualOption : public PathDepOption
{
public:

	RangeAccrualOption(int D, double SMin, double SMax,
		int M) : mSMax(SMax), mSMin(SMin), mD(D), PathDepOption(M, static_cast<double>(D) / 252) {}
	double Payoff(SamplePath &S);
private:
	double mSMin;
	double mSMax;
	int mD;
};