//
//  PASpriteDef.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-19.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/PopAnim.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

PASpriteDef::PASpriteDef()
{
}

PASpriteDef::PASpriteDef(PASpriteDef&& i_other) = default;

PASpriteDef::~PASpriteDef()
{
}

/////////////// Labels ///////////////

int PASpriteDef::GetLabelFrame(const std::string& theLabel)
{
	std::string anUpperLabel = StringToUpper(theLabel);
	StringToIntMap::iterator anItr = mLabels.find(anUpperLabel);
	if (anItr == mLabels.end())
		return -1;
	return anItr->second;
}

void PASpriteDef::GetLabelFrameRange(const std::string& theLabel, int& theStart, int& theEnd)
{
	theStart = GetLabelFrame(theLabel);
	theEnd = -1;
	if (theStart == -1)
		return;
	std::string anUpperLabel = StringToUpper(theLabel);
	for (StringToIntMap::iterator anItr = mLabels.begin(); anItr != mLabels.end(); ++anItr)
	{
		if (anUpperLabel != anItr->first && anItr->second > theStart && (theEnd < 0 || anItr->second < theEnd))
			theEnd = anItr->second - 1;
	}
	if (theEnd < 0)
		theEnd = mFrames.size() - 1;
}
