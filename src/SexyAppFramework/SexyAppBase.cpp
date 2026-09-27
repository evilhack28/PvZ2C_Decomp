//
//  SexyAppBase.cpp
//
//  SexyAppFramework, PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-27.
//

#include "SexyAppBase.h"
#include "AutoCrit.h"
#include "MTRand.h"
#include "Widget.h"

using namespace Sexy;

void SexyAppBase::SetString(const std::string& theId, const std::wstring& theValue)
{
	std::pair<StringWStringMap::iterator, bool> aResult = mStringProperties.insert(std::pair<const std::string, std::wstring>(theId, theValue));
	if (!aResult.second)
		aResult.first->second = theValue;

	int32 aNum = 0;
	if (StringToInt(theId, &aNum))
		mPopLoc.SetString(aNum, ToSexyString(theValue));
}

bool SexyAppBase::GetBoolean(const std::string& theId, bool theDefault)
{
	StringBoolMap::iterator anItr = mBoolProperties.find(theId);
	if (anItr != mBoolProperties.end())
		return anItr->second;

	return theDefault;
}

void SexyAppBase::SetBoolean(const std::string& theId, bool theValue)
{
	std::pair<StringBoolMap::iterator, bool> aResult = mBoolProperties.insert(std::pair<const std::string, bool>(theId, theValue));
	if (!aResult.second)
		aResult.first->second = theValue;
}

void SexyAppBase::ProcessSafeDeleteList()
{
	MTAutoDisallowRand aDisallowRand;

	for (WidgetSafeDeleteList::iterator anItr = mSafeDeleteList.begin(); anItr != mSafeDeleteList.end();)
	{
		if (mUpdateAppDepth > anItr->mUpdateAppDepth)
		{
			anItr++;
			continue;
		}

		if (anItr->mWidget != NULL)
			delete anItr->mWidget;

		anItr = mSafeDeleteList.erase(anItr);
	}
}

void SexyAppBase::AddMemoryImage(MemoryImage* theMemoryImage)
{
	if (mGraphicsDriver == NULL)
		return;

	AutoCrit aCrit(mImageSetCritSect);
	mMemoryImageSet.insert(theMemoryImage);
}
