//
//  ActivityManager.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ActivityManager.h"
#include "TimeMgr.h"
#include "LawnApp.h"
#include "ProfileMgr.h"
#include "ProfileUtils.h"
#include "MapEventItem.h"
#include "PlayerInfo.h"
#include "WorldMapActivityHome.h"
#include "SexyAppFramework/RtSerial.h"
#include "GameCommon.h"
#include "gameNetWork/NetworkData.h"
#include "gameNetWork/NetworkMgr.h"
#include "gameNetWork/NetworkMsgProcess.h"
#include "gameNetWork/ServerTime.h"
#include "TimeUtil.h"
#include "UIWishingPool.h"
#include "UIMiniGameRank.h"
#include "FestivalEventUI.h"
#include "UIDoubleFestivalActivity.h"
#include "UISpringFestivalActivity.h"
#include "FirstRechargeExtra.h"
#include "PennyClassroom.h"
#include "MysteryCrystal.h"
#include "GeneralTaskMgr.h"
#include "DaveTaskMgr.h"
#include "UIDaveTreasure.h"
#include "RechargeDailySignActivity.h"
#include "DiscountShopActivity.h"
#include "PVZ2UnchartedModeNetworkMgr.h"
#include "CardGameNetworkMgr.h"

class ActivityTurnChangeConfig : public Sexy::RtObject {
public:
	ActivityTurnChangeConfig();
	~ActivityTurnChangeConfig();
	std::vector<int> m_vecOriginalAcOrList;
	float m_fSpaseTimeConfig;
};

class WorldMapActivityBtnTurnChangeManager
		: public Sexy::LazySingleton<WorldMapActivityBtnTurnChangeManager> {
public:
	void update();
	void loadData(const ActivityTurnChangeConfig& activityTurnChangeConfig);
	void setIsInit(bool isInit);
	bool getIsInit() const { return m_bIsInit; }
private:
	char m_unknown008[0x59];
	bool m_bIsInit;
};

class FutureGiftBoxData : public INetworkData {
public:
	FutureGiftBoxData();
	~FutureGiftBoxData();
	int m_unknown014_00;
	int m_unknown014_01;
	int m_unknown014_02;
	std::vector<int> m_vecGifts;
	std::vector<int> m_vecShops;
};

class PennyGiftBoxData : public INetworkData {
public:
	PennyGiftBoxData();
	~PennyGiftBoxData();
	std::vector<int> m_vec018;
	std::vector<int> m_vec030;
	std::vector<int> m_vec048;
	std::vector<int> m_vec060;
	std::vector<int> m_vec078;
	std::vector<int> m_vec090;
	int m_unknown0A8_00;
	int m_unknown0A8_01;
	int m_unknown0A8_02;
	int m_unknown0A8_03;
	int m_unknown0A8_04;
	int m_unknown0A8_05;
	int m_unknown0A8_06;
	int m_unknown0A8_07;
	int m_unknown0A8_08;
	int m_unknown0A8_09;
	int m_unknown0A8_10;
	int m_unknown0A8_11;
	int m_unknown0A8_12;
	int m_unknown0A8_13;
	std::vector<int> m_vec0E0;
	std::vector<int> m_vec0F8;
	std::vector<int> m_vec110;
	int m_unknown128_00;
	int m_unknown128_01;
};

class AccumulatedLoginData : public INetworkData {
public:
	AccumulatedLoginData();
	~AccumulatedLoginData();
	std::vector<int> m_vec018;
	std::vector<int> m_vec030;
	std::vector<int> m_vec048;
};

class LanternRiddlesInfo : public Sexy::RtObject {
public:
	LanternRiddlesInfo();
	~LanternRiddlesInfo();
	int m_riddlesAnsweredToday;
	int m_unknown00C;
	int m_riddlesAnsweredDays;
	int m_unknown014;
	std::vector<int> m_vec018;
};

