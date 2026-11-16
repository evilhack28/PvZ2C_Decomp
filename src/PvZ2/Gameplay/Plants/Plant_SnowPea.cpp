//
//  Plant_SnowPea.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_SnowPea.h"

PlantSnowPea::PlantSnowPea()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantSnowPea);

void PlantSnowPea::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantSnowPea);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(PeashooterPlantfood, m_plantfood);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Effect_PopAnim>, m_plantfoodEffect);
	REFLECTION_CLASSBUILDER_END(PlantSnowPea);
}

#include "PlantFramework.h"
void PlantSnowPea::Initialize()
{
	 PlantFramework::Initialize();
}

bool PlantSnowPea::CanApplyPlantfood()
{
	return true;
}
