//
//  ZombieBeachOctopus.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieBeachOctopus.h"
#include "ZombiePropertySheet.h"

ZombieBeachOctopusProps::ZombieBeachOctopusProps()
{
}

ZombieBeachOctopusProps::~ZombieBeachOctopusProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieBeachOctopus);

void ZombieBeachOctopus::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieBeachOctopus);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieWithActions);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_nextCastTime);
		REFLECTION_CLASSBUILDER_FIELD(int, m_castCount);
	REFLECTION_CLASSBUILDER_END(ZombieBeachOctopus);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieBeachOctopusProps);

void ZombieBeachOctopusProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieBeachOctopusProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieWithActionsProps);

	REFLECTION_CLASSBUILDER_END(ZombieBeachOctopusProps);
}

#include "Zombie.h"
void ZombieBeachOctopus::onPlaceOnBoard()
{
	 Zombie::onPlaceOnBoard();
}
