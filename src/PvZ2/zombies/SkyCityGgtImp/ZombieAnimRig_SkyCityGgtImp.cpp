//
//  ZombieAnimRig_SkyCityGgtImp.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieSkyCityGgtImp.h"

ZombieAnimRig_SkyCityGgtImp::~ZombieAnimRig_SkyCityGgtImp()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_SkyCityGgtImp);

void ZombieAnimRig_SkyCityGgtImp::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_SkyCityGgtImp);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_Imp);

	REFLECTION_CLASSBUILDER_FIELD(int, m_iNeedJump);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_SkyCityGgtImp);
}
