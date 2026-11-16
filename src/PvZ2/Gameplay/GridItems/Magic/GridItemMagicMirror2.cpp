//
//  GridItemMagicMirror2.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemMagicMirror2.h"

GridItemMagicMirror2::~GridItemMagicMirror2()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemMagicMirror2);

void GridItemMagicMirror2::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemMagicMirror2);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

		REFLECTION_CLASSBUILDER_FIELD(int, m_state);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<GridItemMagicMirror2>, m_brotherMagicMirror);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_disappeartime);
	REFLECTION_CLASSBUILDER_END(GridItemMagicMirror2);
}
