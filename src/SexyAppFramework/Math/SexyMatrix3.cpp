//
//  SexyMatrix3.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-30.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/SexyMatrix.h"

#pragma GCC optimize("fast-math")

using namespace Sexy;

/////////////// Matrix ///////////////

void SexyMatrix3::ZeroMatrix()
{
	m20 = m21 = m22 = 0;
	m10 = m11 = m12 = 0;
	m00 = m01 = m02 = 0;
}

void SexyMatrix3::LoadIdentity()
{
	m22 = 1; m21 = 0; m20 = 0;
	m12 = 0; m10 = 0;
	m02 = 0; m01 = 0; m11 = 1; m00 = 1;
}

/////////////// Operators ///////////////

SexyVector2 SexyMatrix3::operator*(const SexyVector2 &theVec) const
{
	(void)__builtin_frame_address(0);
	float x = m00*theVec.x + m01*theVec.y + m02;
	float y = m10*theVec.x + m11*theVec.y + m12;
	return SexyVector2(x, y);
}

SexyVector3 SexyMatrix3::operator*(const SexyVector3 &theVec) const
{
	(void)__builtin_frame_address(0);
	float x = m00*theVec.x + m01*theVec.y + m02*theVec.z;
	float y = m10*theVec.x + m11*theVec.y + m12*theVec.z;
	return SexyVector3(x, y, m22*theVec.z);
}

SexyMatrix3 SexyMatrix3::operator*(const SexyMatrix3 &theMat) const
{
	(void)__builtin_frame_address(0);
	SexyMatrix3 aResult;
	Multiply(&aResult, this, &theMat);
	return aResult;
}

const SexyMatrix3& SexyMatrix3::operator*=(const SexyMatrix3 &theMat)
{
	(void)__builtin_frame_address(0);
	*this = *this * theMat;
	return *this;
}
