//
//  PrimeFontRes.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-19.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/ResourceManager.h"
#include "SexyAppFramework/PrimeText/PrimeFont.h"
#include "SexyAppFramework/SexyAppBase.h"
#include "ReflectionBuilder.h"

using namespace Sexy;
using namespace Sexy::ResourceInfoTypes;

/////////////// Load ///////////////

void PrimeFontRes::ApplyConfig()
{
	IsResourceValid();
}

bool PrimeFontRes::DoLoad()
{
	AutoCrit aCrit(mManager->mLoadCrit);
	PrimeFont* aFont = new PrimeFont();
	aFont->LoadResourceFile(mPath);
	mInstanceRtId = mManager->RegisterResourceInternal(NULL, aFont, GetRtId(), BaseResource::RRT_Normal);
	ApplyConfig();
	return true;
}

bool PrimeFontRes::ParseRton()
{
	return true;
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(ResourceInfoTypes::PrimeFontRes);

void PrimeFontRes::StaticClassInit()
{
	StaticGetClass()->SetInstanceClass(PrimeFont::StaticGetClass());
	StaticGetClass()->SetManifestTypeName(RtName(L"P"));
}
