//
//  GridItemJammable.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "GridItemJammable.h"

void GridItemJammable::onGridItemInitialize()
{
}

GridItemJammable::~GridItemJammable()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemJammable);

void GridItemJammable::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemJammable);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemBoardEntityConditionTarget);

	REFLECTION_CLASSBUILDER_END(GridItemJammable);
}

bool GridItemJammable::IsJamming()
{
	return m_isMyJamOn;
}
