//
//  PlayerInfo.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PlayerInfo.h"
#include "ProfileMgr.h"
#include "LawnApp.h"
#include "ActivityConfig.h"
#include "PVZ2UnchartedModeUtils.h"
#include "ZombieTreasureYeti.h"
#include "gameNetWork/NetworkData.h"
#include "PlayerInfoLocalSaveData.h"
#include "ReflectionBuilder.h"
#include "SexyAppFramework/IDiagDriver.h"
#include "WorldMapUtils.h"
#include "AuthMgr.h"
#include "WorldData.h"
#include "MapEventItem.h"
#include "GeneralTaskMgr.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(PlayerInfo);

/////////////// Helpers ///////////////

template <typename T>
int findIndexForName(const std::string& i_name, const std::vector<T>& i_list)
{
	for (size_t i = 0; i < i_list.size(); i++)
	{
		if (i_list[i].Name == i_name)
			return i;
	}
	return -1;
}

int findIndexForName(const std::string& i_name, std::vector<SavedWorldMapEventData>& i_list)
{
	for (size_t i = 0; i < i_list.size(); i++)
	{
		if (i_list[i].GetName() == i_name)
			return i;
	}
	return -1;
}

template <typename T>
int findIndexForWorldName(const std::string& i_worldName, std::vector<T>& i_list)
{
	for (size_t i = 0; i < i_list.size(); i++)
	{
		if (i_list[i].WorldName == i_worldName)
			return i;
	}
	return -1;
}

/////////////// Accessors ///////////////

PennyFuelCurrency PlayerInfo::GetNumPennyFuel() const
{
	return 999;
}

PennyTechCurrency PlayerInfo::GetNumPennyTech() const
{
	return 99;
}

void PlayerInfo::SetZombossSignal(const ZombossSignalCurrency i_resetAmount)
{
}

GemCurrency PlayerInfo::GetGiveGems()
{
	return m_giveGems;
}

void PlayerInfo::SetRecharge(bool i_recharge)
{
	m_bRecharge = i_recharge;
	SAVE_PROFILE();
}

void PlayerInfo::SetProfileId(int32 number)
{
	m_profileId = number;
	SAVE_PROFILE();
}

void PlayerInfo::SetNewerPresent(bool i_newerpresent)
{
	m_bNewerPresent = i_newerpresent;
	SAVE_PROFILE();
}

void PlayerInfo::SetProfileIndex(PlayerProfileIndex i_index)
{
	m_index = i_index;
	SAVE_PROFILE();
}

void PlayerInfo::SetFirstBuyPlant(bool i_first)
{
	m_bFirstBuyPlant = i_first;
	SAVE_PROFILE();
}

void PlayerInfo::SetConsumptionGems(int i_gems)
{
	m_iConsumptionGems = i_gems;
	SAVE_PROFILE();
}

void PlayerInfo::SetHasRebateReward(int iReward)
{
	m_iHasRebateReward = iReward;
	SAVE_PROFILE();
}

void PlayerInfo::SetFirstBuyPlantBag(bool i_first)
{
	m_bFirstBuyPlantBag = i_first;
	SAVE_PROFILE();
}

void PlayerInfo::SetMonthlyCardActive(uint32 fliter)
{
	m_monthlyCardType = fliter;
	SAVE_PROFILE();
}

void PlayerInfo::SetLastConsumGemsTime(time_t i_time)
{
	m_lastConsumGemsTime = i_time;
	SAVE_PROFILE();
}

int PlayerInfo::GetRiftZombossWinField()
{
	return m_riftZombossWinField;
}

void PlayerInfo::SetAdvanceNewerPresent(bool i_advancepresent)
{
	m_bAdvanceNewerPresent = i_advancepresent;
	SAVE_PROFILE();
}

void PlayerInfo::SetGotNewPlayerPackage(bool i_got)
{
	m_hasGotNewPlayerPackage = i_got;
	SAVE_PROFILE();
}

void PlayerInfo::SetRiftZombossWinField(int i_zombossWinField)
{
	m_riftZombossWinField = i_zombossWinField;
	SAVE_PROFILE();
}

void PlayerInfo::SetCurrentDangerRoomLevel(DangerRoomLevelType i_type)
{
	m_currentDangerRoomLevel = i_type;
	SAVE_PROFILE();
}

void PlayerInfo::SetIsRedPackRankRewardGet(bool bGet)
{
	m_bRedPackRewardRankGet = bGet;
	SAVE_PROFILE();
}

void PlayerInfo::SetLotteryConsumptionGems(int i_stones)
{
	m_nLotteryConsumptionGems = i_stones;
	SAVE_PROFILE();
}

int PlayerInfo::GetPennyClassroomTestIndex()
{
	return m_pennyClassroomTestIndex;
}

int PlayerInfo::GetRiftZombossAttemptCount()
{
	return m_riftZombossAttemptCount;
}

void PlayerInfo::SetActiveServerConfigValid(bool i_valid)
{
	m_activeServerConfigValid = i_valid;
	SAVE_PROFILE();
}

void PlayerInfo::SetConsumptionActivityGems(int gems)
{
	m_ConsumptionActivityGems = gems;
	SAVE_PROFILE();
}

void PlayerInfo::SetRiftZombossAttemptCount(int i_count)
{
	m_riftZombossAttemptCount = i_count;
	SAVE_PROFILE();
}

void PlayerInfo::SetShowRechargeDoubleDialog(bool i_showRechargeDoubleDialog)
{
	m_bShowRechargeDoubleDialog = i_showRechargeDoubleDialog;
	SAVE_PROFILE();
}

void PlayerInfo::SetZombossNextAvailableTime(const serializable_time_t i_nextAvailableTime)
{
	m_zombossNextAvailableTime = i_nextAvailableTime;
	SAVE_PROFILE();
}

int PlayerInfo::GetRiftZombossClearedCounter()
{
	return m_riftZombossClearedCounter;
}

void PlayerInfo::SetFirstRechargeRewardStatus(bool i_hasGot)
{
	m_hasGotFirstRechargeReward = i_hasGot;
	SAVE_PROFILE();
}

void PlayerInfo::SetRiftZombossClearedCounter(int i_count)
{
	m_riftZombossClearedCounter = i_count;
	SAVE_PROFILE();
}

int PlayerInfo::GetPVZ2UnchartedModeWorldCount()
{
	return m_pvz2UnchartedModeWorldCount;
}

void PlayerInfo::SetHighestTutorialEventReached(FunnelEvent i_funnelEvent)
{
	m_highestTutorialEventReached = i_funnelEvent;
	SAVE_PROFILE();
}

void PlayerInfo::SetLastTutorialFunnelEventTime(time_t i_time)
{
	m_lastTutorialFunnelEventTime = i_time;
	SAVE_PROFILE();
}

bool PlayerInfo::HasPvpAccount()
{
	return m_hasPvpAccount;
}

bool PlayerInfo::GetVerifyRewarded()
{
	return m_authVerifyRewarded;
}

std::vector<BossKillTimeChallengeInfo>& PlayerInfo::GetBossChallengeInfo()
{
	return m_bossKillTimeChallenge;
}

bool PlayerInfo::GetHasPlayedWorldCup()
{
	return m_hasPlayedWorldCup;
}

bool PlayerInfo::GetPVZ1ModeFirstPlay()
{
	return m_pvz1modeFirstPlay;
}

std::vector<int>& PlayerInfo::GetRebateRewardState()
{
	return m_vRebateRewardState;
}

void PlayerInfo::SetHasPlayedWorldCup(bool i_played)
{
	m_hasPlayedWorldCup = i_played;
	SAVE_PROFILE();
}

void PlayerInfo::SetPVZ1ModeFirstPlay(bool status)
{
	m_pvz1modeFirstPlay = status;
}

const std::vector<TravelLogTaskSaveInfo>& PlayerInfo::GetAllTravelLogSaveInfo()
{
	return m_daveTaskInfos;
}

bool PlayerInfo::GetCustomLevelFirstPlay()
{
	return m_customLevelFirstPlay;
}

const std::vector<int>& PlayerInfo::GetNewPVPSelectedPlants()
{
	return m_newPVPSelectedPlants;
}

void PlayerInfo::SetCustomLevelFirstPlay(bool status)
{
	m_customLevelFirstPlay = status;
}

bool PlayerInfo::GetRiftStoreFirstEntered()
{
	return m_riftStoreFirstEntered;
}

void PlayerInfo::SetRiftStoreFirstEntered(bool i_enter)
{
	m_riftStoreFirstEntered = i_enter;
}

bool PlayerInfo::GetHaveShowEvilDavidIntro()
{
	return m_bShowEvilDavidIntro;
}

void PlayerInfo::SetHaveShowEvilDavidIntro(bool bShow)
{
	m_bShowEvilDavidIntro = bShow;
	SAVE_PROFILE();
}

bool PlayerInfo::GetPVZ1ModeTutorialFinished()
{
	return m_pvz1ModeTutorialFinished;
}

void PlayerInfo::SetPVZ1ModeTutorialFinished(bool i_finished)
{
	m_pvz1ModeTutorialFinished = i_finished;
}

bool PlayerInfo::GetCustomLevelGuessLikeEnable()
{
	return m_customLevelGuessLikeEnable;
}

bool PlayerInfo::GetNewPVPTrainingFirstEntered()
{
	return m_newPVPTrainingFirstEntered;
}

bool PlayerInfo::GetUnchartedAnniversaryReward()
{
	return m_unchartedAnniversaryReward;
}

bool PlayerInfo::GetWorldLevelPackageFirstPlay()
{
	return m_worldLevelPackageFirstPlay;
}

void PlayerInfo::SetUnchartedAnniversaryReward(bool status)
{
	m_unchartedAnniversaryReward = status;
	SAVE_PROFILE();
}

void PlayerInfo::SetWorldLevelPackageFirstPlay(bool status)
{
	m_worldLevelPackageFirstPlay = status;
}

bool PlayerInfo::HasGotCustomLevelTutorialLevel()
{
	return m_hasGotCustomLevelTutorialLevel;
}

const std::vector<PvZ1LevelCompleteInfo>& PlayerInfo::GetPvZ1HardLevelFinishInfoForAchievement()
{
	return m_pvz1HardLevelCompleteInfos;
}

const std::vector<PvZ1LevelCompleteInfo>& PlayerInfo::GetPvZ1NormalLevelFinishInfoForAchievement()
{
	return m_pvz1NormalLevelCompleteInfos;
}

bool PlayerInfo::IsNewPVPTaskExist(int i_id)
{
	return IsTaskExist(m_newPVPTaskInfos, i_id);
}

bool PlayerInfo::IsArborDayTaskExist(int i_id)
{
	return IsTaskExist(m_arborDayTaskInfos, i_id);
}

bool PlayerInfo::IsBattleOrderTaskExist(int i_id)
{
	return IsTaskExist(m_battleOrderTaskInfos, i_id);
}

bool PlayerInfo::IsDaveKitchenTaskExist(int i_id)
{
	return IsTaskExist(m_daveKitchenTaskInfos, i_id);
}

bool PlayerInfo::IsGiftFoReturnTaskExist(int i_id)
{
	return IsTaskExist(m_giftFoReturnTaskInfos, i_id);
}

bool PlayerInfo::IsNewCornucopiaTaskExist(int id)
{
	return IsTaskExist(m_cornucopiaTaskInfos, id);
}

bool PlayerInfo::IsPlantCultivateTaskExist(int i_id)
{
	return IsTaskExist(m_plantCultivateTaskInfos, i_id);
}

const std::vector<int>& PlayerInfo::GetNewTotalRechargeRewardStatus()
{
	return m_newTotalRechargeRewardStatus;
}

void PlayerInfo::SetNumRechargeCurrency(int i_currency)
{
	m_rechargeCurrency = i_currency;
}

const std::vector<std::string>& PlayerInfo::GetRechargeProductId() const
{
	return m_todayRechargeProductId;
}

const std::vector<BundleDisplay>& PlayerInfo::GetDisplayingBundleList()
{
	return m_displayingBundle;
}

const std::vector<int>& PlayerInfo::GetBundleQueueingList()
{
	return m_queuedBundles;
}

std::vector<SignRewardContent>& PlayerInfo::GetDailySignRewardSheet()
{
	return m_dailySignRewardSheet;
}

const std::vector<int>& PlayerInfo::GetHasGotRewardList()
{
	return m_hasGotRewardList;
}

std::vector<PlantTrialCD>& PlayerInfo::GetPlantTrialRecord()
{
	return m_vPlantTrialCD;
}

const std::vector<ArcadePackProgress>& PlayerInfo::GetArcadeProgress() const
{
	return m_arcadeProgress;
}

const std::vector<PowerUpCollectionProgress>& PlayerInfo::GetPowerUpProgress() const
{
	return m_powerUpCollections;
}

const ArenaInfo& PlayerInfo::GetArenaInfo()
{
	return m_arenaInfo;
}

std::vector<FestivalPlantRandomIndex> & PlayerInfo::GetFestivalPlantRandomIndexList()
{
	return m_listFestivalPlantRandomIndexInfo;
}

std::string PlayerInfo::GetDeltaOnlineDataSign()
{
	return m_deltaDataOnline_sign;
}

const std::vector<PlantAvatarPiecesInfo>& PlayerInfo::GetPlantAvatarPiecesInfo() const
{
	return m_listPlantAvatarPiecesInfo;
}

const std::vector<PlantAvatarInfo>& PlayerInfo::GetPlantAvatarInfo() const
{
	return m_listPlantAvatarsAvatarInfo;
}

const std::vector<PlantPieceRecord>& PlayerInfo::GetPlantPiecesInfo() const
{
	return m_plantPieceRecords;
}

const std::vector<PlantStarLevel>& PlayerInfo::GetPlantStarsInfo() const
{
	return m_plantStarLevelArray;
}

const std::vector<AccessoryPiece>& PlayerInfo::GetAccessoryPiecesInfo() const
{
	return m_accessoryPieces;
}

const std::vector<MaterialInfo>& PlayerInfo::GetMaterialInfo() const
{
	return m_materialList;
}

const std::vector<PlantNewAvatarInfo>& PlayerInfo::GetPlantNewAvatarInfo() const
{
	return m_listPlantNewAvatarInfo;
}

const std::vector<PlantNewAvatarPiecesInfo>& PlayerInfo::GetPlantNewAvatarPiecesInfo() const
{
	return m_listPlantNewAvatarPiecesInfo;
}

std::vector<ZombieGift>& PlayerInfo::GetZombieGifts(void)
{
	return m_zombieGifts;
}

std::vector<int>& PlayerInfo::GetRiddlesGotToday()
{
	return m_riddlesGotToday;
}

std::string PlayerInfo::GetSpecialAvatarBonus()
{
	return m_specialAvatarBonuns;
}

std::vector<int> PlayerInfo::GetUnObtainedReward()
{
	return m_dangerRoomUnrewardLevels;
}

int PlayerInfo::GetBirthZRecordCount()
{
	return static_cast<int>(m_vBirthZRecord.size());
}

PvpShopInfo& PlayerInfo::GetPvpShopInfo()
{
	return m_pvpShopInfo;
}

const std::vector<uint8>& PlayerInfo::GetHardWorldOrder()
{
	return m_hardWorldOrder;
}

std::string& PlayerInfo::GetLastACLKey()
{
	return m_aclk;
}

std::string PlayerInfo::GetCurrentTrainingWorldName()
{
	return m_currentTrainingWorldName;
}

const StructuredData& PlayerInfo::GetLuaInfo()
{
	return m_jsonLuaInfo;
}

bool PlayerInfo::IsRecharge()
{
	return m_bRecharge;
}

const StarCurrency PlayerInfo::GetNumStars(int i_worldId)
{
	return m_stars;
}

int PlayerInfo::GetDaysCount()
{
	return m_daysCount;
}

bool PlayerInfo::IsSalesPoped()
{
	return m_salesPoped;
}

void PlayerInfo::SetSalesPoped(bool i_poped)
{
	m_salesPoped = i_poped;
}

bool PlayerInfo::IsNewerPresent()
{
	return m_bNewerPresent;
}

const LeafCurrency PlayerInfo::GetLeafCurrency()
{
	return m_leafs;
}

int PlayerInfo::GetRebateCharge()
{
	return m_iRebateCharge;
}

bool PlayerInfo::IsFirstBuyPlant()
{
	return m_bFirstBuyPlant;
}

const std::vector<CollectionInfo>& PlayerInfo::GetAllCollection()
{
	return m_listCollectionInfo;
}

const std::string& PlayerInfo::GetLastWorldName()
{
	return m_last_world_name;
}

void PlayerInfo::SetVersionNumber(int32 number)
{
	m_versionNumber = number;
}

int PlayerInfo::GetKillZombiesNum()
{
	return m_killZombiesNum;
}

int PlayerInfo::GetCurrentArtifact()
{
	return m_currentArtifact;
}

int PlayerInfo::GetDailyRewardDays()
{
	return m_oppoDailyRewardDays;
}

int PlayerInfo::GetHasRebateReward()
{
	return m_iHasRebateReward;
}

