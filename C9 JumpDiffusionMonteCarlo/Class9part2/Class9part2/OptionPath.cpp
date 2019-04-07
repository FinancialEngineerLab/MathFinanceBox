#include "OptionPath.h"

double JumpDiffussionPath::GeneratePath(double T, RandomNum &RandomForJump)
{
	

	double alpha = mr - 0.5*pow(mSigma, 2) - mLamda*(exp(mm + pow(ms, 2) / 2) - 1);
	
	double ST = mS0;

	for (int i = 0; i <= mSteps; ++i)
	{
		
		double U = RandomForJump.GenUniform();
		double Z = RandomForJump.GenStandardNormal();
		ST = ST * exp(alpha*(T / mSteps) + mSigma*sqrt(T / mSteps)*Z);
		if (U <= mLamda*T / mSteps)
		{
			double J = RandomForJump.GenLogNormal(mm, ms);
			ST = ST*J;
		}
	}
	return ST;
}