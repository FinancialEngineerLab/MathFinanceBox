#pragma once
#include <random>
#include <cmath>
using namespace std;
class RandomNum
{
public:
	RandomNum() {}
	~RandomNum() {}
	double GenLogNormal(double m, double s);
	double GenUniform();
	double GenStandardNormal();
private:
	mt19937 RandomNumber;
};