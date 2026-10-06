//
//  RenaiModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "RenaiModule.h"

RenaiModule::~RenaiModule()
{
}

RenaiModuleProperties::~RenaiModuleProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(RenaiModule);

void RenaiModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(RenaiModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

		REFLECTION_CLASSBUILDER_FIELD(int32, m_currrentState);
	REFLECTION_CLASSBUILDER_END(RenaiModule);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(RenaiModuleProperties);

void RenaiModuleProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(RenaiModuleProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

		REFLECTION_CLASSBUILDER_FIELD(int, NightStartWaveNum);
	REFLECTION_CLASSBUILDER_END(RenaiModuleProperties);
}

void RenaiModule::initializeModule()
{
}
