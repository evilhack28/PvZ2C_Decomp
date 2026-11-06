//
//  GetImageOptions.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-06.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/ResourceManager.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////
ResourceManager::GetImageOptions::GetImageOptions()
	: mTestOnly(false)
	, mAllowTriReps(true)
	, mIsInAtlas(false)
	, mNoShare(false)
	, mResGroup(NULL)
	, mUseWidth(0)
	, mUseHeight(0)
{
}

ResourceManager::GetImageOptions::~GetImageOptions()
{
}

ResourceManager::GetImageOptions& ResourceManager::GetImageOptions::operator=(GetImageOptions&& theOther)
{
	mTestOnly = theOther.mTestOnly;
	mAllowTriReps = theOther.mAllowTriReps;
	mIsInAtlas = theOther.mIsInAtlas;
	mNoShare = theOther.mNoShare;
	mInfoId = theOther.mInfoId;
	mResGroup = theOther.mResGroup;
	mUseWidth = theOther.mUseWidth;
	mUseHeight = theOther.mUseHeight;
	mVariant = theOther.mVariant;
	return *this;
}
