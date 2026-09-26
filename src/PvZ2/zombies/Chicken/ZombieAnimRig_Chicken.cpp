//
//  ZombieAnimRig_Chicken.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_Chicken.h"

ZombieAnimRig_Chicken::ZombieAnimRig_Chicken()
{
}

ZombieAnimRig_Chicken::~ZombieAnimRig_Chicken()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_Chicken);

void ZombieAnimRig_Chicken::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_Chicken);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(Color, m_color);
	REFLECTION_CLASSBUILDER_FIELD(bool, m_friedChickenDeath);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_Chicken);
}

void ZombieAnimRig_Chicken::SetFriedChickenDeath(bool i_arg)
{
	m_friedChickenDeath = i_arg;
}
