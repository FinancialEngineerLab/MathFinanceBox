#pragma once
#include "PathGenerators.h"
#include "stats.h"

struct OptionData
{
	double Price = 0;
	double PriceError = 0;
	double Delta = 0;
	double DeltaError = 0;
	double Gamma = 0;
	double GammaError = 0;
	int NumberOfTrials = 0;
};

class PathDepOption
{
public:
	PathDepOption(int M, double T, int D) : mT(T), mM(M), mD(D) {}

	OptionData PriceByMonteCarlo(int N, double r, double Sigma, double S0);

	
	virtual double Payoff(SamplePath &S) = 0;


protected:
	double mT; //Time in years.
	double mM; //Notional
	double mD; //Number of steps per year
};

class RangeAccrualOption : public PathDepOption
{
public:

	RangeAccrualOption(int D, double SMin, double SMax,
		int M, double T) : mSMax(SMax), mSMin(SMin), PathDepOption(M, T, D) {}
	double Payoff(SamplePath &S);
private:

	double mSMin;
	double mSMax;
	
};

class NonPathDepOption
{
public:
	NonPathDepOption(int M, double T) : mT(T), mM(M) {}
	OptionData PriceByHeston(long N, double r, double Sigma, double S0, double Rou, double Nu, double a, double VarAverage, double D);
	OptionData PriceByHeston(long N, double r, double Sigma, double S0, double Rou, 
		double Nu, double a, double VarAverage, double D, double KLow, double KHi);
	virtual double Payoff(double ST) = 0;
	virtual double Payoff(double K, double ST) = 0;
protected:
	double mT; //Time in years.
	double mM; //Notional
};

class EuropeanCall : public NonPathDepOption
{
public:
	EuropeanCall(double K, int M, double T) : mK(K), NonPathDepOption(M, T) {}
	double Payoff(double ST);
	double Payoff(double K, double ST);

private:
	double mK;
};

