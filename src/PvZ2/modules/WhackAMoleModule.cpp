//
//  WhackAMoleModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "WhackAMoleModule.h"

WhackAMoleModule::WhackAMoleModule()
{
}

WhackAMoleModule::~WhackAMoleModule()
{
}

WhackAMoleModuleProperties::~WhackAMoleModuleProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WhackAMoleModule);

void WhackAMoleModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WhackAMoleModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

		REFLECTION_CLASSBUILDER_FIELD(uint32, m_Score);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_hasDisplayedAdvice);
	REFLECTION_CLASSBUILDER_END(WhackAMoleModule);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WhackAMoleModuleProperties);

void WhackAMoleModuleProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WhackAMoleModuleProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

	REFLECTION_CLASSBUILDER_END(WhackAMoleModuleProperties);
}

void WhackAMoleModule::cancelTouch()
{
}

void WhackAMoleModule::GameplayUpdate()
{
}
