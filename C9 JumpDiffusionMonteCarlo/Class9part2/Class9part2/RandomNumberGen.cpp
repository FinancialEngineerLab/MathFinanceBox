#include "RandomNumberGen.h"

double RandomNum::GenLogNormal(double m, double s)
{
	lognormal_distribution <double> LogNormalGen(m, s);
	return LogNormalGen(RandomNumber);

}

double RandomNum::GenUniform()
{
	uniform_real_distribution<double> UniformDist(0, 1);
	return UniformDist(RandomNumber);
}

double RandomNum::GenStandardNormal()
{
	normal_distribution<double> NormDist(0, 1);
	return NormDist(RandomNumber);
}