//
//  PlantAnimRig_HocusCrocus.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_HocusCrocus.h"

PlantAnimRig_HocusCrocus::PlantAnimRig_HocusCrocus()
{
}

PlantAnimRig_HocusCrocus::~PlantAnimRig_HocusCrocus()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_HocusCrocus);

void PlantAnimRig_HocusCrocus::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_HocusCrocus);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_HocusCrocus);
}