int PlayerInfo::GetReturnGoldValue()
{
	return m_returnGoldValue;
}

int PlayerInfo::GetSpringGiftIndex()
{
	return m_currentSpringGiftIndex;
}

bool PlayerInfo::IsFirstBuyPlantBag()
{
	return m_bFirstBuyPlantBag;
}

void PlayerInfo::SetReturnGoldValue(int i_returnGoldValue)
{
	m_returnGoldValue = i_returnGoldValue;
}

const std::vector<PlantGeneInfo>& PlayerInfo::GetAllPlantGeneInfo()
{
	return m_plantGeneList;
}

int PlayerInfo::GetChildrenDayStart()
{
	return m_childrenDayStart;
}

std::vector<PlantFamilyInfo>& PlayerInfo::GetPlantFamilyInfos()
{
	return m_plantFamilyInfos;
}

void PlayerInfo::SetPaidForGemReturn(bool i_paid)
{
	m_gemReturnPaid = i_paid;
}

int PlayerInfo::GetCurrentRankAvatar()
{
	return m_currentRankAvatar;
}

bool PlayerInfo::GetIsMarkedForDelete()
{
	return m_markedForDelete;
}

const DangerRoomInfo& PlayerInfo::GetVacationLevelInfo()
{
	return m_vacationLevelInfo;
}

void PlayerInfo::SetEndlessRemainLife(int i_life)
{
	m_currentLifeData.CurrentLife = i_life;
	SAVE_PROFILE();
}

bool PlayerInfo::IsAdvanceNewerPresent()
{
	return m_bAdvanceNewerPresent;
}

int PlayerInfo::GetChildrenDayBuyCount()
{
	return m_childrenDayBuyCount;
}

StoredDangerRoomEventData& PlayerInfo::GetDangerRoomEventData()
{
	return m_dangerRoomEventData;
}

int PlayerInfo::GetNumRechargeCurrency()
{
	return m_rechargeCurrency;
}

int PlayerInfo::GetReturnWorldKeyValue()
{
	return m_returnWorldKeyValue;
}

bool PlayerInfo::HasGotNewPlayerPackage()
{
	return m_hasGotNewPlayerPackage;
}

void PlayerInfo::SetChildrenDayBuyCount(int count)
{
	m_childrenDayBuyCount = count;
}

void PlayerInfo::SetReturnWorldKeyValue(int i_returnWorldKeyValue)
{
	m_returnWorldKeyValue = i_returnWorldKeyValue;
}

const std::vector<ArtifactInfo>& PlayerInfo::GetUnlockedArtifactList()
{
	return m_artifactListArray;
}

DangerRoomLifeData& PlayerInfo::GetCurrentDangerRoomLife()
{
	return m_currentLifeData;
}

float PlayerInfo::GetLastWorldMapZoomLevel()
{
	return m_lastWorldMapZoom;
}

int PlayerInfo::GetNumTimesZombossFought()
{
	return m_zombossFightsThisCycle;
}

bool PlayerInfo::IsCurrentSalesNewArrival()
{
	return m_currentSalesInfo.newArrival;
}

void PlayerInfo::SetChristmasLotteryIndex(int i_ChristmasLotteryIndex)
{
	m_nChristmasLotteryIndex = i_ChristmasLotteryIndex;
}

DangerRoomLevelType PlayerInfo::GetCurrentDangerRoomLevel()
{
	return m_currentDangerRoomLevel;
}

int PlayerInfo::GetCurrentEndlessRankData()
{
	return m_endlessCurrentRank;
}

bool PlayerInfo::HasGotFirstRechargeReward()
{
	return m_hasGotFirstRechargeReward;
}

bool PlayerInfo::IsActiveServerConfigValid()
{
	return m_activeServerConfigValid;
}

bool PlayerInfo::GetIsMarkedForKongfuUnlock()
{
	return m_purchasedKongfuUnlock;
}

bool PlayerInfo::IsNeedResetSprintGiftIndex()
{
	return m_needToResetSprintGiftIndex;
}

bool PlayerInfo::IsShowRechargeDoubleDialog()
{
	return m_bShowRechargeDoubleDialog;
}

GemCurrency PlayerInfo::GetNumMonthRechargeCurrency()
{
	return m_monthRechargeCurrency;
}

GemCurrency PlayerInfo::GetNumTodayRechargeCurrency()
{
	return m_todayRechargeCurrency;
}

int PlayerInfo::GetNumTotalRechargeCurrency()
{
	return m_totalRechargeCurrency;
}

serializable_time_t PlayerInfo::GetZombossNextAvailableTime()
{
	return m_zombossNextAvailableTime;
}

void PlayerInfo::SetChristmasLotteryPlantIndex(int i_ChristmasLotteryPlantIndex)
{
	m_nChristmasLotteryPlantIndex = i_ChristmasLotteryPlantIndex;
}

GemCurrency PlayerInfo::GetNumTodayMaxRechargeCurrency()
{
	return m_todayMaxRechargeCurrency;
}

void PlayerInfo::SetPVZ2UnchartedModeWorldCount(int count)
{
	m_pvz2UnchartedModeWorldCount = count;
}

bool PlayerInfo::GetTutorialFirstChecked()
{
	return m_tutorialFirstChecked;
}

void PlayerInfo::SetTutorialFirstChecked(bool i_checked)
{
	m_tutorialFirstChecked = i_checked;
}

bool PlayerInfo::IsHighFPS()
{
	return m_isHighFPS;
}

void PlayerInfo::SetIsHighFPS(bool i_highFPS)
{
	m_isHighFPS = i_highFPS;
	SAVE_PROFILE();
	ProfileMgr::GetInstance().Save(false, false);
}

void PlayerInfo::SetPopupOnceDay(bool i_PopupOnceDay)
{
	m_hasPopupOnceDay = i_PopupOnceDay;
	SAVE_PROFILE();
	ProfileMgr::GetInstance().Save(false, false);
}

void PlayerInfo::SetHasPvpAccount(bool has)
{
	m_hasPvpAccount = has;
	SAVE_PROFILE();
	ProfileMgr::GetInstance().Save(false, false);
}

void PlayerInfo::SetVerifyRewarded(bool flag)
{
	m_authVerifyRewarded = flag;
	SAVE_PROFILE();
	ProfileMgr::GetInstance().Save(false, false);
}

void PlayerInfo::SetCurrentRankAvatar(int i_id)
{
	m_currentRankAvatar = i_id;
	SAVE_PROFILE();
	ProfileMgr::GetInstance().Save(false, false);
}

void PlayerInfo::SetModernWeChatShared(bool bShared)
{
	m_bModernWeChatShare = bShared;
	SAVE_PROFILE();
	ProfileMgr::GetInstance().Save(false, false);
}

void PlayerInfo::SetTwoYearWeChatShared(bool bShared)
{
	m_bTwoYearWeChatShare = bShared;
	SAVE_PROFILE();
	ProfileMgr::GetInstance().Save(false, false);
}

void PlayerInfo::SetPopupPlantTrialToday(bool popup)
{
	m_hasPopupPlantTrial = popup;
	SAVE_PROFILE();
	ProfileMgr::GetInstance().Save(false, false);
}

void PlayerInfo::SetPennyClassroomTestIndex(int index)
{
	m_pennyClassroomTestIndex = index;
	SAVE_PROFILE();
	ProfileMgr::GetInstance().Save(false, false);
}

void PlayerInfo::SetTwoYearBirthdayRewardGet(bool i_twoYearBirthdayRewardGet)
{
	m_bTwoYearBirthdayRewardGet = i_twoYearBirthdayRewardGet;
	SAVE_PROFILE();
	ProfileMgr::GetInstance().Save(false, false);
}

void PlayerInfo::SetCustomLevelGuessLikeEnable(bool enable)
{
	m_customLevelGuessLikeEnable = enable;
	SAVE_PROFILE();
	ProfileMgr::GetInstance().Save(false, false);
}

void PlayerInfo::SetNewPVPTrainingFirstEntered(bool i_enter)
{
	m_newPVPTrainingFirstEntered = i_enter;
	SAVE_PROFILE();
	ProfileMgr::GetInstance().Save(false, false);
}

void PlayerInfo::SetTodayChristmasProtectCurrency(int i_todayChristmasProtectCurrency)
{
	m_todayChristmasProtectCurrency = i_todayChristmasProtectCurrency;
	SAVE_PROFILE();
	ProfileMgr::GetInstance().Save(false, false);
}

void PlayerInfo::SetHasGotCustomLevelTutorialLevel(bool i_got)
{
	m_hasGotCustomLevelTutorialLevel = i_got;
	SAVE_PROFILE();
	ProfileMgr::GetInstance().Save(false, false);
}

int PlayerInfo::GetGoldenEggHammers()
{
	return m_goldenEggInfo.hammers;
}

int PlayerInfo::GetGoldenEggsObjectId()
{
	return m_goldenEggInfo.ObjectId;
}

int PlayerInfo::GetGoldenEggDailyReward()
{
	return m_goldenEggInfo.dailyReward;
}

int PlayerInfo::GetGoldenEggHammersLeft()
{
	return m_goldenEggInfo.hammersLeft;
}

uint32 PlayerInfo::GetCurrentSalesRefreshTime()
{
	return m_currentSalesInfo.refreshTimes;
}

uint32 PlayerInfo::GetGoldenEggLastRefreshTime()
{
	return m_goldenEggInfo.lastRefreshTime;
}

float PlayerInfo::GetGoldenEggDailyChargeAmount()
{
	return m_goldenEggInfo.dailyChargeAmount;
}

int PlayerInfo::GetGoldenEggDailyHammerAmount()
{
	return m_goldenEggInfo.dailyHammerAmount;
}

uint32 PlayerInfo::GetChristmasAccessoryLastRefreshTime()
{
	return m_christmasAccessoryInfo.lastRefreshTime;
}

void PlayerInfo::SetGoldenEggHammers(int i_hammers, bool need_save)
{
	m_goldenEggInfo.hammers = i_hammers;
	if (need_save)
		SAVE_PROFILE();
}

void PlayerInfo::SetGoldenEggDailyReward(int i_dailyReward, bool need_save)
{
	m_goldenEggInfo.dailyReward = i_dailyReward;
	if (need_save)
		SAVE_PROFILE();
}

void PlayerInfo::SetGoldenEggHammersLeft(int i_hammersLeft, bool need_save)
{
	m_goldenEggInfo.hammersLeft = i_hammersLeft;
	if (need_save)
		SAVE_PROFILE();
}

void PlayerInfo::SetGoldenEggLastRefreshTime(uint32 i_time, bool need_save)
{
	m_goldenEggInfo.lastRefreshTime = i_time;
	if (need_save)
		SAVE_PROFILE();
}

void PlayerInfo::SetGoldenEggDailyChargeAmount(float i_amount, bool need_save)
{
	m_goldenEggInfo.dailyChargeAmount = i_amount;
	if (need_save)
		SAVE_PROFILE();
}

void PlayerInfo::SetGoldenEggDailyHammerAmount(int i_amount, bool need_save)
{
	m_goldenEggInfo.dailyHammerAmount = i_amount;
	if (need_save)
		SAVE_PROFILE();
}

void PlayerInfo::SetChristmasAccessoryLastRefreshTime(uint32 i_time, bool need_save)
{
	m_christmasAccessoryInfo.lastRefreshTime = i_time;
	if (need_save)
		SAVE_PROFILE();
}

void PlayerInfo::SetCloseGemsReturn()
{
	m_iGemReturnDays = 8;
}

void PlayerInfo::SetRedPackOpenTotal(int i_num)
{
	m_redPackOpenTotal = i_num < 0 ? 0 : i_num;
	SAVE_PROFILE();
}

void PlayerInfo::SetLastTreasureYetiTime(time_t i_time)
{
	m_treasureYetiInfo.LastSpawnTime = i_time;
	SAVE_PROFILE();
}

void PlayerInfo::SetNextTreasureYetiTime(time_t i_time)
{
	m_treasureYetiInfo.NextSpawnTime = i_time;
	SAVE_PROFILE();
}

void PlayerInfo::SetServerSalesInfo(ServerSalesInfo i_info)
{
	m_serverSalesInfo = i_info;
}

uint64 PlayerInfo::getLastFreeGachaTime()
{
	return m_lastFreeGachaTime;
}

PlayerProfileVersion PlayerInfo::GetVersion() const
{
	return m_version;
}

unsigned long PlayerInfo::GetRandomSeed() const
{
	return m_randomSeed;
}

bool PlayerInfo::HasPopupOnceDay() const
{
	return m_hasPopupOnceDay;
}

PlayerProfileMapConversionState PlayerInfo::GetMapConversionState() const
{
	return m_mapConversionState;
}

bool PlayerInfo::GetLastOSVersonIsSeven() const
{
	return m_lastOSVersonIsSeven;
}

bool PlayerInfo::HasPopupPlantTrialToday() const
{
	return m_hasPopupPlantTrial;
}

ZombossSignalCurrency PlayerInfo::GetCurrentZombossSignal() const
{
	return m_zombossSignal;
}

std::vector<SavedWorldMapEventData>& PlayerInfo::GetSavedWorldMapEvents()
{
	return m_worldMapEventList;
}

std::vector<WorldCompletionData>& PlayerInfo::GetEventCompletionList()
{
	return m_worldMapEventData;
}

std::vector<int>& PlayerInfo::GetUnlockPlantIdList()
{
	return m_unlockedPlants;
}

time_t PlayerInfo::GetLastTreasureYetiTime() const
{
	return m_treasureYetiInfo.LastSpawnTime;
}

time_t PlayerInfo::GetNextTreasureYetiTime() const
{
	return m_treasureYetiInfo.NextSpawnTime;
}

const std::string& PlayerInfo::GetTreasureYetiLocation() const
{
	return m_treasureYetiInfo.WorldMapLocation;
}

const ProfileConversionResults& PlayerInfo::GetProfileConversionResults() const
{
	return m_profileConversionResults;
}

void PlayerInfo::SetProfileConversionResults(const ProfileConversionResults& i_results)
{
	m_profileConversionResults = i_results;
}

void PlayerInfo::SetVacationLevelInfo(const DangerRoomInfo& info)
{
	m_vacationLevelInfo = info;
}

int32 PlayerInfo::GetPlayYetiLevelCount()
{
	return m_curOnlineEventInfo.TodayYetiLeftCount;
}

int PlayerInfo::GetSpringBossCount()
{
	return m_curOnlineEventInfo.SpringbossLeftCount;
}

bool PlayerInfo::IsYetiTutorialPlayed()
{
	return m_curOnlineEventInfo.ToturialPlayered;
}

bool PlayerInfo::IsCheatingCheckFlag(CheatingCheckFlags flag)
{
	return TestFlag(m_CheatingCheckFlags, flag);
}

serializable_time_t PlayerInfo::GetCurrentRiftID()
{
	return m_riftCurrentID;
}

serializable_time_t PlayerInfo::GetCurrentRiftSubEventID()
{
	return m_riftCurrentSubID;
}

void PlayerInfo::SetCurrentRiftSubEventID(const serializable_time_t i_riftID)
{
	m_riftCurrentSubID = i_riftID;
	SAVE_PROFILE();
}

time_t PlayerInfo::GetLastGetVIPGemTime()
{
	return m_lastGetVIPGemTime;
}

time_t PlayerInfo::GetLastGetVIPGoldTime()
{
	return m_lastGetVIPGoldTime;
}

int PlayerInfo::GetMonthVIPState()
{
	return m_monthVIPState;
}

void PlayerInfo::SetGetMonthVIPGemTime(time_t tt)
{
	m_lastGetVIPGemTime = tt;
}

void PlayerInfo::SetGetMonthVIPGoldTime(time_t tt)
{
	m_lastGetVIPGoldTime = tt;
}

void PlayerInfo::SetMonthVIPState(int state)
{
	m_monthVIPState = state;
}

std::vector<WorldCupInfo>& PlayerInfo::GetWorldCupInfo()
{
	return m_worldCupInfo;
}

bool PlayerInfo::IsHappyVaseBreakerTaskExist(int i_id)
{
	for (size_t i = 0; i < m_happyVaseBreakerTaskInfos.size(); i++)
	{
		if (m_happyVaseBreakerTaskInfos[i].ID == i_id)
			return true;
	}
	return false;
}

TravelLogTaskSaveInfo PlayerInfo::GetHappyVaseBreakerTaskInfo(int i_id)
{
	for (size_t i = 0; i < m_happyVaseBreakerTaskInfos.size(); i++)
	{
		if (m_happyVaseBreakerTaskInfos[i].ID == i_id)
			return m_happyVaseBreakerTaskInfos[i];
	}
	TravelLogTaskSaveInfo info;
	info.ID = -1;
	info.GroupID = -1;
	info.Progress = -1;
	info.State = -1;
	info.Creation = 0;
	return info;
}

