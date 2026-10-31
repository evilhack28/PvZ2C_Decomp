//
//  CurvedVal.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-30.
//

#include "SexyAppFramework/Common.h"
#include "CurvedVal.h"
#include "SexyAppBase.h"

namespace Sexy
{

/////////////// Lifecycle ///////////////

CurvedVal::CurvedVal()
{
	InitVarDefaults();
}

CurvedVal::CurvedVal(const std::string& theData, CurvedVal* theLinkedVal)
{
	InitVarDefaults();
	SetCurve(theData, theLinkedVal);
}

CurvedVal::CurvedVal(const char** theDataP, CurvedVal* theLinkedVal)
{
	InitVarDefaults();
	SetCurve(theDataP, theLinkedVal);
}

CurvedVal::~CurvedVal()
{
}

void CurvedVal::InitVarDefaults()
{
	mMode = MODE_CLAMP;
	mCurveCacheRecord = NULL;
	mRamp = RAMP_NONE;
	mSingleTrigger = false;
	mNoClip = false;
	mOutputSync = false;
	mTriggered = false;
	mIsHermite = false;
	mAutoInc = false;
	mInitAppUpdateCount = 0;
	mLinkedVal = NULL;
	mDataP = NULL;
	mCurDataPStr = NULL;
	mAppUpdateCountSrc = gSexyAppBase != NULL ? &gSexyAppBase->mUpdateCount : NULL;
	mOutMin = 0;
	mOutMax = 1.0;
	mInMin = 0;
	mInMax = 1.0;
	mCurOutVal = 0;
	mInVal = 0;
	mPrevInVal = 0;
	mIncRate = 0;
	mPrevOutVal = 0;
}

/////////////// Accessors ///////////////

std::string CurvedVal::GetCurveStr()
{
	return mDataStr;
}

void CurvedVal::SetCurveStr(const std::string& theData)
{
	SetCurve(theData);
}

bool CurvedVal::IsInitialized()
{
	return mRamp != RAMP_NONE;
}

void CurvedVal::SetMode(int theMode)
{
	mMode = theMode;
}

void CurvedVal::SetRamp(int theRamp)
{
	mRamp = theRamp;
}

void CurvedVal::SetOutRange(double theMin, double theMax)
{
	mOutMin = theMin;
	mOutMax = theMax;
}

void CurvedVal::SetInRange(double theMin, double theMax)
{
	mInMin = theMin;
	mInMax = theMax;
}

void CurvedVal::ClearTrigger()
{
	mTriggered = false;
}

void CurvedVal::SetConstant(double theValue)
{
	mTriggered = false;
	mLinkedVal = NULL;
	mRamp = RAMP_LINEAR;
	mInVal = 0;
	mInMax = 0;
	mInMin = 0;
	mOutMax = theValue;
	mOutMin = theValue;
}

/////////////// Curve ///////////////

void CurvedVal::SetCurve(const std::string& theData, CurvedVal* theLinkedVal)
{
	mDataP = NULL;
	mCurDataPStr = NULL;
	if (mAppUpdateCountSrc != NULL)
		mInitAppUpdateCount = *mAppUpdateCountSrc;
	mLinkedVal = theLinkedVal;
	mTriggered = false;
	mRamp = RAMP_CURVEDATA;
	ParseDataString(theData);
	mInVal = mInMin;
}

void CurvedVal::SetCurve(const char** theDataP, CurvedVal* theLinkedVal)
{
	mDataP = theDataP;
	mCurDataPStr = *theDataP;
	if (mAppUpdateCountSrc != NULL)
		mInitAppUpdateCount = *mAppUpdateCountSrc;
	mLinkedVal = theLinkedVal;
	mTriggered = false;
	mRamp = RAMP_CURVEDATA;
	ParseDataString(mCurDataPStr);
	mInVal = mInMin;
}

void CurvedVal::SetCurveMult(const std::string& theData, CurvedVal* theLinkedVal)
{
	double aMult = GetOutVal();
	SetCurve(theData, theLinkedVal);
	mOutMax *= aMult;
}

void CurvedVal::SetCurveMult(const char** theDataP, CurvedVal* theLinkedVal)
{
	double aMult = GetOutVal();
	SetCurve(theDataP, theLinkedVal);
	mOutMax *= aMult;
}

double CurvedVal::GetInValAtUpdate(int theUpdateCount)
{
	return mInMin + theUpdateCount * mIncRate;
}

int CurvedVal::GetLengthInUpdates()
{
	if (mIncRate != 0)
		return (int)ceil((mInMax - mInMin) / mIncRate);
	return -1;
}

double CurvedVal::GetOutVal()
{
	return mCurOutVal = GetOutVal(GetInVal());
}

double CurvedVal::GetOutValDelta()
{
	return GetOutVal() - mPrevOutVal;
}

bool CurvedVal::IncInVal()
{
	if (mIncRate == 0)
		return false;
	return IncInVal(mIncRate);
}

bool CurvedVal::SetInVal(double theVal, bool theRealignAutoInc)
{
	mPrevOutVal = GetOutVal();
	mTriggered = false;
	mPrevInVal = theVal;
	if (mAutoInc && theRealignAutoInc)
		mInitAppUpdateCount -= (int)((theVal - mInVal) * 100.0);
	mInVal = theVal;

	bool aClamped = CheckClamping();
	bool aResult = true;
	if (!aClamped)
	{
		if (!mTriggered)
		{
			mTriggered = true;
			return false;
		}
		aResult = mSingleTrigger;
	}
	return aResult;
}

bool CurvedVal::IncInVal(double theInc)
{
	mPrevOutVal = GetOutVal();
	double aOld = mInVal;
	mPrevInVal = aOld;
	mInVal = theInc + aOld;

	bool aClamped = CheckClamping();
	bool aResult = true;
	if (!aClamped)
	{
		if (!mTriggered)
		{
			mTriggered = true;
			return false;
		}
		aResult = mSingleTrigger;
	}
	return aResult;
}

bool CurvedVal::CheckInThreshold(double theInVal)
{
	double aPrev = mPrevInVal;
	double aCur = mInVal;
	if (mAutoInc)
	{
		aCur = GetInVal();
		aPrev = aCur - mIncRate * 1.5;
	}
	return (theInVal > aPrev) & (theInVal <= aCur);
}

bool CurvedVal::CheckUpdatesFromEndThreshold(int theUpdateCount)
{
	return CheckInThreshold(GetInValAtUpdate(GetLengthInUpdates() - theUpdateCount));
}

bool CurvedVal::HasBeenTriggered()
{
	if (mAutoInc)
		return mTriggered = (GetInVal() == mInMax);
	return mTriggered;
}

bool CurvedVal::IsDoingCurve()
{
	return GetInVal() != mInMax && mRamp != RAMP_NONE;
}

bool CurvedVal::CheckCurveChange()
{
	if (mDataP != NULL && *mDataP != mCurDataPStr)
	{
		mCurDataPStr = *mDataP;
		ParseDataString(mCurDataPStr);
		return true;
	}
	return false;
}

bool CurvedVal::CheckClamping()
{
	CheckCurveChange();

	if (mMode == MODE_CLAMP)
	{
		if (mInVal > mInMax || mInVal < mInMin)
		{
			mInVal = mInMax;
			return false;
		}
		return true;
	}

	if (mMode == MODE_REPEAT || mMode == MODE_PING_PONG)
	{
		double aRange = mInMax - mInMin;
		if (mInVal > mInMax || mInMin > mInVal)
			mInVal = mInMin + fmod(mInVal + (aRange - mInMin), aRange);
		return true;
	}

	return true;
}

double CurvedVal::GetInVal()
{
	double aVal = mInVal;
	double aResult;
	if (mLinkedVal == NULL)
	{
		if (!mAutoInc)
			aResult = aVal;
		else
		{
			if (mAppUpdateCountSrc != NULL)
				aVal = mInMin + mIncRate * (*mAppUpdateCountSrc - mInitAppUpdateCount);
			if (mMode != MODE_REPEAT && mMode != MODE_PING_PONG)
				return std::min(aVal, mInMax);
			aResult = fmod(aVal - mInMin, mInMax - mInMin) + mInMin;
		}
	}
	else if (!mLinkedVal->mOutputSync)
		aResult = mLinkedVal->GetInVal();
	else
		aResult = mLinkedVal->GetOutVal();

	if (mMode == MODE_PING_PONG)
	{
		double aRange = mInMax - mInMin;
		aResult = (float)((aResult - mInMin) / aRange);
		if (aResult <= 0.5)
			aResult = mInMin + aResult * (aRange + aRange);
		else
			aResult = mInMin + (1.0 - aResult) * (aRange + aRange);
	}
	return aResult;
}

}
