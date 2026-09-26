//
//  GridItemCavalryGun.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieCavalry.h"

GridItemCavalryGun::GridItemCavalryGun()
{
}

GridItemCavalryGun::~GridItemCavalryGun()
{
}

GridItemCavalryGunProps::GridItemCavalryGunProps()
{
}

GridItemCavalryGunProps::~GridItemCavalryGunProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemCavalryGun);

void GridItemCavalryGun::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemCavalryGun);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemGravestone);

	REFLECTION_CLASSBUILDER_END(GridItemCavalryGun);
}
