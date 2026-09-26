//
//  ProtectThePlantChallenge.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ProtectThePlantChallenge.h"

ProtectThePlantChallengeProperties::~ProtectThePlantChallengeProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ProtectThePlantChallengeProperties);

void ProtectThePlantChallengeProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ProtectedPlantEntry);
		REFLECTION_CLASSBUILDER_FIELD(std::string, PlantType);
	REFLECTION_CLASSBUILDER_END(ProtectedPlantEntry);

	REFLECTION_CLASSBUILDER_BEGIN(ProtectThePlantChallengeProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

		REFLECTION_CLASSBUILDER_FIELD(int, MustProtectCount);
		REFLECTION_CLASSBUILDER_FIELD(bool, IsPlantDefenceMode);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<ProtectedPlantEntry>, Plants);
	REFLECTION_CLASSBUILDER_END(ProtectThePlantChallengeProperties);
}
