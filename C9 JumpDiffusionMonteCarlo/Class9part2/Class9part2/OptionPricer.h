#pragma once
#include "OptionPath.h"
#include <algorithm>
#include "RandomNumberGen.h"
#include <cmath>

class OptionPricer
{
public:
	OptionPricer(double T): mT(T) {}
	~OptionPricer() {}
	virtual double Payoff(double ST) = 0;
	void PriceByMC(double T, int N, JumpDiffussionPath CallOption);
	double GetPrice() { return PriceOfOption; }
	double GetPriceError() { return PriceError; }
	double GetDelta() { return Delta; }
	double GetDeltaError() { return DeltaError; }
private:
	double mT;
	double PriceOfOption;
	double PriceError;
	double Delta;
	double DeltaError;
};

class EurCall: public OptionPricer
{
public:
	EurCall(double K, double T): mK(K), OptionPricer(T)  {}
	~EurCall() {}
	double Payoff(double ST);
private:
	double mK;
};
