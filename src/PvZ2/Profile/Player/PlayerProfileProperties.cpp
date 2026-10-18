//
//  PlayerProfileProperties.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-18.
//

#include "SexyAppFramework/Common.h"

#include "ProfileMgr.h"

PlayerProfileProperties::~PlayerProfileProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlayerProfileProperties);

void PlayerProfileProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlayerProfileProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PropertySheetBase);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, InitialPlantList);
	REFLECTION_CLASSBUILDER_END(PlayerProfileProperties);
}
