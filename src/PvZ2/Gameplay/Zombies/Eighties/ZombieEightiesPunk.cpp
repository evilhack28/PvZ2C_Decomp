//
//  ZombieEightiesPunk.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieEightiesPunk.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieEightiesPunk);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieEightiesPunkProps);

void ZombieEightiesPunkProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieEightiesPunkProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(std::string, JamStyle);
		REFLECTION_CLASSBUILDER_FIELD(PlantRestrictionSet, PlantsToKickInsteadOfPush);
	REFLECTION_CLASSBUILDER_END(ZombieEightiesPunkProps);
}
