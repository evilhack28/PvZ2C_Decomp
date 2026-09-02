//
//  IceAgeStage.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-02.
//

#include "IceAgeStage.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(IceAgeStage);
void IceAgeStage::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(IceAgeStage);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StageModule);

	REFLECTION_CLASSBUILDER_END(IceAgeStage);
}

RT_CLASS_IMPLEMENT(IceAgeStageProperties);
void IceAgeStageProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(IceAgeStageProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StageModuleProperties);

	REFLECTION_CLASSBUILDER_END(IceAgeStageProperties);
}
