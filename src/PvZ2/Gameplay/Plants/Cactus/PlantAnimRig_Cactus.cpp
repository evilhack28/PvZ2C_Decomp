//
//  PlantAnimRig_Cactus.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Cactus.h"

PlantAnimRig_Cactus::PlantAnimRig_Cactus()
{
	m_hasBeenPlantfooded = 0;
}

PlantAnimRig_Cactus::~PlantAnimRig_Cactus()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Cactus);

#include "Plant_Cactus.h"
void PlantAnimRig_Cactus::PlayCowerIdle()
{
	 PlantAnimRig_Cactus::onCowerContinued();
}
