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

void LawnApp::ButtonPress(int i_id)
{
}

bool LawnApp::DebugKeyDown(int i_key)
{
	return false;
}

#include "LawnApp.h"
void LawnApp::OnCloseDialog()
{
	 LawnApp::KillPVZ2Dialog();
}

void LawnApp::OnGestureFlick(Sexy::GestureFlickDirection i_direction, Sexy::Point i_startingLocation)
{
}

void LawnApp::SetCheatsEnabled(bool i_enabled)
{
}

#include "LawnApp.h"
time_t LawnApp::GetRealBeijingTime()
{
	return LawnApp::GetRealServerTime();
}

void LawnApp::LaunchMerchWebpage(bool i_fromMainMenu)
{
}

bool LawnApp::IsWorldRSBFileLoaded(const std::string& i_world_name)
{
	return true;
}

#include "LawnApp.h"
void LawnApp::onEASquaredFlowEnded(const std::string& i_placementOrigin, int i_coinsEarned, int i_videosWatched)
{
	 LawnApp::KillNetConnectingUI();
}

#include "LogCollector.h"
void LawnApp::AppBecomingForeground()
{
	 BehaviorLog::resume();
}

void LawnApp::onItemPurchasedFromStore(MagentoProductProps* i_props)
{
}

bool LawnApp::NeedShowLoginRewardDialog(bool i_canUseLocalTime)
{
	return false;
}

void LawnApp::onPurchaseRefreshComplete(Sexy::IPurchaseDriver* purchase_driver)
{
}

#include "LawnApp.h"
void LawnApp::onEASquaredAdvertisementsClosed()
{
	 LawnApp::ResumeMusic();
}
