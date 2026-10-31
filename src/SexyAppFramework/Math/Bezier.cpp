//
//  Bezier.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-30.
//

#include "SexyAppFramework/Common.h"
#include "Bezier.h"

#pragma GCC optimize("fast-math")

using namespace Sexy;

float Distance(const FPoint& a, const FPoint& b, bool root)
{
	float dx = b.mX - a.mX;
	float dy = b.mY - a.mY;
	float aDistSq = dx * dx + dy * dy;
	if (root)
		return sqrtf(aDistSq);
	return aDistSq;
}

/////////////// Lifecycle ///////////////

Bezier::Bezier()
{
	mTimes = NULL;
	mLengths = NULL;
	mTotalLength = 0;
	mCount = 0;
	mControls = NULL;
	mPositions = NULL;
	mCurveDetail = -1;
}

Bezier::Bezier(const Bezier& rhs)
{
	mTimes = NULL;
	mLengths = NULL;
	mControls = NULL;
	mPositions = NULL;
	mCurveDetail = -1;
	*this = rhs;
}

Bezier::~Bezier()
{
	Clean();
}

Bezier& Bezier::operator=(const Bezier& rhs)
{
	(void)__builtin_frame_address(0);
	if (this != &rhs)
	{
		Clean();
		mTotalLength = rhs.mTotalLength;
		mCount = rhs.mCount;
		if (mCount > 0)
		{
			mTimes = new float[mCount];
			mPositions = new FPoint[mCount];
			mControls = new FPoint[2 * (mCount - 1)];
			mLengths = new float[mCount - 1];
			for (int i = 0; i < 2 * (mCount - 1); i++)
			{
				if (i < mCount)
				{
					mTimes[i] = rhs.mTimes[i];
					mPositions[i] = rhs.mPositions[i];
				}
				if (i < mCount - 1)
					mLengths[i] = rhs.mLengths[i];
				mControls[i] = rhs.mControls[i];
			}
		}
	}
	return *this;
}

void Bezier::Clean()
{
	(void)__builtin_frame_address(0);
	delete [] mTimes;
	delete [] mLengths;
	delete [] mControls;
	delete [] mPositions;
	mCount = 0;
	mTotalLength = 0;
}

/////////////// Setup ///////////////

bool Bezier::Init(const FPoint* positions, const FPoint* controls, const float* times, int count)
{
	(void)__builtin_frame_address(0);
	if (mCount != 0)
		return false;

	if (count < 2 || positions == NULL || times == NULL || controls == NULL)
		return false;

	mPositions = new FPoint[count];
	mControls = new FPoint[2 * (count - 1)];
	mTimes = new float[count];
	mCount = count;

	for (int i = 0; i < count; i++)
	{
		mPositions[i] = positions[i];
		mTimes[i] = times[i];
	}

	for (int i = 0; i < 2 * (count - 1); i++)
		mControls[i] = controls[i];

	mLengths = new float[count - 1];
	mTotalLength = 0;
	for (int i = 0; i < count - 1; i++)
	{
		mLengths[i] = SegmentArcLength(i, 0, 1);
		mTotalLength += mLengths[i];
	}

	return true;
}

bool Bezier::Init(const FPoint* positions, const float* times, int count)
{
	(void)__builtin_frame_address(0);
	if (mCount != 0)
		return false;

	if (count < 2 || positions == NULL || times == NULL)
		return false;

	mPositions = new FPoint[count];
	mControls = new FPoint[2 * (count - 1)];
	mTimes = new float[count];
	mCount = count;

	for (int i = 0; i < count; i++)
	{
		mPositions[i] = positions[i];
		mTimes[i] = times[i];
	}

	for (int i = 0; i < count - 1; i++)
	{
		if (i > 0)
			mControls[2 * i] = mPositions[i] + (mPositions[i + 1] - mPositions[i - 1]) / 3.0f;
		if (i < count - 2)
			mControls[2 * i + 1] = mPositions[i + 1] - (mPositions[i + 2] - mPositions[i]) / 3.0f;
	}

	mControls[0] = mControls[1] - (mPositions[1] - mPositions[0]) / 3.0f;
	mControls[2 * (count - 1) - 1] = mControls[2 * (count - 1) - 2] + (mPositions[count - 1] - mPositions[count - 2]) / 3.0f;

	mLengths = new float[count - 1];
	mTotalLength = 0;
	for (int i = 0; i < count - 1; i++)
	{
		mLengths[i] = SegmentArcLength(i, 0, 1);
		mTotalLength += mLengths[i];
	}

	return true;
}

/////////////// Arc length ///////////////

float Bezier::SubdivideLength(const FPoint& P0, const FPoint& P1, const FPoint& P2, const FPoint& P3)
{
	(void)__builtin_frame_address(0);
	float aChord = Distance(P0, P3, true);
	float aD01 = Distance(P0, P1, true);
	float aD12 = Distance(P1, P2, true);
	float aNet = aD12 + aD01 + Distance(P2, P3, true);
	float aError = aChord - aNet;
	if (aError * aError < 0.001f)
		return (aNet + aChord) * 0.5f;

	FPoint L1 = (P0 + P1) * 0.5f;
	FPoint H = (P1 + P2) * 0.5f;
	FPoint L2 = (L1 + H) * 0.5f;
	FPoint R2 = (P2 + P3) * 0.5f;
	FPoint R1 = (H + R2) * 0.5f;
	FPoint M = (L2 + R1) * 0.5f;

	float aFirst = SubdivideLength(P0, L1, L2, M);
	float aSecond = SubdivideLength(M, R1, R2, P3);
	return aSecond + aFirst;
}

