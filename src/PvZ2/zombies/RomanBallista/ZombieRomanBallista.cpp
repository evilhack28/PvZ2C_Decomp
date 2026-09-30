//
//  ZombieRomanBallista.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieRomanBallista.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieRomanBallista);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieRomanBallistaProps);

void ZombieRomanBallistaProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieRomanBallistaProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<RtObject>, VaseProjectile);
		REFLECTION_CLASSBUILDER_FIELD(ProbabilityTypeContainer, ZombieSpawnData);
	REFLECTION_CLASSBUILDER_END(ZombieRomanBallistaProps);
}

#include "ZombieRomanBallista.h"
bool ZombieRomanBallista::CanApplyVenomStack()
{
	return ZombieRomanBallista::CanApplySpecialCondition();
}

bool ZombieRomanBallista::hasHeadParticle() const
{
	return false;
}
