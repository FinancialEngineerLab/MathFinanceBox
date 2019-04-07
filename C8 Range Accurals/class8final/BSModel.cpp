#include "BSModel.h"
#include <cmath>
#include <iostream>
using namespace std;

void BSModel::GenerateSamplePath(double T, int D, NormalRandomGenerator &RandomNumber)
{
	double St = mS0;

	for (int k = 0; k < D; k++)
	{
		St = St * exp((mInterestRate - pow(mSigma, 2)*0.5)*
			(T / D) + mSigma * sqrt(T / D)*RandomNumber.generate());
		mS.push_back(St);
	}
}