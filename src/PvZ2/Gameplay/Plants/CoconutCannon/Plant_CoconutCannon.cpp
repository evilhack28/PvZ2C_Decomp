//
//  Plant_CoconutCannon.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_CoconutCannon.h"

PlantCoconutCannon::~PlantCoconutCannon()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantCoconutCannon);

void PlantCoconutCannon::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantCoconutCannon);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_hitRowBelow);
		REFLECTION_CLASSBUILDER_FIELD(float, m_StarRateCoolDown);
	REFLECTION_CLASSBUILDER_END(PlantCoconutCannon);
}

bool PlantCoconutCannon::CanApplyPlantfood()
{
	return true;
}
