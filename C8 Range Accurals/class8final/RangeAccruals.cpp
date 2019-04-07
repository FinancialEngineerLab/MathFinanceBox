#include "RangeAccruals.h"
#include <math.h>
#include 
double PathDepOption::PriceByMonteCarlo(long N, double r, double Sigma, double S0)
{

	double Sum = 0.0;
	
	for (int i = 0; i < N; ++i)
	{
		BSModel SamplePaths(r, Sigma, S0);
		srand(i);
		NormalRandomGenerator RandomNumber;
		SamplePaths.GenerateSamplePath(mT, int(mT * 252), RandomNumber);
		Sum += Payoff(SamplePaths.mS);
	}
	return exp(-r*mT)*Sum / N;
}

double RangeAccrualOption::Payoff(SamplePath & S)
{
	int d = 0;
	for (int k = 0; k < mD; k++)
	{
		if (S[k] < mSMax && S[k] > mSMin)
		{
			++d;
		}
	}
	return (static_cast<double>(d) / mD)*mM;
}