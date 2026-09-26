//
//  SunDropperModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "SunDropperModule.h"

SunDropperModule::SunDropperModule()
{
}

SunDropperModule::~SunDropperModule()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(SunDropperModule);

void SunDropperModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(SunDropperModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

	REFLECTION_CLASSBUILDER_FIELD(int32, m_numSunsDropped);
	REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_nextSunDrop);

	REFLECTION_CLASSBUILDER_END(SunDropperModule);
}
