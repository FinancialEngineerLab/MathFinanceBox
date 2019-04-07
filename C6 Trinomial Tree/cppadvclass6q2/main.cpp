#include "trinomial.h"
#include <iostream>
using namespace std;

int main()
{
	//Model inputs
	double Lamda = 2;
	unsigned int N = 3;
	//Market data
	double S0 = 100;
	double InterestRate = 0.06;
	double Sigma = 0.25;
	// Trade data
	double Time = 1;
	double Strike = 100;
//	char Option = 'C';
	//Trinomial* P;
/*	if (Option == 'C')
	{
		P = new Call(Time, Strike);
	}
	else P = new Put(Time, Strike);*/
	//P = new Call(Time, Strike);

	Call OptionA(Time, Strike);
	cout << "The price of the option is: " << OptionA.PriceOption(Lamda, N, S0, InterestRate, Sigma) << endl;
	system("pause");
//	delete P;
}