void PlayerInfo::UpdateHappyVaseBreakerTaskInfo(TravelLogTaskSaveInfo i_param)
{
	for (size_t i = 0; i < m_happyVaseBreakerTaskInfos.size(); i++)
	{
		TravelLogTaskSaveInfo* info = &m_happyVaseBreakerTaskInfos[i];
		if (info->ID == i_param.ID)
		{
			*info = i_param;
			SAVE_PROFILE();
			ProfileMgr::GetInstance().Save(false, false);
			return;
		}
	}
	m_happyVaseBreakerTaskInfos.push_back(i_param);
	SAVE_PROFILE();
	ProfileMgr::GetInstance().Save(false, false);
}

void PlayerInfo::ClearInvaildHappyVaseBreakerTaskInfo()
{
	std::vector<TravelLogTaskSaveInfo>::iterator it = m_happyVaseBreakerTaskInfos.begin();
	while (it != m_happyVaseBreakerTaskInfos.end())
	{
		if (it->GroupID == 1)
		{
			if (!IsToday(it->Creation))
			{
				it = m_happyVaseBreakerTaskInfos.erase(it);
				continue;
			}
		}
		else if (it->GroupID == 2)
		{
			if (!IsToday(it->Creation))
			{
				it = m_happyVaseBreakerTaskInfos.erase(it);
				continue;
			}
		}
		if (gLawnApp->GetRealServerTime() < it->Creation)
		{
			it = m_happyVaseBreakerTaskInfos.erase(it);
			continue;
		}
		++it;
	}
	SAVE_PROFILE();
	ProfileMgr::GetInstance().Save(false, false);
}

void PlayerInfo::ClearHappyVaseBreakerTaskInfo(int i_serverVersion)
{
	if (m_currentHappyVaseBreakerVersion != i_serverVersion)
	{
		m_happyVaseBreakerTaskInfos.clear();
		m_currentHappyVaseBreakerVersion = i_serverVersion;
		SAVE_PROFILE();
		ProfileMgr::GetInstance().Save(false, false);
	}
}

bool PlayerInfo::IsNoviceSevenDaysTaskExist(int i_id)
{
	for (size_t i = 0; i < m_noviceSevenDaysTaskInfos.size(); i++)
	{
		if (m_noviceSevenDaysTaskInfos[i].ID == i_id)
			return true;
	}
	return false;
}

TravelLogTaskSaveInfo PlayerInfo::GetNoviceSevenDaysTaskInfo(int i_id)
{
	for (size_t i = 0; i < m_noviceSevenDaysTaskInfos.size(); i++)
	{
		if (m_noviceSevenDaysTaskInfos[i].ID == i_id)
			return m_noviceSevenDaysTaskInfos[i];
	}
	TravelLogTaskSaveInfo info;
	info.ID = -1;
	info.GroupID = -1;
	info.Progress = -1;
	info.State = -1;
	info.Creation = 0;
	return info;
}

void PlayerInfo::UpdateNoviceSevenDaysTaskInfo(TravelLogTaskSaveInfo i_param)
{
	for (size_t i = 0; i < m_noviceSevenDaysTaskInfos.size(); i++)
	{
		TravelLogTaskSaveInfo* info = &m_noviceSevenDaysTaskInfos[i];
		if (info->ID == i_param.ID)
		{
			*info = i_param;
			SAVE_PROFILE();
			ProfileMgr::GetInstance().Save(false, false);
			return;
		}
	}
	m_noviceSevenDaysTaskInfos.push_back(i_param);
	SAVE_PROFILE();
	ProfileMgr::GetInstance().Save(false, false);
}

void PlayerInfo::ClearInvaildNoviceSevenDaysTaskInfo()
{
	ClearInvaildTaskInfo(m_noviceSevenDaysTaskInfos);
}

void PlayerInfo::ClearNoviceSevenDaysTaskInfo(int i_serverVersion)
{
	m_noviceSevenDaysTaskInfos.clear();
	SAVE_PROFILE();
	ProfileMgr::GetInstance().Save(false, false);
}

bool PlayerInfo::IsCallofWishTaskExist(int i_id)
{
	for (size_t i = 0; i < m_callofWishTaskInfos.size(); i++)
	{
		if (m_callofWishTaskInfos[i].ID == i_id)
			return true;
	}
	return false;
}

TravelLogTaskSaveInfo PlayerInfo::GetCallofWishTaskInfo(int i_id)
{
	for (size_t i = 0; i < m_callofWishTaskInfos.size(); i++)
	{
		if (m_callofWishTaskInfos[i].ID == i_id)
			return m_callofWishTaskInfos[i];
	}
	TravelLogTaskSaveInfo info;
	info.ID = -1;
	info.GroupID = -1;
	info.Progress = -1;
	info.State = -1;
	info.Creation = 0;
	return info;
}

void PlayerInfo::UpdateCallofWishTaskInfo(TravelLogTaskSaveInfo i_param)
{
	for (size_t i = 0; i < m_callofWishTaskInfos.size(); i++)
	{
		TravelLogTaskSaveInfo* info = &m_callofWishTaskInfos[i];
		if (info->ID == i_param.ID)
		{
			*info = i_param;
			SAVE_PROFILE();
			ProfileMgr::GetInstance().Save(false, false);
			return;
		}
	}
	m_callofWishTaskInfos.push_back(i_param);
	SAVE_PROFILE();
	ProfileMgr::GetInstance().Save(false, false);
}

void PlayerInfo::ClearInvaildCallofWishTaskInfo()
{
	ClearInvaildTaskInfo(m_callofWishTaskInfos);
}

void PlayerInfo::ClearCallofWishTaskInfo(int i_serverVersion)
{
	m_callofWishTaskInfos.clear();
	SAVE_PROFILE();
	ProfileMgr::GetInstance().Save(false, false);
}

bool PlayerInfo::IsGoldenEggTaskExist(int i_id)
{
	for (size_t i = 0; i < m_goldenEggTaskInfos.size(); i++)
	{
		if (m_goldenEggTaskInfos[i].ID == i_id)
			return true;
	}
	return false;
}

TravelLogTaskSaveInfo PlayerInfo::GetGoldenEggTaskInfo(int i_id)
{
	for (size_t i = 0; i < m_goldenEggTaskInfos.size(); i++)
	{
		if (m_goldenEggTaskInfos[i].ID == i_id)
			return m_goldenEggTaskInfos[i];
	}
	TravelLogTaskSaveInfo info;
	info.ID = -1;
	info.GroupID = -1;
	info.Progress = -1;
	info.State = -1;
	info.Creation = 0;
	return info;
}

void PlayerInfo::UpdateGoldenEggTaskInfo(TravelLogTaskSaveInfo i_param)
{
	for (size_t i = 0; i < m_goldenEggTaskInfos.size(); i++)
	{
		TravelLogTaskSaveInfo* info = &m_goldenEggTaskInfos[i];
		if (info->ID == i_param.ID)
		{
			*info = i_param;
			SAVE_PROFILE();
			ProfileMgr::GetInstance().Save(false, false);
			return;
		}
	}
	m_goldenEggTaskInfos.push_back(i_param);
	SAVE_PROFILE();
	ProfileMgr::GetInstance().Save(false, false);
}

void PlayerInfo::ClearInvaildGoldenEggTaskInfo()
{
	ClearInvaildTaskInfo(m_goldenEggTaskInfos);
}

void PlayerInfo::ClearGoldenEggTaskInfo(int i_serverVersion)
{
	m_goldenEggTaskInfos.clear();
	SAVE_PROFILE();
	ProfileMgr::GetInstance().Save(false, false);
}

TravelLogTaskSaveInfo PlayerInfo::GetArborDayTaskInfo(int i_id)
{
	TravelLogTaskSaveInfo info;
	GetTaskInfo(m_arborDayTaskInfos, i_id, info);
	return info;
}

void PlayerInfo::UpdateArborDayTaskInfo(TravelLogTaskSaveInfo i_param)
{
	UpdateTaskInfo(m_arborDayTaskInfos, i_param);
}

TravelLogTaskSaveInfo PlayerInfo::GetBattleOrderTaskInfo(int i_id)
{
	TravelLogTaskSaveInfo info;
	GetTaskInfo(m_battleOrderTaskInfos, i_id, info);
	return info;
}

void PlayerInfo::UpdateBattleOrderTaskInfo(TravelLogTaskSaveInfo i_param)
{
	UpdateTaskInfo(m_battleOrderTaskInfos, i_param);
}

void PlayerInfo::ClearBattleOrderTaskInfo(int i_serverVersion)
{
	if (m_currentBattleOrderVersion != i_serverVersion)
	{
		m_currentBattleOrderVersion = i_serverVersion;
		ClearTaskInfo(m_battleOrderTaskInfos);
	}
}

TravelLogTaskSaveInfo PlayerInfo::GetNewPVPTaskInfo(int i_id)
{
	TravelLogTaskSaveInfo info;
	GetTaskInfo(m_newPVPTaskInfos, i_id, info);
	return info;
}

void PlayerInfo::UpdateNewPVPTaskInfo(TravelLogTaskSaveInfo i_param)
{
	UpdateTaskInfo(m_newPVPTaskInfos, i_param);
}

void PlayerInfo::ClearInvaildNewPVPTaskInfo()
{
	ClearInvaildTaskInfo(m_newPVPTaskInfos);
}

void PlayerInfo::ClearNewPVPTaskInfo(int i_serverVersion)
{
	if (m_currentNewPVPBattlePassVersion != i_serverVersion)
	{
		m_currentNewPVPBattlePassVersion = i_serverVersion;
		ClearTaskInfo(m_newPVPTaskInfos);
	}
}

bool PlayerInfo::IsUnchartedBirthdayTaskExist(int i_id)
{
	std::string world = PVZ2UnchartedModeUtils::GetPrefixWorld();
	bool exists;
	if (world.find("anniversary") != std::string::npos)
	{
		exists = IsTaskExist(m_unchartedBirthdayTaskInfos, i_id);
	}
	else
	{
		exists = m_unchartedTaskInfos.find(world) != m_unchartedTaskInfos.end();
		if (exists)
			exists = IsTaskExist(m_unchartedTaskInfos[world], i_id);
	}
	return exists;
}

TravelLogTaskSaveInfo PlayerInfo::GetUnchartedBirthdayTaskInfo(int i_id)
{
	std::string world = PVZ2UnchartedModeUtils::GetPrefixWorld();
	TravelLogTaskSaveInfo info;
	if (world.find("anniversary") != std::string::npos)
	{
		GetTaskInfo(m_unchartedBirthdayTaskInfos, i_id, info);
	}
	else
	{
		if (m_unchartedTaskInfos.find(world) != m_unchartedTaskInfos.end())
			GetTaskInfo(m_unchartedTaskInfos[world], i_id, info);
	}
	return info;
}

void PlayerInfo::UpdateUnchartedBirthdayTaskInfo(TravelLogTaskSaveInfo i_param)
{
	std::string world = PVZ2UnchartedModeUtils::GetPrefixWorld();
	if (world.find("anniversary") != std::string::npos)
	{
		UpdateTaskInfo(m_unchartedBirthdayTaskInfos, i_param);
	}
	else
	{
		if (m_unchartedTaskInfos.find(world) != m_unchartedTaskInfos.end())
		{
			UpdateTaskInfo(m_unchartedTaskInfos[world], i_param);
		}
		else
		{
			std::vector<TravelLogTaskSaveInfo> empty;
			m_unchartedTaskInfos[world] = empty;
			UpdateTaskInfo(m_unchartedTaskInfos[world], i_param);
		}
	}
}

void PlayerInfo::ClearInvaildUnchartedBirthdayTaskInfo()
{
	ClearInvaildTaskInfo(m_unchartedBirthdayTaskInfos);
}

void PlayerInfo::ClearUnchartedBirthdayTaskInfo(int i_serverVersion)
{
	std::string world = PVZ2UnchartedModeUtils::GetPrefixWorld();
	if (world.find("anniversary") == std::string::npos)
	{
		if (m_currentUnchartedTaskVersions.find(world) != m_currentUnchartedTaskVersions.end())
		{
			if (i_serverVersion != m_currentUnchartedTaskVersions[world])
			{
				m_currentUnchartedTaskVersions[world] = i_serverVersion;
				ClearTaskInfo(m_unchartedTaskInfos[world]);
			}
		}
		else
		{
			m_currentUnchartedTaskVersions[world] = i_serverVersion;
			std::vector<TravelLogTaskSaveInfo> empty;
			m_unchartedTaskInfos[world] = empty;
			ClearTaskInfo(m_unchartedTaskInfos[world]);
		}
	}
	else if (m_currentUnchartedBirthdayVersion != i_serverVersion)
	{
		m_currentUnchartedBirthdayVersion = i_serverVersion;
		ClearTaskInfo(m_unchartedBirthdayTaskInfos);
	}
}

TravelLogTaskSaveInfo PlayerInfo::GetCornucopiaTaskInfo(int i_id)
{
	TravelLogTaskSaveInfo info;
	GetTaskInfo(m_cornucopiaTaskInfos, i_id, info);
	return info;
}

void PlayerInfo::UpdatetCornucopiaTaskInfo(TravelLogTaskSaveInfo i_param)
{
	UpdateTaskInfo(m_cornucopiaTaskInfos, i_param);
}

void PlayerInfo::ClearInvaildCornucopiaTaskInfo()
{
	ClearInvaildTaskInfo(m_cornucopiaTaskInfos);
}

TravelLogTaskSaveInfo PlayerInfo::GetPlantCultivateTaskInfo(int i_id)
{
	TravelLogTaskSaveInfo info;
	GetTaskInfo(m_plantCultivateTaskInfos, i_id, info);
	return info;
}

void PlayerInfo::UpdatePlantCultivateTaskInfo(TravelLogTaskSaveInfo i_param)
{
	UpdateTaskInfo(m_plantCultivateTaskInfos, i_param);
}

void PlayerInfo::ClearInvaildPlantCultivateTaskInfo()
{
	ClearInvaildTaskInfo(m_plantCultivateTaskInfos);
}

TravelLogTaskSaveInfo PlayerInfo::GetGiftFoReturnTaskInfo(int i_id)
{
	TravelLogTaskSaveInfo info;
	GetTaskInfo(m_giftFoReturnTaskInfos, i_id, info);
	return info;
}

void PlayerInfo::UpdateGiftFoReturnTaskInfo(TravelLogTaskSaveInfo i_param)
{
	UpdateTaskInfo(m_giftFoReturnTaskInfos, i_param);
}

void PlayerInfo::ClearInvaildGiftFoReturnTaskInfo()
{
	ClearInvaildTaskInfo(m_giftFoReturnTaskInfos);
}

void PlayerInfo::ClearGiftFoReturnTaskInfo(int i_serverVersion)
{
	if (m_currentGiftFoReturnVersion != i_serverVersion)
	{
		m_currentGiftFoReturnVersion = i_serverVersion;
		ClearTaskInfo(m_giftFoReturnTaskInfos);
		SAVE_PROFILE();
		ProfileMgr::GetInstance().Save(false, false);
	}
}

TravelLogTaskSaveInfo PlayerInfo::GetDaveKitchenTaskInfo(int i_id)
{
	TravelLogTaskSaveInfo info;
	GetTaskInfo(m_daveKitchenTaskInfos, i_id, info);
	return info;
}

void PlayerInfo::UpdateDaveKitchenTaskInfo(TravelLogTaskSaveInfo i_param)
{
	UpdateTaskInfo(m_daveKitchenTaskInfos, i_param);
}

void PlayerInfo::ClearInvaildDaveKitchenTaskInfo()
{
	ClearInvaildTaskInfo(m_daveKitchenTaskInfos);
}

bool PlayerInfo::IsLuckyChestTaskExist(int i_id)
{
	return IsTaskExist(m_luckyChestTaskInfos, i_id);
}

TravelLogTaskSaveInfo PlayerInfo::GetLuckyChestTaskInfo(int i_id)
{
	TravelLogTaskSaveInfo info;
	GetTaskInfo(m_luckyChestTaskInfos, i_id, info);
	return info;
}

void PlayerInfo::UpdateLuckyChestTaskInfo(TravelLogTaskSaveInfo i_param)
{
	UpdateTaskInfo(m_luckyChestTaskInfos, i_param);
}

void PlayerInfo::ClearInvaildLuckyChestTaskInfo()
{
	ClearInvaildTaskInfo(m_luckyChestTaskInfos);
}

void PlayerInfo::ClearLuckyChestTaskInfo(int i_serverVersion)
{
	ClearTaskInfo(m_luckyChestTaskInfos);
}

bool PlayerInfo::IsNFSLinkageTaskExist(int i_id)
{
	return IsTaskExist(m_nfsLinkageTaskInfos, i_id);
}

TravelLogTaskSaveInfo PlayerInfo::GetNFSLinkageTaskInfo(int i_id)
{
	TravelLogTaskSaveInfo info;
	GetTaskInfo(m_nfsLinkageTaskInfos, i_id, info);
	return info;
}

void PlayerInfo::UpdateNFSLinkageTaskInfo(TravelLogTaskSaveInfo i_param)
{
	UpdateTaskInfo(m_nfsLinkageTaskInfos, i_param);
}

void PlayerInfo::ClearInvaildNFSLinkageTaskInfo()
{
	ClearInvaildTaskInfo(m_nfsLinkageTaskInfos);
}

