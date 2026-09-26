//
//  ZombieAnimRig_PirateBarrel.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_PirateBarrel.h"

ZombieAnimRig_PirateBarrel::~ZombieAnimRig_PirateBarrel()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_PirateBarrel);

void ZombieAnimRig_PirateBarrel::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_PirateBarrel);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(int32, m_barrelDamageIndex);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_PirateBarrel);
}

#include "ZombieAnimRig.h"
void ZombieAnimRig_PirateBarrel::onNeedsToDie()
{
	 ZombieAnimRig::setReadyToDie();
}
