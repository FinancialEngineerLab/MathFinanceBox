#pragma once
#include <vector>
using namespace std;
class Trinomial
{
public:
	Trinomial(double T, double K) : mT(T), mK(K) {};
	double PriceOption(double Lamda, unsigned int N, double S0, double InterestRate, double Sigma);
	
	virtual double Payoff(double x) = 0;
	double ST(unsigned int N, unsigned int i, double S0, double U, double D, double M);
protected:

	double mT;
	double mK;
	vector <double> price;
};

class Call : public Trinomial
{
public:
	Call(double T, double K) : Trinomial(T, K) { ; }
	
	double Payoff(double x);

private:
};