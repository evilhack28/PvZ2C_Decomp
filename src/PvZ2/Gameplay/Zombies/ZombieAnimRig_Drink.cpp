//
//  ZombieAnimRig_Drink.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_Drink.h"

ZombieAnimRig_Drink::ZombieAnimRig_Drink()
{
	m_bCrazy = 0;
}

ZombieAnimRig_Drink::~ZombieAnimRig_Drink()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_Drink);

void ZombieAnimRig_Drink::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_Drink);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_bCrazy);
	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_Drink);
}
