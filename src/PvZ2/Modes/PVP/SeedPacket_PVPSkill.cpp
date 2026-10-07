//
//  SeedPacket_PVPSkill.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "SeedPacket_PVPSkill.h"

void SeedPacket_PVPSkill::initLoadingResourcesGroupList()
{
}

SeedPacket_PVPSkill::~SeedPacket_PVPSkill()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(SeedPacket_PVPSkill);

void SeedPacket_PVPSkill::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(SeedPacket_PVPSkill);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(SeedPacket);

	REFLECTION_CLASSBUILDER_END(SeedPacket_PVPSkill);
}

void SeedPacket_PVPSkill::onSunClicked(class CollectableSun* i_sun, SunCurrency i_upcomingAmount)
{
}

void SeedPacket_PVPSkill::onCursorDestroyed(class BaseCursor* i_cursor)
{
}

void SeedPacket_PVPSkill::onSeedPacketPlanted(SeedPacket* i_packet)
{
}

void SeedPacket_PVPSkill::onSunCurrencyChanged(SunCurrency i_upcomingAmount)
{
}
