//
//  ScaledBoardModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ScaledBoardModule.h"

ScaledBoardModule::ScaledBoardModule()
{
}

ScaledBoardModule::~ScaledBoardModule()
{
}

ScaledBoardModuleProperties::ScaledBoardModuleProperties()
{
}

ScaledBoardModuleProperties::~ScaledBoardModuleProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ScaledBoardModule);

void ScaledBoardModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ScaledBoardModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

	REFLECTION_CLASSBUILDER_END(ScaledBoardModule);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ScaledBoardModuleProperties);

void ScaledBoardModuleProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ScaledBoardModuleProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

		REFLECTION_CLASSBUILDER_FIELD(float, BoardEntityScale);
	REFLECTION_CLASSBUILDER_END(ScaledBoardModuleProperties);
}
