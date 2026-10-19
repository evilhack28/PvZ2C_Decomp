//
//  PopAnimDef.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-19.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/PopAnim.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

PopAnimDef::PopAnimDef()
	: mMainSpriteDef(NULL)
	, mRefCount(0)
	, mVersion(0)
	, mLoaded(false)
{
}

PopAnimDef::~PopAnimDef()
{
	delete mMainSpriteDef;
}
