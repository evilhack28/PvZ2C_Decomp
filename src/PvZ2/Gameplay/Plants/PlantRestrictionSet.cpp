//
//  PlantRestrictionSet.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-20.
//

#include "SexyAppFramework/Common.h"

#include "RestrictionSet.h"
#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantRestrictionSet);

void PlantRestrictionSet::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantRestrictionSet);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StringRestrictionSet);

	REFLECTION_CLASSBUILDER_END(PlantRestrictionSet);
}