class UIFutureGiftBoxMgr : public Sexy::LazySingleton<UIFutureGiftBoxMgr> {
public:
	void LoadData(const FutureGiftBoxData& data);
};

class PennyGiftBoxManager : public Sexy::LazySingleton<PennyGiftBoxManager> {
public:
	void LoadData();
};

class AccumulatedLoginManager : public Sexy::LazySingleton<AccumulatedLoginManager> {
public:
	void LoadData();
};

/////////////// Lifecycle ///////////////

ActivityManager::ActivityManager()
{
	gMessageRouter->Subscribe(Message::MsgError, Sexy::MakeDelegate(*this, &ActivityManager::onNetworkError));
	gMessageRouter->Subscribe(Message::NotifyRefreshActivityList, Sexy::MakeDelegate(*this, &ActivityManager::onNotifyRefreshActivityList));
	gMessageRouter->Subscribe(Message::BuyItemFinish, Sexy::MakeDelegate(*this, &ActivityManager::OnBuyItemFinish));
}

ActivityManager::~ActivityManager()
{
}

void ActivityManager::Reset()
{
	m_ItemList.clear();
	m_bInit = false;
}

void ActivityManager::Update()
{
	if (m_timerRequest > 0 && PVZ_T() >= m_timerRequest)
		m_timerRequest = -1;
	WorldMapActivityBtnTurnChangeManager::GetInstancePtr()->update();
}

/////////////// Accessors ///////////////

ActiveItem ActivityManager::GetActiveItem(int i_id)
{
	ActiveItem item;
	std::map<int, ActiveItem>::iterator it = m_ItemList.find(i_id);
	if (it != m_ItemList.end()) {
		item = it->second;
		if (!item.m_jsonData.empty())
			item.m_jsonData = " ";
	}
	return item;
}

void ActivityManager::SetActivityPopuped(int i_id)
{
	std::map<int, ActiveItem>::iterator it = m_ItemList.find(i_id);
	if (it != m_ItemList.end())
		it->second.m_actionPopupNum--;
}

void ActivityManager::SetActiveUpdateNotice(int i_id,
		std::function<void(ActiveItem*)> i_notice)
{
	m_ItemList[i_id].m_notice = i_notice;
}

/////////////// Network ///////////////

void ActivityManager::onNetworkError(int erroId)
{
	if (m_timerRequest > 0)
		m_timerRequest = -1;
}

void ActivityManager::Request(int i_id, bool i_wait, int i_client_status)
{
	INetworkMsgProcess* process = NetworkMgr::Instance()->GetNewNetWorkProcess();
	std::vector<std::pair<int, int>> idList{{i_id, 1}};
	process->RequestActivityList(idList, i_client_status, i_wait);
}

void ActivityManager::RequestUseGem(int i_actID, int i_count, bool i_bWait)
{
	INetworkMsgProcess* process = NetworkMgr::Instance()->GetNewNetWorkProcess();
	process->ICloudRequestUseGem(i_actID, i_count,
			DRefPtr<ICloudRequestCallbackFunctionBase>(nullptr), 1, i_bWait);
}

void ActivityManager::OnBuyItemFinish(MsgResultInfo* io_result,
		const S2C_ICloud_GetConsumeGemInfo* pInfo,
		const S2C_PlayerInfo* pGemChanged)
{
	if (io_result && pInfo && io_result->m_errorID == 0)
		Cpp2Lua(std::string("OnBuyItemFinish"), pInfo->m_actid);
}

/////////////// Logic ///////////////

void ActivityManager::InitLevelOfTheDayActivity(ActivityTypeID id,
		const std::set<int>& changeList)
{
	if (changeList.find(id) != changeList.end()) {
		LevelofTheDayActivityInfo info;
		GetActiveItem(id).GetDataSerialized(info);
		PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
		LevelofTheDayActiveInfo active;
		active.currentChance = info.currentChance;
		active.currentDay = info.currentDay;
		active.remainDays = info.remainDays;
		profile->SetLevelOfTheDayInfo(GetActiveItem(id).m_bOpen, active, (int)id);
	}
}

