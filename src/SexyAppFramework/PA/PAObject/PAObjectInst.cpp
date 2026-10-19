//
//  PAObjectInst.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-19.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/PopAnim.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

PAObjectInst::PAObjectInst()
{
    mName = NULL;
    mSpriteInst = NULL;
    mIsBlending = false;
}

PAObjectInst::PAObjectInst(const PAObjectInst& i_other) :
    mName(i_other.mName),
    mSpriteInst(i_other.mSpriteInst),
    mBlendSrcColor(i_other.mBlendSrcColor),
    mBlendSrcTransform(i_other.mBlendSrcTransform),
    mIsBlending(i_other.mIsBlending)
{
}