void PlayerInfo::ClearNFSLinkageTaskInfo(int i_serverVersion)
{
	ClearTaskInfo(m_nfsLinkageTaskInfos);
}

bool PlayerInfo::IsTourismOctoberTaskExist(int i_id)
{
	return IsTaskExist(m_tourismOctoberTaskInfos, i_id);
}

TravelLogTaskSaveInfo PlayerInfo::GetTourismOctoberTaskInfo(int i_id)
{
	TravelLogTaskSaveInfo info;
	GetTaskInfo(m_tourismOctoberTaskInfos, i_id, info);
	return info;
}

void PlayerInfo::UpdateTourismOctoberTaskInfo(TravelLogTaskSaveInfo i_param)
{
	UpdateTaskInfo(m_tourismOctoberTaskInfos, i_param);
}

void PlayerInfo::ClearInvaildTourismOctoberTaskInfo()
{
	ClearInvaildTaskInfo(m_tourismOctoberTaskInfos);
}

void PlayerInfo::ClearTourismOctoberTaskInfo(int i_serverVersion)
{
	ClearTaskInfo(m_tourismOctoberTaskInfos);
}


bool PlayerInfo::IsTaskExist(const std::vector<TravelLogTaskSaveInfo>& i_taskInfos, int i_id)
{
	for (size_t i = 0; i < i_taskInfos.size(); i++)
	{
		if (i_taskInfos[i].ID == i_id)
			return true;
	}
	return false;
}

void PlayerInfo::GetTaskInfo(const std::vector<TravelLogTaskSaveInfo>& i_taskInfos, int i_id, TravelLogTaskSaveInfo& i_result)
{
	for (size_t i = 0; i < i_taskInfos.size(); i++)
	{
		if (i_taskInfos[i].ID == i_id)
		{
			i_result = i_taskInfos[i];
			return;
		}
	}
	i_result.ID = -1;
	i_result.GroupID = -1;
	i_result.Progress = -1;
	i_result.State = -1;
	i_result.Creation = 0;
}

void PlayerInfo::UpdateTaskInfo(std::vector<TravelLogTaskSaveInfo>& i_taskInfos, TravelLogTaskSaveInfo i_param)
{
	size_t i;
	for (i = 0; i < i_taskInfos.size(); i++)
	{
		if (i_taskInfos[i].ID == i_param.ID)
		{
			i_taskInfos[i] = i_param;
			break;
		}
	}
	if (i == i_taskInfos.size())
		i_taskInfos.push_back(i_param);
	SAVE_PROFILE();
	ProfileMgr::GetInstance().Save(false, false);
}

void PlayerInfo::ClearTaskInfo(std::vector<TravelLogTaskSaveInfo>& i_taskInfos)
{
	i_taskInfos.clear();
	SAVE_PROFILE();
	ProfileMgr::GetInstance().Save(false, false);
}

void PlayerInfo::ClearInvaildTaskInfo(std::vector<TravelLogTaskSaveInfo>& i_taskInfos)
{
	std::vector<TravelLogTaskSaveInfo>::iterator it = i_taskInfos.begin();
	while (it != i_taskInfos.end())
	{
		if (it->GroupID == 1 && !IsToday(it->Creation))
		{
			it = i_taskInfos.erase(it);
			continue;
		}
		if (it->GroupID == 2 && !IsInThisWeek(it->Creation))
		{
			it = i_taskInfos.erase(it);
			continue;
		}
		if (gLawnApp->GetRealServerTime() < it->Creation)
		{
			it = i_taskInfos.erase(it);
			continue;
		}
		++it;
	}
	SAVE_PROFILE();
	ProfileMgr::GetInstance().Save(false, false);
}

const int PlayerInfo::GetAccessoryInfosSize()
{
	return m_plantAccessoryInfos.size();
}

DangerRoomSpecialOfferSaveData PlayerInfo::GetDangerRoomSpecialOfferSaveData()
{
	return m_dangerRoomSpecialOfferSaveData;
}

GemReturnButtonState PlayerInfo::GetGemReturnButtonInfo(int i_index)
{
	return (GemReturnButtonState)m_gemsReturnList[i_index];
}

int PlayerInfo::GetPlantAdventureTeamCount()
{
	return m_plantAdventureInfos.size();
}

void PlayerInfo::SetYetiToturialEnd()
{
	m_curOnlineEventInfo.ToturialPlayered = true;
	SAVE_PROFILE();
	TreasureYeti::RemoveFromMap();
	TreasureYeti::ScheduleNextYeti();
}

uint32 PlayerInfo::getTotalUnlockedAvatarSize()
{
	return m_listPlantAvatarsAvatarInfo.size();
}

void PlayerInfo::AddPvpShopRefresh(bool isrefresh)
{
	if (isrefresh)
	{
		m_pvpShopInfo.refreshTimes++;
	}
	m_pvpShopInfo.buyObjIds.clear();
}

void PlayerInfo::ClearCardGameLevelProgress(bool i_hard)
{
	m_CardGameProgressBitfieldDifficulty0 = 0;
	if (i_hard)
		m_CardGameProgressBitfieldDifficulty1 = 0;
	SAVE_PROFILE();
}

void PlayerInfo::ClearPVZ1LevelProgress(bool i_hard)
{
	m_pvz1ProgressBitfieldDifficulty0 = 0;
	if (i_hard)
		m_pvz1ProgressBitfieldDifficulty1 = 0;
	SAVE_PROFILE();
}

void PlayerInfo::ClearUnchartedLevelProgress(bool i_hard)
{
	m_UnchartedProgressBitfieldDifficulty0 = 0;
	if (i_hard)
		m_UnchartedProgressBitfieldDifficulty1 = 0;
	SAVE_PROFILE();
}

int PlayerInfo::GetLimitGachaDrawTimes(int type)
{
	return type == 1 ? m_limitGachaDrawTimesOne : m_limitGachaDrawTimesTen;
}

void PlayerInfo::GetRichmanGuessGameRatio(float& win, float& lose)
{
	win = m_richmanGameSaveData._winRatio;
	lose = m_richmanGameSaveData._loseRatio;
}

void PlayerInfo::FinishUpdateDeltaDataForServer()
{
	m_deltaDataOnlineSaveTime = m_deltaDataOfflineSaveTime;
	m_deltaDataOnline_sign = m_deltaDataOffline_sign;
}

void PlayerInfo::CheckConsumptionActivityVersion(int serverVersion)
{
	if (m_consumeAndReceiveVersion != serverVersion)
	{
		m_ConsumptionActivityGems = 0;
		m_consumeAndReceiveVersion = serverVersion;
		SAVE_PROFILE();
	}
}

void PlayerInfo::ClearLoginDayEvt(eDayEvtRec e)
{
	m_iDayRecEventFlag &= ~e;
	if (e == eDayEvtRec_SpringGift)
		m_iDayRecEventFlag |= eDayEvtRec_SpringGiftGet;
	SAVE_PROFILE();
}

void PlayerInfo::ClearUnchartedAnniveraryReward(int version)
{
	if (m_unchartedAnniversaryRewardVersion != version)
	{
		m_unchartedAnniversaryRewardVersion = version;
		m_unchartedAnniversaryReward = false;
	}
	SAVE_PROFILE();
}

void PlayerInfo::CompleteActivityLevel()
{
	if (m_activityLeftTime > 0)
	{
		m_activityLeftTime--;
		SAVE_PROFILE();
	}
}

bool PlayerInfo::DidProfileExistOnOldMap() const
{
	return m_mapConversionState <= MAPCONVERSION_RewardsPresented;
}

void PlayerInfo::DoUpdatePlantStarRewards()
{
	gLawnApp->GetWorldMapList();
}

bool PlayerInfo::GetHasBeenConvertedToNewMap() const
{
	return m_mapConversionState > MAPCONVERSION_None;
}

bool PlayerInfo::GetHasBeenGivenConversionRewards() const
{
	return m_mapConversionState > MAPCONVERSION_ProgressConverted;
}

GemCurrency PlayerInfo::GetRechargeGems()
{
	return m_gems - m_giveGems;
}

bool PlayerInfo::HasUsedServerSalesConfig()
{
	return m_currentSalesInfo.configName == m_serverSalesInfo.configName;
}

bool PlayerInfo::IsMonthlyCardActivated(eMonthlyCardType type)
{
	return (type & m_monthlyCardType) != 0;
}

bool PlayerInfo::IsValid()
{
	return m_name != L"-";
}

void PlayerInfo::SetCurrentDangerRoomLife(DangerRoomLifeData& i_life)
{
	m_currentLifeData = i_life;
	SAVE_PROFILE();
}

void PlayerInfo::SetCurrentEndlessRankData(int i_rank)
{
	if (i_rank != -1)
		m_endlessCurrentRank = i_rank;
	SAVE_PROFILE();
}

bool PlayerInfo::TestLoginDayEvt(eDayEvtRec e)
{
	return (e & m_iDayRecEventFlag) != 0;
}

void PlayerInfo::UnlockPVP()
{
	m_unlockPVP = true;
	SAVE_PROFILE();
}

int PlayerInfo::GetAdvertisementWatchCount(AdvertisementTimeType type)
{
	if (type == ADS_TIME_ENDLEVEL)
		return m_advertisementWatchCountInfo.EndlessCount;
	return 0;
}

int PlayerInfo::GetBirthZGetCount(time_t iStamp)
{
	BirthZRecord* record = GetBirthZRecord(iStamp);
	if (record)
		return record->iGetCount;
	return 0;
}

bool PlayerInfo::GetHardLevelCompleted(const std::string& i_levelName)
{
	return GetWorldMapEventStatus(i_levelName) >= EVENTSTATUS_HARD_CLEARED;
}

bool PlayerInfo::GetLevelCompleted(const std::string& i_levelName)
{
	return GetWorldMapEventStatus(i_levelName) >= EVENTSTATUS_CLEARED;
}

bool PlayerInfo::IsGeneLocked(int i_geneID)
{
	return GetPlantGeneInfoByID(i_geneID).LockState != 0;
}

bool PlayerInfo::IsStarCompletedByLevel(const std::string& level_name)
{
	return GetStarCompleted(level_name) > 2;
}

bool PlayerInfo::IsTodayRiddleTaskComplete()
{
	return !NeedResetRiddleInfo();
}

void PlayerInfo::SetChildrenDayInfo(int dayStart, int buyLimit, const std::string& version)
{
	m_childrenDayStart = dayStart;
	m_childrenDayBuyLimit = buyLimit;
	m_childrenDayVersion = version;
}

void PlayerInfo::SetNeedShowSpringGift(bool setting)
{
	if (m_bNeedShowSpringGift != setting)
	{
		m_bNeedShowSpringGift = setting;
		SAVE_PROFILE();
	}
}

bool PlayerInfo::HasValidSales()
{
	if (m_currentSalesInfo.ObjectId == -1)
		return false;
	return GetCurrentSalesPricesCount() > 0;
}

bool PlayerInfo::IsNeedShowSpringGift() const
{
	return m_bNeedShowSpringGift && gLawnApp->GetActivityConfig()->IsSpringGiftActivated();
}

int PlayerInfo::ResetGoldenEggsObjectId()
{
	m_goldenEggInfo.ObjectId = TryToResetGoldenEggsObjectId();
	SAVE_PROFILE();
	return m_goldenEggInfo.ObjectId;
}

void PlayerInfo::SetDelaySave(pvztime_t delay_time)
{
	m_timerDelaySave = PVZ_T() + delay_time;
}

void PlayerInfo::SetPlayerGems(const struct S2C_PlayerInfo& i_info)
{
	SetGems(i_info.m_Gems);
	SetGiveGems(i_info.m_freeGem);
}

void PlayerInfo::setLastFreeGachaTimeNew(int i_type, int32 lastFreeGacha)
{
	if (i_type == GACHA_NORMAL)
		m_lastFreeGachaTimeNormal = lastFreeGacha;
	else if (i_type == GACHA_RARE)
		m_lastFreeGachaTimeRare = lastFreeGacha;
	else if (i_type == GACHA_AVATAR)
		m_lastFreeGachaTimeAvatar = lastFreeGacha;
	SAVE_PROFILE();
}

void PlayerInfo::ClearLostNetActivityRecord()
{
	m_lastLostNetTokenDate = 0;
	m_lostNetTokenDate.clear();
	SAVE_PROFILE();
}

void PlayerInfo::GenerateRandomSeed()
{
	m_randomSeed = time(NULL);
	SAVE_PROFILE();
}

std::string PlayerInfo::GetChildrenDayVersion()
{
	return m_childrenDayVersion;
}

std::vector<std::string> PlayerInfo::GetPvZ1AchievementBeatEliteZombieList()
{
	return m_pvz1BeatEliteZombieList;
}

RichmanGameSaveData PlayerInfo::GetRichmanGameSaveData()
{
	return m_richmanGameSaveData;
}

RichmanBattleEventSaveData PlayerInfo::GetRichmanTileBattleSaveData()
{
	return m_richmanBattleEventData;
}

/////////////// Logic ///////////////

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

void PlayerInfo::AM_SetLevel(std::string string)
{
}

void PlayerInfo::AddPennyFuel(const PennyFuelCurrency i_amount, const bool i_willBeBankedLater)
{
}

void PlayerInfo::AddPennyTech(const PennyTechCurrency i_amount)
{
}

bool PlayerInfo::CanRiddleToday()
{
	return PlayerInfo::NeedResetRiddleInfo();
}

void PlayerInfo::ClearRebateData()
{
	 PlayerInfo::ResetRebateData();
}

void PlayerInfo::AddZombossSignal(const ZombossSignalCurrency i_amount)
{
}

void PlayerInfo::SubtractPennyFuel(const PennyFuelCurrency i_amount)
{
}

void PlayerInfo::SubtractPennyTech(const PennyTechCurrency i_amount)
{
}

void PlayerInfo::saveCurrentProfile()
{
	 PlayerInfo::SAVE_PROFILE();
}

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

void PlayerInfo::setiOSBugCompen(bool hasCompen)
{
	m_iOSBugCompen = hasCompen;
	SAVE_PROFILE();
}

void PlayerInfo::setFirstDiamondGacha(bool bfirstGacha)
{
	m_firstDiamondGacha = bfirstGacha;
	SAVE_PROFILE();
}

void PlayerInfo::setLastFreeGachaTime(int32 lastFreeGacha)
{
	m_lastFreeGachaTime = lastFreeGacha;
	SAVE_PROFILE();
}

void PlayerInfo::setLastZmatchShopRefrashTime(time_t lastZmatchShopRefrashTime)
{
	m_lastZmatchShopRefrashTime = lastZmatchShopRefrashTime;
	SAVE_PROFILE();
}

void PlayerInfo::AddRebateCharge(int iAdd)
{
	m_iRebateCharge += iAdd;
	SAVE_PROFILE();
}

void PlayerInfo::AddConsumptionGems(int iAdd)
{
	m_iConsumptionGems += iAdd;
	SAVE_PROFILE();
}

void PlayerInfo::IncrementSessionCount()
{
	m_lifetimeSessionCount++;
	SAVE_PROFILE();
}

bool PlayerInfo::getHasPurchaseCukePkg()
{
	return m_bHasPurchaseCukePkg;
}

void PlayerInfo::setHasPurchaseCukePkg(bool hasPurchase)
{
	m_bHasPurchaseCukePkg = hasPurchase;
	SAVE_PROFILE();
}

void PlayerInfo::AddConsumptionRewardCount(int iAdd)
{
	m_iConsumptionRewardCount += iAdd;
	SAVE_PROFILE();
}

void PlayerInfo::IncrementZombossFightCount()
{
	m_zombossFightsThisCycle++;
	SAVE_PROFILE();
}

void PlayerInfo::clearHeadShot()
{
	m_unlockHeadShotIds.clear();
}

void PlayerInfo::AddBossChallengeInfo(const BossKillTimeChallengeInfo& info)
{
	m_bossKillTimeChallenge.push_back(info);
}

void PlayerInfo::ClearVaseBreakerData()
{
	m_arcadeProgress.clear();
}

void PlayerInfo::ClearArborDayTaskInfo(int i_serverVersion)
{
	ClearTaskInfo(m_arborDayTaskInfos);
}

void PlayerInfo::ClearBossChallengeInfo()
{
	m_bossKillTimeChallenge.clear();
}

void PlayerInfo::ClearCornucopiaTaskInfo(int i_serverVersion)
{
	ClearTaskInfo(m_cornucopiaTaskInfos);
}

void PlayerInfo::ClearDaveKitchenTaskInfo(int i_serverVersion)
{
	ClearTaskInfo(m_daveKitchenTaskInfos);
}

void PlayerInfo::ClearPlantCultivateTaskInfo(int i_serverVersion)
{
	ClearTaskInfo(m_plantCultivateTaskInfos);
}

void PlayerInfo::ClearInvaildArborDayTaskInfo()
{
	ClearInvaildTaskInfo(m_arborDayTaskInfos);
}

void PlayerInfo::ClearInvaildBattleOrderTaskInfo()
{
	ClearInvaildTaskInfo(m_battleOrderTaskInfos);
}

