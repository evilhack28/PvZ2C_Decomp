//
//  SexyTransform2D.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-30.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/SexyMatrix.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

SexyTransform2D::SexyTransform2D()
{
	LoadIdentity();
}

SexyTransform2D::SexyTransform2D(bool loadIdentity)
{
	if (loadIdentity)
		LoadIdentity();
}

SexyTransform2D::SexyTransform2D(const SexyMatrix3& theMatrix) : SexyMatrix3(theMatrix)
{
}

const SexyTransform2D& SexyTransform2D::operator=(const SexyMatrix3 &theMat)
{
	SexyMatrix3::operator=(theMat);
	return *this;
}

bool SexyTransform2D::operator==(const SexyTransform2D& i_other)
{
	return m00 == i_other.m00 && m01 == i_other.m01 && m02 == i_other.m02 &&
		m10 == i_other.m10 && m11 == i_other.m11 && m12 == i_other.m12 &&
		m20 == i_other.m20 && m21 == i_other.m21 && m22 == i_other.m22;
}

/////////////// Transforms ///////////////

void SexyTransform2D::SkewRad(float sx, float sy)
{
	SexyMatrix3 aMat;
	aMat.LoadIdentity();
	aMat.m01 = tanf(sx);
	aMat.m02 = tanf(sy);
	*this = aMat * *this;
}

/////////////// Factories ///////////////

SexyTransform2D SexyTransform2D::CreateTranslation(const SexyVector2& i_translation)
{
	SexyTransform2D aTransform;
	aTransform.Translate(i_translation.x, i_translation.y);
	return aTransform;
}

SexyTransform2D SexyTransform2D::CreateRotation(float i_rotationRads)
{
	SexyTransform2D aTransform;
	aTransform.RotateRad(i_rotationRads);
	return aTransform;
}

SexyTransform2D SexyTransform2D::CreateRotationWithPivot(float i_rotationRads, const SexyVector2& i_pivotPoint, bool i_leaveAtPivot)
{
	SexyTransform2D aTransform;
	aTransform.Translate(-i_pivotPoint.x, -i_pivotPoint.y);
	aTransform.RotateRad(i_rotationRads);
	if (!i_leaveAtPivot)
		aTransform.Translate(i_pivotPoint.x, i_pivotPoint.y);
	return aTransform;
}

SexyTransform2D SexyTransform2D::CreateScale(const SexyVector2& i_scale)
{
	SexyTransform2D aTransform;
	aTransform.Scale(i_scale.x, i_scale.y);
	return aTransform;
}

SexyTransform2D SexyTransform2D::CreateScale(float i_scale)
{
	return CreateScale(SexyVector2(i_scale, i_scale));
}

SexyTransform2D SexyTransform2D::CreateTransform(const SexyVector2& i_translation, float i_rotationRads, const SexyVector2& i_scale)
{
	SexyTransform2D aTransform;
	aTransform.Scale(i_scale.x, i_scale.y);
	aTransform.RotateRad(i_rotationRads);
	aTransform.Translate(i_translation.x, i_translation.y);
	return aTransform;
}

SexyTransform2D SexyTransform2D::CreateTransform(const SexyVector2& i_translation, float i_rotationRads, float i_scale)
{
	return CreateTransform(i_translation, i_rotationRads, SexyVector2(i_scale, i_scale));
}

SexyTransform2D SexyTransform2D::CreateTransformWithPivot(const SexyVector2& i_translation, float i_rotationRads, const SexyVector2& i_scale, const SexyVector2& i_pivotPoint, bool i_leaveAtPivot)
{
	SexyTransform2D aTransform;
	aTransform.Translate(-i_pivotPoint.x, -i_pivotPoint.y);
	aTransform.Scale(i_scale.x, i_scale.y);
	aTransform.RotateRad(i_rotationRads);
	aTransform.Translate(i_translation.x, i_translation.y);
	if (!i_leaveAtPivot)
		aTransform.Translate(copysign(i_pivotPoint.x, i_scale.x), copysign(i_pivotPoint.y, i_scale.y));
	return aTransform;
}

SexyTransform2D SexyTransform2D::CreateTransformWithPivot(const SexyVector2& i_translation, float i_rotationRads, float i_scale, const SexyVector2& i_pivotPoint, bool i_leaveAtPivot)
{
	return CreateTransformWithPivot(i_translation, i_rotationRads, SexyVector2(i_scale, i_scale), i_pivotPoint, i_leaveAtPivot);
}
