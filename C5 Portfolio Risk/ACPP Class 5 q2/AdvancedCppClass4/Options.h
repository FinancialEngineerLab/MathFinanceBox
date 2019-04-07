#pragma once
#include <iostream>
using namespace std;
class EurOption
{
public:
	virtual double PriceByBSFormula(double S0,
		double sigma, double r) {
		return 0;
	}
	virtual double DeltaByBSFormula(double S0,
		double sigma, double r) {
		return 0;
	}
	virtual double GammaByBSFormula(double S0,
		double sigma, double r) {
		return 0;
	}
	virtual double ThetaByBSFormula(double S0,
		double sigma, double r) {
		return 0;
	}
	double d_plus(double S0, double sigma, double r);
	double d_minus(double S0, double sigma, double r);
	EurOption(double T_, double K_);
//	friend ostream &operator<<(ostream &stream, MarketData &Object);
//	ostream PrintData(ostream &stream, MarketData &Object, EurOption* p);

protected:
	double m_T, m_K;
};

class MarketData
{
	double S0=0, sigma=0, r=0;
public:
	
	double GetS0() { return S0; };
	double Getsigma() { return sigma; };
	double Getr() { return r; };
	void GetMarketData();
};