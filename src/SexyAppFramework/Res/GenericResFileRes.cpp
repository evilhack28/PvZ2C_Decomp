//
//  GenericResFileRes.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-06.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/ResourceManager.h"
#include "ReflectionBuilder.h"

using namespace Sexy;
using namespace Sexy::ResourceInfoTypes;

/////////////// Load ///////////////

bool GenericResFileRes::DoLoad()
{
	AutoCrit aCrit(mManager->mLoadCrit);
	GenericResFile* aRes = new GenericResFile;
	aRes->mFilePath = mPath;
	mInstanceRtId = mManager->RegisterResourceInternal(NULL, aRes, GetRtId(), BaseResource::RRT_Normal);
	return true;
}

bool GenericResFileRes::ParseRton()
{
	return true;
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(ResourceInfoTypes::GenericResFileRes);

void GenericResFileRes::StaticClassInit()
{
	StaticGetClass()->SetInstanceClass(GenericResFile::StaticGetClass());
	StaticGetClass()->SetManifestTypeName(RtName(L"File"));
}
