//
//  PlantWarsOutroProperties.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-21.
//

#include "SexyAppFramework/Common.h"

#include "PlantWarsOutro.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(PlantWarsOutroProperties);

void PlantWarsOutroProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantWarsOutroProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(OutroModuleProperties);

	REFLECTION_CLASSBUILDER_END(PlantWarsOutroProperties);
}
