#include "EurCall.h"
#include "EurPut.h"
#include <iostream>

using namespace std;

int main()
{
	double T, K;
	int i;
	cout << "Enter Time to expiry: " << endl;
	cin >> T;
	cout << "Enter Strike price: " << endl;
	cin >> K;
	MarketData Object;
	Object.GetMarketData();
	cout << "Call (1) or Put (2): " << endl;
	cin >> i;
	EurOption* p;
	switch (i)
	{
	case 1:
	{
		p = new EurCall(T, K);
		break;
	}
	case 2:
	{
		p = new EurPut(T,K);
		break;
	}
	default:
		return 0;
	}

	cout << "The price is: " << p->PriceByBSFormula(Object.GetS0(), Object.Getsigma(), Object.Getr()) << endl;
	cout << "The Delta is: " << p->DeltaByBSFormula(Object.GetS0(), Object.Getsigma(), Object.Getr()) << endl;
	cout << "The Gamma is: " << p->GammaByBSFormula(Object.GetS0(), Object.Getsigma(), Object.Getr()) << endl;
	cout << "The Theta is: " << p->ThetaByBSFormula(Object.GetS0(), Object.Getsigma(), Object.Getr()) << endl;

	delete p;
	system("pause");
}
