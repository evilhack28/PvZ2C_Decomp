//
//  ZombieAnimRig_MonkDrink.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_MonkDrink.h"

ZombieAnimRig_MonkDrink::ZombieAnimRig_MonkDrink()
{
	m_bCrazy = 0;
}

ZombieAnimRig_MonkDrink::~ZombieAnimRig_MonkDrink()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_MonkDrink);

void ZombieAnimRig_MonkDrink::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_MonkDrink);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_bCrazy);
	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_MonkDrink);
}
