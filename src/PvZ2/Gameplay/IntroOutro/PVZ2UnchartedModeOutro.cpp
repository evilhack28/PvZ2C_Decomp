//
//  PVZ2UnchartedModeOutro.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-21.
//

#include "SexyAppFramework/Common.h"

#include "PVZ2UnchartedModeNetworkMgr.h"
#include "PVZ2UnchartedModeOutro.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(PVZ2UnchartedModeOutroProperties);

void PVZ2UnchartedModeOutroProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PVZ2UnchartedModeOutroProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(OutroModuleProperties);

	REFLECTION_CLASSBUILDER_END(PVZ2UnchartedModeOutroProperties);
}
