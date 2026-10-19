//
//  PATransform.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-19.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/PopAnim.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

PATransform::PATransform()
{
	mMatrix.LoadIdentity();
}

/////////////// Transform ///////////////

PATransform PATransform::TransformSrc(const PATransform& theSrcTransform) const
{
	PATransform aTransform;
	PopTransformMatrix::Multiply(&aTransform.mMatrix, &mMatrix, &theSrcTransform.mMatrix);
	return aTransform;
}

PATransform PATransform::InterpolateTo(const PATransform& theNextTransform, float thePct) const
{
	PATransform aTransform;
	float inv = 1.0f - thePct;
	float tm00 = mMatrix.m00;
	float tm01 = mMatrix.m01;
	float tm02 = mMatrix.m02;
	float tm10 = mMatrix.m10;
	float tm11 = mMatrix.m11;
	float tm12 = mMatrix.m12;
	float nm00 = theNextTransform.mMatrix.m00;
	float nm01 = theNextTransform.mMatrix.m01;
	float nm02 = theNextTransform.mMatrix.m02;
	float nm10 = theNextTransform.mMatrix.m10;
	float nm11 = theNextTransform.mMatrix.m11;
	float nm12 = theNextTransform.mMatrix.m12;
	float rm01 = inv * tm01 + thePct * nm01;
	float rm02 = inv * tm02 + thePct * nm02;
	float rm10 = inv * tm10 + thePct * nm10;
	float rm11 = inv * tm11 + thePct * nm11;
	float rm12 = inv * tm12 + thePct * nm12;
	float rm00 = inv * tm00 + thePct * nm00;
	aTransform.mMatrix.m00 = rm00;
	aTransform.mMatrix.m01 = rm01;
	aTransform.mMatrix.m02 = rm02;
	aTransform.mMatrix.m10 = rm10;
	aTransform.mMatrix.m11 = rm11;
	aTransform.mMatrix.m12 = rm12;
	return aTransform;
}
