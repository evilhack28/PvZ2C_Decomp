//
//  GridItemMagicMirrorProps2.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemMagicMirror2.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

GridItemMagicMirrorProps2::GridItemMagicMirrorProps2()
{
}

GridItemMagicMirrorProps2::~GridItemMagicMirrorProps2()
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(GridItemMagicMirrorProps2);

void GridItemMagicMirrorProps2::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemMagicMirrorProps2);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimationProps);

	REFLECTION_CLASSBUILDER_END(GridItemMagicMirrorProps2);
}