void PlayerInfo::ClearBundleQueueingList()
{
	m_queuedBundles.clear();
}

void PlayerInfo::setLastOrderId( const char* orderid )
{
	lastOrderId_ = orderid;
}

void PlayerInfo::increaseUploadKey()
{
	++m_uploadKey;saveCurrentProfile();
}

GemCurrency PlayerInfo::AM_GetGems()
{
	return m_gems;
}

CoinCurrency PlayerInfo::AM_GetCoins()
{
	return m_coins;
}

void PlayerInfo::setGachaCompen(bool hasCompen)
{
	m_gachaCompen = hasCompen;
}

bool PlayerInfo::getiOSBugCompen()
{
	return m_iOSBugCompen;
}

void PlayerInfo::setAvatarCompen(bool hasCompen)
{
	m_avatarCompen = hasCompen;
}

bool PlayerInfo::getPlantStoreOpen()
{
	return m_plantstoreOpen;
}

void PlayerInfo::setPlantStoreOpen(bool hasCompen)
{
	m_plantstoreOpen = hasCompen;
}

bool PlayerInfo::getQihooLoginReward()
{
	return m_qihooLoginReward;
}

bool PlayerInfo::isFirstDiamondGacha()
{
	return m_firstDiamondGacha;
}

void PlayerInfo::setQihooLoginReward(bool hasObtain)
{
	m_qihooLoginReward = hasObtain;
}

bool PlayerInfo::getDailyRewardCompen()
{
	return m_dailyRewardCompen;
}

void PlayerInfo::setDailyRewardCompen(bool hasCompen)
{
	m_dailyRewardCompen = hasCompen;
}

void PlayerInfo::setAvatarAdvanceCompen(bool bAdvanceCompen)
{
	m_avatarAdvanceCompen = bAdvanceCompen;
}

time_t PlayerInfo::getLastZmatchShopRefrashTime()
{
	return m_lastZmatchShopRefrashTime;
}

void PlayerInfo::MarkForDelete()
{
	m_markedForDelete = true;
	SAVE_PROFILE();
}

void PlayerInfo::UpdateVersion()
{
	m_version = PLAYERPROFILEVER_NMTWorld_Sep15_2016;
	SAVE_PROFILE();
}

void PlayerInfo::ResetRebateCharge()
{
	m_iRebateCharge = 0;
	SAVE_PROFILE();
}

void PlayerInfo::IncrementDaysCount()
{
	m_daysCount++;
}

void PlayerInfo::MarkForKongfuUnlock()
{
	m_purchasedKongfuUnlock = true;
	SAVE_PROFILE();
}

void PlayerInfo::AddRedPackOpenTotalCount(int iNum)
{
	SetRedPackOpenTotal(iNum + m_redPackOpenTotal);
}

void PlayerInfo::AddRechargeGiftTimes()
{
	m_rechargeGiftTimes++;
	SAVE_PROFILE();
}

void PlayerInfo::ResetRechargeGiftTimes()
{
	m_rechargeGiftTimes = 0;
	m_rechargeGiftCached = false;
}

bool PlayerInfo::CanBuyChildrenDayItem()
{
	return m_childrenDayBuyCount < m_childrenDayBuyLimit;
}

void PlayerInfo::ClearZombossFightCount()
{
	m_zombossFightsThisCycle = 0;
	SAVE_PROFILE();
}

void PlayerInfo::ResetConsumptionRewardDate()
{
	m_iConsumptionRewardCount = 0;
	m_iConsumptionGems = 0;
	SAVE_PROFILE();
}

void PlayerInfo::ResetTotalLoginGotRewardDays()
{
	m_bHasGotDailyReward = false;
	SAVE_PROFILE();
}

void PlayerInfo::SaveRechargePlantPieceReward()
{
	m_bHasRechargePieceReward = true;
	SAVE_PROFILE();
}

void PlayerInfo::ResetNeedResetSprintGiftIndex()
{
	m_needToResetSprintGiftIndex = true;
}

void PlayerInfo::ClearRiftLevelProgress()
{
	m_riftProgressBitfieldDifficulty0 = 0;
	m_riftProgressBitfieldDifficulty1 = 0;
	m_riftProgressBitfieldDifficulty2 = 0;
	SAVE_PROFILE();
}

void PlayerInfo::ResetLotteryConsumptionGems(bool isNeedSave)
{
	m_nLotteryConsumptionGems = 0;
	if (isNeedSave)
		SAVE_PROFILE();
}

void PlayerInfo::ResetConsumptionActivityGems(bool isNeedSave)
{
	m_ConsumptionActivityGems = 0;
	if (isNeedSave)
		SAVE_PROFILE();
}

bool PlayerInfo::StillRemainsGemsReturn()
{
	return m_iGemReturnDays >= 1 && m_iGemReturnDays <= 7;
}

void PlayerInfo::ForceRefreshGoldenEggInfo()
{
	m_goldenEggInfo.inited = false;
	DailyRefreshGoldenEggInfo();
}

void PlayerInfo::ForceRefreshChristmasAccessoryInfo()
{
	m_christmasAccessoryInfo.inited = false;
	DailyRefreshChristmasAccessoryInfo();
}

void PlayerInfo::ClearAvatarInfo()
{
	m_listPlantAvatarsAvatarInfo.clear();
}

void PlayerInfo::ClearNewAvatarInfo()
{
	m_listPlantNewAvatarInfo.clear();
}

void PlayerInfo::ClearNewAvatarPieceInfo()
{
	m_listPlantNewAvatarPiecesInfo.clear();
}

void PlayerInfo::ClearCollection()
{
	m_listCollectionInfo.clear();
}

void PlayerInfo::ClearRiftZombossAttemptDifficulty()
{
	m_riftZombossAttemptDifficulty.clear();
}

void PlayerInfo::AddWorldAnimPlayed(const std::string& i_world)
{
	m_worldAnimPlayed.push_back(i_world);
}

ArcadeLastPlayData* PlayerInfo::GetArcadeLastPlayForMode(const std::string& i_modeID)
{
	return LocalProfileSaveData::GetOrCreateArcadeLastPlayData(this, i_modeID);
}

const std::vector<CardInfo>& PlayerInfo::GetAllCardList()
{
	return m_listCardInfo;
}

bool PlayerInfo::IsKilledZombie(const std::string& i_zombieTypeName)
{
	return m_zombieAlmanac.IsKilledZombie(i_zombieTypeName);
}

bool PlayerInfo::getIsAuthIDCard()
{
	return m_bIsAuthIDCard;
}

void PlayerInfo::setIsAuthIDCard(bool isAuthIDCard)
{
	m_bIsAuthIDCard = isAuthIDCard;
	SAVE_PROFILE();
}

void PlayerInfo::PushACLog(const S2C_ACLog& acLog)
{
	m_acLogData.logList.push_back(acLog);
}

void PlayerInfo::SetCheatingCheckFlag(CheatingCheckFlags flag, bool status)
{
	SetFlag(m_CheatingCheckFlags, flag, status);
}

void PlayerInfo::SetWorldMapZoomData(const float i_zoomLevel, const bool i_isOnUniverseMap)
{
	m_onUniverseMap = i_isOnUniverseMap;
	m_lastWorldMapZoom = i_zoomLevel;
	SAVE_PROFILE();
}

bool PlayerInfo::ShouldRequestTrigger()
{
	return m_noviceSevenDaysTaskInfos.empty();
}

void PlayerInfo::OnOK()
{
	gLawnApp->KillPVZ2Dialog();
}

bool PlayerInfo::IsPopupRichmanTileBattleEvent()
{
	return m_richmanBattleEventData._needPopup;
}

DangerRoomTrainingRecord PlayerInfo::GetDangerRoomTrainingRecord(const std::string& i_world)
{
	return findTrainingRecord(i_world);
}

void PlayerInfo::SetTwDailySignDay(int day, int newTime, std::string itemVersion)
{
	if (m_twLoginDays < day)
		m_twLoginDays = day;
	m_twLastRewardTime = newTime;
	m_twDailySignVersion = itemVersion;
}

void PlayerInfo::AddPlantAdventureOpenInfo(std::string i_dungeonName)
{
	m_plantAdventureOpenInfo.push_back(i_dungeonName);
	SAVE_PROFILE();
}

void PlayerInfo::AddZombieStoredMarks(ZombieWarning i_warning)
{
	m_zombieStoredMarks.push_back(i_warning);
	SAVE_PROFILE();
}

std::string PlayerInfo::AM_GetLevel()
{
	return m_level;
}

std::wstring PlayerInfo::AM_GetName()
{
	return m_name;
}

void PlayerInfo::BuyPvpShopObj(int32 objId)
{
	m_pvpShopInfo.buyObjIds.push_back(objId);
}

void PlayerInfo::ClearAccessoryPieceCount()
{
	m_accessoryPieces.clear();
	resetAccessoryPieceSign();
}

void PlayerInfo::ClearACLog()
{
	m_acLogData.logList.clear();
	m_aclog.clear();
}

void PlayerInfo::ClearAllDisplayingBundle()
{
	m_displayingBundle.clear();
	SAVE_PROFILE();
}

void PlayerInfo::clearPlantPieceCount()
{
	m_plantPieceRecords.clear();
	resetPlantPieceSign();
}

std::vector<AdventurePlants> PlayerInfo::GetAdventurePlantsInfo()
{
	return m_plantsInAdventure;
}

std::vector<int> PlayerInfo::getAllChallengeCount()
{
	return m_challengeCount;
}

ChristmasAccessoryInfo PlayerInfo::GetChristmasAccessoryInfo()
{
	return m_christmasAccessoryInfo;
}

CurrentSalesInfo PlayerInfo::GetCurrentSalesInfo()
{
	return m_currentSalesInfo;
}

std::string PlayerInfo::GetCurrentLevel() const
{
	return m_level;
}

std::vector<int> PlayerInfo::GetGemReturnInfo()
{
	return m_gemsReturnList;
}

GeilivableLotteryInfo PlayerInfo::GetGLInfo()
{
	return m_geilivableLotteryInfo;
}

GoldenEggInfo PlayerInfo::GetGoldenEggInfo()
{
	return m_goldenEggInfo;
}

std::vector<int> PlayerInfo::GetGoldenEggsStat()
{
	return m_goldenEggInfo.eggsStat;
}

const std::vector<int> PlayerInfo::GetKilledZombieList() const
{
	return m_killedZombies;
}

Sexy::StructuredData PlayerInfo::GetLuaShareJson(void) const
{
	return m_jsonLuaInfo;
}

std::wstring PlayerInfo::GetName() const
{
	return m_name;
}

bool PlayerInfo::GetPowerupUnlockState(const std::string& i_powerupName) const
{
	return findIndexForName(i_powerupName, m_powerupRecords) >= 0;
}

std::string PlayerInfo::GetSaveSignUUID() const
{
	return m_save_sign_uuid;
}

ServerSalesInfo PlayerInfo::GetServerSalesInfo()
{
	return m_serverSalesInfo;
}

std::string PlayerInfo::GetSignUUID() const
{
	return m_sign_uuid;
}

const ZombieStoredMarks PlayerInfo::GetZombieStoredMarks()
{
	return m_zombieStoredMarks;
}

const bool PlayerInfo::HasDangerRoomInfo(const std::string& i_worldName)
{
	return findIndexForWorldName(i_worldName, m_dangerRoomInfo) >= 0;
}

bool PlayerInfo::HasFirstPlantAdventureOpenInfo()
{
	return (int)m_plantAdventureOpenInfo.size() > 0;
}

bool PlayerInfo::HasPlantPiece()
{
	return m_plantPieceRecords.size() != 0;
}

bool PlayerInfo::HasQueueingBundle()
{
	return m_queuedBundles.size() != 0;
}

void PlayerInfo::RemoveAllPlantAdventureOpenInfo()
{
	m_plantAdventureOpenInfo.clear();
	SAVE_PROFILE();
}

void PlayerInfo::SetArenaInfo(const ArenaInfo& i_arenaInfo)
{
	m_arenaInfo = i_arenaInfo;
	SAVE_PROFILE();
}

void PlayerInfo::setChallengeCount(std::vector<int> i_challengeCount)
{
	m_challengeCount = i_challengeCount;
	SAVE_PROFILE();
}

void PlayerInfo::SetCurrentSalesInfo(CurrentSalesInfo i_info)
{
	m_currentSalesInfo = i_info;
	SAVE_PROFILE();
}

void PlayerInfo::SetGiveGems(const GemCurrency i_amount)
{
	m_giveGems = i_amount;
	resetGemsSign();
	SAVE_PROFILE();
}

void PlayerInfo::SetLastWorldName(const std::string& i_world_name)
{
	m_last_world_name = i_world_name;
	SAVE_PROFILE();
}

void PlayerInfo::SetName(const std::wstring& i_name)
{
	m_name = i_name;
	SAVE_PROFILE();
}

void PlayerInfo::SetTreasureYetiLocation(const std::string& i_location)
{
	m_treasureYetiInfo.WorldMapLocation = i_location;
	SAVE_PROFILE();
}

bool PlayerInfo::HasCompletedRiftLevel(int i_nodeIndex)
{
	return ((1 << i_nodeIndex) & (m_riftProgressBitfieldDifficulty0 | m_riftProgressBitfieldDifficulty1 | m_riftProgressBitfieldDifficulty2)) != 0;
}

void PlayerInfo::OnTodayLostNetActivityBought()
{
	m_lostNetTokenDate.push_back(m_lastLostNetTokenDate);
	SAVE_PROFILE();
}

void PlayerInfo::ResetNationalDayDate()
{
	m_vNationalDayDate.clear();
	SAVE_PROFILE();
}

void PlayerInfo::ResetRechargePlantPieceReward()
{
	m_bHasRechargePieceReward = false;
	ResetActitiyDaysRechargeCurrency();
	SAVE_PROFILE();
}

void PlayerInfo::SetArcadeProgress(std::vector<ArcadePackProgress>& i_newProgress)
{
	m_arcadeProgress = i_newProgress;
	SAVE_PROFILE();
}

void PlayerInfo::SetCurrentTrainingWorldName(const std::string& i_name)
{
	m_currentTrainingWorldName = i_name;
	SAVE_PROFILE();
}

void PlayerInfo::SetNewPVPSelectedPlants(const std::vector<int>& i_plants)
{
	m_newPVPSelectedPlants = i_plants;
	SAVE_PROFILE();
}

void PlayerInfo::SetPowerUpProgress(std::vector<PowerUpCollectionProgress>& i_newProgress)
{
	m_powerUpCollections = i_newProgress;
	SAVE_PROFILE();
}

void PlayerInfo::ClearSavedProgress()
{
	m_completedNarrationEvents.clear();
	m_tutorialNewProgress = (MapTutorialState)0;
	m_unlockedGameFeatures.clear();
	SAVE_PROFILE();
}

bool PlayerInfo::getIsExperiencePlant(const std::string& i_plantTypeName)
{
	return getIsExperiencePlantById(PlantNameMapper::GetInstance().GetIdForName(i_plantTypeName));
}

int PlayerInfo::GetMaterialNum(const std::string& i_materialName) const
{
	return GetMaterialNum(MaterialItemMapper::GetInstance().GetIdForName(i_materialName));
}

int PlayerInfo::GetNumWorldKeys()
{
	if (!checkWorldKeysSign())
		resetWorldKeysZeroSign();
	return m_worldkeys;
}

std::vector<PlantAccessoryInfo>& PlayerInfo::GetPlantAccessoryInfos()
{
	if (!checkAccessoryInfoSign())
		resetAccessoryInfoZeroSign();
	return m_plantAccessoryInfos;
}

int PlayerInfo::GetStarCompleted(const std::string& i_eventDataName)
{
	WorldMapEventStatus status = GetWorldMapEventStatus(i_eventDataName);
	if (status == EVENTSTATUS_CLEARED)
		return 1;
	return status == EVENTSTATUS_HARD_CLEARED ? 3 : 0;
}

bool PlayerInfo::HasCompletedCardGameLevel(int i_nodeIndex, bool i_hard)
{
	int64_t bit = 1 << i_nodeIndex;
	if (i_hard)
		return (bit & m_CardGameProgressBitfieldDifficulty1) != 0;
	return (bit & m_CardGameProgressBitfieldDifficulty0) != 0;
}

bool PlayerInfo::HasCompletedPVZ1Level(int i_nodeIndex, bool i_hard)
{
	int64_t bit = 1 << i_nodeIndex;
	if (i_hard)
		return (bit & m_pvz1ProgressBitfieldDifficulty1) != 0;
	return (bit & m_pvz1ProgressBitfieldDifficulty0) != 0;
}

bool PlayerInfo::HasCompletedUnchartedLevel(int i_nodeIndex, bool i_hard)
{
	int64_t bit = 1 << i_nodeIndex;
	if (i_hard)
		return (bit & m_UnchartedProgressBitfieldDifficulty1) != 0;
	return (bit & m_UnchartedProgressBitfieldDifficulty0) != 0;
}

bool PlayerInfo::HasPaidForGemReturn()
{
	return m_gemReturnPaid && m_gemsReturnList.size() != 0;
}

