//
//  Plant_Dendrobiumguard.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Dendrobiumguard.h"

PlantDendrobiumguard::PlantDendrobiumguard()
{
}

PlantDendrobiumguard::~PlantDendrobiumguard()
{
}

PlantDendrobiumguardProps::~PlantDendrobiumguardProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantDendrobiumguard);

void PlantDendrobiumguard::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantDendrobiumguard);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(float, _maxHealthRatio);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<GameObject>, _jointDefenceEffect);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<BoardEntity> >, _jointDefencePlantList);
	REFLECTION_CLASSBUILDER_END(PlantDendrobiumguard);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantDendrobiumguardProps);

void PlantDendrobiumguardProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantDendrobiumguardProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantPropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(int, AddLeafLifeTimes);
		REFLECTION_CLASSBUILDER_FIELD(float, Level5AttackRatio);
	REFLECTION_CLASSBUILDER_END(PlantDendrobiumguardProps);
}

bool PlantDendrobiumguard::CanApplyPlantfood()
{
	return true;
}
