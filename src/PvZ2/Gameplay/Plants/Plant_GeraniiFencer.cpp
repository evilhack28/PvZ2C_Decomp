//
//  Plant_GeraniiFencer.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_GeraniiFencer.h"

PlantGeraniiFencer::PlantGeraniiFencer()
{
}

PlantGeraniiFencer::~PlantGeraniiFencer()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantGeraniiFencer);

void PlantGeraniiFencer::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantGeraniiFencer);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_END(PlantGeraniiFencer);
}

bool PlantGeraniiFencer::CanBeTargetedBy(const BoardEntity * i_entity)
{
	return true;
}

void PlantGeraniiFencer::UpdatePlantfood()
{
}

void PlantGeraniiFencer::DoSpecialForAvatarNormal()
{
}
