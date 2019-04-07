#include "PathGenerators.h"
#include <cmath>
#include <iostream>
using namespace std;

void BSModel::GenerateSamplePath(double T, int D, NormalRandomGenerator &RandomNumber)
{
	double St = mS0;

	for (int k = 0; k < T*D; k++)
	{
		St = St * exp((mInterestRate - pow(mSigma, 2)*0.5)*
			(T / D) + mSigma * sqrt(T / D)*RandomNumber.generate());
		mS.push_back(St);
	}
}

double HestonModel::GenerateFuturePrice(double T, NormalRandomGenerator &RandomNumber)
{
	double St = mS0;
	double Variance = pow(mSigma0,2);
	for (int k = 0; k < mD*T; k++)
	{
	//	cout << "ST " << k << "'th value: " << St << endl;
		double e1 = RandomNumber.generate();
		double e2 = mRou*e1 + sqrt(1 - pow(mRou, 2))*RandomNumber.generate();
		
		St = St * exp((mInterestRate - Variance*0.5)*(1 / mD) + 
			sqrt(Variance / mD)*e1);
		Variance = pow(sqrt(Variance) + mNu * 0.5*sqrt(1 / mD)*e2, 2) -
			ma * (Variance - mVarAverage)*(1 / mD) - (pow(mNu, 2) / 4)*(1 / mD);
	}
	return St;
}