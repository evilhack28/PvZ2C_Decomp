//
//  Plant_Guacodile.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Guacodile.h"

PlantGuacodile::PlantGuacodile()
{
}

PlantGuacodile::~PlantGuacodile()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantGuacodile);

void PlantGuacodile::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantGuacodile);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_END(PlantGuacodile);
}

#include "PlantFramework.h"
void PlantGuacodile::Initialize()
{
	 PlantFramework::Initialize();
}

GroundEffectType PlantGuacodile::GetTideEffect()
{
	return (GroundEffectType)true;
}

bool PlantGuacodile::CanApplyPlantfood()
{
	return true;
}
