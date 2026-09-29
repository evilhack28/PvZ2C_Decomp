//
//  DandelionBomb.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "DandelionBomb.h"

DandelionBomb::~DandelionBomb()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(DandelionBomb);

void DandelionBomb::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(DandelionBomb);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(BoardEntity);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<PopAnimRig>, m_animRig);
		REFLECTION_CLASSBUILDER_FIELD(uint, m_state);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector3, m_plantPos);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<SexyVector3>, m_explodePos);
	REFLECTION_CLASSBUILDER_END(DandelionBomb);
}

void DandelionBomb::onInitialized()
{
}
