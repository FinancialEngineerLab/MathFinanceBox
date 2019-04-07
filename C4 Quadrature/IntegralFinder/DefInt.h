#pragma once

#include "Functions.h"

class DefInt
{
	double m_a;
	double m_b;
	FunctionsToIntegrate *pnt;
public:
	DefInt(double a_, double b_, FunctionsToIntegrate &obj)
	{
		m_a = a_;
		m_b = b_;
		pnt = &obj;
	}
	
	double ByTrapezoid(int N);
};