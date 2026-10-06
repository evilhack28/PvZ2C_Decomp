//
//  ZombieIceAgeDodo.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieIceAgeDodo.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieIceAgeDodo);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieIceAgeDodoProps);

void ZombieIceAgeDodoProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieIceAgeDodoProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieWithActionsProps);

		REFLECTION_CLASSBUILDER_FIELD(PlantRestrictionSet, PlantsToFlyOver);
		REFLECTION_CLASSBUILDER_FIELD(GridItemRestrictionSet, GridItemsToFlyOver);
		REFLECTION_CLASSBUILDER_FIELD(std::string, ElectrocutePAMName);
	REFLECTION_CLASSBUILDER_END(ZombieIceAgeDodoProps);
}
