//
//  ZombieAnimRig_Gentleman.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieGentleman.h"

ZombieAnimRig_Gentleman::ZombieAnimRig_Gentleman()
{
	m_iCurCol = 0;
	m_eSkiOldState = -1;
}

ZombieAnimRig_Gentleman::~ZombieAnimRig_Gentleman()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_Gentleman);

void ZombieAnimRig_Gentleman::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_Gentleman);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<GameObject>, m_ptrOwner);
	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_Gentleman);
}