bool ActivityManager::SerializeMessage(const std::string& i_json,
		std::set<int>& o_activeList)
{
	o_activeList.clear();
	std::string error;
	Sexy::RtSerialBuffer buffer(NULL, 0);
	Sexy::RtSerialRtonWriter writer(&buffer);
	bool result = Sexy::RtSerial::JsonToRton(i_json.c_str(), writer, error);
	if (!result) {
		Sexy::OutputDebugStrF("%s", error.c_str());
	} else {
		Sexy::RtSerialRtonReader reader(&buffer);
		Sexy::RtSerialRtonSync sync(&reader);
		Sexy::RtSerialRtonReader* documentReader = sync.GetReader();
		documentReader->BeginDocumentObject();
		uint32 count = 0;
		if (reader.BeginArray("d", count)) {
			for (uint32 i = 0; i < count; i++) {
				Sexy::RtSerialRtonReader::Value item = reader.GetCurrentScope().GetArrayIndexValue(i);
				Sexy::RtSerialRtonReader::Key key = item.GetChildNamed("id");
				int id = key.GetValue().GetInt32();
				Sexy::OutputDebugStrF("change list id : %d", id);
				if (id > 0) {
					o_activeList.insert(id);
					m_ItemList[id].Serialize(Sexy::RtSerializeContext(&sync, ""));
					m_ItemList[id].RefreshDate();
					m_ItemList[id].Notify();
					Sexy::OutputDebugStrF("id:%d op:%d", id, m_ItemList[id].m_bOpen);
				}
			}
			reader.EndArray();
		}
		documentReader->EndDocumentObject();
	}
	return result;
}

