//
//  Plant_Vanilla.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Vanilla.h"

PlantVanilla::PlantVanilla()
{
}

PlantVanilla::~PlantVanilla()
{
}

PlantTypeVanilla::PlantTypeVanilla()
{
}

PlantTypeVanilla::~PlantTypeVanilla()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantVanilla);

void PlantVanilla::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantVanilla);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<int>, ZombieTargetWeights);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<BoardEntity>>, PlantfoodTargetedZombies);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_bLevel5Triggled);
		REFLECTION_CLASSBUILDER_FIELD(int, m_nAttackTimes);
	REFLECTION_CLASSBUILDER_END(PlantVanilla);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantTypeVanilla);

void PlantTypeVanilla::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantTypeVanilla);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantType);

		REFLECTION_CLASSBUILDER_FIELD(std::string, AvatarPlantFoodLayer);
	REFLECTION_CLASSBUILDER_END(PlantTypeVanilla);
}

bool PlantVanilla::CanApplyPlantfood()
{
	return true;
}
