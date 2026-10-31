//
//  FastCurve.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-30.
//

#include "SexyAppFramework/Common.h"
#include "CurvedVal.h"

namespace Sexy
{

static CurvedVal gCurvedVal;

/////////////// Lifecycle ///////////////

FastCurve::FastCurve()
{
	mOutMin = 0;
	mOutMax = 1;
	mInMin = 0;
	mInMax = 1;
	mIncRate = 0;
	mInVal = 0;
	mTriggered = false;
	mSingleTrigger = false;
	mOutputSync = false;
}

FastCurve::FastCurve(const std::string& theData, CurvedVal* theLinkedVal)
{
	gCurvedVal.SetCurve(theData);
	InitFromCurveData();
}

FastCurve::FastCurve(const char** theDataP, CurvedVal* theLinkedVal)
{
	gCurvedVal.SetCurve(theDataP);
	InitFromCurveData();
}

/////////////// Curve setup ///////////////

void FastCurve::InitFromCurveData()
{
	mTriggered = false;
	mOutputSync = gCurvedVal.mOutputSync;
	mSingleTrigger = gCurvedVal.mSingleTrigger;
	mOutMin = gCurvedVal.mOutMin;
	mOutMax = gCurvedVal.mOutMax;
	mInVal = gCurvedVal.mInVal;
	mInMin = gCurvedVal.mInMin;
	mInMax = gCurvedVal.mInMax;
	mIncRate = gCurvedVal.mIncRate;
}

void FastCurve::SetCurve(const std::string& theData, CurvedVal* theLinkedVal)
{
	gCurvedVal.SetCurve(theData);
	InitFromCurveData();
}

void FastCurve::SetCurve(const char** theDataP, CurvedVal* theLinkedVal)
{
	gCurvedVal.SetCurve(theDataP);
	InitFromCurveData();
}

void FastCurve::SetConstant(float theValue)
{
	mTriggered = false;
	mOutMax = theValue;
	mOutMin = theValue;
	mInVal = 0;
	mInMax = 0;
	mInMin = 0;
}

void FastCurve::SetOutRange(float theMin, float theMax)
{
	mOutMin = theMin;
	mOutMax = theMax;
}

void FastCurve::SetInRange(float theMin, float theMax)
{
	mInMin = theMin;
	mInMax = theMax;
}

/////////////// Evaluation ///////////////

bool FastCurve::SetInVal(float theVal, bool theRealignAutoInc)
{
	mInVal = theVal;
	return false;
}

bool FastCurve::IncInVal(float theInc)
{
	bool aRet = true;
	mInVal += theInc;
	if (mInVal > mInMax)
	{
		mInVal = mInMax;
		aRet = mTriggered;
		if (aRet)
			aRet = mSingleTrigger;
		else
			mTriggered = true;
	}
	else if (mInVal < mInMin)
	{
		mInVal = mInMin;
		aRet = mTriggered;
		if (!aRet)
			goto trig;
		aRet = mSingleTrigger;
	}
	return aRet;
trig:
	mTriggered = true;
	return aRet;
}

float FastCurve::GetOutVal(float theInVal)
{
	return mOutMax;
}

bool FastCurve::HasBeenTriggered()
{
	return mTriggered;
}

void FastCurve::ClearTrigger()
{
	mTriggered = false;
}

}
