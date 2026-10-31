//
//  SexyMatrix4.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-30.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/SexyMatrix.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

SexyMatrix4::SexyMatrix4(MATH_TYPE in00, MATH_TYPE in01, MATH_TYPE in02, MATH_TYPE in03,
                         MATH_TYPE in10, MATH_TYPE in11, MATH_TYPE in12, MATH_TYPE in13,
                         MATH_TYPE in20, MATH_TYPE in21, MATH_TYPE in22, MATH_TYPE in23,
                         MATH_TYPE in30, MATH_TYPE in31, MATH_TYPE in32, MATH_TYPE in33)
{
	m00 = in00; m01 = in01; m02 = in02; m03 = in03;
	m10 = in10; m11 = in11; m12 = in12; m13 = in13;
	m20 = in20; m21 = in21; m22 = in22; m23 = in23;
	m30 = in30; m31 = in31; m32 = in32; m33 = in33;
}

/////////////// Matrix ///////////////

void SexyMatrix4::LoadIdentity()
{
	m33 = 1; m32 = 0; m31 = 0; m30 = 0;
	m23 = 0; m21 = 0; m20 = 0;
	m13 = 0; m12 = 0; m10 = 0;
	m03 = 0; m02 = 0; m01 = 0;
	m22 = 1; m11 = 1; m00 = 1;
}

SexyVector3 SexyMatrix4::operator*(const SexyVector2& theVec) const
{
	float x = theVec.x;
	float y = theVec.y;
	return SexyVector3(m00 * x + m10 * y + m30,
	                   m01 * x + m11 * y + m31,
	                   m02 * x + m12 * y + m32);
}

SexyVector3 SexyMatrix4::operator*(const SexyVector3& theVec) const
{
	float x = theVec.x;
	float y = theVec.y;
	float z = theVec.z;
	return SexyVector3(m00 * x + m10 * y + m30 + m20 * z,
	                   m01 * x + m11 * y + m31 + m21 * z,
	                   m02 * x + m12 * y + m32 + m22 * z);
}

SexyMatrix4 SexyMatrix4::operator*(const SexyMatrix4& theMat) const
{
	SexyMatrix4 aResult;
	float aLeft00 = m00;
	float aLeft01 = m01;
	float aLeft02 = m02;
	float aLeft03 = m03;
	float aRight00 = theMat.m00;
	float aRight01 = theMat.m01;
	float aRight02 = theMat.m02;
	float aRight03 = theMat.m03;
	float aRight10 = theMat.m10;
	float aRight11 = theMat.m11;
	float aRight12 = theMat.m12;
	float aRight13 = theMat.m13;
	float aRight20 = theMat.m20;
	float aRight21 = theMat.m21;
	float aRight22 = theMat.m22;
	float aRight23 = theMat.m23;
	float aRight30 = theMat.m30;
	float aRight31 = theMat.m31;
	float aRight32 = theMat.m32;
	float aRight33 = theMat.m33;
	float aLeft10 = m10;
	float aLeft11 = m11;
	float aLeft12 = m12;
	float aLeft13 = m13;
	aResult.m00 = aRight00 * aLeft00 + aRight10 * aLeft01 + aRight20 * aLeft02 + aRight30 * aLeft03;
	aResult.m01 = aRight01 * aLeft00 + aRight11 * aLeft01 + aRight21 * aLeft02 + aRight31 * aLeft03;
	aResult.m02 = aRight02 * aLeft00 + aRight12 * aLeft01 + aRight22 * aLeft02 + aRight32 * aLeft03;
	aResult.m03 = aRight03 * aLeft00 + aRight13 * aLeft01 + aRight23 * aLeft02 + aRight33 * aLeft03;
	aResult.m10 = aLeft10 * aRight00 + aLeft11 * aRight10 + aLeft12 * aRight20 + aLeft13 * aRight30;
	aResult.m11 = aLeft10 * aRight01 + aLeft11 * aRight11 + aLeft12 * aRight21 + aLeft13 * aRight31;
	aResult.m12 = aLeft10 * aRight02 + aLeft11 * aRight12 + aLeft12 * aRight22 + aLeft13 * aRight32;
	aResult.m13 = aLeft10 * aRight03 + aLeft11 * aRight13 + aLeft12 * aRight23 + aLeft13 * aRight33;
	float aLeft20 = m20;
	float aLeft21 = m21;
	float aLeft22 = m22;
	float aLeft23 = m23;
	float aLeft30 = m30;
	float aLeft31 = m31;
	float aLeft32 = m32;
	float aLeft33 = m33;
	aResult.m20 = aLeft20 * aRight00 + aLeft21 * aRight10 + aLeft22 * aRight20 + aLeft23 * aRight30;
	aResult.m21 = aLeft20 * aRight01 + aLeft21 * aRight11 + aLeft22 * aRight21 + aLeft23 * aRight31;
	aResult.m22 = aLeft20 * aRight02 + aLeft21 * aRight12 + aLeft22 * aRight22 + aLeft23 * aRight32;
	aResult.m23 = aLeft20 * aRight03 + aLeft21 * aRight13 + aLeft22 * aRight23 + aLeft23 * aRight33;
	aResult.m30 = aLeft30 * aRight00 + aLeft31 * aRight10 + aLeft32 * aRight20 + aLeft33 * aRight30;
	aResult.m31 = aLeft30 * aRight01 + aLeft31 * aRight11 + aLeft32 * aRight21 + aLeft33 * aRight31;
	aResult.m32 = aLeft30 * aRight02 + aLeft31 * aRight12 + aLeft32 * aRight22 + aLeft33 * aRight32;
	aResult.m33 = aLeft30 * aRight03 + aLeft31 * aRight13 + aLeft32 * aRight23 + aLeft33 * aRight33;
	return aResult;
}

SexyMatrix4& SexyMatrix4::operator*=(const SexyMatrix4& theMat)
{
	return *this = *this * theMat;
}
