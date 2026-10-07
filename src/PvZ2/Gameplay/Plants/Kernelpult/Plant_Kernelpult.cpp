//
//  Plant_Kernelpult.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Kernelpult.h"

PlantKernelpult::PlantKernelpult()
{
}

PlantKernelpult::~PlantKernelpult()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantKernelpult);

void PlantKernelpult::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantKernelpult);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(float, m_fButterRand);
		REFLECTION_CLASSBUILDER_FIELD(int, m_iFireCount);
	REFLECTION_CLASSBUILDER_END(PlantKernelpult);
}

#include "PlantFramework.h"
void PlantKernelpult::ApplyPlantfood()
{
	 PlantFramework::ApplyPlantfood();
}

bool PlantKernelpult::CanApplyPlantfood()
{
	return true;
}

#include "Plant_Kernelpult.h"
void PlantKernelpult::DoSpecial(int i_extraParam)
{
	 PlantKernelpult::launchMassButterAssault();
}
