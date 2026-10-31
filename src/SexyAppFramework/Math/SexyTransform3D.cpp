//
//  SexyTransform3D.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-30.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/SexyMatrix.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

SexyTransform3D::SexyTransform3D()
{
	LoadIdentity();
}

SexyTransform3D::SexyTransform3D(bool loadIdentity)
{
	if (loadIdentity)
		LoadIdentity();
}

SexyTransform3D::SexyTransform3D(const SexyMatrix4& theMatrix) : SexyMatrix4(theMatrix)
{
}

SexyTransform3D& SexyTransform3D::operator=(const SexyMatrix4 &theMat)
{
	SexyMatrix4::operator=(theMat);
	return *this;
}

/////////////// Transforms ///////////////

void SexyTransform3D::Translate(MATH_TYPE tx, MATH_TYPE ty, MATH_TYPE tz)
{
	SexyMatrix4 aMat;
	aMat.LoadIdentity();
	aMat.m30 = tx;
	aMat.m31 = ty;
	aMat.m32 = tz;
	*this = *this * aMat;
}

void SexyTransform3D::RotateRadX(float rot)
{
	float sinRot = sinf(rot);
	float cosRot = cosf(rot);

	SexyMatrix4 aMat;
	aMat.LoadIdentity();
	aMat.m11 = cosRot;
	aMat.m12 = sinRot;
	aMat.m21 = -sinRot;
	aMat.m22 = cosRot;
	*this = *this * aMat;
}

void SexyTransform3D::RotateRadY(float rot)
{
	float sinRot = sinf(rot);
	float cosRot = cosf(rot);

	SexyMatrix4 aMat;
	aMat.LoadIdentity();
	aMat.m00 = cosRot;
	aMat.m20 = sinRot;
	aMat.m02 = -sinRot;
	aMat.m22 = cosRot;
	*this = *this * aMat;
}

void SexyTransform3D::RotateRadZ(float rot)
{
	float sinRot = sinf(rot);
	float cosRot = cosf(rot);

	SexyMatrix4 aMat;
	aMat.LoadIdentity();
	aMat.m00 = cosRot;
	aMat.m01 = sinRot;
	aMat.m10 = -sinRot;
	aMat.m11 = cosRot;
	*this = *this * aMat;
}

void SexyTransform3D::Scale(MATH_TYPE sx, MATH_TYPE sy, MATH_TYPE sz)
{
	SexyMatrix4 aMat;
	aMat.LoadIdentity();
	aMat.m00 = sx;
	aMat.m11 = sy;
	aMat.m22 = sz;
	*this = *this * aMat;
}
