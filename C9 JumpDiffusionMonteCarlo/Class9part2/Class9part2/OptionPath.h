#pragma once
#include <cmath>
#include "RandomNumberGen.h"
class JumpDiffussionPath
{
public:
	JumpDiffussionPath(int Steps, double Sigma, double r, double S0, 
		double Lamda, double m, double s): mSteps(Steps), mSigma(Sigma), 
		mr(r), mS0(S0), mLamda(Lamda), mm(m), ms(s) {}
	~JumpDiffussionPath(){}
	double GeneratePath(double T, RandomNum &RandomForJump);
	double Getr() { return mr; }
private:
	int mSteps;
	double mSigma;
	double mr;
	double mS0;
	double mLamda;
	double mm; //Mean of Log J
	double ms; //Volatility of LogJ;
};

