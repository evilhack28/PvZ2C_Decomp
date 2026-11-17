//
//  AutoTestPlantLevelUp.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-16.
//

#include "SexyAppFramework/Common.h"

#include "AutoTest.h"
#include "LawnApp.h"
#include "PlantLevelUpListView.h"
#include "Cheats.h"
#include "DebugLog.h"
#include "MagentoService.h"
#include "PlayerInfo.h"
#include "ProfileMgr.h"
#include "PlantPropertySheet.h"
#include "WorldMap.h"
#include "PVZCheats.h"
#include "PVZ2UIDialog.h"
#include "PrimeText_Game.h"
#include "NameMapper.h"
#include "ObjectTypeDirectory.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

AutoTestPlantLevelUp::AutoTestPlantLevelUp()
{
	m_curPlantIndex = 0;
	m_curLevel = 0;
	m_bLevelUping = 0;
}

AutoTestPlantLevelUp::~AutoTestPlantLevelUp()
{
}

/////////////// Logic ///////////////

unsigned int AutoTestPlantGetNeedPieceCountToMaxLevel(PlayerInfo* i_profile, const RtWeakPtr<const PlantType>& i_type, const MagentoProductPropsPtr& i_props);

void AutoTestPlantLevelUp::AutoConfirmOver()
{
	gLawnApp->KillPVZ2Dialog();
}

void AutoTestPlantLevelUp::PlantTestUnlockOver()
{
	m_bLevelUping = false;
	PlantTestSelectedOk();
}

void AutoTestPlantLevelUp::PlantTestShowUI()
{
	m_curPlantIndex = 0;
	m_curLevel = 0;
	PlantLevelUpListView* listView = gLawnApp->GetPlantLevelUpListView();
	if (listView)
		listView->AutoTestSelected(0);
}

void AutoTestPlantLevelUp::PlantTestLevelUpOver()
{
	m_bLevelUping = false;
	PlantTestSelectedOk();
}

void AutoTestPlantLevelUp::PlantTestSelectedOk()
{
	if (!CheatManager::GetInstancePtr()->GetToggleValue("AutoTestPlantLevelUp") || m_bLevelUping)
		return;

	PlantLevelUpListView* listView = gLawnApp->GetPlantLevelUpListView();
	PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
	if (gLawnApp && listView && profile)
	{
		const MagentoProductPropsPtr& props = listView->GetCurrentPlantProp();
		props.Get();
		int coins;
		if (!profile->GetIsPlantUnlocked(props->ObjectItem))
		{
			m_curLevel = 0;
			coins = 0;
		}
		else
		{
			m_curLevel = profile->GetPlantStarLevel(props->ObjectItem);
			LevelUpPriceData priceData;
			props->GetCurrentLevelPriceData(m_curLevel, priceData);
			coins = priceData.iCurrentPrice;
		}
		profile->SetCoins(coins);

		std::string log = StrFormat("[AutoTest-- Plant: %s Level:%d]", props->ObjectItem.c_str(), m_curLevel);
		DebugLog::GetInstancePtr()->SendLog(log, DebugLog_LoadGroup, DebugPath_File);
		if (m_curLevel <= 0)
		{
			m_bLevelUping = true;
			listView->AutoTestSelected(m_curPlantIndex);
		}
		else
		{
			RtWeakPtr<const PlantType> type = ObjectTypeDirectory<PlantType>::GetInstancePtr()->GetTypeFromTypeName(props->ObjectItem);
			int maxLevel = type->GetProps()->MaxLevel;
			if (maxLevel > 4)
				maxLevel = 4;
			if (m_curLevel < maxLevel)
			{
				if (m_curLevel > 0)
				{
					m_bLevelUping = true;
					listView->AutoTestPlantLevelUp();
				}
			}
			else if (m_curPlantIndex < ObjectTypeDirectory<PlantType>::GetInstancePtr()->GetCount())
			{
				m_bLevelUping = false;
				m_curPlantIndex++;
				listView->AutoTestSelected(m_curPlantIndex);
			}
		}
	}
}

