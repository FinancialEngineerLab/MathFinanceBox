#include "OptionPricers.h"
#include <math.h>



OptionData NonPathDepOption::PriceByHeston(long N, double r, double Sigma, double S0, double Rou, double Nu, double a, double VarAverage, double D)
{
	OptionData HestonOption;
	NormalRandomGenerator RandomNumber;
	Stats1 HestonFigures;
	for (int i = 0; i< N; ++i)
	{
		HestonModel HSamplePath(r, Sigma, S0, Rou, Nu, a, VarAverage, D);

		double ST = HSamplePath.GenerateFuturePrice(mT, RandomNumber); //Need to have D available.
		HestonFigures.add(Payoff(ST));
	}

	HestonOption.PriceError = exp(-r*mT)*HestonFigures.stdevP() / sqrt(N - 1);
	HestonOption.Price = exp(-r*mT)*HestonFigures.mean();
	HestonOption.NumberOfTrials = N;
	return HestonOption;
}
OptionData NonPathDepOption::PriceByHeston(long N, double r, double Sigma, double S0, double Rou, double Nu, 
	double a, double VarAverage, double D, const double KLow, const double KHi)
{
	OptionData HestonOption;
	NormalRandomGenerator RandomNumber;
	Stats1 HestonFigures;
	for (int i = 0; i < N; ++i)
	{
		HestonModel HSamplePath(r, Sigma, S0, Rou, Nu, a, VarAverage, D);

		double ST = HSamplePath.GenerateFuturePrice(mT, RandomNumber);
		double Payoffs[KHi - KLow] = 
		HestonFigures.add(Payoff(ST));
	}

	HestonOption.PriceError = exp(-r * mT)*HestonFigures.stdevP() / sqrt(N - 1);
	HestonOption.Price = exp(-r * mT)*HestonFigures.mean();
	HestonOption.NumberOfTrials = N;
	return HestonOption;
}

double EuropeanCall::Payoff(double ST)
{
	if (ST < mK) return 0;
	else return ST - mK;
}
double EuropeanCall::Payoff(double K, double ST)
{
	if (ST < mK) return 0;
	else return ST - mK;
}

OptionData PathDepOption::PriceByMonteCarlo(int N, double r, double Sigma, double S0)
{
	OptionData OptionA;
	NormalRandomGenerator RandomNumber;
	Stats1 MCSummation;
	Stats1 MCDelta;
	Stats1 MCGamma;
	double epsilon = 0.001;
	for (int i = 0; i < N; ++i)
	{
		BSModel SamplePaths(r, Sigma, S0);
		SamplePaths.GenerateSamplePath(mT, int(mT * 252), RandomNumber);
		double Pay1 = Payoff(SamplePaths.mS);
		MCSummation.add(Pay1);

		for (SamplePath::iterator it = SamplePaths.mS.begin(); it != SamplePaths.mS.end(); ++it)
		{
			*it = *it *(1 + epsilon);
		}
		double Pay2 = Payoff(SamplePaths.mS);
		MCDelta.add((Pay2 - Pay1));

		for (SamplePath::iterator it = SamplePaths.mS.begin(); it != SamplePaths.mS.end(); ++it)
		{
			*it = *it *(1 - epsilon)/(1 + epsilon);
		}
		double Pay3 = Payoff(SamplePaths.mS);
		MCGamma.add(Pay3 + Pay2 - 2*Pay1);
	}
	OptionA.Price = exp(-r*mT)*MCSummation.mean();
	OptionA.PriceError = exp(-r*mT)*MCSummation.stdevP() / sqrt(N-1);
	OptionA.Delta = exp(-r * mT)*(MCDelta.mean()) / (epsilon*S0);
	OptionA.DeltaError = exp(-r*mT)*MCDelta.stdevP() / (epsilon*S0*sqrt(N-1));
	OptionA.Gamma = exp(-r * mT)*((MCGamma.mean()) / pow(epsilon*S0, 2));
	OptionA.GammaError = exp(-r*mT)*MCGamma.stdevP() / (sqrt(N-1)*pow(epsilon*S0,2));
	return OptionA;
}

double RangeAccrualOption::Payoff(SamplePath & S)
{
	int d = 0;
	for (int k = 0; k < mT *mD; k++)
	{
		if (S[k] < mSMax && S[k] > mSMin)
		{
			++d;
		}
	}
	return (static_cast<double>(d) / (mT*mD))*mM;
}