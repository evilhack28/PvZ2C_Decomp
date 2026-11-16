//
//  BarrelWaveAction.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "BarrelWaveAction.h"

BarrelWaveAction::BarrelWaveAction()
{
}

BarrelWaveAction::~BarrelWaveAction()
{
}

BarrelWaveActionProps::~BarrelWaveActionProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(BarrelWaveAction);

void BarrelWaveAction::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(BarrelWaveAction);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(WaveAction);

		REFLECTION_CLASSBUILDER_FIELD(int, m_index);
	REFLECTION_CLASSBUILDER_END(BarrelWaveAction);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(BarrelWaveActionProps);

void BarrelWaveActionProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(BarrelDescription);
		REFLECTION_CLASSBUILDER_FIELD(int, Row);
		REFLECTION_CLASSBUILDER_FIELD(std::string, Type);
		REFLECTION_CLASSBUILDER_FIELD(GriditemBarrelParams, Params);
	REFLECTION_CLASSBUILDER_END(BarrelDescription);

	REFLECTION_CLASSBUILDER_BEGIN(BarrelWaveActionProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(WaveActionProperties);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<BarrelDescription>, Barrels);
		REFLECTION_CLASSBUILDER_FIELD(float, Interval);
	REFLECTION_CLASSBUILDER_END(BarrelWaveActionProps);
}
