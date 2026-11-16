//
//  LevelOfTheDayOutro.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "LevelOfTheDayOutro.h"

bool LevelOfTheDayOutro::getPreventSave()
{
	return true;
}

void LevelOfTheDayOutro::showAwardScreen()
{
}

void LevelOfTheDayOutro::getReward()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(LevelOfTheDayOutro);

void LevelOfTheDayOutro::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(LevelOfTheDayOutro);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(OutroModule);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_nextRequestTime);
		REFLECTION_CLASSBUILDER_FIELD(int, m_requestCount);
	REFLECTION_CLASSBUILDER_END(LevelOfTheDayOutro);
}
