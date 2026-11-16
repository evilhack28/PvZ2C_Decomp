//
//  RayEntity.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "RayEntity.h"

RayEntity::~RayEntity()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(RayEntity);

void RayEntity::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(RayEntity);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(BoardEntity);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<BoardEntity>, m_owner);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector3, m_endPos);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<PopAnimRig> >, m_tiledRigs);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Effect_PopAnim>, m_effect);
	REFLECTION_CLASSBUILDER_END(RayEntity);
}

void RayEntity::onInitialized()
{
}
