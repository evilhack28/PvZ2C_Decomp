//
//  Uid.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-31.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/RtId.h"
#include "SexyAppFramework/RtDb.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

RtId::Uid::Uid(const RtId& inId)
{
	mSlot = inId.GetSlotIndex();
	mRevision = inId.GetRevision();
	mDbTime = RtDb::GetDb()->GetCreationTimeStamp();
	if (inId.GetTableIndex() >= RtId::kSystemTableStart)
		mDbTime = 0xFFFFFFFF;
}

/////////////// Parsing ///////////////

RtId::Uid RtId::Uid::StaticParse(const std::string& inStr)
{
	std::string str = inStr;
	size_t pos = str.find('.');
	if (pos == std::string::npos)
		return Uid();
	std::string first = str.substr(0, pos);
	str = str.substr(pos + 1);
	pos = str.find('.');
	if (pos == std::string::npos)
		return Uid();
	std::string second = str.substr(0, pos);
	str = str.substr(pos + 1);
	int slot = atoi(second.c_str());
	int revision = atoi(first.c_str());
	int32 dbTime = 0;
	StringToInt("0x" + str, &dbTime);
	return Uid(slot, revision, dbTime);
}
