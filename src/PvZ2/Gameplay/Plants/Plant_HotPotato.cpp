//
//  Plant_HotPotato.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_HotPotato.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantHotPotato);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantTypeHotPotato);

void PlantTypeHotPotato::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantTypeHotPotato);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantType);

		REFLECTION_CLASSBUILDER_FIELD(GridItemRestrictionSet, TargetableGridItemTypes);
	REFLECTION_CLASSBUILDER_END(PlantTypeHotPotato);
}

#include "Plant_HotPotato.h"
void PlantHotPotato::UpdateActions()
{
	 PlantHotPotato::updateCurrentState();
}
