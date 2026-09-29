//
//  LightningBoltToGround.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "LightningBoltToGround.h"

LightningBoltToGround::~LightningBoltToGround()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(LightningBoltToGround);

void LightningBoltToGround::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(LightningBoltToGround);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(BoardEntity);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<BoardEntity>, m_owner);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector3, m_endPos);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<SexyVector3>, m_hitTargets);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<PopAnimRig> >, m_tiledRigs);
	REFLECTION_CLASSBUILDER_END(LightningBoltToGround);
}
