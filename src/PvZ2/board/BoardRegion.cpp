//
//  BoardRegion.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "BoardRegion.h"

BoardRegion::~BoardRegion()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(BoardRegion);

void BoardRegion::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(BoardRegion);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GameObject);

	REFLECTION_CLASSBUILDER_FIELD(FRect, m_region);
	REFLECTION_CLASSBUILDER_FIELD(int, m_flags);

	REFLECTION_CLASSBUILDER_END(BoardRegion);
}
