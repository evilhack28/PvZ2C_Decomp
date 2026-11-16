//
//  WorldMap_WelfareButton.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_WelfareButton.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_WelfareButton);

void WorldMap_WelfareButton::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_WelfareButton);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIEasyButtonWidget);

	REFLECTION_CLASSBUILDER_END(WorldMap_WelfareButton);
}
