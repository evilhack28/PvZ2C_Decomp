//
//  WorldMap_GiftFoReturn.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_TurnChangeButton.h"
#include "ReflectionBuilder.h"
#include "ActivityManager.h"
#include "UIGiftFoReturn.h"

/////////////// Lifecycle ///////////////

namespace RiftUtils { bool IsWorldMapButtonsEnabled(); }

WorldMap_GiftFoReturn::WorldMap_GiftFoReturn()
{
	SetImageNormal("IMAGE_UI_HUD_WORLDMAP_ACTIVITY_HOME_GIFT_FOR_RETURN");
}

WorldMap_GiftFoReturn::~WorldMap_GiftFoReturn()
{
}

/////////////// Logic ///////////////

bool WorldMap_GiftFoReturn::CheckActivated()
{
	if (!RiftUtils::IsWorldMapButtonsEnabled())
	{
		SetVisible(false);
		return false;
	}
	ActiveItem item = ActivityManager::GetInstancePtr()->GetActiveItem(Activity_GiftFoReturn);
	SetVisible(item.m_bOpen);
	return item.m_bOpen;
}

void WorldMap_GiftFoReturn::onButtonClicked()
{
	ActivityManager::GetInstancePtr()->Request(Activity_GiftFoReturn, true, false);
	m_bRequested = true;
}

void WorldMap_GiftFoReturn::onNotifyRefreshActivityListReal(bool i_success, const std::set<int>& changeList)
{
	if (i_success && changeList.find(Activity_GiftFoReturn) != changeList.end() && m_bRequested)
		UISingletonDialog<UIGiftFoReturn>::ShowDialog();
	m_bRequested = false;
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(WorldMap_GiftFoReturn);

void WorldMap_GiftFoReturn::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_GiftFoReturn);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(WorldMap_TurnChangeButton);

	REFLECTION_CLASSBUILDER_END(WorldMap_GiftFoReturn);
}
