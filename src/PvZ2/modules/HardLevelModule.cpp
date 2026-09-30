//
//  HardLevelModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "HardLevelModule.h"

HardLevelModule::~HardLevelModule()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HardLevelModule);

void HardLevelModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieLevelCreater);
		REFLECTION_CLASSBUILDER_FIELD(float, ControlNum);
	REFLECTION_CLASSBUILDER_END(ZombieLevelCreater);

	REFLECTION_CLASSBUILDER_BEGIN(HardLevelModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

		REFLECTION_CLASSBUILDER_FIELD(ZombieLevelCreater, m_creater);
	REFLECTION_CLASSBUILDER_END(HardLevelModule);
}
