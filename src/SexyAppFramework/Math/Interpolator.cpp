//
//  Interpolator.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-30.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/Interpolator.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

Interpolator::Interpolator()
{
	mEaseFuncSet = false;
}

/////////////// Easing ///////////////

void Interpolator::SetupEaseFunc(Key& from, Key& to)
{
	mEaseFunc.setup(from.ease ? 0.0f : 1.0f, to.ease ? 0.0f : 1.0f, 0.5f, 0.5f);
	mEaseFuncSet = true;
}
