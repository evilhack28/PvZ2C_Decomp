//
//  TowerDefendUpgradeUI.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "TowerDefendUpgradeUI.h"

void TowerDefendUpgradeUI::unregisterForEvents()
{
}

void TowerDefendUpgradeUI::initLoadingResourcesGroupList()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(TowerDefendUpgradeUI);

void TowerDefendUpgradeUI::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(TowerDefendUpgradeUI);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

		REFLECTION_CLASSBUILDER_FIELD(Point, m_PlantGridPosition);
		REFLECTION_CLASSBUILDER_FIELD(int, m_nSun);
	REFLECTION_CLASSBUILDER_END(TowerDefendUpgradeUI);
}
