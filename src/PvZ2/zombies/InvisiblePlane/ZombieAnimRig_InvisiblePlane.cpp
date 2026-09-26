//
//  ZombieAnimRig_InvisiblePlane.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieInvisiblePlane.h"

ZombieAnimRig_InvisiblePlane::~ZombieAnimRig_InvisiblePlane()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_InvisiblePlane);

void ZombieAnimRig_InvisiblePlane::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_InvisiblePlane);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(int, m_damageIndex);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_InvisiblePlane);
}
