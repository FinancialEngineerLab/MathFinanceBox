#include <iostream>
#include <cmath>
#include "PathGenerators.h"
#include "OptionPricers.h"
#include <iomanip>
#include "eurCall.h"
using namespace std;


/*int main()
{
	double SMin = 100;
	double SMax = 110;
	int M = 1000000;
	int D = 252; // Number of steps per year.
	int T = 1; // Number of years.
	double S0 = 105;
	double Sigma = 0.25;
	double r = 0.05;
	double N = 450000;
	RangeAccrualOption OptionA(D, SMin, SMax, M, T);
	
	cout << fixed << setprecision(10);
	OptionData RangeAccrualOption;

	RangeAccrualOption = OptionA.PriceByMonteCarlo(N, r, Sigma, S0);
	cout << "Option price: " << RangeAccrualOption.Price << " +/- " << RangeAccrualOption.PriceError << endl;
	cout << "Option delta: " << RangeAccrualOption.Delta << " +/- " << RangeAccrualOption.DeltaError << endl;
	cout << "Option gamma: " << RangeAccrualOption.Gamma << " +/- " << RangeAccrualOption.GammaError << endl;
	
	system("pause");
}*/

/*Q1:
Number of paths required for 0.1% statistical error: 412,754
Delta: -1210.65 (Should the delta be multiplied by M?)
Gamma: 24,884.91 (This feel far to large, but I'm not sure exactly how to calculate it).
Option value: 254,642.68
*/

/*Updated
Delta: -890.9 +/- 73.37
Gamma: -1454 +/- 807.40*/


int main() //Usage of Heston Model
{
	int D = 365; // Number of steps per year.
	double S0 = 100;
	double Sigma0 = 0.2;
	double r = 0.05;
	long N = 3500000;
	double K = 105.0;
	double T = 1.0; // Number of years.
	int M = 1;
	double VarAverage = 0.09;
	double a = 1.25;
	double Nu = 0.3;
	double Rou = 0.1;

	cout << fixed << setprecision(10);
	EuropeanCall HestonCheck(K, M, T);
	OptionData HestonModelData;
	HestonModelData = HestonCheck.PriceByHeston(N, r, Sigma0, S0, Rou, Nu, a, VarAverage, D);
	
	cout << "The price by Heston's model of a Eur Call is: " << HestonModelData.Price << " +/- " << HestonModelData.PriceError << endl;
	
	double Tgt = HestonModelData.Price;
	double TgtLow = HestonModelData.Price - HestonModelData.PriceError;
	BSWrapper FindHestonImpVol(S0, r, K, T);
	double ImpliedVol = FindHestonImpVol.CalcImpliedVolatility(S0, r, Tgt);
	double ImpliedVolError = ImpliedVol - FindHestonImpVol.CalcImpliedVolatility(S0, r, TgtLow);
	cout << "Implied volatility is: " << FindHestonImpVol.CalcImpliedVolatility(S0, r, Tgt) << " +/- " << ImpliedVolError << endl;

	system("pause");
}

/*Price of european call using Heston's model is 10.61 at 1% statistical error. (Greater accuracy wouldn't compile.)
Implied vol of 0.26. This makes sense, as it is between the original vol of 0.2 and the set average vol of 0.3.


update: The price by Heston's model of a Eur Call is: 9.7142590143 +/- 0.0094214921
Implied volatility is: 0.2431640625 +/- 0.0000000000
*/
