//
//  LawnApp.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "LawnApp.h"

bool LawnApp::IsConnecting()
{
	return false;
}

bool LawnApp::IsAppTopLevel()
{
	return true;
}

bool LawnApp::IsAutoSmoking()
{
	return false;
}

int LawnApp::GetAllMapCount()
{
	return 16;
}

bool LawnApp::GetCheatsEnabled()
{
	return false;
}

void LawnApp::KillRatingDialog()
{
}

void LawnApp::ShowRatingDialog()
{
}

void LawnApp::KillIwatchRewardUI()
{
}

void LawnApp::KillPennyFuelStore()
{
}

void LawnApp::ShowIwatchRewardUI()
{
}

void LawnApp::RemapWorldMapEvents()
{
}

void LawnApp::PopulateWorldMapData()
{
}

int LawnApp::getCurrentWorldIndex()
{
	return true;
}

void LawnApp::KillNationalHolidayUI()
{
}

void LawnApp::RefreshTGPieceTableUI()
{
}

void LawnApp::ShowNationalHolidayUI()
{
}

int LawnApp::GetDragThresholdPixels()
{
	return 6;
}

void LawnApp::KillDangerRoomRewardUI()
{
}

void LawnApp::ShowDangerRoomRewardUI()
{
}

void LawnApp::ShowConsumptionRewardUI()
{
}

void LawnApp::RefreshTGAvatarPieceTableUI()
{
}

int LawnApp::GetButtonReleaseExpansionPixels()
{
	return 15;
}

void LawnApp::ButtonPress(int i_arg)
{
}

bool LawnApp::DebugKeyDown(int i_arg)
{
	return false;
}

#include "LawnApp.h"
void LawnApp::OnCloseDialog()
{
	 LawnApp::KillPVZ2Dialog();
}

void LawnApp::OnGestureFlick(Sexy::GestureFlickDirection i_arg0, Sexy::Point i_arg1)
{
}

void LawnApp::SetCheatsEnabled(bool i_arg)
{
}

#include "LawnApp.h"
time_t LawnApp::GetRealBeijingTime()
{
	return LawnApp::GetRealServerTime();
}

void LawnApp::LaunchMerchWebpage(bool i_arg)
{
}

bool LawnApp::IsWorldRSBFileLoaded(const std::string& i_arg)
{
	return true;
}

#include "LawnApp.h"
void LawnApp::onEASquaredFlowEnded(const std::string& i_arg0, int i_arg1, int i_arg2)
{
	 LawnApp::KillNetConnectingUI();
}

#include "LogCollector.h"
void LawnApp::AppBecomingForeground()
{
	 BehaviorLog::resume();
}

void LawnApp::onItemPurchasedFromStore(MagentoProductProps* i_arg)
{
}

bool LawnApp::NeedShowLoginRewardDialog(bool i_arg)
{
	return false;
}

void LawnApp::onPurchaseRefreshComplete(Sexy::IPurchaseDriver* i_arg)
{
}

#include "LawnApp.h"
void LawnApp::onEASquaredAdvertisementsClosed()
{
	 LawnApp::ResumeMusic();
}
