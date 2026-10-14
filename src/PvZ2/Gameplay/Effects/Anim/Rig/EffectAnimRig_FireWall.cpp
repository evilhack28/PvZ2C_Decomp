//
//  EffectAnimRig_FireWall.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "EffectAnimRig_FireWall.h"

EffectAnimRig_FireWall::~EffectAnimRig_FireWall()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(EffectAnimRig_FireWall);

void EffectAnimRig_FireWall::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(EffectAnimRig_FireWall);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PopAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_iRunningTime);
	REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<GridItemFireWall>, m_pGridItemFireWall);

	REFLECTION_CLASSBUILDER_END(EffectAnimRig_FireWall);
}
