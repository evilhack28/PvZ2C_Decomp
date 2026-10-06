//
//  GridItemHeavyShield.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieFairyTaleGargantuar.h"

GridItemHeavyShield::GridItemHeavyShield()
{
}

GridItemHeavyShield::~GridItemHeavyShield()
{
}

GridItemHeavyShieldProps::GridItemHeavyShieldProps()
{
}

GridItemHeavyShieldProps::~GridItemHeavyShieldProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemHeavyShield);

void GridItemHeavyShield::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemHeavyShield);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemGravestone);

	REFLECTION_CLASSBUILDER_FIELD(bool, m_hasPlayDieAnim);

	REFLECTION_CLASSBUILDER_END(GridItemHeavyShield);
}

#include "GridItem.h"
void GridItemHeavyShield::KillGridItem()
{
	 GridItem::KillGridItem();
}

void GridItemHeavyShield::onAnimStoppedCallback(const std::string& i_arg)
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemHeavyShieldProps);

void GridItemHeavyShieldProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemHeavyShieldProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemGravestonePropertySheet);

	REFLECTION_CLASSBUILDER_END(GridItemHeavyShieldProps);
}

PlantingReason GridItemHeavyShield::GetCantPlantReason() const
{
	return (PlantingReason)110;
}
