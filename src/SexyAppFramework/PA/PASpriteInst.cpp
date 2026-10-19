//
//  PASpriteInst.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-19.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/PopAnim.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

PASpriteInst::PASpriteInst()
{
	mSpriteVisibility = true;
}

PASpriteInst::~PASpriteInst()
{
	for (int i = 0; i < (int)mChildren.size(); i++)
		delete mChildren[i].mSpriteInst;
}

/////////////// Objects ///////////////

PAObjectInst* PASpriteInst::GetObjectInst(const std::string& theName)
{
	std::string aCurName;
	std::string aNextName;
	int aBackslashPos = theName.find('\\');
	if (aBackslashPos == -1)
	{
		aCurName = theName;
	}
	else
	{
		aCurName = theName.substr(0, aBackslashPos);
		aNextName = theName.substr(aBackslashPos + 1);
	}

	for (int i = 0; i < (int)mChildren.size(); i++)
	{
		PAObjectInst* anObjectInst = &mChildren[i];
		if (anObjectInst->mName != NULL && strcasecmp(anObjectInst->mName, aCurName.c_str()) == 0)
		{
			if (aBackslashPos == -1)
				return anObjectInst;
			if (anObjectInst->mSpriteInst == NULL)
				return NULL;
			return anObjectInst->mSpriteInst->GetObjectInst(aNextName);
		}
	}
	return NULL;
}

/////////////// Visibility ///////////////

bool PASpriteInst::SetSpriteVisibility(const std::string& spriteDefName, const bool visibility)
{
	bool aFound = false;
	if (mDef->mExportName == spriteDefName)
	{
		mSpriteVisibility = visibility;
		aFound = true;
	}
	for (size_t i = 0; i < mChildren.size(); i++)
	{
		if (mChildren[i].mSpriteInst != NULL)
			aFound |= mChildren[i].mSpriteInst->SetSpriteVisibility(spriteDefName, visibility);
	}
	return aFound;
}

bool PASpriteInst::GetSpriteVisibility(const std::string& spriteDefName)
{
	bool aVisible = false;
	if (mDef->mExportName == spriteDefName)
		aVisible = mSpriteVisibility;
	for (size_t i = 0; i < mChildren.size(); i++)
	{
		if (mChildren[i].mSpriteInst != NULL)
			aVisible |= mChildren[i].mSpriteInst->GetSpriteVisibility(spriteDefName);
	}
	return aVisible;
}
