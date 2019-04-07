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

class HestonModel
{
public:
	HestonModel(double InterestRate, double Sigma, double S0, double Rou, double Nu, double a, double VarAverage, double D) : mInterestRate(InterestRate), mSigma0(Sigma), mS0(S0),
		mRou(Rou), mNu(Nu), ma(a), mVarAverage(VarAverage), mD(D) {}
	~HestonModel() { 	}
	double GenerateFuturePrice(double T, NormalRandomGenerator &RandomNumber);
	
private:
	double mInterestRate, mSigma0, mS0;
	double mRou, mNu, ma, mVarAverage;
	double mD; //Number of steps per year.
};