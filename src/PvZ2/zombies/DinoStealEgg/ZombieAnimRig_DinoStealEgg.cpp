//
//  ZombieAnimRig_DinoStealEgg.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieDinoStealEgg.h"

ZombieAnimRig_DinoStealEgg::ZombieAnimRig_DinoStealEgg()
{
	m_hasEgg = 1;
}

ZombieAnimRig_DinoStealEgg::~ZombieAnimRig_DinoStealEgg()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_DinoStealEgg);

void ZombieAnimRig_DinoStealEgg::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_DinoStealEgg);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_Basic);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_hasEgg);
	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_DinoStealEgg);
}
