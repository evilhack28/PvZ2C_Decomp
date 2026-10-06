//
//  ThunderWaveAction.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ThunderWaveAction.h"

ThunderWaveAction::ThunderWaveAction()
{
}

ThunderWaveAction::~ThunderWaveAction()
{
}

ThunderWaveActionProps::~ThunderWaveActionProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ThunderWaveAction);

void ThunderWaveAction::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ThunderWaveAction);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(WaveAction);

		REFLECTION_CLASSBUILDER_FIELD(int, m_index);
	REFLECTION_CLASSBUILDER_END(ThunderWaveAction);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ThunderWaveActionProps);