void ActivityManager::Initialse()
{
	if (m_bInit)
		return;
	m_bInit = true;
	SetActiveUpdateNotice(Activity_RechargeBundle, std::function<void(ActiveItem*)>());
	std::vector<std::pair<int, int>> ids;
	ids.push_back(std::pair<int, int>(Activity_All, 0));
	ids.push_back(std::pair<int, int>(Activity_Spring_Sale, 1));
	ids.push_back(std::pair<int, int>(Activity_Summer_Boss, 1));
	ids.push_back(std::pair<int, int>(Activity_Summer_Fire, 1));
	ids.push_back(std::pair<int, int>(Activity_Summer_Ice, 1));
	ids.push_back(std::pair<int, int>(Activity_Summer_PlantComposit, 1));
	ids.push_back(std::pair<int, int>(Activity_Anniversary, 1));
	ids.push_back(std::pair<int, int>(Activity_Levels, 1));
	ids.push_back(std::pair<int, int>(Activity_WorldUnlockPack, 1));
	ids.push_back(std::pair<int, int>(Activity_Anniversary_2nd, 1));
	ids.push_back(std::pair<int, int>(Activity_First_Recharge, 1));
	ids.push_back(std::pair<int, int>(Activity_Recharge_Reward, 1));
	ids.push_back(std::pair<int, int>(Activity_RechargeBundle, 1));
	if (gLawnApp->IsChannelWithBigDeal())
		ids.push_back(std::pair<int, int>(Activity_Consumption_Reward, 1));
	ids.push_back(std::pair<int, int>(Activity_DailySign_TW4399, 1));
	ids.push_back(std::pair<int, int>(Activity_Special_Gem_Offer, 1));
	ids.push_back(std::pair<int, int>(Activity_TransGenosis, 1));
	ids.push_back(std::pair<int, int>(Activity_DinosaurDanger, 1));
	ids.push_back(std::pair<int, int>(Activity_SpringShop, 1));
	ids.push_back(std::pair<int, int>(Activity_RedPacket, 1));
	ids.push_back(std::pair<int, int>(Activity_PlantTree, 1));
	ids.push_back(std::pair<int, int>(Activity_ChildrenDay, 1));
	ids.push_back(std::pair<int, int>(Activity_ChildrenDay2018, 1));
	ids.push_back(std::pair<int, int>(Activity_SummerEvent, 1));
	ids.push_back(std::pair<int, int>(Activity_Festival_Game_2019, 1));
	ids.push_back(std::pair<int, int>(Activity_TimeTravel, 1));
	ids.push_back(std::pair<int, int>(Activity_WechatShare, 1));
	ids.push_back(std::pair<int, int>(Activity_DaveClub, 1));
	ids.push_back(std::pair<int, int>(Activity_Chrismas, 1));
	ids.push_back(std::pair<int, int>(Activity_FestivalEvent, 1));
	ids.push_back(std::pair<int, int>(Activity_Turn_charge, 1));
	ids.push_back(std::pair<int, int>(Activity_worldCup, 1));
	ids.push_back(std::pair<int, int>(Activity_FestivalDragonBoat, 1));
	ids.push_back(std::pair<int, int>(Activity_NationdayEntrance2018, 1));
	ids.push_back(std::pair<int, int>(Activity_Joust, 0));
	ids.push_back(std::pair<int, int>(Activity_5th, 1));
	ids.push_back(std::pair<int, int>(Activity_LimitLottery, 1));
	ids.push_back(std::pair<int, int>(Activity_Daily_Sign_Activity, 1));
	ids.push_back(std::pair<int, int>(Activity_NewYear_2018, 1));
	ids.push_back(std::pair<int, int>(Activity_FestivalEvent_2019, 1));
	ids.push_back(std::pair<int, int>(Activity_FestivalRechargeReward_2019, 1));
	ids.push_back(std::pair<int, int>(Activity_Festival_Monthly_Card_Try_2019, 1));
	ids.push_back(std::pair<int, int>(Activity_LimitGroupBuy, 0));
	ids.push_back(std::pair<int, int>(Activity_TravelLog, 1));
	ids.push_back(std::pair<int, int>(Activity_PlatformGift, 1));
	ids.push_back(std::pair<int, int>(Activity_ChildrenDay2019, 1));
	ids.push_back(std::pair<int, int>(Activity_WorldCup_2019, 1));
	ids.push_back(std::pair<int, int>(Activity_WorldCup_2019_Shop, 1));
	ids.push_back(std::pair<int, int>(Activity_TransGenosis_BlackList, 1));
	ids.push_back(std::pair<int, int>(Activity_SecretGacha, 1));
	ids.push_back(std::pair<int, int>(Activity_Spring_ConsumeAndReceive, 1));
	ids.push_back(std::pair<int, int>(Activity_ConsumeAndReceiveExtra, 1));
	ids.push_back(std::pair<int, int>(Activity_HappyVaseBreaker, 1));
	ids.push_back(std::pair<int, int>(Activity_RechargeDailySignActivity, 1));
	ids.push_back(std::pair<int, int>(Activity_DiscountShopActivity, 1));
	ids.push_back(std::pair<int, int>(Activity_PennyGuide, 1));
	ids.push_back(std::pair<int, int>(Activity_FirstRecharge, 1));
	ids.push_back(std::pair<int, int>(Activity_PlantAdventure, 1));
	ids.push_back(std::pair<int, int>(Activity_MysteryStore, 1));
	ids.push_back(std::pair<int, int>(Activity_Rift, 0));
	ids.push_back(std::pair<int, int>(Activity_SecretStore, 0));
	ids.push_back(std::pair<int, int>(Activity_National_LevelOfDay_Entrance, 0));
	ids.push_back(std::pair<int, int>(Activity_BossChallengeMedalLottery, 0));
	ids.push_back(std::pair<int, int>(Activity_RichMan, 0));
	ids.push_back(std::pair<int, int>(Activity_NoviceSevenDays, 0));
	ids.push_back(std::pair<int, int>(Activity_PVZ1_Mode, 1));
	ids.push_back(std::pair<int, int>(Activity_PennyClassroom, 1));
	ids.push_back(std::pair<int, int>(Activity_PVP, 0));
	ids.push_back(std::pair<int, int>(Activity_PVP_Shop, 0));
	ids.push_back(std::pair<int, int>(Activity_GiftFoReturn, 1));
	ids.push_back(std::pair<int, int>(Activity_PartyAssist, 0));
	ids.push_back(std::pair<int, int>(Activity_NewPlayerCollection, 1));
	ids.push_back(std::pair<int, int>(Activity_LimitedSummon, 1));
	ids.push_back(std::pair<int, int>(Activity_WishingPool, 1));
	ids.push_back(std::pair<int, int>(10886, 1));
	if (gLawnApp->GetPlatform() == PLATFORM_BUBUGAO_HD)
		ids.push_back(std::pair<int, int>(Activity_VivoGacha, 0));
	if (ProfileUtils::HasCompletedSecondWorldLevel(2, false)) {
		ids.push_back(std::pair<int, int>(Activity_UnchartedMode, 1));
		Sexy::OutputDebugStrF("ActivityManager::Request Activity_UnchartedMode");
	}
	if (ProfileUtils::HasCompletedSecondWorldLevel(7, false))
		ids.push_back(std::pair<int, int>(Activity_CardGame, 1));
	ids.push_back(std::pair<int, int>(Activity_NewPVP, 1));
	if (ProfileUtils::Profile()->PlayerHasCompletedTutorial(TUTORIAL_GACHA_INTRO_1))
		ids.push_back(std::pair<int, int>(Activity_Cornucopia, 0));
	ids.push_back(std::pair<int, int>(Activity_InvitationRewards, 1));
	ids.push_back(std::pair<int, int>(10883, 1));
	ids.push_back(std::pair<int, int>(10884, 1));
	ids.push_back(std::pair<int, int>(10888, 0));
	ids.push_back(std::pair<int, int>(10889, 1));
	ids.push_back(std::pair<int, int>(10891, 1));
	ids.push_back(std::pair<int, int>(10892, 1));
	ids.push_back(std::pair<int, int>(10894, 1));
	NetworkMgr::Instance()->GetNewNetWorkProcess()->RequestActivityList(ids, 0, true);
	m_timerRequest = PVZ_T() + 10;
}

