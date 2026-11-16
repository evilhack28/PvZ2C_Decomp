//
//  StarLightningCloud.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "StarLightningCloud.h"

StarLightningCloud::~StarLightningCloud()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(StarLightningCloud);

void StarLightningCloud::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(StarLightningCloud);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(BoardEntity);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<BoardEntity>, m_owner);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<BoardEntity> >, m_target);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_canAttack);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<PopAnimRig>, m_animRig);
	REFLECTION_CLASSBUILDER_END(StarLightningCloud);
}
