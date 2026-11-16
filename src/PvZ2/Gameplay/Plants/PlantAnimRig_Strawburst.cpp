//
//  PlantAnimRig_Strawburst.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Strawburst.h"

PlantAnimRig_Strawburst::~PlantAnimRig_Strawburst()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Strawburst);

void PlantAnimRig_Strawburst::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Strawburst);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(std::string, m_lastUsedIdleAnim);
		REFLECTION_CLASSBUILDER_FIELD(uint8, m_currentGrowthStage);
	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Strawburst);
}

#include "Plant_Strawburst.h"
bool PlantAnimRig_Strawburst::PlayPlantFoodEnd()
{
	return PlantAnimRig_Strawburst::PlayRecoverLooped();
}
