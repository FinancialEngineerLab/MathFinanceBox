#include <iostream>
#include "OptionPath.h"
#include "OptionPricer.h"


using namespace std;

int main()
{
	int N = 1000000;
	int Steps = 52;
	double Sigma = 0.15;
	double S0 = 100;
	double r = 0.05;
	double Lamda = 1;
	double m = 0.05;
	double s = 0.3;
	double T = 0.5;
	double K = 105;
	JumpDiffussionPath OptionA(Steps, Sigma, r, S0, Lamda, m, s);
	EurCall Option1(K, T);
	Option1.PriceByMC(T, N, OptionA);
	cout << "The price of the call is: " << Option1.GetPrice() << "+/-" <<
		Option1.GetPriceError() << endl;
	system("pause");
	
}