//
//  CommonUIManager.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-07.
//

#include "SexyAppFramework/Common.h"

#include "CommonUIManager.h"
#include "LawnApp.h"
#include "UIRedPacket.h"
#include "GameCommon.h"
#include "TodLib/TodStringFile.h"
#include "UIMessageBox.h"
#include "drivers/app/android/JavaInterface.h"

/////////////// Lifecycle ///////////////

CommonUIManager::CommonUIManager()
{
	_bonus = nullptr;
	gLawnApp->LoadGroup("UI_ActivityCommon");
	gLawnApp->LoadGroup("UI_GLLottery");
	gLawnApp->LoadGroup("UI_Accessory_Dev2");
	gLawnApp->LoadGroup("Effects_Lottery_Result");
	if (gLawnApp->CanLoadGroup("RenderEffects"))
	{
		gLawnApp->LoadGroup("RenderEffects");
	}
	gLawnApp->LoadGroup("UI_Fragment_Avatar");
	gLawnApp->LoadGroup("UI_Fragment_Pieces");
	gLawnApp->LoadGroup("UI_Fragment_Material");
	gLawnApp->LoadGroup("UI_NewAvatar");
	gLawnApp->LoadGroup("UI_NationalCenter");
}

CommonUIManager::~CommonUIManager()
{
	gLawnApp->DeleteGroup("UI_ActivityCommon");
	gLawnApp->DeleteGroup("UI_GLLottery");
	gLawnApp->DeleteGroup("UI_Accessory_Dev2");
	gLawnApp->DeleteGroup("Effects_Lottery_Result");
	if (gLawnApp->CanLoadGroup("RenderEffects"))
	{
		gLawnApp->DeleteGroup("RenderEffects");
	}
	gLawnApp->DeleteGroup("UI_Fragment_Avatar");
	gLawnApp->DeleteGroup("UI_Fragment_Pieces");
	gLawnApp->DeleteGroup("UI_Fragment_Material");
	gLawnApp->DeleteGroup("UI_NewAvatar");
	gLawnApp->DeleteGroup("UI_NationalCenter");
}

/////////////// Bonus ///////////////

void CommonUIManager::ShowBonus(const std::vector<LotteryBonus>& reward, const std::vector<LotteryBonus>& chestReward, Delegate0 func)
{
	if (_bonus == nullptr)
	{
		_bonus = new CommonBonusUI();
		_bonus->SetAward(reward);
		_bonus->SetChestAward(chestReward);
		_bonus->SetSubmitDelegate(func);
		gLawnApp->mWidgetManager->AddWidget(_bonus);
		gLawnApp->mWidgetManager->BringToFront(_bonus);
	}
	gLawnApp->PushOverlaysToTop();
	gLawnApp->mWidgetManager->AddBaseModal(_bonus);
	gLawnApp->mWidgetManager->SetFocus(_bonus);
	if (_bonus != nullptr)
	{
		_bonus->NormalInit(PT_FromCenter | PT_FromMiddle | PT_Scaled | PT_Fade);
		_bonus->StartPop();
	}
}

void CommonUIManager::CloseBonus()
{
	if (_bonus != nullptr)
	{
		gLawnApp->mWidgetManager->RemoveWidget(_bonus);
		gLawnApp->mWidgetManager->RemoveBaseModal(_bonus);
		gLawnApp->SafeDeleteWidget(_bonus);
		_bonus = nullptr;
	}
}

void CommonUIManager::ShowBonusRedPachet(const std::vector<LotteryBonus>& reward)
{
	std::map<int, int> rewardMap;
	std::vector<int> idList;
	std::vector<LotteryBonus>::const_iterator it = reward.begin();
	std::vector<LotteryBonus>::const_iterator end = reward.end();
	for (; it != end; ++it)
	{
		GAME_ITEM_INFO info = ProfileChangeItemAmount((*it).BonusId, (*it).Quantity, false);
		std::map<int, int>::iterator found = rewardMap.find(info.m_nId);
		std::map<int, int>::iterator notFound = rewardMap.end();
		if (found != notFound)
		{
			found->second += info.m_nPieceRequire;
		}
		else
		{
			rewardMap[info.m_nId] = info.m_nPieceRequire;
			idList.push_back(info.m_nId);
		}
	}
	UIRedPacketResult::create(rewardMap, idList, true);
}

/////////////// Cheating check ///////////////

void CommonUIManager::OnCheatingCheckCallback(UIMessageBox* pBox, int buttonID)
{
	UISingletonDialog<UIMessageBox>::CloseDialog();
	Android::Device::ExitApp();
}

void CommonUIManager::ShowCheatingCheckWarning(int warningLevel)
{
	UIMessageBox* box = UISingletonDialog<UIMessageBox>::ShowDialog();
	if (box != nullptr)
	{
		box->SetShowType(UIMessageBox::Type_ShowCancel);
		SexyString title = TodStringTranslate(L"[PVZ2_CHEATING_CHECK_TITLE]");
		SexyString message = TodStringTranslate(Sexy::StrFormat(L"[PVZ2_CHEATING_WARNING_%d]", (warningLevel > 4 ? 4 : warningLevel)));
		box->SetMessage(message, title);
		box->SetBackground(StringHelper::ToImage("IMAGE_UI_DIALOG_ASSET_BG_ROUND_GREEN", false));
		SexyString ok = TodStringTranslate(L"[BUTTON_OK]");
		box->GetButtonCancel()->mLabel = ok;
		if (warningLevel > 3)
		{
			box->SetCallback(Sexy::MakeDelegate(*this, &CommonUIManager::OnCheatingCheckCallback));
		}
	}
}