/////////////// Refresh ///////////////

#define REFRESH_LEVEL_OF_THE_DAY(ID) \
	if (changeList.find(ID) != changeList.end()) { \
		LevelofTheDayActivityInfo info; \
		GetActiveItem(ID).GetDataSerialized(info); \
		PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile(); \
		LevelofTheDayActiveInfo active; \
		active.currentChance = info.currentChance; \
		active.currentDay = info.currentDay; \
		active.remainDays = info.remainDays; \
		profile->SetLevelOfTheDayInfo(GetActiveItem(ID).m_bOpen, active, (int)(ID)); \
	}

#define REFRESH_CHRISTMAS_CHARGE(ID, HINT) \
	if (__builtin_expect(changeList.find(ID) != changeList.end(), HINT)) { \
		ActiveItem item = ActivityManager::GetInstancePtr()->GetActiveItem(ID); \
		if (item.IsValid() && __builtin_expect(item.m_bOpen, 0)) { \
			ChagreDoubleFesivalConfig config; \
			if (item.GetDataSerialized(config)) { \
				if (!gLawnApp->isSameDay(config.m_tGivePlantIDTime, ServerTime::Instance()->GetServerTime())) { \
					int plantID = ChristmasChargeManager::GetInstancePtr()->getChristmasValuablePlantID(); \
					Sexy::OutputDebugStrF("ChristmasChargeManager::GetInstancePtr() plantID not same Day= %d", plantID); \
					ChristmasChargeManager::GetInstancePtr()->setCurPlantID(plantID); \
					if (plantID > 0) \
						NetworkMgr::Instance()->GetNewNetWorkProcess()->ICloudRequestChargeRewardID(ID, plantID); \
				} else { \
					int plantID = ChristmasChargeManager::GetInstancePtr()->getCurPlantIDFromServer(); \
					Sexy::OutputDebugStrF("ChristmasChargeManager::GetInstancePtr() plantID is same Day= %d", plantID); \
					ChristmasChargeManager::GetInstancePtr()->setCurPlantID(plantID); \
				} \
				ChristmasChargeManager::GetInstancePtr()->setAlreadyAwardIndex(config.m_nAreadyAwardIndex); \
				ChristmasChargeManager::GetInstancePtr()->setNumTodayChargeCurrency(config.m_nNumTodayChargeCurrency); \
			} \
		} \
	}

