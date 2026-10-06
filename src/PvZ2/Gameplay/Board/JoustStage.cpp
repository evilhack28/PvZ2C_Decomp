//
//  JoustStage.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "JoustStage.h"

JoustStage::JoustStage()
{
}

JoustStage::~JoustStage()
{
}

JoustStageProperties::~JoustStageProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(JoustStage);

void JoustStage::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(JoustStage);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StageModule);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<float>, m_scoreMultipliers);
	REFLECTION_CLASSBUILDER_END(JoustStage);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(JoustStageProperties);

void JoustStageProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(JoustStageProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StageModuleProperties);

	REFLECTION_CLASSBUILDER_END(JoustStageProperties);
}
