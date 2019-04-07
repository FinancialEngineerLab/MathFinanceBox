#include "trinomial.h"
#include <cmath>
#include <iostream>

using namespace std;
double Trinomial::PriceOption(double Lamda, unsigned int N, double S0, double InterestRate, double Sigma)
{
	double H = mT / N;
	double U = exp(Lamda*Sigma*sqrt(H));
	double D = 1 / U;

	double M = exp(InterestRate*H);
	double V = exp(2 * InterestRate*H)*(exp(pow(Sigma, 2)*H) - 1);

	double QU = ((V + pow(M, 2) - M)*U - (M - 1)) / ((U - 1)*(pow(U, 2) - 1));
	double QD = ((V + pow(M, 2) - M)*pow(U,2) - pow(U, 3)*(M - 1)) / ((U - 1)*(pow(U, 2) - 1));
	double QNC = 1 - QU - QD;

	double DiscountR = exp(-InterestRate * H);

	for (unsigned int i = 0; i <= 2 * N + 1; ++i)
	{
		price.push_back(Payoff(ST(N, i, S0, U, D, M)));
	}
	--N;
	for (unsigned int n = 2 * N + 1; n > 0; --n)
	{
		for (unsigned int i = 0; i <= n; ++i)
		{
			price[i] = DiscountR * (QD * price[i] + QNC * price[i + 1] + QU * price[i + 2]);
		}
	}
	
	return price[0];

}
double Call::Payoff(double x)
{
	if (x > mK) return x - mK;
	else return 0;
}

double Trinomial::ST(unsigned int N, unsigned int i, double S0, double U, double D, double M)
{
	if (N == i) return S0;
	else if (N < i) return S0 * pow(U, (i - N));
	else if (N > i) return S0 * pow(D, (N - i));
	else
	{
		cout << "Error in ST function" << endl;
		exit(EXIT_FAILURE);
	}
}