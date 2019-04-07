#include "EurCall.h"
#include "EurPut.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main()
{
	double T, K;
	char CallPutFlag;
	int Nominal;
	MarketData Object;
	Object.GetMarketData();
	EurOption* p;
	ifstream inFile;
	inFile.open("Datafile.txt");
	if (!inFile)
	{
		cout << "Unable to open file. ";
		system("pause");
		exit(EXIT_FAILURE);
	}
	cout << setprecision(2) << fixed;
	cout << setw(10) << "Option " << setw(10) << "Price" << setw(10) << "Delta" << setw(10) << "Gamma" << setw(10) << "Theta"<< endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	int OptionNumber = 0;
	double SumOfPrice = 0;
	double SumOfDelta = 0;
	double SumOfGamma = 0;
	double SumOfTheta = 0;
	while (inFile >> CallPutFlag >> Nominal >> K >> T)
	{
		if (CallPutFlag == 'C')
		{
			p = new EurCall(T, K);
		}
		else if(CallPutFlag == 'P')
		{
			p = new EurPut(T, K);
		}
		else
		{
			cout << "incorrect Call Put Flag" << endl;
			exit(EXIT_FAILURE);
		}
		OptionNumber++;
		cout << setw(10) << OptionNumber << setw(10);
		SumOfPrice += p->PriceByBSFormula(Object.GetS0(), Object.Getsigma(), Object.Getr())*Nominal;
		SumOfDelta += p->DeltaByBSFormula(Object.GetS0(), Object.Getsigma(), Object.Getr())*Nominal;
		SumOfGamma += p->GammaByBSFormula(Object.GetS0(), Object.Getsigma(), Object.Getr())*Nominal;
		SumOfTheta += p->ThetaByBSFormula(Object.GetS0(), Object.Getsigma(), Object.Getr())*Nominal;
		cout << p->PriceByBSFormula(Object.GetS0(), Object.Getsigma(), Object.Getr())*Nominal << setw(10);
		cout << p->DeltaByBSFormula(Object.GetS0(), Object.Getsigma(), Object.Getr())*Nominal << setw(10);
		cout << p->GammaByBSFormula(Object.GetS0(), Object.Getsigma(), Object.Getr())*Nominal << setw(10);
		cout << p->ThetaByBSFormula(Object.GetS0(), Object.Getsigma(), Object.Getr())*Nominal << endl;
		delete p;
	}
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << setw(10) << "Totals" << setw(10) << SumOfPrice << setw(10) << SumOfDelta << setw(10) << SumOfGamma << setw(10) << SumOfTheta << endl;
	
	system("pause");
}
