//
//  PlantAnimRig_CoconutCannon.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PlantAnimRig_CoconutCannon.h"

PlantAnimRig_CoconutCannon::PlantAnimRig_CoconutCannon()
{
}

PlantAnimRig_CoconutCannon::~PlantAnimRig_CoconutCannon()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_CoconutCannon);

void PlantAnimRig_CoconutCannon::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_CoconutCannon);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(std::string, m_lastUsedIdleAnim);
	REFLECTION_CLASSBUILDER_END(PlantAnimRig_CoconutCannon);
}

#include "PlantAnimRig_CoconutCannon.h"
bool PlantAnimRig_CoconutCannon::PlayPlantFoodEnd()
{
	return PlantAnimRig_CoconutCannon::PlayRecoverLooped();
}
