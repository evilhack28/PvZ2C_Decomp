//
//  PlayerInfo.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PlayerInfo.h"

bool PlayerInfo::checkGemsSign()
{
	return true;
}

bool PlayerInfo::checkKeysSign()
{
	return true;
}

bool PlayerInfo::checkCoinsSign()
{
	return true;
}

bool PlayerInfo::checkLeafsSign()
{
	return true;
}

bool PlayerInfo::getGachaCompen()
{
	return true;
}

bool PlayerInfo::checkStonesSign()
{
	return true;
}

bool PlayerInfo::getAvatarCompen()
{
	return true;
}

bool PlayerInfo::checkPowerupSign()
{
	return true;
}

bool PlayerInfo::checkWorldKeysSign()
{
	return true;
}

bool PlayerInfo::CheckAvatarInfoSign()
{
	return true;
}

bool PlayerInfo::checkPlantPieceSign()
{
	return true;
}

bool PlayerInfo::checkRedPacketsSign()
{
	return true;
}

bool PlayerInfo::WasOnUniverseMapLast()
{
	return false;
}

bool PlayerInfo::checkPlantAwakenSign()
{
	return true;
}

bool PlayerInfo::checkAccessoryInfoSign()
{
	return true;
}

bool PlayerInfo::checkAccessoryPieceSign()
{
	return true;
}

bool PlayerInfo::checkPlantStarLevelSign()
{
	return true;
}

bool PlayerInfo::checkUnlockedPlantsSign()
{
	return true;
}

void PlayerInfo::resetChallengeCountSize()
{
}

bool PlayerInfo::checkRestorePurchaseSign()
{
	return true;
}

bool PlayerInfo::checkWorldMapEeventsSign()
{
	return true;
}

bool PlayerInfo::CheckAvatarPiecesInfoSign()
{
	return true;
}

bool PlayerInfo::checkUnlockedGameFeaturesSign()
{
	return true;
}

PennyFuelCurrency PlayerInfo::GetNumPennyFuel() const
{
	return 999;
}

PennyTechCurrency PlayerInfo::GetNumPennyTech() const
{
	return 99;
}

void PlayerInfo::AM_SetLevel(std::string string)
{
}

void PlayerInfo::AddPennyFuel(const PennyFuelCurrency i_amount, const bool i_willBeBankedLater)
{
}

void PlayerInfo::AddPennyTech(const PennyTechCurrency i_amount)
{
}

#include "PlayerInfo.h"
bool PlayerInfo::CanRiddleToday()
{
	return PlayerInfo::NeedResetRiddleInfo();
}

#include "PlayerInfo.h"
void PlayerInfo::ClearRebateData()
{
	 PlayerInfo::ResetRebateData();
}

void PlayerInfo::AddZombossSignal(const ZombossSignalCurrency i_amount)
{
}

void PlayerInfo::SetZombossSignal(const ZombossSignalCurrency i_resetAmount)
{
}

void PlayerInfo::SubtractPennyFuel(const PennyFuelCurrency i_amount)
{
}

void PlayerInfo::SubtractPennyTech(const PennyTechCurrency i_amount)
{
}

#include "PlayerInfo.h"
void PlayerInfo::saveCurrentProfile()
{
	 PlayerInfo::SAVE_PROFILE();
}

#include "PlayerInfo.h"
void PlayerInfo::RegainPlantPieceSign()
{
	 PlayerInfo::resetPlantPieceSign();
}

void PlayerInfo::SubtractZombossSignal(const ZombossSignalCurrency i_amount)
{
}

void PlayerInfo::increaseChallengeCount(int worldIndex, int levelIndex)
{
}

void PlayerInfo::AddCard(int i_cardID)
{
}

int PlayerInfo::getChallengeCount(int worldIndex, int levelIndex) const
{
	return false;
}