bool PlayerInfo::IsServerSalesConfigValid()
{
	return m_serverSalesInfo.fromServer && m_serverSalesInfo.priceList.size() != 0;
}

void PlayerInfo::ResetPvpShop(int32 lastResetDay)
{
	m_pvpShopInfo.refreshTimes = 0;
	m_pvpShopInfo.lastGotTimeDay = lastResetDay;
	m_pvpShopInfo.buyObjIds.clear();
	m_pvpShopInfo.sellObjIds.clear();
}

void PlayerInfo::setFirstDiamondGachaNew(int i_type, bool bfirstGacha)
{
	if (i_type == GACHA_NORMAL)
		m_firstDiamondGachaNormal = bfirstGacha;
	else if (i_type == GACHA_RARE)
		m_firstDiamondGachaRare = bfirstGacha;
	else if (i_type == GACHA_AVATAR)
		m_firstDiamondGachaAvatar = bfirstGacha;
	SAVE_PROFILE();
}

void PlayerInfo::AddRiftZombossAttemptDifficulty(int i_difficulty)
{
	m_riftZombossAttemptDifficulty.push_back(i_difficulty);
	SAVE_PROFILE();
}

void PlayerInfo::AddToGoldenEggOpenedInfo(int i_index, bool need_save)
{
	if (!IsOpenedIndex(i_index))
		m_goldenEggInfo.openedInfo.push_back(i_index);
}

bool PlayerInfo::CanEnjoyActivity()
{
	RefreshActivityRecharge(false);
	return m_bActivityRecharge && m_activityLeftTime > 0;
}

void PlayerInfo::ClearArtifactInfo()
{
	m_artifactListArray.clear();
	SAVE_PROFILE();
	ProfileMgr::GetInstance().Save(false, false);
}

void PlayerInfo::ClearOldMapEventStatus()
{
	if (GetHasBeenConvertedToNewMap() == false)
		m_worldMapEventList.clear();
}

void PlayerInfo::ClearPlantGeneEssenceInfo()
{
	m_plantGeneEssenceList.clear();
	SAVE_PROFILE();
	ProfileMgr::GetInstance().Save(false, false);
}

void PlayerInfo::ClearPlantGeneInfo()
{
	m_plantGeneList.clear();
	SAVE_PROFILE();
	ProfileMgr::GetInstance().Save(false, false);
}

void PlayerInfo::FixRepeatData()
{
	m_vecLevelLostInfo.clear();
	UniquePlantPieceCount();
	UniquePlantStartLevel();
	UniqueZombieStartLevel();
}

int PlayerInfo::GetChristmasAccessoryChances(int i_type)
{
	switch (i_type)
	{
	case 1:
		return m_christmasAccessoryInfo.freeChances;
	case 2:
		return m_christmasAccessoryInfo.coinChances;
	case 3:
		return m_christmasAccessoryInfo.gemChances;
	}
	return 0;
}

uint64 PlayerInfo::getLastFreeGachaTimeNew(int i_type)
{
	if (i_type == GACHA_NORMAL)
		return m_lastFreeGachaTimeNormal;
	if (i_type == GACHA_RARE)
		return m_lastFreeGachaTimeRare;
	if (i_type == GACHA_AVATAR)
		return m_lastFreeGachaTimeAvatar;
	return 0;
}

void PlayerInfo::IncGemReturnDays()
{
	m_iGemReturnDays++;
	m_iDayRecEventFlag &= ~1;
	SAVE_PROFILE();
	ProfileMgr::GetInstance().Save(false, false);
}

void PlayerInfo::PushPlantGeneInfo(const PlantGeneInfo& i_info)
{
	m_plantGeneList.push_back(i_info);
	SAVE_PROFILE();
	ProfileMgr::GetInstance().Save(false, false);
}

void PlayerInfo::SaveTotalLoginGotRewardDays()
{
	m_bHasGotDailyReward = true;
	ProfileMgr::GetInstance().Save(false, false);
	SAVE_PROFILE();
}

int PlayerInfo::SetCurrentArtifact(int i_artifactID)
{
	m_currentArtifact = i_artifactID;
	SAVE_PROFILE();
	ProfileMgr::GetInstance().Save(false, false);
	return m_currentArtifact;
}

void PlayerInfo::SetRechargeGiftCached(bool bCached)
{
	if (!bCached)
	{
		if (m_rechargeGiftCached != 0)
			m_rechargeGiftCached--;
	}
	else if (m_rechargeGiftCached + m_rechargeGiftTimes == 0)
	{
		m_rechargeGiftCached++;
	}
	SAVE_PROFILE();
}

void PlayerInfo::SetRichmanGameSaveData(RichmanGameSaveData data, bool save)
{
	m_richmanGameSaveData = data;
	if (save)
	{
		SAVE_PROFILE();
		ProfileMgr::GetInstance().Save(false, false);
	}
}

void PlayerInfo::SetRichmanGuessGameRatio(float win, float lose, bool save)
{
	m_richmanGameSaveData._winRatio = win;
	m_richmanGameSaveData._loseRatio = lose;
	if (save)
	{
		SAVE_PROFILE();
		ProfileMgr::GetInstance().Save(false, false);
	}
}

bool PlayerInfo::CanStartNewPlantAdventure()
{
	return GetPlantAdventureTeamCount() < gLawnApp->GetPlantAdventureConfig().GetMaxTeam();
}

void PlayerInfo::ClearPvZ1AchievementInfo(int i_serverVersion)
{
	m_pvz1AchievementInfos.clear();
	SAVE_PROFILE();
	ProfileMgr::GetInstance().Save(false, false);
}

void PlayerInfo::ClearRankAvatars()
{
	m_unlockRankAvatarIds.clear();
	SAVE_PROFILE();
	ProfileMgr::GetInstance().Save(false, false);
}

bool PlayerInfo::isFirstDiamondGachaNew(int i_type)
{
	if (i_type == GACHA_NORMAL)
		return m_firstDiamondGachaNormal;
	if (i_type == GACHA_RARE)
		return m_firstDiamondGachaRare;
	if (i_type == GACHA_AVATAR)
		return m_firstDiamondGachaAvatar;
	return true;
}

bool PlayerInfo::IsLevelOfTheDayInfoValid(int activityTypeId)
{
	return isActivityExist(activityTypeId) && m_leveloftheDayInfo[activityTypeId].fromServer;
}

bool PlayerInfo::IsLevelOfTheDayOpening(int activityTypeId)
{
	return isActivityExist(activityTypeId) && m_leveloftheDayInfo[activityTypeId].opening;
}

void PlayerInfo::RemoveAllAdventurePlants(bool i_clearInfo)
{
	m_plantsInAdventure.clear();
	if (i_clearInfo)
		m_plantAdventureInfos.clear();
}

void PlayerInfo::ResetGoldenEggOpenedInfo(bool need_save)
{
	m_goldenEggInfo.openedInfo.clear();
	if (need_save)
		SAVE_PROFILE();
}

void PlayerInfo::SetKilledZombie(const std::string& i_zombieTypeName)
{
	if (m_zombieAlmanac.SetKilledZombie(i_zombieTypeName))
		SAVE_PROFILE();
}

void PlayerInfo::AddGLChances(int i_addition)
{
	CheckGLInfo();
	m_geilivableLotteryInfo.remainChances += i_addition;
	m_geilivableLotteryInfo.totalChances += i_addition;
	SAVE_PROFILE();
}

void PlayerInfo::ClearServerSalesInfo()
{
	m_serverSalesInfo.fromServer = false;
	m_serverSalesInfo.opening = false;
	m_serverSalesInfo.configName = "";
	m_serverSalesInfo.salesList.clear();
	m_serverSalesInfo.priceList.clear();
}

bool PlayerInfo::DoOnlineRefreshEventTime()
{
	ServerTime::Instance()->GetServerTimeFromNet(nullptr, false);
	CheckAndUpdateActivityTopic();
	CheckAndUpdateVaseBreakerActId();
	return true;
}

int32 PlayerInfo::GetFestivalGameLeftCount(FestivalGameMode i_mode)
{
	switch (i_mode)
	{
	case FestivalGameMode_CrazyYeti:
	case FestivalGameMode_WealthGod:
		return m_curOnlineEventInfo.TodayCrazyYetiLeftCount;
	case FestivalGameMode_GargantuarCrisis:
		return m_curOnlineEventInfo.TodayGargantuarCrisisLeftCount;
	case FestivalGameMode_DevilInvade:
		return m_curOnlineEventInfo.ToadyDevilInvadeLeftCount;
	}
	return 0;
}

const std::string* PlayerInfo::GetPurchasedPlantTrialObj()
{
	if (m_purchasedPlantTrial.size() != 0)
		return &m_purchasedPlantTrial[0];
	return nullptr;
}

bool PlayerInfo::IsNeedDelaySave() const
{
	return m_timerDelaySave > 0.0f && m_timerDelaySave < PVZ_T();
}

void PlayerInfo::SetChristmasAccessoryChances(int i_type, int i_chances, bool need_save)
{
	switch (i_type)
	{
	case 1:
		m_christmasAccessoryInfo.freeChances = i_chances;
		break;
	case 2:
		m_christmasAccessoryInfo.coinChances = i_chances;
		break;
	case 3:
		m_christmasAccessoryInfo.gemChances = i_chances;
		break;
	}
	if (need_save)
		SAVE_PROFILE();
}

void PlayerInfo::SetCurrentRiftID(const serializable_time_t i_riftID)
{
	m_riftCurrentID = i_riftID;
	gMessageRouter->Broadcast(Message::RiftIDChanged, i_riftID);
	SAVE_PROFILE();
}

void PlayerInfo::SetGLInfo(GeilivableLotteryInfo i_info)
{
	m_geilivableLotteryInfo.totalChances = i_info.totalChances;
	m_geilivableLotteryInfo.remainChances = i_info.remainChances;
	m_geilivableLotteryInfo.configName = i_info.configName;
}

void PlayerInfo::SetRechargeGems(const GemCurrency i_amount)
{
	m_gems = GetGiveGems() + i_amount;
	resetGemsSign();
	SAVE_PROFILE();
}

void PlayerInfo::SetRedPacket(const RedPacketCurrency i_amount)
{
	m_redPacket = i_amount;
	resetRedPacketsSign();
	SAVE_PROFILE();
	ProfileMgr::GetInstance().Save(false, false);
}

void PlayerInfo::SubPlayYetiLevelCount()
{
	if ((int)m_curOnlineEventInfo.TodayYetiLeftCount > 0)
		m_curOnlineEventInfo.TodayYetiLeftCount -= 1;
	SAVE_PROFILE();
}

void PlayerInfo::AM_SetGems(GemCurrency i_gems)
{
	m_gems = i_gems;
	gMessageRouter->Post(Message::GemCurrencyChanged, m_gems);
	SAVE_PROFILE();
}

bool PlayerInfo::canFreeGacha()
{
	return gLawnApp->IsConnected() && getFreeGachaLeftTime() <= 0;
}

void PlayerInfo::CheckAndUpdateVaseBreakerActId()
{
	if (m_vaseBreakerActId != 10895)
	{
		m_vaseBreakerActId = 10895;
		ClearVaseBreakerData();
		SAVE_PROFILE();
	}
}

void PlayerInfo::ClearChristmasAccessoryInfo()
{
	m_christmasAccessoryInfo.inited = false;
	m_christmasAccessoryInfo.lastRefreshTime = 0;
	m_christmasAccessoryInfo.freeChances = 0;
	m_christmasAccessoryInfo.coinChances = 0;
	m_christmasAccessoryInfo.gemChances = 0;
	m_christmasAccessoryInfo.freeIndex.clear();
	m_christmasAccessoryInfo.coinIndex.clear();
	m_christmasAccessoryInfo.gemIndex.clear();
}

void PlayerInfo::EnableGemReturn()
{
	if (m_iGemReturnDays == 0)
	{
		m_iGemReturnDays = 1;
		SAVE_PROFILE();
		ProfileMgr::GetInstance().Save(false, false);
	}
}

BirthZRecord* PlayerInfo::GetLastBirthZRecord()
{
	if (!m_vBirthZRecord.empty())
		return &m_vBirthZRecord.back();
	return nullptr;
}

void PlayerInfo::RemoveAllPlantAccessoryInfos()
{
	if (!checkAccessoryInfoSign())
		resetAccessoryInfoZeroSign();
	m_plantAccessoryInfos.clear();
	resetAccessoryInfoSign();
	SAVE_PROFILE();
}

void PlayerInfo::SetDangerRoomEventData(StoredDangerRoomEventData& i_data)
{
	m_dangerRoomEventData = i_data;
	ProfileMgr::GetInstance().Save(false, false);
	SAVE_PROFILE();
}

void PlayerInfo::AddPlantAdventureInfo(PlantAdventureInfo i_info)
{
	if (CanStartNewPlantAdventure())
	{
		m_plantAdventureInfos.push_back(i_info);
		SAVE_PROFILE();
	}
}

int PlayerInfo::GetGLRemainChances()
{
	CheckGLInfo();
	if (__builtin_expect("" != m_geilivableLotteryInfo.configName, 1))
		return m_geilivableLotteryInfo.remainChances;
	return 0;
}

int PlayerInfo::GetGLTotalChances()
{
	CheckGLInfo();
	if (__builtin_expect("" != m_geilivableLotteryInfo.configName, 1))
		return m_geilivableLotteryInfo.totalChances;
	return 0;
}

int PlayerInfo::GetRiftZombossAttemptDifficulty(int i_attempt)
{
	if (m_riftZombossAttemptDifficulty.size() > i_attempt)
		return m_riftZombossAttemptDifficulty[i_attempt];
	return 0;
}

bool PlayerInfo::canFreeGachaNew(int i_type)
{
	return gLawnApp->IsConnected() && getFreeGachaLeftTimeNew(i_type) <= 0;
}

void PlayerInfo::ClearAllPurchaseRedeemInfo()
{
	m_bundlePurchaseInfo.clear();
	m_purchasedPlantTrial.clear();
	m_purchasedWorldPack.clear();
	SAVE_PROFILE();
	ProfileMgr::GetInstance().Save(false, false);
}

void PlayerInfo::ClearGoldenEggInfo()
{
	m_goldenEggInfo.inited = false;
	m_goldenEggInfo.ObjectId = 0;
	m_goldenEggInfo.hammers = 0;
	m_goldenEggInfo.hammersLeft = 0;
	m_goldenEggInfo.dailyReward = 0;
	m_goldenEggInfo.dailyChargeAmount = 0;
	m_goldenEggInfo.lastRefreshTime = 0;
	m_goldenEggInfo.dailyHammerAmount = 0;
	m_goldenEggInfo.eggsStat.clear();
	m_goldenEggInfo.openedInfo.clear();
}

void PlayerInfo::DecSpringBossCount()
{
	if ((int)m_curOnlineEventInfo.SpringbossLeftCount > 0)
	{
		m_curOnlineEventInfo.SpringbossLeftCount -= 1;
		SAVE_PROFILE();
	}
}

int PlayerInfo::GetACLogIndex()
{
	if (m_acLogData.logList.size() != 0)
		return m_acLogData.logList[m_acLogData.logList.size() - 1].GetIndex();
	return 0;
}

StoneCurrency PlayerInfo::GetNumStones(bool i_check)
{
	if (i_check && !checkStonesSign())
		resetStonesZeroSign();
	return m_stones;
}

int PlayerInfo::GetPowerupUsesLeft(const std::string& i_powerupName) const
{
	int index = findIndexForName(i_powerupName, m_powerupRecords);
	if (index >= 0)
		return m_powerupRecords[index].Inventory;
	return 0;
}

RedPacketCurrency PlayerInfo::GetRedPacketCount(bool i_check)
{
	if (i_check && !checkRedPacketsSign())
		resetRedPacketsZeroSign();
	return m_redPacket;
}

PurchaseInfo PlayerInfo::GetRestorePurchaseInfo()
{
	if (!checkRestorePurchaseSign())
	{
		resetRestorePurchaseZeroSign();
		SAVE_PROFILE();
	}
	return m_restorePurchaseInfo;
}

bool PlayerInfo::HasReceivedFirstClearReward(int i_nodeIndex, int i_difficulty)
{
	i_nodeIndex--;
	uint64 progress = 0;
	if (i_difficulty == 0)
		progress = m_riftProgressBitfieldDifficulty0;
	else if (i_difficulty == 1)
		progress = m_riftProgressBitfieldDifficulty1;
	else if (i_difficulty == 2)
		progress = m_riftProgressBitfieldDifficulty2;
	else
		return false;
	int64_t bit = 1 << i_nodeIndex;
	return (progress & bit) != 0;
}

void PlayerInfo::RemoveLastBossFightLevel()
{
	if (m_bossFightLevels.HasItem(m_lastBossLevel))
	{
		m_bossFightLevels.RemoveItem(m_lastBossLevel);
		m_lastBossLevel = -1;
	}
	SAVE_PROFILE();
}

void PlayerInfo::AddWorldKeys(const int i_amount)
{
	if (!checkWorldKeysSign())
		resetWorldKeysZeroSign();
	m_worldkeys += i_amount;
	resetWorldKeysSign();
	SAVE_PROFILE();
}

