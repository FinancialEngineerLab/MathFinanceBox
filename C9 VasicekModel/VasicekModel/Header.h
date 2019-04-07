#pragma once
#include <vector>
#include <random>
using namespace std;

class VasicekModel
{
public:
	VasicekModel(double a, double b, double Sigma, double r0) :
		ma(a), mb(b), mSigma(Sigma), mr0(r0) {}
	void GeneratePath(double Time, int Steps);
	double PathDependentDF(double Time, int Steps);
	double MCDF(double Time, int steps, int N, double &DFError);
	double DiscountFactor(double Time);
	double A(double Time);
	double B(double Time);
	double Rcc(double Time);
	double Fcc(double Time, double epsilon);

private:
	double ma;
	double mb;
	double mSigma;
	double mr0;
	vector<double> MyPath;
};