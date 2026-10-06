//
//  ZombieAnimRig_Ski.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieIceAgeSki.h"

ZombieAnimRig_Ski::ZombieAnimRig_Ski()
{
	m_iCurCol = 0;
	m_eSkiOldState = -1;
}

ZombieAnimRig_Ski::~ZombieAnimRig_Ski()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_Ski);

void ZombieAnimRig_Ski::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_Ski);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<GameObject>, m_ptrOwner);
	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_Ski);
}
