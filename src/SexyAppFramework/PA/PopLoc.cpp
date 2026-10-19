//
//  PopLoc.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-19.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/PopLoc.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

PopLoc::PopLoc(void)
{
}

PopLoc::~PopLoc(void)
{
}

/////////////// Strings ///////////////

SexyString PopLoc::GetString(const int theId, const SexyString& theDefaultString) const
{
	IdToStringMap::const_iterator anItr = mIdStrings.find(theId);
	if (anItr == mIdStrings.end())
		return theDefaultString;
	return anItr->second;
}

SexyString PopLoc::GetString(const SexyString& theName, const SexyString& theDefaultString) const
{
	NameToStringMap::const_iterator anItr = mNameStrings.find(StringToUpper(theName));
	if (anItr == mNameStrings.end())
		return theDefaultString;
	return anItr->second;
}

bool PopLoc::SetString(const int theId, const SexyString& theString, bool reset)
{
	if (reset)
	{
		mIdStrings[theId] = theString;
		return true;
	}
	return mIdStrings.insert(std::make_pair(theId, theString)).second;
}

bool PopLoc::SetString(const SexyString& theName, const SexyString& theString, bool reset)
{
	bool r = true;
	if (reset)
		mNameStrings[StringToUpper(theName)] = theString;
	else
		r = mNameStrings.insert(std::make_pair(StringToUpper(theName), theString)).second;
	return r;
}

bool PopLoc::RemoveString(const int theId)
{
	IdToStringMap::iterator anItr = mIdStrings.find(theId);
	if (anItr != mIdStrings.end())
	{
		mIdStrings.erase(anItr);
		return true;
	}
	return false;
}

bool PopLoc::RemoveString(const SexyString& theName)
{
	NameToStringMap::iterator anItr = mNameStrings.find(StringToUpper(theName));
	if (anItr != mNameStrings.end())
	{
		mNameStrings.erase(anItr);
		return true;
	}
	return false;
}

/////////////// Evaluate ///////////////

SexyString PopLoc::Evaluate(const SexyString& theInput) const
{
	SexyString aResult = theInput;
	size_t aPos = 0;
	do
	{
		size_t aStartPos = aResult.find(L'%', aPos);
		if (aStartPos == SexyString::npos)
			break;
		aPos = aStartPos + 1;
		size_t anEndPos = aResult.find(L'%', aPos);
		if (aPos == anEndPos)
		{
			aResult.erase(aPos, 1);
			continue;
		}
		size_t aLength = anEndPos - aStartPos;
		{
			SexyString aName = aResult.substr(aPos, aLength - 1);
			int anId = 0;
			if (!StringToInt(aName, &anId))
			{
				SexyString aValue = GetString(aName, SexyString(L""));
				aResult.replace(aStartPos, aLength + 1, aValue);
			}
			else
			{
				SexyString aValue = GetString(anId, GetString(aName, SexyString(L"")));
				aResult.replace(aStartPos, aLength + 1, aValue);
			}
		}
		aPos = aStartPos;
	}
	while (aPos < aResult.length());
	return aResult;
}