void PlayerInfo::ResetRebateData()
{
	m_iRebateCharge = 0;
	m_vRebateRewardState[0] = 0;
	m_vRebateRewardState[1] = 0;
	m_vRebateRewardState[2] = 0;
}

void PlayerInfo::SetCardGameLevelComplete(int i_nodeIndex, bool i_hard)
{
	if (i_nodeIndex > 0)
	{
		if (i_hard)
			m_CardGameProgressBitfieldDifficulty1 |= 1 << (i_nodeIndex - 1);
		else
			m_CardGameProgressBitfieldDifficulty0 |= 1 << (i_nodeIndex - 1);
		SAVE_PROFILE();
	}
}

void PlayerInfo::SetDangerRoomSpecialOfferSaveData(DangerRoomSpecialOfferSaveData data, bool save)
{
	m_dangerRoomSpecialOfferSaveData = data;
	if (save)
	{
		SAVE_PROFILE();
		ProfileMgr::GetInstance().Save(false, false);
	}
}

void PlayerInfo::SetPVZ1LevelComplete(int i_nodeIndex, bool i_hard)
{
	if (i_nodeIndex > 0)
	{
		if (i_hard)
			m_pvz1ProgressBitfieldDifficulty1 |= 1 << (i_nodeIndex - 1);
		else
			m_pvz1ProgressBitfieldDifficulty0 |= 1 << (i_nodeIndex - 1);
		SAVE_PROFILE();
	}
}

void PlayerInfo::SetUnchartedLevelComplete(int i_nodeIndex, bool i_hard)
{
	if (i_nodeIndex > 0)
	{
		if (i_hard)
			m_UnchartedProgressBitfieldDifficulty1 |= 1 << (i_nodeIndex - 1);
		else
			m_UnchartedProgressBitfieldDifficulty0 |= 1 << (i_nodeIndex - 1);
		SAVE_PROFILE();
	}
}

void PlayerInfo::SetRestorePurchaseInfo(PurchaseInfo& i_purchaseInfo)
{
	if (!checkRestorePurchaseSign())
		resetRestorePurchaseZeroSign();
	m_restorePurchaseInfo = i_purchaseInfo;
	resetRestorePurchaseSign();
	SAVE_PROFILE();
}

void PlayerInfo::SetRichmanTileBattleSaveData(RichmanBattleEventSaveData data, bool save)
{
	m_richmanBattleEventData = data;
	if (save)
	{
		SAVE_PROFILE();
		ProfileMgr::GetInstance().Save(false, false);
	}
}

bool PlayerInfo::UpdateAdvertisementWatchCountInfo(AdvertisementTimeType type, int count, bool save)
{
	bool updated = false;
	if (type == ADS_TIME_ENDLEVEL)
	{
		m_advertisementWatchCountInfo.EndlessCount = count;
		updated = true;
	}
	if (save)
	{
		SAVE_PROFILE();
		ProfileMgr::GetInstance().Save(false, false);
	}
	return updated;
}

void PlayerInfo::UpdateDeltaDataOfflineSaveTime()
{
	time_t now = gLawnApp->GetRealServerTime();
	if (now <= 0)
		now = time(nullptr);
	m_deltaDataOfflineSaveTime = now;
}

void PlayerInfo::ClearPlantAccessoryInfos(int id)
{
	if (!checkAccessoryInfoSign())
		resetAccessoryInfoZeroSign();
	m_plantAccessoryInfos[id].PlantID = -1;
	resetAccessoryInfoSign();
	SAVE_PROFILE();
}

bool PlayerInfo::GetDeltaDataForServer(std::string& i_json, std::string& i_md5, std::string& i_summary)
{
	i_json = m_deltaDataJsonString;
	i_md5 = m_deltaDataOffline_sign;
	i_summary = m_deltaInfoOfflineSummaryString;
	return true;
}

int PlayerInfo::GetTwDailySignDay(std::string itemVersion)
{
	if (!(m_twDailySignVersion == itemVersion))
	{
		m_twLoginDays = 0;
		m_twDailySignVersion = itemVersion;
	}
	return m_twLoginDays;
}

bool PlayerInfo::HasGotTodayOppoNewerDailyReward()
{
	time_t now = gLawnApp->GetRealBeijingTime();
	if (now == 0)
		return true;
	return (int)(difftime(now, m_oppoDailyLoginGotTime) * (1.0 / 86400)) <= 0;
}

void PlayerInfo::SetStarCompleted(const std::string& i_eventDataName, bool i_hard)
{
	int completed = GetStarCompleted(i_eventDataName);
	int stars = i_hard ? 3 : 1;
	if (stars > completed)
		AddStars(stars - completed, 0);
}

void PlayerInfo::AddKillZombiesNum(const int i_amount)
{
	int killZombiesNum = m_killZombiesNum + i_amount;
	if (i_amount > 0)
	{
		if (m_killZombiesNum > killZombiesNum)
		{
			killZombiesNum = std::numeric_limits<int>::max();
			m_killZombiesNum = killZombiesNum;
		}
		else
			m_killZombiesNum = killZombiesNum;
	}
	else
		m_killZombiesNum = killZombiesNum;
	SAVE_PROFILE();
}

void PlayerInfo::ClearAboutRiddlesData()
{
	m_riddlesHasAnswered.clear();
	m_riddlesGotToday.clear();
	m_riddlesAnsweredToday = 0;
	m_riddlesCorrectNum = 0;
	m_riddlesAnsweredDays = 0;
	m_riddlesPrizeGotIndex = 0;
	m_riddlesCorrectTotal = 0;
	m_lastRiddleTimeStamp = 0;
	m_redPackRank = 0;
	m_redPackOpenTotal = 0;
	m_bRedPackRewardRankGet = false;
	m_redPacket = 0;
}

void PlayerInfo::ClearRestorePurchaseInfo()
{
	m_restorePurchaseInfo.receipt = "";
	m_restorePurchaseInfo.receiptId = "";
	m_restorePurchaseInfo.productId = "";
	m_restorePurchaseInfo.objectId = 0;
	resetRestorePurchaseSign();
	SAVE_PROFILE();
}

bool PlayerInfo::IsSalesOpening()
{
	if (m_serverSalesInfo.fromServer && m_serverSalesInfo.opening && HasUsedServerSalesConfig() && m_currentSalesInfo.opening && HasValidSales())
		return true;
	return false;
}

bool PlayerInfo::OverCurrentSalesRefreshTime()
{
	time_t now = gLawnApp->GetRealBeijingTime();
	if (now <= 0)
		return true;
	return now >= GetCurrentSalesRefreshTime();
}

void PlayerInfo::resetChallengeCount()
{
	for (size_t i = 0; i < m_challengeCount.size() + 1; i++)
		m_challengeCount[i] = 0;
}

void PlayerInfo::ResetPlantBundleBuyTime(int i_left)
{
	SetPlantBundleBuyTime(gLawnApp->GetRealBeijingTime());
	SetPlantBundleLeftBuy(i_left);
	SAVE_PROFILE();
}

void PlayerInfo::SetCoins(const CoinCurrency i_amount)
{
	m_coins = i_amount;
	resetCoinsSign();
	SAVE_PROFILE();
	if (i_amount > 500)
		ProfileMgr::GetInstance().Save(false, false);
}

void PlayerInfo::ClearAllDaveTaskInfo(int configVersion)
{
	if (m_currentDaveTreasureVersion != configVersion)
	{
		m_daveTaskInfos.clear();
		m_currentDaveTreasureVersion = configVersion;
		SAVE_PROFILE();
		ProfileMgr::GetInstance().Save(false, false);
	}
}

void PlayerInfo::ClearAllPennyTaskInfo(int configVersion)
{
	if (m_currentPennyGuideVersion != configVersion)
	{
		m_pennyTaskInfos.clear();
		m_currentPennyGuideVersion = configVersion;
		SAVE_PROFILE();
		ProfileMgr::GetInstance().Save(false, false);
	}
}

void PlayerInfo::ClearGLInfo(bool init)
{
	m_geilivableLotteryInfo.totalChances = 0;
	m_geilivableLotteryInfo.remainChances = 0;
	m_geilivableLotteryInfo.configName = "";
	if (!init)
		SAVE_PROFILE();
}

void PlayerInfo::ClearPlantStarLevel()
{
	for (size_t i = 0; i < m_plantStarLevelArray.size() + 1; i++)
		m_plantStarLevelArray[i].iCurrentLevel = 1;
}

void PlayerInfo::AM_SetCoins(CoinCurrency i_coins)
{
	int delta = i_coins - m_coins;
	m_coins = i_coins;
	gMessageRouter->Post(Message::CoinCurrencyChanged, delta);
	SAVE_PROFILE();
}

void PlayerInfo::ClearCurrentSalesInfo(bool i_init)
{
	m_currentSalesInfo.newArrival = false;
	m_currentSalesInfo.opening = false;
	m_currentSalesInfo.ObjectId = -1;
	m_currentSalesInfo.refreshTimes = 0;
	m_currentSalesInfo.configName = "";
	m_currentSalesInfo.priceList.clear();
	if (!i_init)
		SAVE_PROFILE();
}

int PlayerInfo::GetGoldenEggsStatByIndex(int i_index)
{
	int stat = 0;
	if (m_goldenEggInfo.eggsStat.size() == 0 || m_goldenEggInfo.eggsStat.size() < i_index)
		return stat;
	stat = m_goldenEggInfo.eggsStat[i_index];
	return stat;
}

int PlayerInfo::GetLevelOfTheDayRemainDays(int activityTypeId)
{
	if (IsLevelOfTheDayInfoValid(activityTypeId) && IsLevelOfTheDayOpening(activityTypeId))
		return m_leveloftheDayInfo[activityTypeId].activeStates.remainDays;
	return 0;
}

void PlayerInfo::SetBundleInPurchase(const PurchasedBundleInfo& bundle)
{
	OutputDebugStrF("PlayerInfo::SetBundleInPurchase, sku : %s, index : %d", bundle.sku.c_str(), bundle.index);
	m_bundlePurchaseInfo.push_back(bundle);
	SAVE_PROFILE();
	ProfileMgr::GetInstance().Save(false, false);
}

void PlayerInfo::updateGemsLotteryInfo()
{
	time_t lastTime = GetLastConsumGemsTime();
	time_t now = ServerTime::Instance()->GetServerTime();
	if (!gLawnApp->isSameDay(lastTime, now))
		ResetLotteryConsumptionGems(false);
	m_lastConsumGemsTime = now;
}

void PlayerInfo::ResetBossFightLevels()
{
	int count = gLawnApp->GetActivityConfig()->GetBossFightConfigLevelsCount();
	for (int i = 0; i < count; i++)
		m_bossFightLevels.AddItem(i, 1);
}

void PlayerInfo::SetLeafs(const LeafCurrency i_amount)
{
	if (!checkLeafsSign())
		resetStonesZeroSign();
	m_leafs = i_amount;
	resetLeafsSign();
	gMessageRouter->Post(Message::LeafCurrencyChanged, m_leafs);
}

void PlayerInfo::SubtractStars(const StarCurrency i_amount, int i_worldId)
{
	int stars = m_stars;
	m_stars -= (stars <= i_amount) ? stars : i_amount;
	gMessageRouter->Post(Message::StarCurrencyChanged, m_stars);
	SAVE_PROFILE();
}

std::string PlayerInfo::TimeToString(time_t iTimeStamp)
{
	struct tm* time = gLawnApp->BeijingTime(&iTimeStamp);
	return Sexy::StrFormat("%04d%02d%02d", time->tm_year + 1900, time->tm_mon + 1, time->tm_mday);
}

void PlayerInfo::UpdateArcadeLastPlayForMode(const std::string& i_modeID, const std::string& i_levelID, const LastPlayStatus i_status, int i_waveIndex)
{
	ArcadeLastPlayData* data = LocalProfileSaveData::GetOrCreateArcadeLastPlayData(this, i_modeID);
	if (data)
	{
		data->LevelID = i_levelID;
		data->Status = i_status;
		data->LastPlayTime = gLawnApp->GetRealBeijingTime();
		data->LastPlayWave = i_waveIndex;
	}
}

void PlayerInfo::UpdateLawnKeyField()
{
	if (!m_hasUseAug05LawnKeyField)
	{
		m_hasUseAug05LawnKeyField = true;
		m_curOnlineEventInfo.TodayMiniGameLeftCount.updateToAug05LawnKey();
		m_curOnlineEventInfo.TodayYetiLeftCount.updateToAug05LawnKey();
		m_coins.updateToAug05LawnKey();
		m_gems.updateToAug05LawnKey();
		m_stars.updateToAug05LawnKey();
		SAVE_PROFILE();
	}
}

GemCurrency PlayerInfo::GetNumGems(bool i_check)
{
	if (i_check)
	{
		if (!checkGemsSign())
		{
			resetGemsZeroSign();
			gMessageRouter->Post(Message::GemCurrencyChanged, m_gems);
		}
	}
	return m_gems;
}

void PlayerInfo::SetHasGotRewardList(int i_id, int i_value)
{
	if (m_hasGotRewardList.size() <= i_id)
		m_hasGotRewardList.push_back(i_value);
	m_hasGotRewardList[i_id] = i_value;
}

void PlayerInfo::UpdateUUIDAndOSVerson()
{
	m_sign_uuid = gSexyAppBase->mDiagDriver->GetInfoString(IDiagDriver::INFO_DeviceID);
	m_save_sign_uuid = m_sign_uuid;
	SAVE_PROFILE();
}

bool PlayerInfo::Serialize(const RtSerializeContext& inContext)
{
	bool result = RtObject::Serialize(inContext);
	if (result && inContext.GetSync()->IsReading())
		m_zombieAlmanac.AssignKilledZombiesCollection(m_killedZombies);
	return result;
}

void PlayerInfo::SetMaterialNum(int i_id, int i_num)
{
	int diff = i_num - GetMaterialNum(i_id);
	if (!LazySingleton<GeneralTaskStateManager>::GetInstancePtr()->GetTaskLockState())
		gMessageRouter->Post(Message::BeforeChangeMaterialNumber, i_id, diff);

	bool found = false;
	{
		std::vector<MaterialInfo>::iterator it = m_materialList.begin();
		std::vector<MaterialInfo>::iterator end = m_materialList.end();
		for (; it != end; ++it)
		{
			if (i_id == it->id)
			{
				if (i_num != it->count)
					it->count = i_num;
				found = true;
				break;
			}
		}
	}
	if (!found)
	{
		MaterialInfo info;
		info.id = i_id;
		info.count = i_num;
		m_materialList.push_back(info);
	}

	if (gLawnApp->CheckProfileOpen())
	{
		S2C_ACLog log;
		log.SetMaterial(i_id, diff);
		gMessageRouter->Post(Message::RequestACLog, log);
	}
}

BirthZRecord* PlayerInfo::GetBirthZRecord(time_t iStamp)
{
	std::string day = TimeToString(iStamp);
	std::vector<BirthZRecord>::iterator it = std::find(m_vBirthZRecord.begin(), m_vBirthZRecord.end(), day);
	if (it != m_vBirthZRecord.end())
		return &*it;
	return NULL;
}

int PlayerInfo::SubtractWorldKeys(const int i_amount)
{
	if (!checkWorldKeysSign())
		resetWorldKeysZeroSign();
	if (i_amount <= 0)
		return -1;
	m_worldkeys -= i_amount;
	resetWorldKeysSign();
	SAVE_PROFILE();
	return i_amount;
}

void PlayerInfo::SetLimitGachaDrawTimes(int type, int times)
{
	if (type == 1)
		m_limitGachaDrawTimesOne = times;
	else if (type == 10)
		m_limitGachaDrawTimesTen = times;
	SAVE_PROFILE();
	ProfileMgr::GetInstance().Save(false, false);
}

bool PlayerInfo::GetIsPlantUnlocked(const std::string& i_plantTypeName)
{
	return m_unlockedPlants.end() != getIterForName(i_plantTypeName);
}

bool PlayerInfo::GetIsPlantAwaken(const std::string& i_plantTypeName)
{
	return m_plantAwakenInfo.end() != getIterForName(i_plantTypeName);
}

uint32 PlayerInfo::getTotalUnlockedPlantSize()
{
	return GetUnlockedPlantList().size();
}

void PlayerInfo::ResetRechargeDoubleData()
{
	if (m_GetRechargeDoubleList.empty())
		return;
	m_GetRechargeDoubleList.clear();
	SAVE_PROFILE();
	ProfileMgr::GetInstance().Save(false, false);
}

void PlayerInfo::RemoveAllAdventure(bool i_clearInfo, bool i_clearPlants, bool i_clearStates)
{
	if (i_clearInfo)
		m_plantAdventureInfos.clear();
	if (i_clearPlants)
		m_plantsInAdventure.clear();
	if (i_clearStates)
		m_plantAdventureStates.clear();
}

bool PlayerInfo::IsToday(time_t i_time)
{
	int now = gLawnApp->GetRealServerTime();
	return (now - 57600) / 86400 == ((int)i_time - 57600) / 86400;
}