void AutoTestPlantLevelUp::PlantTestAddPiceceToServer()
{
	PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
	if (profile && ObjectTypeDirectory<PlantType>::GetInstancePtr())
	{
		std::map<std::string, int> pieceCounts;
		pieceCounts.clear();
		MagentoCategoryPropsPtr category = Magento::GetPlantLevelUp();
		for (size_t i = 0; i < category->Products.size(); i++)
		{
			const MagentoProductPropsPtr& product = category->Products[i];
			RtWeakPtr<const PlantType> type = ObjectTypeDirectory<PlantType>::GetInstancePtr()->GetTypeFromTypeName(product->ObjectItem);
			profile->GetPlantPieceCount(type->TypeName);
			unsigned int need = AutoTestPlantGetNeedPieceCountToMaxLevel(profile, type, product);
			if (PlantChipNameMapperServerID::GetInstance().GetIdForName(product->ObjectItem) - 111135U < 5)
				continue;
			pieceCounts[product->ObjectItem] = need;
			profile->SetPlantPieceCount(product->ObjectItem, need, true, true, true, true);
		}
		gLawnApp->GetWorldMap()->SwitchToLevelUp();
	}
}

void AutoTestPlantLevelUp::PlantTestSyncPlantFinish(bool i_success)
{
	if (CheatManager::GetInstancePtr()->GetToggleValue("AutoTestPlantLevelUp"))
	{
		if (i_success)
		{
			gLawnApp->GetWorldMap()->SwitchToLevelUp();
		}
		else
		{
			PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2DialogOneLine(L"Sync Server Plant Data Failed !Please Try");
			dialog->AddButton(L"[BUTTON_OK]", Sexy::MakeDelegate(*this, &AutoTestPlantLevelUp::AutoConfirmOver), PVZ2UIDialog::BUTTON_TYPE_GENERIC_SECONDARY);
			dialog->SetHeaderFont(PrimeText_Game::Typeface_FZCuYuan_19_HardShadow->Typeface(), Sexy::Color(Sexy::Color::White));
			dialog->SetBackgroundDarken(true);
			CheatManager::GetInstancePtr()->SetToggleValue("AutoTestPlantLevelUp", false);
		}
	}
}

void AutoTestPlantLevelUp::updateState(bool i_isOn)
{
	if (i_isOn)
	{
		PVZCheats::CheatSkipAllTutorials();
		gMessageRouter->Subscribe(&Message::AutoTestPlantUIShow, Sexy::Delegate0(Sexy::MakeDelegate(*this, &AutoTestPlantLevelUp::PlantTestShowUI)));
		gMessageRouter->Subscribe(&Message::AutoTestPlantSelected, Sexy::Delegate0(Sexy::MakeDelegate(*this, &AutoTestPlantLevelUp::PlantTestSelectedOk)));
		gMessageRouter->Subscribe(&Message::AutoTestPlantUnLock, Sexy::Delegate0(Sexy::MakeDelegate(*this, &AutoTestPlantLevelUp::PlantTestUnlockOver)));
		gMessageRouter->Subscribe(&Message::AutoTestPlantLevelUpOver, Sexy::Delegate0(Sexy::MakeDelegate(*this, &AutoTestPlantLevelUp::PlantTestLevelUpOver)));
		gMessageRouter->Subscribe(&Message::SyncPlantFinish, Sexy::MakeDelegate(*this, &AutoTestPlantLevelUp::PlantTestSyncPlantFinish));
		WorldMap* worldMap = gLawnApp->GetWorldMap();
		if (worldMap && worldMap->GetCurrentWorld())
		{
			m_curPlantIndex = 0;
			m_curLevel = 0;
			PlantTestAddPiceceToServer();
		}
	}
	else
	{
		gMessageRouter->Unsubscribe(&Message::AutoTestPlantUIShow, Sexy::MakeDelegate(*this, &AutoTestPlantLevelUp::PlantTestShowUI));
		gMessageRouter->Unsubscribe(&Message::AutoTestPlantSelected, Sexy::MakeDelegate(*this, &AutoTestPlantLevelUp::PlantTestSelectedOk));
		gMessageRouter->Unsubscribe(&Message::AutoTestPlantUnLock, Sexy::MakeDelegate(*this, &AutoTestPlantLevelUp::PlantTestUnlockOver));
		gMessageRouter->Unsubscribe(&Message::AutoTestPlantLevelUpOver, Sexy::MakeDelegate(*this, &AutoTestPlantLevelUp::PlantTestLevelUpOver));
		gMessageRouter->Unsubscribe(&Message::SyncPlantFinish, Sexy::MakeDelegate(*this, &AutoTestPlantLevelUp::PlantTestSyncPlantFinish));
		m_bLevelUping = false;
	}
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(AutoTestPlantLevelUp);
