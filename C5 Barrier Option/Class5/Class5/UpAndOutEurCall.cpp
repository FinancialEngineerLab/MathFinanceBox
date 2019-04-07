#include "UpAndOutEurCall.h"
#include <cmath>
#include <vector>

using namespace std;

UpAndOutEurCall::UpAndOutEurCall(double B, double S0, double K, double r, double sigma, double T)
{
	m_S0 = S0;
	m_K = K;
	m_r = r;
	m_sigma = sigma;
	m_T = T;
	m_B = B;
}

double N(double x)
{
	double gamma = 0.2316419;     double a1 = 0.319381530;
	double a2 = -0.356563782;   double a3 = 1.781477937;
	double a4 = -1.821255978;   double a5 = 1.330274429;
	double pi = 4.0*atan(1.0); double k = 1.0 / (1.0 + gamma*x);
	if (x >= 0.0)
	{
		return 1.0 - ((((a5*k + a4)*k + a3)*k + a2)*k + a1)
			*k*exp(-x*x / 2.0) / sqrt(2.0*pi);
	}
	else return 1.0 - N(-x);
}

double D(double x, double r, double sigma, double Time)
{
	return (log(x) + (r + 0.5*sigma*sigma)*Time) / (sigma*sqrt(Time));
}

double UpAndOutEurCall::PriceByBSFormula()
{
	double d1 = D(m_S0 / m_K, m_r, m_sigma, m_T);
	double d2 = d1 - m_sigma*sqrt(m_T);
	double d3 = D(m_S0 / m_B, m_r, m_sigma, m_T);
	double d4 = d3 - m_sigma*sqrt(m_T);
	double d5 = D(m_S0 / m_B, -m_r, m_sigma, m_T);
	double d6 = d5 - m_sigma*sqrt(m_T);
	double d7 = D(m_S0*m_K / (m_B*m_B), -m_r, m_sigma, m_T);
	double d8 = d7 - m_sigma*sqrt(m_T);
	double IndexA = 2 * m_r / (m_sigma*m_sigma);


	return m_S0*(N(d1) - N(d3) - (N(d6) - N(d8))*pow(m_B / m_S0, 1 + IndexA)) -
		m_K*exp(-m_r*m_T)*(N(d2) - N(d4) - (N(d5) - N(d7))*pow(m_B / m_S0, -1 + IndexA));

}

double UpAndOutEurCall::PriceByCRR(BinModel Model)
{
	double q = Model.RiskNeutralProb();
	vector<double> Price;
	for (int i = 0; i <= m_N; i++)
	{
		Price.push_back(PayOff(Model.S(m_N, i)));
	}
	for (int n = m_N - 1; n >= 0; n--)
	{
		for (int i = 0; i <= n; i++)
		{
			Price[i] = (q*Price[i + 1] + (1 - q)*Price[i]) / (1 + Model.GetR());
			if (Model.S(n, i) >= m_B)
			{
				Price[i] = 0;
			}
		}
	}
	return Price[0];
}

double UpAndOutEurCall::PayOff(double z)
{
	if (z > m_K && z < m_B) return z - m_K;
	return 0.0;
}

BinModel::BinModel(double S0, double U, double D, double R)
{
	mB_S0 = S0;
	m_U = U;
	m_D = D;
	m_R = R;
}

double BinModel::RiskNeutralProb()
{
	return (m_R - m_D) / (m_U - m_D);
}

double BinModel::S(int n, int i)
{
	return mB_S0*pow(1 + m_U, i)*pow(1 + m_D, n - i);
}
double BinModel::GetR()
{
	return m_R;
}