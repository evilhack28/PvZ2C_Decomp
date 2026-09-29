//
//  SchoolBusWaveAction.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "SchoolBusWaveAction.h"

SchoolBusWaveAction::SchoolBusWaveAction()
{
}

SchoolBusWaveAction::~SchoolBusWaveAction()
{
}

SchoolBusWaveActionProps::~SchoolBusWaveActionProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(SchoolBusWaveAction);

void SchoolBusWaveAction::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(SchoolBusWaveAction);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(WaveAction);

	REFLECTION_CLASSBUILDER_END(SchoolBusWaveAction);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(SchoolBusWaveActionProps);

void SchoolBusWaveActionProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(SchoolBusDescription);
		REFLECTION_CLASSBUILDER_FIELD(int, Row);
		REFLECTION_CLASSBUILDER_FIELD(std::string, Type);
		REFLECTION_CLASSBUILDER_FIELD(GriditemSchoolBusParams, Params);
	REFLECTION_CLASSBUILDER_END(SchoolBusDescription);

	REFLECTION_CLASSBUILDER_BEGIN(SchoolBusWaveActionProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(WaveActionProperties);

		REFLECTION_CLASSBUILDER_FIELD(SchoolBusDescription, Des);
	REFLECTION_CLASSBUILDER_END(SchoolBusWaveActionProps);
}

void SchoolBusWaveAction::WaveUpdate(int i_arg0, Sexy::MTRand & i_arg1)
{
}

void SchoolBusWaveAction::WaveEnd(int i_arg0, Sexy::MTRand & i_arg1)
{
}
