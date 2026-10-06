//
//  PlantAnimRig_Hydrocotyledrummer.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_HydrocotyleDrummer.h"

PlantAnimRig_Hydrocotyledrummer::PlantAnimRig_Hydrocotyledrummer()
{
}

PlantAnimRig_Hydrocotyledrummer::~PlantAnimRig_Hydrocotyledrummer()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Hydrocotyledrummer);

void PlantAnimRig_Hydrocotyledrummer::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Hydrocotyledrummer);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Hydrocotyledrummer);
}