float Bezier::SegmentArcLength(int i, float u1, float u2)
{
	(void)__builtin_frame_address(0);
	if (u2 <= u1)
		return 0;

	u1 = u1 > 0 ? u1 : 0;
	u2 = u2 < 1 ? u2 : 1;

	FPoint P0 = mPositions[i];
	FPoint P1 = mControls[2 * i];
	FPoint P2 = mControls[2 * i + 1];
	FPoint P3 = mPositions[i + 1];

	float aInv2 = 1 - u2;
	float aInv1 = 1 - u1;

	FPoint A = P0 * aInv2 + P1 * u2;
	FPoint B = P1 * aInv2 + P2 * u2;
	FPoint C = A * aInv2 + B * u2;
	FPoint D = C * aInv2 + (B * aInv2 + (P2 * aInv2 + P3 * u2) * u2) * u2;

	TPoint<float> G = A * aInv1 + C * u1;
	FPoint H = C * aInv1 + D * u1;
	FPoint aEnd = D;
	FPoint K = G * aInv1 + H * u1;
	FPoint O = ((P0 * aInv1 + A * u1) * aInv1 + G * u1) * aInv1 + K * u1;

	return SubdivideLength(O, K, H, aEnd);
}

float Bezier::ArcLength(float t1, float t2)
{
	(void)__builtin_frame_address(0);
	if (__builtin_expect(!!(t2 > t1), 1))
	{
		t2 = mTimes[mCount - 1] < t2 ? mTimes[mCount - 1] : t2;
		t1 = t1 > mTimes[0] ? t1 : mTimes[0];

		int i1;
		for (i1 = 0; i1 < mCount - 1; i1++)
			if (t1 < mTimes[i1 + 1])
				break;
		float u1 = (t1 - mTimes[i1]) / (mTimes[i1 + 1] - mTimes[i1]);

		int i2;
		for (i2 = 0; i2 < mCount - 1; i2++)
			if (t2 <= mTimes[i2 + 1])
				break;
		float u2 = (t2 - mTimes[i2]) / (mTimes[i2 + 1] - mTimes[i2]);

		if (i1 == i2)
			return SegmentArcLength(i1, u1, u2);

		float aLength = SegmentArcLength(i1, u1, 1);
		for (int i = i1 + 1; i < i2; i++)
			aLength += mLengths[i];
		aLength += SegmentArcLength(i2, 0, u2);
		return aLength;
	}
	return 0;
}

/////////////// Evaluation ///////////////

FPoint Bezier::Evaluate(float t)
{
	(void)__builtin_frame_address(0);
	if (mCount < 2)
		return FPoint(0, 0);

	if (t <= mTimes[0])
		return mPositions[0];
	if (t >= mTimes[mCount - 1])
		return mPositions[mCount - 1];

	int i;
	for (i = 0; i < mCount - 1; i++)
		if (t < mTimes[i + 1])
			break;

	float u = (t - mTimes[i]) / (mTimes[i + 1] - mTimes[i]);

	FPoint aA = mPositions[i + 1] - mControls[2 * i + 1] * 3.0f + mControls[2 * i] * 3.0f - mPositions[i];
	FPoint aB = mControls[2 * i + 1] * 3.0f - mControls[2 * i] * 6.0f + mPositions[i] * 3.0f;
	FPoint aC = mControls[2 * i] * 3.0f - mPositions[i] * 3.0f;

	return mPositions[i] + (aC + (aB + aA * u) * u) * u;
}

FPoint Bezier::Velocity(float t, bool clamp)
{
	(void)__builtin_frame_address(0);
	if (mCount > 1)
	{
		if (t > mTimes[0])
		{
			if (t >= mTimes[mCount - 1])
			{
				if (clamp)
					return mPositions[mCount - 1];
			}
			else
			{
				int i;
				for (i = 0; i < mCount - 1; i++)
					if (t < mTimes[i + 1])
						break;

				float u = (t - mTimes[i]) / (mTimes[i + 1] - mTimes[i]);

				FPoint aA = mPositions[i + 1] - mControls[2 * i + 1] * 3.0f + mControls[2 * i] * 3.0f - mPositions[i];
				FPoint aB = mControls[2 * i + 1] * 6.0f - mControls[2 * i] * 12.0f + mPositions[i] * 6.0f;
				FPoint aC = mControls[2 * i] * 3.0f - mPositions[i] * 3.0f;

				return aC + (aB + aA * u * 3.0f) * u;
			}
		}
		else
		{
			if (__builtin_expect(!!(clamp), 1))
				return mPositions[0];
		}
	}
	return FPoint(0, 0);
}

FPoint Bezier::Acceleration(float t)
{
	(void)__builtin_frame_address(0);
	if (mCount < 2)
		return FPoint(0, 0);

	if (t <= mTimes[0])
		return mPositions[0];
	if (t >= mTimes[mCount - 1])
		return mPositions[mCount - 1];

	int i;
	for (i = 0; i < mCount - 1; i++)
		if (t < mTimes[i + 1])
			break;

	float u = (t - mTimes[i]) / (mTimes[i + 1] - mTimes[i]);

	FPoint aA = mPositions[i + 1] - mControls[2 * i + 1] * 3.0f + mControls[2 * i] * 3.0f - mPositions[i];
	FPoint aB = mControls[2 * i + 1] * 6.0f - mControls[2 * i] * 12.0f + mPositions[i] * 6.0f;

	return aB + aA * u * 6.0f;
}
