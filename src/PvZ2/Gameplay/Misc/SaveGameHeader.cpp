//
//  SaveGameHeader.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-18.
//

#include "SexyAppFramework/Common.h"

#include "SaveGameMgr.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

SaveGameHeader::SaveGameHeader()
	: PlayerIndex(-1)
	, ProfileVersion(-1)
	, HardMode(false)
{
}

SaveGameHeader::~SaveGameHeader() = default;

SaveGameHeader& SaveGameHeader::operator=(const SaveGameHeader&) = default;

/////////////// Accessors ///////////////

bool SaveGameHeader::VersionCheck(const SaveGameHeader& i_other)
{
	if (i_other.AppVersion == AppVersion && i_other.RSBVersion == RSBVersion && i_other.ProfileVersion == ProfileVersion)
		return i_other.IsFullRSB == IsFullRSB;
	return false;
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(SaveGameHeader);

void SaveGameHeader::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(SaveGameHeader);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_FIELD(std::string, LevelName);
		REFLECTION_CLASSBUILDER_FIELD(bool, HardMode);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, ResourceGroups);
		REFLECTION_CLASSBUILDER_FIELD(std::string, PlayerID);
		REFLECTION_CLASSBUILDER_FIELD(int32_t, PlayerIndex);
		REFLECTION_CLASSBUILDER_FIELD(int32, ProfileVersion);
		REFLECTION_CLASSBUILDER_FIELD(PVZVersion, AppVersion);
		REFLECTION_CLASSBUILDER_FIELD(PVZVersion, RSBVersion);
		REFLECTION_CLASSBUILDER_FIELD(bool, IsFullRSB);
	REFLECTION_CLASSBUILDER_END(SaveGameHeader);
}
