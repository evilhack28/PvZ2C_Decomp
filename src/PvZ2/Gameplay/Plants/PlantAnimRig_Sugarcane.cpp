//
//  PlantAnimRig_Sugarcane.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Sugarcane.h"

PlantAnimRig_Sugarcane::PlantAnimRig_Sugarcane()
{
}

PlantAnimRig_Sugarcane::~PlantAnimRig_Sugarcane()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Sugarcane);

void PlantAnimRig_Sugarcane::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Sugarcane);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Sugarcane);
}

int PlantAnimRig_Sugarcane::CalcDamageStateCount()
{
	return true;
}

#include "Plant_Sugarcane.h"
void PlantAnimRig_Sugarcane::onDamageStateIndexChanged(int i_oldDamageIndex)
{
	 PlantAnimRig_Sugarcane::UpdateDamageState();
}
