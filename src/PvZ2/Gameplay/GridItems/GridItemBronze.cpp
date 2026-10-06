//
//  GridItemBronze.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemBronze.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemBronze);

void GridItemBronze::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemBronze);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItem);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<PopAnimRig>, m_animBronzeStump);
	REFLECTION_CLASSBUILDER_END(GridItemBronze);
}