void ActivityManager::onNotifyRefreshActivityList(bool i_success,
		const std::set<int>& changeList)
{
	if (m_timerRequest > 0)
		m_timerRequest = -1;
	if (changeList.find(Activity_WishingPool) != changeList.end())
		UIWishingPool::SynchronizeResVersion();
	REFRESH_LEVEL_OF_THE_DAY(Activity_NationdayEntrance2018)
	REFRESH_LEVEL_OF_THE_DAY(Activity_ChildrenDay)
	REFRESH_LEVEL_OF_THE_DAY(Activity_ChildrenDay2018)
	REFRESH_LEVEL_OF_THE_DAY(Activity_SummerEvent)
	REFRESH_LEVEL_OF_THE_DAY(Activity_Festival_Game_2019)
	InitLevelOfTheDayActivity(Activity_ChildrenDay2019, changeList);
	REFRESH_LEVEL_OF_THE_DAY(Activity_TimeTravel)
	if (changeList.find(Activity_MiniGameRank) != changeList.end()) {
		ActiveItem item = ActivityManager::GetInstancePtr()->GetActiveItem(Activity_MiniGameRank);
		if (item.IsValid() && __builtin_expect(item.m_bOpen, 0)) {
			MiniGameRankItemConfig config;
			if (item.GetDataSerialized(config) && !config.m_vecMiniGameAward.empty() && changeList.size() > 2) {
				UIMiniGameRankAward* dialog = UISingletonDialog<UIMiniGameRankAward>::ShowDialog();
				dialog->loadData(config.m_vecMiniGameAward, config.m_nLastMonthOrder, config.m_strPeriod);
				dialog->initView();
			}
		}
	}
	if (changeList.find(Activity_Spring_ConsumeAndReceive) != changeList.end()) {
		ActiveItem item = ActivityManager::GetInstancePtr()->GetActiveItem(Activity_Spring_ConsumeAndReceive);
		if (__builtin_expect(item.m_bOpen, 0)) {
			NetworkConsumeAndReceive data;
			bool success = item.GetDataSerialized(data);
			PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
			if (success)
				profile->CheckConsumptionActivityVersion(data.Number);
		}
	}
	if (changeList.find(Activity_HappyVaseBreaker) != changeList.end()) {
		ActiveItem item = ActivityManager::GetInstancePtr()->GetActiveItem(Activity_HappyVaseBreaker);
		if (item.IsValid() && item.m_bOpen)
			HappyVaseBreakerTaskManager::GetInstancePtr()->Initialize();
	}
	if (changeList.find(Activity_PennyGuide) != changeList.end()) {
		if (UISingletonDialog<UIPennyGuide>::GetSingletonPtr())
			return;
		ActiveItem item = ActivityManager::GetInstancePtr()->GetActiveItem(Activity_PennyGuide);
		if (item.IsValid() && item.m_bOpen)
			PennyTaskManager::GetInstancePtr()->Init();
	}
	if (changeList.find(Activity_RechargeDailySignActivity) != changeList.end()) {
		ActiveItem item = ActivityManager::GetInstancePtr()->GetActiveItem(Activity_RechargeDailySignActivity);
		if (item.IsValid() && item.m_bOpen)
			RechargeDailySignActivityManager::GetInstancePtr()->Init(item);
	}
	if (changeList.find(Activity_DiscountShopActivity) != changeList.end()) {
		ActiveItem item = ActivityManager::GetInstancePtr()->GetActiveItem(Activity_DiscountShopActivity);
		if (item.IsValid() && item.m_bOpen)
			DiscountShopActivityManager::GetInstancePtr()->Init(item);
	}
	if (changeList.find(Activity_PennyClassroom) != changeList.end()) {
		ActiveItem item = ActivityManager::GetInstancePtr()->GetActiveItem(Activity_PennyClassroom);
		if (item.IsValid() && item.m_bOpen) {
			NetworkPennyClassroomData data;
			if (item.GetDataSerialized(data))
				PennyClassroomManager::GetInstancePtr()->LoadData(data);
		}
	}
	REFRESH_CHRISTMAS_CHARGE(Activity_ChristmasChargeReward, 0)
	REFRESH_CHRISTMAS_CHARGE(Activity_FestivalRechargeReward, 0)
	REFRESH_CHRISTMAS_CHARGE(Activity_RechargeReward, 0)
	REFRESH_CHRISTMAS_CHARGE(Activity_NewYear_2018_Recharge, 0)
	if (changeList.find(Activity_FestivalRechargeReward_2019) != changeList.end()) {
		ActiveItem item = ActivityManager::GetInstancePtr()->GetActiveItem(Activity_FestivalRechargeReward_2019);
		if (item.IsValid() && __builtin_expect(item.m_bOpen, 0)) {
			NewYearChargeConfig config;
			if (item.GetDataSerialized(config)) {
				if (NewYearChargeManager::GetInstancePtr()->IsDuringAcivity())
					NewYearChargeManager::GetInstancePtr()->setCurPlantID(NewYearChargeManager::GetInstancePtr()->getCurPlantIDFromServer());
				NewYearChargeManager::GetInstancePtr()->setNumWeeklyChargeCurrency(config.m_nNumWeekChargeCurrency);
				NewYearChargeManager::GetInstancePtr()->setAlreadyAwardIndex(config.m_nNumWeekChargeIndex);
				NewYearChargeManager::GetInstancePtr()->CheckAlter();
			}
		}
	}
	if (changeList.find(Activity_SpringDailyReward_2019) != changeList.end()) {
		ActiveItem item = ActivityManager::GetInstancePtr()->GetActiveItem(Activity_SpringDailyReward_2019);
		if (item.IsValid()) {
			SpringDailyLoginConfig config;
			if (item.GetDataSerialized(config)) {
				PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
				if (profile) {
					SpringChargeManager::GetInstancePtr()->loadData(config);
					Sexy::OutputDebugStrF("Activity_SpringDailyReward_2019 %d\n", config.m_vecExperPlant.size());
					for (std::vector<int>::iterator it = config.m_vecExperPlant.begin(); it != config.m_vecExperPlant.end(); ++it) {
						Sexy::OutputDebugStrF("Activity_SpringDailyReward_2019 it =%d\n", *it);
						profile->addExperiencePlants(*it);
					}
				}
			}
		}
	}
	if (changeList.find(Activity_LanternRiddle) != changeList.end()) {
		ActiveItem item = ActivityManager::GetInstancePtr()->GetActiveItem(Activity_LanternRiddle);
		if (__builtin_expect(item.m_bOpen, 0)) {
			LanternRiddlesInfo info;
			if (item.GetDataSerialized(info)) {
				PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
				profile->SetRiddlesAnsweredToday(info.m_riddlesAnsweredToday);
				profile->SetRiddlesAnsweredDays(info.m_riddlesAnsweredDays);
			}
		}
	}
	if (changeList.find(Activity_FirstRecharge) != changeList.end()) {
		ActiveItem item = ActivityManager::GetInstancePtr()->GetActiveItem(Activity_FirstRecharge);
		if (item.IsValid() && item.m_bOpen) {
			FirstRechargeExtraNetworkData data;
			if (item.GetDataSerialized(data)) {
				if (!data.IsNoRecharge()) {
					FirstRechargeExtraManager::GetInstancePtr()->LoadData(data, data.IsPopUp());
				} else {
					EventTimesRecord record = ProfileMgr::GetInstance().GetCurrentProfile()->GetEventRecordByName("firstrecharge");
					if (!TimeUtil::IsToday(record.theTime))
						FirstRechargeExtraManager::GetInstancePtr()->LoadData(data, true);
				}
			}
		}
	}
	if (changeList.find(Activity_MysteryStore) != changeList.end()) {
		ActiveItem item = ActivityManager::GetInstancePtr()->GetActiveItem(Activity_MysteryStore);
		if (__builtin_expect(item.m_bOpen, 0))
			MysteryCrystalMgr::GetInstance().Init(false);
	}
	if (changeList.find(Activity_UnchartedMode) != changeList.end()) {
		UnchartedModeNetworkMgr::GetInstance().syncMainEntryInfo();
		Sexy::OutputDebugStrF("ActivityManager Activity_UnchartedMode suncMainEntryInfo");
	}
	if (changeList.find(Activity_CardGame) != changeList.end())
		CardGameNetworkMgr::GetInstance().syncMainEntryInfo();
	changeList.find(Activity_NewPVP);
	changeList.end();
	if (changeList.find(10883) != changeList.end()) {
		ActiveItem item = ActivityManager::GetInstancePtr()->GetActiveItem(10883);
		if (item.IsValid() && item.m_bOpen) {
			FutureGiftBoxData data;
			if (item.GetDataSerialized(data))
				UIFutureGiftBoxMgr::GetInstance().LoadData(data);
		}
	}
	if (changeList.find(10884) != changeList.end()) {
		ActiveItem item = ActivityManager::GetInstancePtr()->GetActiveItem(10884);
		if (item.IsValid() && item.m_bOpen) {
			PennyGiftBoxData data;
			if (item.GetDataSerialized(data))
				PennyGiftBoxManager::GetInstancePtr()->LoadData();
		}
	}
	if (changeList.find(10890) != changeList.end()) {
		ActiveItem item = ActivityManager::GetInstancePtr()->GetActiveItem(10890);
		if (item.IsValid() && item.m_bOpen) {
			AccumulatedLoginData data;
			if (item.GetDataSerialized(data))
				AccumulatedLoginManager::GetInstancePtr()->LoadData();
		}
	}
	if (changeList.find(Activity_Turn_charge) != changeList.end()) {
		Sexy::OutputDebugStrF("ChristmasChargeManager::GetInstancePtr() Activity_Turn_charge ");
		if (changeList.size() > 2) {
			ActiveItem item = ActivityManager::GetInstancePtr()->GetActiveItem(Activity_Turn_charge);
			if (item.IsValid() && __builtin_expect(item.m_bOpen, 0)) {
				ActivityTurnChangeConfig config;
				if (item.GetDataSerialized(config))
					WorldMapActivityBtnTurnChangeManager::GetInstancePtr()->loadData(config);
			}
		}
	}
	if (!WorldMapActivityBtnTurnChangeManager::GetInstancePtr()->getIsInit())
		WorldMapActivityBtnTurnChangeManager::GetInstancePtr()->setIsInit(true);
}

#undef REFRESH_LEVEL_OF_THE_DAY
#undef REFRESH_CHRISTMAS_CHARGE
