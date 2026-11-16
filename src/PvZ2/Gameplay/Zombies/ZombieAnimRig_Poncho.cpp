//
//  ZombieAnimRig_Poncho.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_Poncho.h"

ZombieAnimRig_Poncho::ZombieAnimRig_Poncho()
{
	m_hasPlate = 0;
	m_plateDamageIndex = 0;
}

ZombieAnimRig_Poncho::~ZombieAnimRig_Poncho()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_Poncho);

void ZombieAnimRig_Poncho::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_Poncho);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_hasPlate);
		REFLECTION_CLASSBUILDER_FIELD(int32, m_plateDamageIndex);
	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_Poncho);
}
