//
//  Plant_HatMushroom.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_HatMushroom.h"

PlantHatMushroom::~PlantHatMushroom()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantHatMushroom);

void PlantHatMushroom::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantHatMushroom);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<BoardEntityPtr>, m_plantfoodTargetsLocked);
		REFLECTION_CLASSBUILDER_FIELD(Point, m_floorEffectPoint);
	REFLECTION_CLASSBUILDER_END(PlantHatMushroom);
}

bool PlantHatMushroom::OnAnimCommand(const std::string & i_animCommand, const std::string & i_animCommandParam)
{
	return true;
}

#include "Plant_HatMushroom.h"
void PlantHatMushroom::UpdateActions()
{
	 PlantHatMushroom::updateFloorEffect();
}

bool PlantHatMushroom::CanApplyPlantfood()
{
	return true;
}
