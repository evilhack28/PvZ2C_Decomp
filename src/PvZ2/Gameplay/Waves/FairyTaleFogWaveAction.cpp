//
//  FairyTaleFogWaveAction.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "FairyTaleFogWaveAction.h"

FairyTaleFogWaveAction::FairyTaleFogWaveAction()
{
	m_fogTipTime = PVZ_EOT();
}

FairyTaleFogWaveAction::~FairyTaleFogWaveAction()
{
}

FairyTaleFogWaveActionProps::~FairyTaleFogWaveActionProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(FairyTaleFogWaveAction);

void FairyTaleFogWaveAction::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(FairyTaleFogWaveAction);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(WaveAction);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_fogTipTime);
	REFLECTION_CLASSBUILDER_END(FairyTaleFogWaveAction);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(FairyTaleFogWaveActionProps);

void FairyTaleFogWaveActionProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(FairyTaleFogWaveActionProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(WaveActionProperties);

		REFLECTION_CLASSBUILDER_FIELD(Rect, Range);
		REFLECTION_CLASSBUILDER_FIELD(int, Distance);
		REFLECTION_CLASSBUILDER_FIELD(float, MovingTime);
		REFLECTION_CLASSBUILDER_FIELD(std::string, FogType);
	REFLECTION_CLASSBUILDER_END(FairyTaleFogWaveActionProps);
}

void FairyTaleFogWaveAction::OnSetNextWaveVisible(bool i_visible)
{
}

void FairyTaleFogWaveAction::WaveEnd(int i_waveNumber, Sexy::MTRand & i_random)
{
}
