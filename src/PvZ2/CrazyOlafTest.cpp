//
//  CrazyOlafTest.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "CrazyOlafTest.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CrazyOlafTest);

void CrazyOlafTest::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CrazyOlafTest);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_actionTimer);
	REFLECTION_CLASSBUILDER_END(CrazyOlafTest);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CrazyOlafTestProperties);
