//
//  AvatarPackageItem.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-18.
//

#include "SexyAppFramework/Common.h"

#include "PlantViewSubWidgets.h"
#include "PlantNewAvatar.h"
#include "PlayerInfo.h"
#include "ProfileMgr.h"

AvatarPackageItem::AvatarPackageItem()
    : m_selected(false)
{
}

AvatarPackageItem::~AvatarPackageItem()
{
}

void AvatarPackageItem::InitView(int i_avatarId, AvatarLevel i_avatarLevel)
{
	m_avatarId = i_avatarId;
	m_avatarLevel = i_avatarLevel;
	Refresh();
}

void AvatarPackageItem::Refresh()
{
	PlayerInfo* playerInfo = Sexy::LazySingleton<ProfileMgr>::GetInstance().GetCurrentProfile();
	m_isNewAvatar = PlantNewAvatarMapper::GetInstance().ContainsId(m_avatarId);
	m_avatarUnlocked = NewAvatar::IsAvatarUnlocked(m_avatarId);
	m_equiped = playerInfo->IsEquipAvatar(m_avatarId);
	m_avatarImage = NewAvatar::GetAvatarImage(m_avatarId);
	m_avatarName = NewAvatar::GetAvatarName(m_avatarId);
	m_currentNumber = NewAvatar::GetAvatarPieceNum(m_avatarId);
	m_exchangeNum = NewAvatar::GetAvatarPieceMaxNum(m_avatarId);
}

void AvatarPackageItem::SelectPackageItem(bool i_flag)
{
	m_selected = i_flag;
	Refresh();
}

void AvatarPackageItem::TouchBegan(const Sexy::Touch& touch)
{
	m_touch = touch.ident;
}

void AvatarPackageItem::TouchEnded(const Sexy::Touch& touch)
{
	if (m_touch == touch.ident)
		UINewPlantView_AvatarPackage::GetSingletonPtr()->FocusAvatar(m_avatarId);
}
