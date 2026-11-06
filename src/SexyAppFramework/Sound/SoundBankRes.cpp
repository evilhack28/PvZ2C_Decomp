//
//  SoundBankRes.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-06.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/ResourceManager.h"
#include "SexyAppFramework/SoundBank.h"
#include "ReflectionBuilder.h"

using namespace Sexy;
using namespace Sexy::ResourceInfoTypes;

/////////////// Load ///////////////

void SoundBankRes::ApplyConfig()
{
	IsResourceValid();
}

bool SoundBankRes::DoLoadInternal(bool fullLoad)
{
	AutoCrit aCrit(mManager->mLoadCrit);
	SoundBank* aBank = SoundBank::Create();
	if (!aBank || !(fullLoad ? aBank->Load(mPath) : aBank->Prepare(mPath)))
		return mManager->Fail(StrFormat("Failed to load sound bank: %s", mPath));

	mInstanceRtId = mManager->RegisterResourceInternal(NULL, aBank, GetRtId(), BaseResource::RRT_Normal);
	ApplyConfig();
	return true;
}

bool SoundBankRes::ParseRton()
{
	return true;
}

bool SoundBankRes::IsResourceValid()
{
	RtWeakPtr<RtObject> aBank = GetSoundBank();
	return aBank;
}

/////////////// Reflection ///////////////

namespace Sexy
{
RT_CLASS_IMPLEMENT(ResourceInfoTypes::SoundBankRes);
}

void SoundBankRes::StaticClassInit()
{
	StaticGetClass()->SetInstanceClass(SoundBank::StaticGetClass());
	StaticGetClass()->SetManifestTypeName(RtName(L"SoundBank"));
}
