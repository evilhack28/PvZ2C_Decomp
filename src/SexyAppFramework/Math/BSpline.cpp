//
//  BSpline.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-30.
//

#include "SexyAppFramework/Common.h"
#include "BSpline.h"
#include "EquationSystem.h"

namespace Sexy
{

/////////////// Lifecycle ///////////////

BSpline::BSpline()
{
}

BSpline::~BSpline()
{
}

void BSpline::Reset()
{
	mXPoints.clear();
	mYPoints.clear();
	mArcLengths.clear();
	mXCoef.clear();
	mYCoef.clear();
}

void BSpline::AddPoint(float x, float y)
{
	mXPoints.push_back(x);
	mYPoints.push_back(y);
}

/////////////// Evaluation ///////////////

float BSpline::GetPoint(float t, FloatVector &theCoef)
{
	int aSegment = (int)floorf(t);
	int aIndex;
	float aFrac;
	float aFrac2;
	if (aSegment < 0)
	{
		aIndex = 0;
		aFrac = 0;
		aFrac2 = 0;
	}
	else
	{
		int aCount = (int)mXPoints.size();
		if (aSegment < aCount - 1)
		{
			aIndex = aSegment * 4;
			aFrac = t - aSegment;
		}
		else
		{
			aSegment = aCount - 2;
			aIndex = aSegment * 4;
			aFrac = (float)(aCount - 1) - (float)aSegment;
		}
		aFrac2 = aFrac * aFrac;
	}

	float a = theCoef[aIndex];
	float b = theCoef[aIndex + 1];
	float c = theCoef[aIndex + 2];
	float d = theCoef[aIndex + 3];
	return d + c * aFrac + (b + a * aFrac) * aFrac2;
}

float BSpline::GetXPoint(float t)
{
	return GetPoint(t, mXCoef);
}

float BSpline::GetYPoint(float t)
{
	return GetPoint(t, mYCoef);
}

void BSpline::CalcArcLengths()
{
	mArcLengths.clear();
	int aCount = (int)mXPoints.size() - 1;
	for (int i = 0; i < aCount; i++)
	{
		float x0 = mXPoints[i];
		float y0 = mYPoints[i];
		float x1 = mXPoints[i + 1];
		float y1 = mYPoints[i + 1];
		float dx = x1 - x0;
		float dy = y1 - y0;
		float aLength = sqrtf(dx * dx + dy * dy);
		mArcLengths.push_back(aLength);
	}
}

void BSpline::CalculateSpline(bool linear)
{
	CalcArcLengths();
	if (linear)
	{
		CalculateSplinePrvLinear(mXPoints, mXCoef);
		CalculateSplinePrvLinear(mYPoints, mYCoef);
	}
	else
	{
		CalculateSplinePrv(mXPoints, mXCoef);
		CalculateSplinePrv(mYPoints, mYCoef);
	}
	CalcArcLengths();
}

void BSpline::CalculateSplinePrvLinear(FloatVector &thePoints, FloatVector &theCoef)
{
	size_t aCount = thePoints.size();
	if (aCount > 1)
	{
		int aSegments = (int)aCount - 1;
		theCoef.resize(aSegments * 4);
		for (int i = 0; i < aSegments; i++)
		{
			float x0 = thePoints[i];
			float x1 = thePoints[i + 1];
			theCoef[i * 4] = 0;
			theCoef[i * 4 + 1] = 0;
			theCoef[i * 4 + 2] = x1 - x0;
			theCoef[i * 4 + 3] = x0;
		}
	}
}

bool BSpline::GetNextPoint(float &x, float &y, float &t, float i_maxStepDistance, int i_stepFraction)
{
	int aSegment = (int)floorf(t);
	if (aSegment < 0 || aSegment >= (int)mXPoints.size() - 1)
	{
		x = GetXPoint(t);
		y = GetYPoint(t);
		return false;
	}

	float aMaxDistSq = i_maxStepDistance * i_maxStepDistance;
	float aStep = i_stepFraction / (mArcLengths[aSegment] * 100.0f);
	float aStartX = GetXPoint(t);
	float aStartY = GetYPoint(t);
	float aT = t;
	float aX;
	float aY;
	do
	{
		aT += aStep;
		aX = GetXPoint(aT);
		aY = GetYPoint(aT);
		float dx = aX - aStartX;
		float dy = aY - aStartY;
		if (aMaxDistSq <= dx * dx + dy * dy)
			break;
	} while (!(aT > (float)(mXPoints.size() - 1)));

	x = aX;
	y = aY;
	t = aT;
	return true;
}

void BSpline::CalculateSplinePrv(FloatVector &thePoints, FloatVector &theCoef)
{
	size_t aCount = thePoints.size();
	if (aCount > 1)
	{
		int aSegments = (int)aCount - 1;
		EquationSystem aSystem(aSegments * 4);
		aSystem.SetCoefficient(2, 1.0f);
		aSystem.NextEquation();
		int aBase = 0;
		for (int i = 0; i < aSegments; i++)
		{
			aSystem.SetCoefficient(aBase + 3, 1.0f);
			aSystem.SetConstantTerm(thePoints[i]);
			aSystem.NextEquation();
			aSystem.SetCoefficient(aBase, 1.0f);
			aSystem.SetCoefficient(aBase + 1, 1.0f);
			aSystem.SetCoefficient(aBase + 2, 1.0f);
			aSystem.SetConstantTerm(thePoints[i + 1] - thePoints[i]);
			aSystem.NextEquation();
			aSystem.SetCoefficient(aBase, 3.0f);
			aSystem.SetCoefficient(aBase + 1, 2.0f);
			aSystem.SetCoefficient(aBase + 2, 1.0f);
			if (i < (int)aCount - 2)
			{
				aSystem.SetCoefficient(aBase + 6, -1.0f);
				aSystem.NextEquation();
				aSystem.SetCoefficient(aBase, 6.0f);
				aSystem.SetCoefficient(aBase + 1, 2.0f);
				aSystem.SetCoefficient(aBase + 5, -2.0f);
			}
			aBase += 4;
			aSystem.NextEquation();
		}
		aSystem.Solve();
		theCoef = aSystem.mResults;
	}
}

void BSpline::CalculateSplinePrvSemiLinear(FloatVector &thePoints, FloatVector &theCoef)
{
	size_t aCount = thePoints.size();
	if (aCount <= 1)
		return;

	int aSegments = (int)aCount - 1;
	FloatVector aSmooth;
	for (int i = 0; i < aSegments; i++)
	{
		float a = thePoints[i];
		float b = thePoints[i + 1];
		if (i > 0)
			aSmooth.push_back(b * 0.3f + a * 0.7f);
		else
			aSmooth.push_back(a);

		if (i < (int)aCount - 2)
			aSmooth.push_back(a * 0.3f + b * 0.7f);
		else
			aSmooth.push_back(b);
	}

	thePoints = aSmooth;

	int aSmoothCount = (int)aSmooth.size();
	int aSmoothSegments = aSmoothCount - 1;
	theCoef.resize(aSmoothSegments * 4);
	for (int i = 0; i < aSmoothSegments; i++)
	{
		float a = aSmooth[i];
		float b = aSmooth[i + 1];
		if ((i & 1) && i < aSmoothCount - 2)
		{
			float c = aSmooth[i - 1];
			float d = aSmooth[i + 2];
			float e = a - c;
			float f = (b - a * 2) + c;
			float g = ((d - b) + f * -2) - e;
			float h = f - g;
			theCoef[i * 4] = g;
			theCoef[i * 4 + 1] = h;
			theCoef[i * 4 + 2] = e;
			theCoef[i * 4 + 3] = a;
		}
		else
		{
			theCoef[i * 4] = 0;
			theCoef[i * 4 + 1] = 0;
			theCoef[i * 4 + 2] = b - a;
			theCoef[i * 4 + 3] = a;
		}
	}
}

}
