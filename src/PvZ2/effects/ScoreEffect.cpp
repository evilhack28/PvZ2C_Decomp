//
//  ScoreEffect.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ScoreEffect.h"

void ScoreEffect::onDestroy()
{
}

ScoreEffect::~ScoreEffect()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ScoreEffect);

void ScoreEffect::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ScoreEffect);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(BoardEntity);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<Image>>, m_ImageList);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_startTime);
		REFLECTION_CLASSBUILDER_FIELD(float, m_fScale);
	REFLECTION_CLASSBUILDER_END(ScoreEffect);
}

bool ScoreEffect::ShouldDrawShadow() const
{
	return false;
}
