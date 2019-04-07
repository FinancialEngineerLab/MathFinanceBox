#include "OptionPricer.h"

using namespace std;

void OptionPricer::PriceByMC(double T, int N, JumpDiffussionPath CallOption)
{
	RandomNum RandomForJump;
	double Sum = 0;
	double SumSquared = 0;
	for (int i = 0; i < N; ++i)
	{
		double ST = CallOption.GeneratePath(T, RandomForJump);
		double Payoff1 = Payoff(ST);
		Sum += Payoff1;
		SumSquared += pow(Payoff1, 2);
	}
	double MeanOfPayoffs = Sum / N;
	double MeanOfSquares = SumSquared / N;
	double Variance = (MeanOfSquares) - pow(MeanOfPayoffs, 2);
	PriceOfOption = exp(-CallOption.Getr()*T)*MeanOfPayoffs;
	PriceError = exp(-CallOption.Getr()*T)*sqrt(Variance) / sqrt(N - 1);

}

double EurCall::Payoff(double ST)
{
	return max(ST - mK, 0.0);
}