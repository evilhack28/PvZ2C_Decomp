//
//  StarChallengePlantsLost.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "StarChallengePlantsLost.h"

StarChallengePlantsLost::~StarChallengePlantsLost()
{
}

StarChallengePlantsLostProps::~StarChallengePlantsLostProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(StarChallengePlantsLost);

void StarChallengePlantsLost::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(StarChallengePlantsLost);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Challenge);

		REFLECTION_CLASSBUILDER_FIELD(int32, m_plantsLost);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<class UIWidget>, m_plantCountUI);
	REFLECTION_CLASSBUILDER_END(StarChallengePlantsLost);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(StarChallengePlantsLostProps);

void StarChallengePlantsLostProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(StarChallengePlantsLostProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

		REFLECTION_CLASSBUILDER_FIELD(int, MaximumPlantsLost);
	REFLECTION_CLASSBUILDER_END(StarChallengePlantsLostProps);
}

#include "StarChallengePlantsLost.h"
void StarChallengePlantsLost::onLilyPadDied(class GridItemLilyPad* i_lilyPad)
{
	 StarChallengePlantsLost::handlePlantDied();
}

void StarChallengePlantsLost::onFlowerPotDied(class GridItemFlowerPot* i_flowerPot)
{
}
