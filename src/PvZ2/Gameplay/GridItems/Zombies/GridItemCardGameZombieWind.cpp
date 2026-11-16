//
//  GridItemCardGameZombieWind.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemCardGameZombieWind.h"

GridItemCardGameZombieWind::~GridItemCardGameZombieWind()
{
}

GridItemCardGameZombieWindProps::GridItemCardGameZombieWindProps()
{
	NinjaZombieCount = (decltype(NinjaZombieCount))5;
	GargantuarZombieCount = (decltype(GargantuarZombieCount))3;
	WindPushZombieBlocks = (decltype(WindPushZombieBlocks))3;
	WindTornadoCount = (decltype(WindTornadoCount))3;
}

GridItemCardGameZombieWindProps::~GridItemCardGameZombieWindProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemCardGameZombieWind);

void GridItemCardGameZombieWind::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemCardGameZombieWind);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemCardGameZombie);

	REFLECTION_CLASSBUILDER_END(GridItemCardGameZombieWind);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemCardGameZombieWindProps);

void GridItemCardGameZombieWindProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemCardGameZombieWindProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemCardGameZombieProps);

	REFLECTION_CLASSBUILDER_END(GridItemCardGameZombieWindProps);
}
