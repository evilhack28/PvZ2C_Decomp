//
//  GameResourceUtil.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-04.
//

#include "SexyAppFramework/Common.h"

#include "ResourceHelpers.h"

using namespace Sexy;

#include "GameCommon.h"
#include "UIEditor/UIRewardFrame.h"

#include "GameInfoUtil.h"
#include "GameResourceUtil.h"

static CachedUIResourcePtr<Image> IMAGE_UI_ACCESSORY_ICON_BG_NORMAL("IMAGE_UI_ACCESSORY_ICON_BG_NORMAL");
static CachedUIResourcePtr<Image> IMAGE_UI_ACCESSORY_ICON_BG_GREEN("IMAGE_UI_ACCESSORY_ICON_BG_GREEN");
static CachedUIResourcePtr<Image> IMAGE_UI_ACCESSORY_ICON_BG_BLUE("IMAGE_UI_ACCESSORY_ICON_BG_BLUE");
static CachedUIResourcePtr<Image> IMAGE_UI_ACCESSORY_ICON_BG_PURPLE("IMAGE_UI_ACCESSORY_ICON_BG_PURPLE");
static CachedUIResourcePtr<Image> IMAGE_UI_ACCESSORY_ICON_BG_GOLD("IMAGE_UI_ACCESSORY_ICON_BG_GOLD");
static CachedUIResourcePtr<Image> IMAGE_UI_GEILIVABLE_LOTTERY_BONUS_COIN("IMAGE_UI_GEILIVABLE_LOTTERY_BONUS_COIN");
static CachedUIResourcePtr<Image> IMAGE_UI_GEILIVABLE_LOTTERY_BONUS_GEM("IMAGE_UI_GEILIVABLE_LOTTERY_BONUS_GEM");

/////////////// GameResourceUtil ///////////////

Image* GameResourceUtil::GetFrameImageByRare(int rare)
{
	if (rare == 1)
	{
		return IMAGE_UI_ACCESSORY_ICON_BG_GREEN;
	}
	if (rare == 2)
	{
		return IMAGE_UI_ACCESSORY_ICON_BG_BLUE;
	}
	if (rare == 3)
	{
		return IMAGE_UI_ACCESSORY_ICON_BG_PURPLE;
	}
	if (rare == 4)
	{
		return IMAGE_UI_ACCESSORY_ICON_BG_GOLD;
	}

	return IMAGE_UI_ACCESSORY_ICON_BG_NORMAL;
}

Image* GameResourceUtil::GetFrameImageById(int id)
{
	Image* result;
	if (id == 4013)
	{
		result = IMAGE_UI_ACCESSORY_ICON_BG_BLUE;
	}
	else if (id == 3008)
	{
		result = IMAGE_UI_ACCESSORY_ICON_BG_PURPLE;
	}
	else
	{
		GameItemInfo info;
		if (GameInfoUtil::GetItemInfoById(id, info))
			result = GetFrameImageByRare(info._rare);
		else
			result = NULL;
	}

	return result;
}

Image* GameResourceUtil::GetImageById(int id)
{
	Image* result;
	if (id == 4013)
	{
		result = IMAGE_UI_GEILIVABLE_LOTTERY_BONUS_COIN;
	}
	else if (id == 3008)
	{
		result = IMAGE_UI_GEILIVABLE_LOTTERY_BONUS_GEM;
	}
	else
	{
		GameItemInfo info;
		if (GameInfoUtil::GetItemInfoById(id, info))
			result = info._img;
		else
			result = NULL;
	}

	return result;
}
