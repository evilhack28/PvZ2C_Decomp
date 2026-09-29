//
//  PlantAnimRig_Impatiensshooter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PlantAnimRig_Impatiensshooter.h"

PlantAnimRig_Impatiensshooter::PlantAnimRig_Impatiensshooter()
{
}

PlantAnimRig_Impatiensshooter::~PlantAnimRig_Impatiensshooter()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Impatiensshooter);

void PlantAnimRig_Impatiensshooter::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Impatiensshooter);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Impatiensshooter);
}

#include "PlantAnimRig.h"
void PlantAnimRig_Impatiensshooter::onPopAnimInitialized()
{
	 PlantAnimRig::onPopAnimInitialized();
}
