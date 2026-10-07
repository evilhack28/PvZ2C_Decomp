//
//  ZombieDinoPushEgg.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieDinoPushEgg.h"

ZombieDinoPushEggProps::~ZombieDinoPushEggProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieDinoPushEgg);

void ZombieDinoPushEgg::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieDinoPushEgg);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieWithPushingAction);

		REFLECTION_CLASSBUILDER_FIELD(int, m_renderOrder);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_isOnScreen);
	REFLECTION_CLASSBUILDER_END(ZombieDinoPushEgg);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieDinoPushEggProps);

void ZombieDinoPushEggProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieDinoPushEggProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieWithActionsProps);

		REFLECTION_CLASSBUILDER_FIELD(int32_t, NumberOfEggsToSpawnWith);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<EntityWeight>, EggTypesToSpawn);
	REFLECTION_CLASSBUILDER_END(ZombieDinoPushEggProps);
}

void ZombieDinoPushEgg::drawPushRectangle(const Sexy::Graphics* i_g)
{
}

bool ZombieDinoPushEgg::willDieToShrinking()
{
	return true;
}
