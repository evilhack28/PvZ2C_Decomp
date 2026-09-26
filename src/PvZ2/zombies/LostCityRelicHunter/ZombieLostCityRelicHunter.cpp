//
//  ZombieLostCityRelicHunter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieLostCityRelicHunter.h"

ZombieLostCityRelicHunterProps::ZombieLostCityRelicHunterProps()
{
}

ZombieLostCityRelicHunterProps::~ZombieLostCityRelicHunterProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieLostCityRelicHunterProps);

void ZombieLostCityRelicHunterProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieLostCityRelicHunterProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieSwashbucklerProps);

	REFLECTION_CLASSBUILDER_END(ZombieLostCityRelicHunterProps);
}
