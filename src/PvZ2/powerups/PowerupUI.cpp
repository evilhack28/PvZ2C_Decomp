//
//  PowerupUI.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PowerupUI.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PowerupUI);

void PowerupUI::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PowerupUI);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

	REFLECTION_CLASSBUILDER_END(PowerupUI);
}
