//
//  GridItemMagicMirrorRig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "GridItemMagicMirror.h"

GridItemMagicMirrorRig::GridItemMagicMirrorRig()
{
}

GridItemMagicMirrorRig::~GridItemMagicMirrorRig()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemMagicMirrorRig);

void GridItemMagicMirrorRig::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemMagicMirrorRig);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PopAnimRig);

	REFLECTION_CLASSBUILDER_END(GridItemMagicMirrorRig);
}
