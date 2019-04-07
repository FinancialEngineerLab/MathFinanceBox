#pragma once

class BinModel;

class UpAndOutEurCall
{
public:
	UpAndOutEurCall(double B, double S0, double K, double r, double sigma, double T);
	double PriceByBSFormula();
	double PriceByCRR(BinModel Model);
	void SetN(int N_) { m_N = N_; }
	double PayOff(double z);
private:
	double m_S0, m_K, m_r, m_sigma, m_T, m_B;
	int m_N;

};


class BinModel
{
	double mB_S0, m_U, m_D, m_R;
public:
	double RiskNeutralProb();
	double S(int n, int i);
	BinModel(double S0, double U, double D, double R);
	double GetR();
};