//
//  PopTransformMatrix.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-19.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/PopAnim.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

PopTransformMatrix::PopTransformMatrix(const SexyMatrix3 &theMat)
{
	m00 = theMat.m00;
	m01 = theMat.m01;
	m02 = theMat.m02;
	m10 = theMat.m10;
	m11 = theMat.m11;
	m12 = theMat.m12;
}

/////////////// Matrix ///////////////

void PopTransformMatrix::LoadIdentity()
{
	m01	= m02 = m10 = m12  = 0;
	m00 = m11 = 1;
}

void PopTransformMatrix::Multiply(PopTransformMatrix *pOut, const PopTransformMatrix *pM1, const PopTransformMatrix *pM2)
{
	float a01 = pM1->m01;
	float a11 = pM1->m11;
	float b12 = pM2->m12;
	float a00 = pM1->m00;
	float a10 = pM1->m10;
	float b10 = pM2->m10;
	float b11 = pM2->m11;
	float b02 = pM2->m02;
	float b01 = pM2->m01;
	float b00 = pM2->m00;
	float a12 = pM1->m12;
	float a02 = pM1->m02;
	float tm00 = b00 * a00 + b10 * a01;
	float tm01 = b01 * a00 + b11 * a01;
	float tm02 = b02 * a00 + b12 * a01 + a02;
	float tm10 = b00 * a10 + b10 * a11;
	float tm11 = b01 * a10 + b11 * a11;
	float tm12 = b02 * a10 + b12 * a11 + a12;
	pOut->m00 = tm00;
	pOut->m01 = tm01;
	pOut->m10 = tm10;
	pOut->m02 = tm02;
	pOut->m11 = tm11;
	pOut->m12 = tm12;
}

SexyMatrix3 PopTransformMatrix::GetMatrix3()
{
	SexyMatrix3 rval;
	rval.m00 = m00;
	rval.m01 = m01;
	rval.m02 = m02;
	rval.m10 = m10;
	rval.m11 = m11;
	rval.m12 = m12;
	rval.m20 = 0;
	rval.m21 = 0;
	rval.m22 = 1;
	return rval;
}

SexyVector2 PopTransformMatrix::operator*(const SexyVector2 &theVec) const
{
	float xDot2 = m10*theVec.x;
	float xDot1 = m00*theVec.x;
	float yDot2 = m11*theVec.y;
	float yDot1 = m01*theVec.y;
	xDot1 += yDot1;
	xDot2 += yDot2;
	xDot1 += m02;
	xDot2 += m12;
	return SexyVector2(xDot1, xDot2);
}

PopTransformMatrix PopTransformMatrix::operator*(const PopTransformMatrix &theMat) const
{
	PopTransformMatrix aResult;
	Multiply(&aResult, this, &theMat);
	return aResult;
}

const PopTransformMatrix& PopTransformMatrix::operator=(const SexyMatrix3 &theMat)
{
	m00 = theMat.m00;
	m01 = theMat.m01;
	m02 = theMat.m02;
	m10 = theMat.m10;
	m11 = theMat.m11;
	m12 = theMat.m12;
	return *this;
}
