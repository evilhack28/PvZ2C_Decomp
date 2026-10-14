//
//  CustomLevelConfig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "CustomLevelConfig.h"

CustomLevelConfig::CustomLevelConfig()
{
}

CustomLevelConfig::~CustomLevelConfig()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CustomLevelConfig);

void CustomLevelConfig::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(DefaultWaveConfig);
		REFLECTION_CLASSBUILDER_FIELD(std::string, ZombieTypeName);
		REFLECTION_CLASSBUILDER_FIELD(int, Weight);
	REFLECTION_CLASSBUILDER_END(DefaultWaveConfig);

	REFLECTION_CLASSBUILDER_BEGIN(DefaultWave);
		REFLECTION_CLASSBUILDER_FIELD(int, PickCount);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<DefaultWaveConfig>, Configs);
	REFLECTION_CLASSBUILDER_END(DefaultWave);

	REFLECTION_CLASSBUILDER_BEGIN(ModuleConfig);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<DefaultWave>, DefaultWaveList);
	REFLECTION_CLASSBUILDER_END(ModuleConfig);

	REFLECTION_CLASSBUILDER_BEGIN(WaveEventConfig);
		REFLECTION_CLASSBUILDER_FIELD(std::map<std::string RT_COMMA float>, ValueMaps);
		REFLECTION_CLASSBUILDER_FIELD(std::map<std::string RT_COMMA std::string>, StringMaps);
	REFLECTION_CLASSBUILDER_END(WaveEventConfig);

	REFLECTION_CLASSBUILDER_BEGIN(CustomLevelConfig);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PropertySheetBase);

		REFLECTION_CLASSBUILDER_FIELD(std::map<std::string RT_COMMA float>, CommonConfigs);
		REFLECTION_CLASSBUILDER_FIELD(std::map<std::string RT_COMMA ModuleConfig>, ModuleConfigs);
		REFLECTION_CLASSBUILDER_FIELD(std::map<std::string RT_COMMA WaveEventConfig>, WaveEventConfigs);
	REFLECTION_CLASSBUILDER_END(CustomLevelConfig);
}
