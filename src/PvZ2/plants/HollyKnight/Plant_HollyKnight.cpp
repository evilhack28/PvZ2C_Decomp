//
//  Plant_HollyKnight.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_HollyKnight.h"

PlantHollyKnight::PlantHollyKnight()
{
}

PlantHollyKnight::~PlantHollyKnight()
{
}

PlantTypeHollyKnight::PlantTypeHollyKnight()
{
}

PlantTypeHollyKnight::~PlantTypeHollyKnight()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantHollyKnight);

void PlantHollyKnight::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantHollyKnight);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_lastAttack);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_hasTarget);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<BoardEntity>, m_target);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<ComponentPlantLauncher>, m_launcherComponent);
	REFLECTION_CLASSBUILDER_END(PlantHollyKnight);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantTypeHollyKnight);

bool PlantHollyKnight::CanApplyPlantfood()
{
	return true;
}

void PlantHollyKnight::SetupLevelBasedProjectileProps(const HollyKnightProps* i_arg)
{
}
