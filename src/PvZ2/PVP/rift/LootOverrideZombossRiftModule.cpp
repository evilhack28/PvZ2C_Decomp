//
//  LootOverrideZombossRiftModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "LootOverrideZombossRiftModule.h"

LootOverrideZombossRiftModule::LootOverrideZombossRiftModule()
{
}

LootOverrideZombossRiftModule::~LootOverrideZombossRiftModule()
{
}

LootOverrideZombossRiftModuleProps::~LootOverrideZombossRiftModuleProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(LootOverrideZombossRiftModule);

void LootOverrideZombossRiftModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(LootOverrideZombossRiftModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<serializable_time_t>, LootTimeRemaining);
	REFLECTION_CLASSBUILDER_END(LootOverrideZombossRiftModule);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(LootOverrideZombossRiftModuleProps);

void LootOverrideZombossRiftModuleProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombossRiftLootEntry);
		REFLECTION_CLASSBUILDER_FIELD(Loot, Drop);
	REFLECTION_CLASSBUILDER_END(ZombossRiftLootEntry);

	REFLECTION_CLASSBUILDER_BEGIN(LootOverrideZombossRiftModuleProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<ZombossRiftLootEntry>, Entries);
	REFLECTION_CLASSBUILDER_END(LootOverrideZombossRiftModuleProps);
}
