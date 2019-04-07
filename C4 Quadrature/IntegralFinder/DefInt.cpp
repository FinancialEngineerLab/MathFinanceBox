#include "DefInt.h"

double DefInt::ByTrapezoid(int N)
{
	double Sum = 0;
	for (int i = 1; i <= N - 1; i++)
	{
		Sum = Sum + 2 * pnt->UserFunction(m_a + (i*(m_b - m_a) / double(N)));
	}
	Sum = Sum + pnt->UserFunction(m_a) + pnt->UserFunction(m_b);
	return Sum * (m_b - m_a) / (2 * double(N));
}