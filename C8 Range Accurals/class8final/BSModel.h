#pragma once
#include <vector>
#include <iostream>
#include <cmath>
#include "normalRandomGenerator.h"
using namespace std;

typedef vector<double> SamplePath;

class BSModel
{
public:
	BSModel(double InterestRate, double Sigma, double S0) : mInterestRate(InterestRate), mSigma(Sigma), mS0(S0) {
		mS.clear();

	}
	~BSModel()
	{
		mS.clear();
	}
	void GenerateSamplePath(double T, int m, NormalRandomGenerator &RandomNumber);
	SamplePath mS;
private:
	double mInterestRate, mSigma, mS0;

};
