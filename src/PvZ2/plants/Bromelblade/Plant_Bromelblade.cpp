//
//  Plant_Bromelblade.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Bromelblade.h"

PlantBromelblade::PlantBromelblade()
{
}

PlantBromelblade::~PlantBromelblade()
{
}

PlantBromelbladeProps::~PlantBromelbladeProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantBromelblade);

void PlantBromelblade::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantBromelblade);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(int, m_attackCounter);
		REFLECTION_CLASSBUILDER_FIELD(ZombiePtr, m_targetZombie);
	REFLECTION_CLASSBUILDER_END(PlantBromelblade);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantBromelbladeProps);

void PlantBromelbladeProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantBromelbladeProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantPropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, ZombieBlacklist);
	REFLECTION_CLASSBUILDER_END(PlantBromelbladeProps);
}

void PlantBromelblade::UpdatePlantfood()
{
}
