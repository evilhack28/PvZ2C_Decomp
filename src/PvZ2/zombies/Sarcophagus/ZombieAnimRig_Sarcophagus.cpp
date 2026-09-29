//
//  ZombieAnimRig_Sarcophagus.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_Sarcophagus.h"

ZombieAnimRig_Sarcophagus::ZombieAnimRig_Sarcophagus()
{
}

ZombieAnimRig_Sarcophagus::~ZombieAnimRig_Sarcophagus()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_Sarcophagus);

void ZombieAnimRig_Sarcophagus::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_Sarcophagus);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_hasShield);
	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_Sarcophagus);
}
