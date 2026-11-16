//
//  NewLightningBolt.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "NewLightningBolt.h"

NewLightningBolt::~NewLightningBolt()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(NewLightningBolt);

void NewLightningBolt::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(NewLightningBolt);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(NewRayEntity);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<BoardEntity> >, m_hitTargets);
	REFLECTION_CLASSBUILDER_END(NewLightningBolt);
}
