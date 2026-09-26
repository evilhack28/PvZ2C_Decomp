//
//  ZombieAnimRig_LostCityGargantuar.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieLostCityGargantuar.h"

ZombieAnimRig_LostCityGargantuar::~ZombieAnimRig_LostCityGargantuar()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_LostCityGargantuar);

void ZombieAnimRig_LostCityGargantuar::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_LostCityGargantuar);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_Gargantuar);

	REFLECTION_CLASSBUILDER_FIELD(bool, m_hasTorch);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_LostCityGargantuar);
}
