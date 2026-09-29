//
//  ZombossBattleModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombossBattleModule.h"

ZombossBattleModule::ZombossBattleModule()
{
}

ZombossBattleModule::~ZombossBattleModule()
{
}

ZombossBattleModuleProperties::~ZombossBattleModuleProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombossBattleModule);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombossBattleModuleProperties);

void ZombossBattleModuleProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombossBattleModuleProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

		REFLECTION_CLASSBUILDER_FIELD(Point, ZombossSpawnGridPosition);
		REFLECTION_CLASSBUILDER_FIELD(std::string, ZombossMechType);
	REFLECTION_CLASSBUILDER_END(ZombossBattleModuleProperties);
}
