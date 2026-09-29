//
//  GridItemMole.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "IntrosWhackAMole.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemMole);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemMoleProps);

void GridItemMoleProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemMoleProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimationProps);

		REFLECTION_CLASSBUILDER_FIELD(std::string, PopAnim);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector2, PopAnimRenderOffset);
	REFLECTION_CLASSBUILDER_END(GridItemMoleProps);
}
