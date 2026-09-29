//
//  ZombieAnimRig_LostCityLostPilot.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieLostCityLostPilot.h"

ZombieAnimRig_LostCityLostPilot::ZombieAnimRig_LostCityLostPilot()
{
	m_isHanging = 0;
}

ZombieAnimRig_LostCityLostPilot::~ZombieAnimRig_LostCityLostPilot()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_LostCityLostPilot);

void ZombieAnimRig_LostCityLostPilot::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_LostCityLostPilot);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_isHanging);
	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_LostCityLostPilot);
}
