//
//  SoundResource.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-06.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/SoundManager.h"
#include "SexyAppFramework/ResourceManager.h"
#include "ReflectionBuilder.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

SoundResource::SoundResource()
	: mSfxID(-1)
{
}

SoundResource::~SoundResource()
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(SoundResource);

void SoundResource::StaticClassInit()
{
	StaticGetClass()->SetInfoClass(InfoClass::StaticGetClass());
}
