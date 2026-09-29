//
//  Plant_Caulipower.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Caulipower.h"

PlantCaulipower::PlantCaulipower()
{
}

PlantCaulipower::~PlantCaulipower()
{
}

PlantTypeCaulipower::PlantTypeCaulipower()
{
}

PlantTypeCaulipower::~PlantTypeCaulipower()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantCaulipower);

void PlantCaulipower::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantCaulipower);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<int>, ZombieTargetWeights);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<BoardEntity>>, PlantfoodTargetedZombies);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_bLevel5Triggled);
	REFLECTION_CLASSBUILDER_END(PlantCaulipower);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantTypeCaulipower);

void PlantTypeCaulipower::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantTypeCaulipower);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantType);

		REFLECTION_CLASSBUILDER_FIELD(std::string, AvatarPlantFoodLayer);
	REFLECTION_CLASSBUILDER_END(PlantTypeCaulipower);
}

BoardEntityTypeFlag PlantCaulipower::GetTargetEntityTypesForWeapon(PlantWeapon i_arg)
{
	return (BoardEntityTypeFlag)2;
}

bool PlantCaulipower::HasShadow()
{
	return false;
}
