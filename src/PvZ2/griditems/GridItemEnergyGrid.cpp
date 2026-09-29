//
//  GridItemEnergyGrid.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemEnergyGrid.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemEnergyGrid);

void GridItemEnergyGrid::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemEnergyGrid);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItem);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Effect_PopAnim>, effectBagua);
	REFLECTION_CLASSBUILDER_END(GridItemEnergyGrid);
}
