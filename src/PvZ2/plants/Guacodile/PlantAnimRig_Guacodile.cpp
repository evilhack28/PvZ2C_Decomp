//
//  PlantAnimRig_Guacodile.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Guacodile.h"

PlantAnimRig_Guacodile::PlantAnimRig_Guacodile()
{
}

PlantAnimRig_Guacodile::~PlantAnimRig_Guacodile()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Guacodile);

void PlantAnimRig_Guacodile::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Guacodile);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Guacodile);
}

#include "PlantAnimRig.h"
void PlantAnimRig_Guacodile::onPopAnimInitialized()
{
	 PlantAnimRig::onPopAnimInitialized();
}
