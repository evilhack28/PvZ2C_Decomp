//
//  LightningBolt.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "LightningBolt.h"

LightningBolt::~LightningBolt()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(LightningBolt);

void LightningBolt::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(LightningBolt);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(BoardEntity);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<BoardEntity>, m_owner);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector3, m_endPos);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<BoardEntity> >, m_hitTargets);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<PopAnimRig> >, m_tiledRigs);
		REFLECTION_CLASSBUILDER_FIELD(float, m_chainAttackRate);
	REFLECTION_CLASSBUILDER_END(LightningBolt);
}
