//
//  DinoTreadWaveAction.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "DinoTreadWaveAction.h"

DinoTreadWaveAction::DinoTreadWaveAction()
{
}

DinoTreadWaveAction::~DinoTreadWaveAction()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(DinoTreadWaveAction);

void DinoTreadWaveAction::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(DinoTreadWaveAction);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(WaveAction);

	REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_timeToSpawnShadow);

	REFLECTION_CLASSBUILDER_END(DinoTreadWaveAction);
}
