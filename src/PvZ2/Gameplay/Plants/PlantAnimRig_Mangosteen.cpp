//
//  PlantAnimRig_Mangosteen.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Mangosteen.h"

PlantAnimRig_Mangosteen::PlantAnimRig_Mangosteen()
{
}

PlantAnimRig_Mangosteen::~PlantAnimRig_Mangosteen()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Mangosteen);

void PlantAnimRig_Mangosteen::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Mangosteen);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Mangosteen);
}
