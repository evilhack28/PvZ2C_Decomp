//
//  GridItemMagicMirrorRig2.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "GridItemMagicMirror2.h"

GridItemMagicMirrorRig2::GridItemMagicMirrorRig2()
{
}

GridItemMagicMirrorRig2::~GridItemMagicMirrorRig2()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemMagicMirrorRig2);

void GridItemMagicMirrorRig2::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemMagicMirrorRig2);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PopAnimRig);

	REFLECTION_CLASSBUILDER_END(GridItemMagicMirrorRig2);
}
