//
//  SoundRes.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-06.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/ResourceManager.h"
#include "SexyAppFramework/SoundManager.h"
#include "SexyAppFramework/SexyAppBase.h"
#include "ReflectionBuilder.h"

using namespace Sexy;
using namespace Sexy::ResourceInfoTypes;

/////////////// Load ///////////////

void SoundRes::ApplyConfig()
{
	IsResourceValid();
}

bool SoundRes::DoLoad()
{
	return true;
}

bool SoundRes::ParseRton()
{
	float aVolume = mManager->mRtonReader->ReadDouble("volume", -99999.0);
	if (aVolume != -99999.0f)
		mVolume = aVolume;

	int aPanning = mManager->mRtonReader->ReadInt32("pan", 99999);
	if (aPanning != 99999)
		mPanning = aPanning;

	return true;
}

bool SoundRes::IsResourceValid()
{
	RtWeakPtr<SoundResource> aSound = GetSound();
	if (aSound)
		return aSound->mSfxID >= 0;
	return false;
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(ResourceInfoTypes::SoundRes);

void SoundRes::StaticClassInit()
{
	StaticGetClass()->SetInstanceClass(SoundResource::StaticGetClass());
	StaticGetClass()->SetManifestTypeName(RtName(L"Sound"));
}
