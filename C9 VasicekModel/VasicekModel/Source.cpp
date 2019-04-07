#include "Header.h"
#include <cmath>
#include <iostream>
mt19937 RandomNumber;

double VasicekModel::DiscountFactor(double Time)
{
	return exp(A(Time) - B(Time)*mr0);
}
double VasicekModel::A(double Time)
{
	return ((B(Time) - Time)*(pow(ma, 2)*mb - 0.5*pow(mSigma, 2))) / pow(ma, 2) -
		(pow(mSigma, 2)*pow(B(Time), 2)) / (4 * ma);
}
double VasicekModel::B(double Time)
{
	return (1 - exp(-ma * Time)) / ma;
}
double VasicekModel::Rcc(double Time)
{
	return -log(DiscountFactor(Time)) / Time;
}

double VasicekModel::Fcc(double Time, double epsilon)
{
	double DiffRCC = (Rcc(Time + epsilon) - Rcc(Time-epsilon)) / (2*epsilon*Time);
	return DiffRCC + Rcc(Time);
}

void VasicekModel::GeneratePath(double Time, int steps)
{
	
	normal_distribution<double> RandomEngine(0.0, 1.0);
	
	double r = mr0;
	MyPath.push_back(r);
	for (int i = 0; i < steps; ++i)
	{
		double Z = RandomEngine(RandomNumber);
		double deltaT = Time / steps;
		double Deltar = ma * (mb - r)*deltaT + mSigma * sqrt(deltaT)*Z;
		r += Deltar;
		
		MyPath.push_back(r);
	}

	return;
}

double VasicekModel::PathDependentDF(double Time, int Steps)
{
	GeneratePath(Time, Steps);
	double PDDF = 0;
	double DeltaT = Time / Steps;
	for (vector<double>::iterator it = MyPath.begin(); it != MyPath.end(); ++it)
	{
		PDDF += *it*DeltaT;
	}
	
	MyPath.resize(0);
	MyPath.shrink_to_fit();
	return exp(-PDDF);
}

double VasicekModel::MCDF(double Time, int Steps, int N, double &DFEroor)
{
	double Sum = 0;
	double SumSquared = 0;
	for (int i = 0; i < N; ++i)
	{
		double PDDF = PathDependentDF(Time, Steps);
		Sum += PDDF;
		SumSquared += pow(PDDF, 2);
	}
	double MeanDF = Sum / N;
	double Variance = SumSquared / N - MeanDF;
	double DFError = sqrt(Variance) / (N - 1);
	return MeanDF;
}