bool PlayerInfo::IsInThisWeek(time_t i_time)
{
	int now = gLawnApp->GetRealServerTime();
	return (now - 316800) / 604800 == ((int)i_time - 316800) / 604800;
}

bool PlayerInfo::HasTargetWorldPlayedAnim(const std::string& i_world)
{
	for (size_t i = 0; i != m_worldAnimPlayed.size(); i++)
	{
		if (i_world == m_worldAnimPlayed[i])
			return true;
	}
	return false;
}

bool accessoryLesser(PlantAccessoryInfo i_a, PlantAccessoryInfo i_b);

void PlayerInfo::SortPlantAccessoryInfos()
{
	if (!checkAccessoryInfoSign())
		resetAccessoryInfoZeroSign();
	std::sort(m_plantAccessoryInfos.begin(), m_plantAccessoryInfos.end(), accessoryLesser);
	resetAccessoryInfoSign();
	SAVE_PROFILE();
}

const int PlayerInfo::GetRandomBossLevelIndex()
{
	if (m_lastBossLevel != -1)
		return m_lastBossLevel;
	if (m_bossFightLevels.GetSize() == 0)
		ResetBossFightLevels();
	m_lastBossLevel = m_bossFightLevels.PickItem();
	SAVE_PROFILE();
	return m_lastBossLevel;
}

void PlayerInfo::SetDailySignRewardSheet(int32 itemId, int32 amount)
{
	SignRewardContent content;
	content.itemId = itemId;
	content.amount = amount;
	m_dailySignRewardSheet.push_back(content);
}

void PlayerInfo::SetRiftLevelComplete(int i_nodeIndex, int i_difficulty)
{
	if (i_nodeIndex <= 0)
		return;
	i_nodeIndex--;
	if (i_difficulty == 0)
		m_riftProgressBitfieldDifficulty0 |= 1 << i_nodeIndex;
	else if (i_difficulty == 1)
		m_riftProgressBitfieldDifficulty1 |= 1 << i_nodeIndex;
	else if (i_difficulty == 2)
		m_riftProgressBitfieldDifficulty2 |= 1 << i_nodeIndex;
	else
		return;
	SAVE_PROFILE();
}

void PlayerInfo::SetCurrentLevel(const std::string& i_levelName)
{
	m_level = i_levelName;
	if (gLawnApp->GetLevelDaysByLevelString(m_level) > gLawnApp->GetLevelDaysByLevelString(m_deltaInfoSummaryLevelString))
		m_deltaInfoSummaryLevelString = m_level;
	SAVE_PROFILE();
}

int PlayerInfo::GetCurrentSalesPricesCount()
{
	int count = 0;
	if (IsServerSalesConfigValid())
		count = m_currentSalesInfo.priceList.size();
	return std::max(0, count);
}

void PlayerInfo::SyncOfflineDataFromOnlineData()
{
	m_deltaInfoOfflineSummary.days = m_deltaInfoOnlineSummary.days;
	m_deltaInfoOfflineSummary.coins = m_deltaInfoOnlineSummary.coins;
	m_deltaInfoOfflineSummary.gems = m_deltaInfoOnlineSummary.gems;
	m_deltaInfoOfflineSummary.egystars = m_deltaInfoOnlineSummary.egystars;
	m_deltaInfoOfflineSummary.piratestars = m_deltaInfoOnlineSummary.piratestars;
	m_deltaInfoOfflineSummary.cowstars = m_deltaInfoOnlineSummary.cowstars;
	m_deltaInfoOfflineSummary.kongfustars = m_deltaInfoOnlineSummary.kongfustars;
	m_deltaInfoOfflineSummary.level = m_deltaInfoOnlineSummary.level;
	m_deltaInfoOfflineSummary.unlockedplantsize = m_deltaInfoOnlineSummary.unlockedplantsize;
	m_deltaInfoOfflineSummary.unlockedavatarsize = m_deltaInfoOnlineSummary.unlockedavatarsize;
	m_deltaInfoOfflineSummary.totalplantlevel = m_deltaInfoOnlineSummary.totalplantlevel;
}

bool PlayerInfo::IsDaveTaskSaveInfoExist(int i_id)
{
	for (size_t i = 0; i != m_daveTaskInfos.size(); i++)
	{
		if (m_daveTaskInfos[i].ID == i_id)
			return true;
	}
	return false;
}

bool PlayerInfo::IsPennyTaskSaveInfoExist(int i_id)
{
	for (size_t i = 0; i != m_pennyTaskInfos.size(); i++)
	{
		if (m_pennyTaskInfos[i].ID == i_id)
			return true;
	}
	return false;
}

bool PlayerInfo::IsTravelLogSaveInfoExist(int i_id)
{
	for (size_t i = 0; i != m_travelLogTaskInfos.size(); i++)
	{
		if (m_travelLogTaskInfos[i].ID == i_id)
			return true;
	}
	return false;
}

bool PlayerInfo::IsPvZ1AchievementExist(int i_id)
{
	for (size_t i = 0; i != m_pvz1AchievementInfos.size(); i++)
	{
		if (m_pvz1AchievementInfos[i].ID == i_id)
			return true;
	}
	return false;
}

bool PlayerInfo::IsUnlockRechargeNode(RechargeNode i_node)
{
	for (size_t i = 0; i != m_unlockedRechargeNodes.size(); i++)
	{
		if (m_unlockedRechargeNodes[i] == i_node)
			return true;
	}
	return false;
}

bool PlayerInfo::IsArtifactUnlocked(int i_artifactID)
{
	for (size_t i = 0; i != m_artifactListArray.size(); i++)
	{
		if (m_artifactListArray[i].ArtifactID == i_artifactID)
			return true;
	}
	return false;
}

int PlayerInfo::GetGeneEssence(int i_geneEssenceId)
{
	for (size_t i = 0; i != m_plantGeneEssenceList.size(); i++)
	{
		if (m_plantGeneEssenceList[i].GeneEssenceID == i_geneEssenceId)
			return m_plantGeneEssenceList[i].Number;
	}
	return 0;
}

int PlayerInfo::GetNewAvatarPiecesCount(int i_newPiecesID)
{
	for (size_t i = 0; i != m_listPlantNewAvatarPiecesInfo.size(); i++)
	{
		if (m_listPlantNewAvatarPiecesInfo[i].iPlantNewPiecesID == i_newPiecesID)
			return m_listPlantNewAvatarPiecesInfo[i].iPiecesCount;
	}
	return 0;
}

int32 PlayerInfo::GetPlantSuperAccessoryLevel(int64 accessoryId)
{
	for (size_t i = 0; i != m_plantAccessoryInfos.size(); i++)
	{
		if (m_plantAccessoryInfos[i].AccessoryId == accessoryId)
			return m_plantAccessoryInfos[i].Level;
	}
	return 0;
}

bool PlayerInfo::isPlantStarRewards(int plantId)
{
	for (size_t i = 0; i != m_plantStarRewardsRecord.size(); i++)
	{
		if (m_plantStarRewardsRecord[i] == plantId)
			return true;
	}
	return false;
}

void PlayerInfo::RecordGroupBuy(int i_index)
{
	m_groupBuyRecord.push_back(SynInfo{ gLawnApp->GetRealServerTime(), i_index });
	SAVE_PROFILE();
}

void PlayerInfo::SetRiddlesGotToday(const std::vector<int>& i_riddles)
{
	m_riddlesGotToday.clear();
	for (uint32 i = 0; i < i_riddles.size(); i++)
		m_riddlesGotToday.push_back(i_riddles[i]);
	SAVE_PROFILE();
}

void PlayerInfo::SetupPowerupUses(const std::string& i_powerupName, int i_num)
{
	int index = findIndexForName(i_powerupName, m_powerupRecords);
	if (index >= 0)
	{
		PowerupRecord& record = m_powerupRecords[index];
		int oldNum = record.Inventory;
		record.Inventory = i_num;
		if (record.Inventory < 0)
			record.Inventory = 0;
		if (oldNum != record.Inventory)
			gMessageRouter->Broadcast(Message::NotifyPowerupUsesChanged, &record);
	}
	SAVE_PROFILE();
}

void PlayerInfo::ClearWorldMapEventStatus(const std::string& i_savedDataString)
{
	const MapEventItem* event = WorldMapUtils::GetWorldDataForEdit()->FindEventByDataName(i_savedDataString);
	if (event)
	{
		bool cleared = ClearMapEventStatusByIds(event->GetWorldDataPtr()->m_worldId, event->GetEventId());
		if (cleared)
			SAVE_PROFILE();
	}
}

void PlayerInfo::AM_SetName(const std::wstring i_name)
{
	ProfileMgr::GetInstance().RenameProfile(GetName(), i_name);
}

bool PlayerInfo::HasCollection(int i_collectionID)
{
	for (size_t i = 0; i != m_listCollectionInfo.size(); i++)
	{
		if (m_listCollectionInfo[i].CollectionID == i_collectionID && m_listCollectionInfo[i].Rare > 0)
			return true;
	}
	return false;
}

void PlayerInfo::SetCollectionRare(int i_collectionID, int rare)
{
	for (size_t i = 0; i != m_listCollectionInfo.size(); i++)
	{
		if (m_listCollectionInfo[i].CollectionID == i_collectionID)
		{
			m_listCollectionInfo[i].Rare = rare;
			return;
		}
	}
}

void PlayerInfo::SetCollectionState(int i_collectionID, bool i_equip)
{
	for (size_t i = 0; i != m_listCollectionInfo.size(); i++)
	{
		if (m_listCollectionInfo[i].CollectionID == i_collectionID)
		{
			m_listCollectionInfo[i].State = i_equip;
			return;
		}
	}
}

int PlayerInfo::GetZombieStarLevel(const std::string& i_zombie)
{
	int zombieId = m_zombieAlmanac.GetIdForName(i_zombie);
	for (size_t i = 0; i != m_zombieStarLevelArray.size(); i++)
	{
		if (zombieId == m_zombieStarLevelArray[i].iZombieId)
			return m_zombieStarLevelArray[i].iCurrentLevel;
	}
	return -1;
}

void PlayerInfo::ModifyPowerupUses(const std::string& i_powerupName, int i_diff)
{
	int index = findIndexForName(i_powerupName, m_powerupRecords);
	if (index >= 0)
	{
		PowerupRecord& record = m_powerupRecords[index];
		int oldNum = record.Inventory;
		int newNum = oldNum + i_diff;
		record.Inventory = newNum;
		if (newNum < 0)
		{
			record.Inventory = 0;
			newNum = 0;
		}
		if (oldNum != newNum)
			gMessageRouter->Broadcast(Message::NotifyPowerupUsesChanged, &record);
	}
	SAVE_PROFILE();
}

int PlayerInfo::SubtractStones(const StoneCurrency i_amount)
{
	if (!checkStonesSign())
		resetStonesZeroSign();
	if (i_amount <= 0)
		return -1;
	int stones = m_stones;
	m_stones -= (stones <= i_amount) ? stones : i_amount;
	resetStonesSign();
	SAVE_PROFILE();
	return i_amount;
}

void PlayerInfo::AddFestivalGameLeftCount(FestivalGameMode i_mode, int i_count)
{
	switch (i_mode)
	{
	case FestivalGameMode_GargantuarCrisis:
		m_curOnlineEventInfo.TodayGargantuarCrisisLeftCount += i_count;
		break;
	case FestivalGameMode_DevilInvade:
		m_curOnlineEventInfo.ToadyDevilInvadeLeftCount += i_count;
		break;
	case FestivalGameMode_CrazyYeti:
	case FestivalGameMode_WealthGod:
		m_curOnlineEventInfo.TodayCrazyYetiLeftCount += i_count;
		break;
	}
	SAVE_PROFILE();
}

bool PlayerInfo::SubGLChances()
{
	CheckGLInfo();
	bool result = "" != m_geilivableLotteryInfo.configName;
	if (result)
	{
		result = m_geilivableLotteryInfo.remainChances > 0;
		if (result)
		{
			m_geilivableLotteryInfo.remainChances -= 1;
			SAVE_PROFILE();
			ProfileMgr::GetInstance().Save(false, false);
		}
	}
	return result;
}

void PlayerInfo::setPlantStarRewards(int plantId)
{
	for (size_t i = 0; i != m_plantStarRewardsRecord.size(); i++)
	{
		if (m_plantStarRewardsRecord[i] == plantId)
			return;
	}
	m_plantStarRewardsRecord.push_back(plantId);
}

void PlayerInfo::SetPlantSuperAccessoryLevel(int64 accessoryId, int level)
{
	for (size_t i = 0; i != m_plantAccessoryInfos.size(); i++)
	{
		if (m_plantAccessoryInfos[i].AccessoryId == accessoryId)
			m_plantAccessoryInfos[i].Level = level;
	}
	SAVE_PROFILE();
}

bool PlayerInfo::getIsExperiencePlantById(int plantID)
{
	return std::find(m_vecExperiencePlants.begin(), m_vecExperiencePlants.end(), plantID) != m_vecExperiencePlants.end();
}

bool PlayerInfo::HasObtainedNewTotalRechargeReward(int i_node)
{
	return std::find(m_newTotalRechargeRewardStatus.begin(), m_newTotalRechargeRewardStatus.end(), i_node) != m_newTotalRechargeRewardStatus.end();
}

void PlayerInfo::SetCrashContext()
{
	CrashTracking::SetInt("MapConversionState", m_mapConversionState);
}

bool PlayerInfo::isActivityExist(int activityType) const
{
	bool exists = false;
	if (activityType != 0)
		exists = m_leveloftheDayInfo.find(activityType) != m_leveloftheDayInfo.end();
	return exists;
}

void PlayerInfo::ClearLevelOfTheDayInfoByType(int activityTypeId)
{
	if (!isActivityExist(activityTypeId))
		return;
	ServerLevelOfTheDayInfo info;
	m_leveloftheDayInfo[activityTypeId] = info;
}

void PlayerInfo::SAVE_PROFILE()
{
	if (!AuthMgr::GetInstance().HasNoAuth() && NeedSave() && (m_timerDelaySave < 0.0f || m_timerDelaySave < PVZ_T()))
	{
		m_timerDelaySave = -1.0f;
		UpdateDeltaDataOfflineSaveTime();
		ProfileMgr::GetInstance().RequestSave();
	}
}

BirthZRecord* PlayerInfo::GetBirthZRecord(int iIndex)
{
	if (iIndex < m_vBirthZRecord.size())
		return &m_vBirthZRecord[iIndex];
	return NULL;
}

bool PlayerInfo::GameFeatureIsUnlocked(GameFeature i_feature)
{
	return std::find(m_unlockedGameFeatures.begin(), m_unlockedGameFeatures.end(), i_feature) != m_unlockedGameFeatures.end();
}

time_t PlayerInfo::GetTimeStamp(const std::string& strDate, const std::string& strDateFormat)
{
	struct tm tmDate = {};
	strptime(strDate.c_str(), strDateFormat.c_str(), &tmDate);
	return GetTimegm(&tmDate);
}

bool PlayerInfo::HasAccessoryPiece(const std::string& i_type)
{
	if (!checkAccessoryPieceSign())
		resetAccessoryPieceZeroSign();
	for (size_t i = 0; i != m_accessoryPieces.size(); i++)
	{
		if (i_type == m_accessoryPieces[i].Type)
			return true;
	}
	return false;
}

int PlayerInfo::GetEquipAvatarID(const std::string& i_plantTypeName)
{
	int plantId = PlantNameMapperServerID::GetInstance().GetIdForName(i_plantTypeName);
	for (size_t i = 0; i != m_listPlantAvatarEquipInfo.size(); i++)
	{
		if (plantId == m_listPlantAvatarEquipInfo[i].iPlantID)
			return m_listPlantAvatarEquipInfo[i].iAvatarID;
	}
	return -1;
}

bool PlayerInfo::IsPlantOnlyNameExist(const std::string& strPlantName)
{
	return std::find(m_vPlantTrialRecord.begin(), m_vPlantTrialRecord.end(), strPlantName) != m_vPlantTrialRecord.end();
}

bool PlayerInfo::IsPlantTrialObjExist(const std::string& strPlantName)
{
	return std::find(m_vPlantTrialCD.begin(), m_vPlantTrialCD.end(), strPlantName) != m_vPlantTrialCD.end();
}

bool PlayerInfo::isUnlockHeadshotId(int headshotId)
{
	return std::find(m_unlockHeadShotIds.begin(), m_unlockHeadShotIds.end(), headshotId) != m_unlockHeadShotIds.end();
}

bool PlayerInfo::IsUnlockRankAvatar(int i_id)
{
	return std::find(m_unlockRankAvatarIds.begin(), m_unlockRankAvatarIds.end(), i_id) != m_unlockRankAvatarIds.end();
}

int PlayerInfo::GetLevelPlayCount(const std::string& i_levelName)
{
	std::string levelName = Sexy::StringToLower(i_levelName);
	int index = findIndexForName(levelName, m_worldMapEventList);
	if (index >= 0)
		return m_worldMapEventList[index].PlayCount;
	return 0;
}
