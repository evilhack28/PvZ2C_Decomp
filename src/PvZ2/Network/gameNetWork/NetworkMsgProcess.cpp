//
//  NetworkMsgProcess.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-09.
//

#include "SexyAppFramework/Common.h"

#include "NetworkMsgProcess.h"
#include "LawnApp.h"
#include "BossChallenge.h"
#include "MiniGame.h"
#include "ActivityManager.h"
#include "NameMapperEnum.h"
#include "TGALogMgr.h"
#include "PVZDB.h"
#include "PVP/PVPManager.h"
#include "SettingsDialog.h"
#include "UIWorldCupEntrance.h"
#include "ActiveSummery.h"
#include "GameStateMgr.h"
#include "PlayerInfo.h"
#include "ProfileUtils.h"
#include "PVP/PVPShopConfigData.h"
#include "MainMenu.h"
#include "UIDoubleFestivalActivity.h"
#include "NameMapper.h"
#include "ActivityConfig.h"
#include "HintUI.h"
#include "UIEditor/UIMessageBox.h"
#include "AutoLock.h"
#include "TodLib/TodStringFile.h"
#include "UISecretAreaReward.h"
#include "PVZ2UnchartedModeNetworkMgr.h"
#include "DangerRoomManager.h"
#include "UIEditor/StringHelper.h"
#include "Social/LoginSDKMgr.h"
#include "PVZ1ModeShop.h"
#include "RiftaShop.h"
#include "ZMatchShopDlg.h"
#include "UINewPVPShop.h"
#include "ADManager.h"
#include "Social/Widgets/AccountBindDialog.h"

void MiniGameRewardEndMsg(bool) asm("_ZN7Message23NotifyMiniGameRewardEndEb");
void WorldCupBeginGameMsg(bool) asm("_ZN7Message19GLWorldCupBeginGameEb");
void BuyWorldCupTicketMsg(bool) asm("_ZN7Message19GLBuyWorldCupTicketEb");
void Verify2015NewTearChargeMsg(bool) asm("_ZN7Message23Verify2015NewTearChargeEb");
void NotifyLevelupBookMsg(bool) asm("_ZN7Message17NotifyLevelupBookEb");
void AcFirstRechargeSucMsg(bool) asm("_ZN7Message18AcFirstRechargeSucEb");
void ComposePlantMsg(bool) asm("_ZN7Message12ComposePlantEb");
void BoardInfoGetRewardMsg(const S2C_NoticeInfoGet*) asm("_ZN7Message24NotifyBoardInfoGetRewardEPK17S2C_NoticeInfoGet");
void RefreshActivityLevelEndMsg(int, S2C_VacationLevelEndData*) asm("_ZN7Message29NotifyRefreshActivityLevelEndEiP24S2C_VacationLevelEndData");
void BoardInfoListMsg(const S2C_NoticeInfoList*) asm("_ZN7Message19NotifyBoardInfoListEPK18S2C_NoticeInfoList");
void CodeRewardResultMsg(bool, const S2C_CodeRewardResult*) asm("_ZN7Message22NotifyCodeRewardResultEbPK20S2C_CodeRewardResult");
void WechatRewardResultMsg(bool, const S2C_WechatShareResult*) asm("_ZN7Message24NotifyWechatRewardResultEbPK21S2C_WechatShareResult");
void ChallengeRewardMsg(const std::string&) asm("_ZN7Message21NotifyChallengeRewardERKSs");
void PVPCompleteUpgradeGemSuccessMsg(int) asm("_ZN7Message31GetPVPCompleteUpgradeGemSuccessEi");
void PVPPingMsg(bool) asm("_ZN7Message15PVP_PingSuccessEb");
void SubPvpCoinMsg(int, int) asm("_ZN7Message16NotifyPvpSubCoinEii");
void AchievementRewardMsg(int, int) asm("_ZN7Message23NotifyAchievementRewardEii");
void PlatformGiftListMsg(bool, const S2C_PlatformGiftData*) asm("_ZN7Message22NotifyPlatformGiftListEbPK20S2C_PlatformGiftData");
void BillingRewardMsg(bool, const S2C_BillingReward*) asm("_ZN7Message19NotifyBillingRewardEbPK17S2C_BillingReward");
void LimitLotteryCrystalBuyMsg(bool, const S2C_LimitLotteryCrystalBuy*) asm("_ZN7Message34NotifyLimitLotteryBuyCrystalFinishEbPK26S2C_LimitLotteryCrystalBuy");
void LimitLotteryCupShopMsg(bool, const S2C_S2C_LimitLotteryCupShop*) asm("_ZN7Message34NotifyLimitLotteryBuyCupShopFinishEbPK27S2C_S2C_LimitLotteryCupShop");
void PiggyBankRewardMsg(bool, const S2C_PiggyBankReward*) asm("_ZN7Message35NotifySpringOutingConsumeAndReceiveEbPK19S2C_PiggyBankReward");
void LimitLotteryRewardMsg(bool, const S2C_LimitLotteryReward*) asm("_ZN7Message24NotifyLimitLotteryRewardEbPK22S2C_LimitLotteryReward");
void UnlockWorldCupTeamMsg(bool) asm("_ZN7Message20GLUnlockWorldCupTeamEb");
void SummeryLotteryMsg(int, const S2C_SummeryLotteryData&) asm("_ZN7Message20NotifySummeryLotteryEiRK22S2C_SummeryLotteryData");
void SummeryLottery2018Msg(int, const S2C_SummeryLotteryData2018&) asm("_ZN7Message24NotifySummeryLottery2018EiRK26S2C_SummeryLotteryData2018");
void BattleZRankListEffectMsg(const std::vector<int>&) asm("_ZN7Message27NotifyBattleZRankListEffectERKSt6vectorIiSaIiEE");
void PVPTrainingFinishGemsMsg(int) asm("_ZN7Message21PVPTrainingFinishGemsEi");
void StaticConfigMsg(int, const S2C_StaticConfig*) asm("_ZN7Message18NotifyStaticConfigEiPK16S2C_StaticConfig");
void PVPTrainingSellMsg(bool) asm("_ZN7Message21PVPTrainingSellResultEb");
void BossChallengeLevelEndMsg(int, const S2C_BossChallengeLevelEndData*) asm("_ZN7Message27NotifyBossChallengeLevelEndEiPK29S2C_BossChallengeLevelEndData");
void BossChallengeRewardMsg(int, const S2C_BossChallengteReward*) asm("_ZN7Message25NotifyBossChallengeRewardEiPK24S2C_BossChallengteReward");
void SavePVPPlayerInfoMsg(bool, int) asm("_ZN7Message17SavePVPPlayerInfoEbi");
void PVPCompleteUpgradeMsg(S2C_PVPCompleteUpgradeData*) asm("_ZN7Message24GetPVPCompletePVPUpgradeEP26S2C_PVPCompleteUpgradeData");
void LanternRiddlesResultMsg(const S2C_LanternRiddlesResult&) asm("_ZN7Message28CompeleteTodayLanternRiddlesERK24S2C_LanternRiddlesResult");
void UnlockNewAvatarMsg(bool, int) asm("_ZN7Message21NotifyUnlockNewAvatarEbi");
void DangerRoomBoostEndMsg() asm("_ZN7Message18DangerRoomBoostEndEv");
void BuySecretAreaRewardMsg(bool, const New_S2C_BuySecretAreaReward*) asm("_ZN7Message29NotifySecretAreaRewardDetailsEbPK27New_S2C_BuySecretAreaReward");
void UnEquipArtifactMsg(int) asm("_ZN7Message15UnEquipArtifactEi");
void EquipArtifactMsg(int) asm("_ZN7Message13EquipArtifactEi");
void SpringBuyPlantMsg(bool, int) asm("_ZN7Message12GLBuyPlantIDEbi");
void BeginPVPUpgradeMsg() asm("_ZN7Message22BeginPVPUpgradeSuccessEv");
void EquipCollectionMsg(int, int) asm("_ZN7Message21NotifyEquipCollectionEii");
void PlantTrialMsg() asm("_ZN7Message20PlantTrialPaySuccessEv");
void CRChargeRewardPlantIDMsg(bool) asm("_ZN7Message21CRChargeRewardPlantIDEb");
void ChangePlantSuccessMsg(const std::string&) asm("_ZN7Message18ChangePlantSuccessERKSs");
void DailySignWithTWMsg(bool, const S2C_DailySignWithTW*) asm("_ZN7Message27NotifyDailySignWithTwResultEbPK19S2C_DailySignWithTW");
void PVPCompensationNoticeMsg(int, int, int) asm("_ZN7Message21PVPCompensationRewardEiii");
void LoginReward7DaysMsg(bool, const S2C_7DaysLoginReward*) asm("_ZN7Message18GL7DaysLoginRewardEbPK20S2C_7DaysLoginReward");
void LoginRewardSpringMsg(bool, const S2C_7DaysLoginSpringReward*) asm("_ZN7Message24GL7DaysLoginSpringRewardEbPK26S2C_7DaysLoginSpringReward");
void BuyZMatchTicketMsg(bool) asm("_ZN7Message17GLBuyZMatchTicketEb");
void DeliverySendMsg(bool) asm("_ZN7Message14GLDeliverySendEb");

void INetworkMsgProcess::OnRequestLuaGeneral(const NetWorkMsg& i_arg)
{
}

void INetworkMsgProcess::OnRequestDinosaurDanger(const NetWorkMsg& i_arg)
{
}

void INetworkMsgProcess::OnICloudRequestNoviceSevenDaysTrigger(const NetWorkMsg& i_arg)
{
}

INetworkMsgProcess::ICloudState INetworkMsgProcess::GetICloudState() const
{
	return m_ICIoudState;
}

void INetworkMsgProcess::SetICloudState(const ICloudState& state)
{
	m_ICIoudState = state;
}

AString INetworkMsgProcess::getUserID()
{
	return m_UserId;
}

AString INetworkMsgProcess::getSessionKey()
{
	return m_sk;
}

NetworkCacheQueue* INetworkMsgProcess::GetNetworkCacheQueue()
{
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_NETWORK_CACHE); it; ++it)
	{
		NetworkCacheQueuePtr queue = *it;
		if (queue.IsValid())
		{
			return queue;
		}
	}
	return NULL;
}

void INetworkMsgProcess::flushCache()
{
	NetworkCacheQueue* queue = GetNetworkCacheQueue();
	if (queue != NULL)
	{
		queue->flush();
	}
}

bool INetworkMsgProcess::isSessionKeyValid()
{
	return m_sk.size() > 31;
}

int INetworkMsgProcess::GetMsgID(const std::string& i_msgID)
{
	return atoi(&i_msgID[1]);
}

long INetworkMsgProcess::GetRandom()
{
	if (m_random == 0)
	{
		Sexy::SexyTime();
		srand(0);
		m_random = rand();
	}
	return m_random;
}

bool INetworkMsgProcess::IsJsonObj(const std::string& i_text)
{
	const char* text = i_text.c_str();
	return text[0] == '[' || text[0] == '{' || text[i_text.size() - 1] == ']' || text[i_text.size() - 1] == '}';
}

void INetworkMsgProcess::SaveCache()
{
	std::string path = GetFolder(Sexy::IFileDriver::PathType_NoBackup) + "networkcache.dat";
	PVZDB::GetInstance().SavePackageForTableToFile(PVZDB::TABLE_NETWORK_CACHE, path, false, true);
}

void INetworkMsgProcess::OnRequestRankList(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		BossChallenge::ResponseRankList(i_data.msg);
	}
	else
	{
		ShowErrorMessage(INetworkErrorData(i_data.msg));
	}
}

void INetworkMsgProcess::onRequestPVPRank(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		S2C_PvPRankInfo info;
		info.SerializeJson(i_data.msg);
		PVPManager::GetInstance().AddRankInfo(info);
	}
}

void INetworkMsgProcess::onRequestPvpShop(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		S2C_PvpShopData info;
		info.SerializeJson(i_data.msg);
		PVPManager::GetInstancePtr()->GetPVPShopConfigData().onResponseShopList(info);
	}
}

void INetworkMsgProcess::onRequestBuyPvpShopObject(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		S2C_BuyPvpShopData info;
		info.SerializeJson(i_data.msg);
		PVPManager::GetInstancePtr()->GetPVPShopConfigData().onResponseBuyResult(info);
	}
}

void INetworkMsgProcess::onRequestOtherZbList(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		S2C_PvPOtherUserZbInfo info;
		info.SerializeJson(i_data.msg);
		PVPManager::GetInstance().AddOtherUserZbList(info.m_profileId, info.m_zbInfoList);
	}
}

void INetworkMsgProcess::OnRequestMiniGameRewardEnd(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		gMessageRouter->Broadcast(MiniGameRewardEndMsg, true);
	}
	else
	{
		ShowErrorMessage(INetworkErrorData(i_data.msg));
	}
}

void INetworkMsgProcess::OnRequestDisplayID(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		S2C_ICloud_DisplayID info;
		info.SerializeJson(i_data.msg);
		SettingsDialog::SetDisplayID(info.m_displayID);
		SettingsDialog::SetDisplayUUID(info.m_displayUUID);
	}
}

void INetworkMsgProcess::onRequestBoardInfoList(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		S2C_NoticeInfoList info;
		info.SerializeJson(i_data.msg);
		gMessageRouter->Broadcast(BoardInfoListMsg, &info);
	}
}

void INetworkMsgProcess::onRequestSummerPlantComposit(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0 && ActiveSummery::GetSingletonPtr() != NULL)
	{
		ActiveSummery::GetSingletonPtr()->ResponsePlantCompositMsg(i_data.msg);
	}
}

void INetworkMsgProcess::OnICloudRequestClearworldcupdata(const NetWorkMsg& i_data)
{
	Sexy::OutputDebugStrF("INetworkMsgProcess::OnICloudRequestClearworldcupdata %d ", i_data.erro);
	if (i_data.erro == 0)
	{
		WorldCupManager::GetInstancePtr()->ClearData();
	}
}

void INetworkMsgProcess::OnICloudRequestGetWorldCupBeginGame(const NetWorkMsg& i_data)
{
	Sexy::OutputDebugStrF("INetworkMsgProcess::OnICloudRequestGetWorldCupBeginGame %d ", i_data.erro);
	bool success = true;
	if (i_data.erro != 0)
	{
		success = false;
	}
	gMessageRouter->Post(WorldCupBeginGameMsg, success);
}

void INetworkMsgProcess::OnICloudRequestGetbuyWorldCupTicket(const NetWorkMsg& i_data)
{
	Sexy::OutputDebugStrF("INetworkMsgProcess::OnICloudRequestGetbuyWorldCupTicket %d ", i_data.erro);
	if (i_data.erro == 0)
	{
		gMessageRouter->Post(BuyWorldCupTicketMsg, true);
	}
}

bool INetworkMsgProcess::ICloudRequest2015NewTearChargeStat()
{
	gMessageRouter->Post(Verify2015NewTearChargeMsg, false);
	return true;
}

void INetworkMsgProcess::OnICloudRequestLevelUpByPlantBook(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		gMessageRouter->Post(NotifyLevelupBookMsg, true);
	}
	else
	{
		gMessageRouter->Post(NotifyLevelupBookMsg, false);
	}
}

void INetworkMsgProcess::OnICloudRequestfirstChargeSucceed(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		gMessageRouter->Post(AcFirstRechargeSucMsg, true);
	}
}

void INetworkMsgProcess::OnICloudRequestComposePlant(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		gMessageRouter->Post(ComposePlantMsg, true);
	}
	else
	{
		gMessageRouter->Post(ComposePlantMsg, false);
	}
}

void INetworkMsgProcess::ShowMainMenu()
{
	gLawnApp->KillPVZ2Dialog();
	gGameStateMgr->ShowMainMenu(GAMETRANSITION_None, GAMETRANSITION_None);
}

void INetworkMsgProcess::ShowLogoScreen()
{
	gLawnApp->KillPVZ2Dialog();
	gLawnApp->silenceRelogin();
}

S2C_PlayerInfo INetworkMsgProcess::SubtractGems(const S2C_PlayerInfo& i_src)
{
	PlayerInfo* profile = ProfileUtils::Profile();
	profile->GetNumGems();
	int gems = i_src.m_Gems - profile->GetNumGems();
	int freeGems = i_src.m_freeGem - profile->GetGiveGems();
	profile->SetGems(i_src.m_Gems);
	profile->SetGiveGems(i_src.m_freeGem);
	S2C_PlayerInfo result;
	result.m_Gems = gems;
	result.m_freeGem = freeGems;
	return result;
}

void INetworkMsgProcess::OnError(int i_errorId, const std::string& i_reqID)
{
	gMessageRouter->Post(Message::MsgError, i_errorId);
	gMessageRouter->Post(Message::MsgErrorRequest, i_errorId, std::string(i_reqID));
}

void INetworkMsgProcess::onRequestBoardInfoGet(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		S2C_NoticeInfoGet info;
		info.SerializeJson(i_data.msg);
		info.m_currency.SetToPlayerInfo();
		gMessageRouter->Broadcast(BoardInfoGetRewardMsg, &info);
	}
}

void INetworkMsgProcess::onRequestPlaybackUpload(const NetWorkMsg& i_data)
{
	if (i_data.erro != 0)
	{
		ShowPVPErrorMessage(INetworkErrorData(i_data.msg));
	}
	Sexy::OutputDebugStrF("[P9] onRequestPlaybackUpload %s\n", i_data.msg.c_str());
}

void INetworkMsgProcess::onRequestActivityLevelEnd(const NetWorkMsg& i_data)
{
	S2C_VacationLevelEndData info;
	if (i_data.erro == 0)
	{
		info.SerializeJson(i_data.msg);
	}
	gMessageRouter->Broadcast(RefreshActivityLevelEndMsg, i_data.erro, &info);
}

static void BroadcastCodeRewardResultFailed(MessageRouter* i_router)
{
	i_router->Broadcast(CodeRewardResultMsg, false, (S2C_CodeRewardResult*)NULL);
}

void INetworkMsgProcess::OnRequestCodeReward(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		S2C_CodeRewardResult info;
		info.SerializeJson(i_data.msg);
		TGALogMgr::GetInstance().LogGiftCodeData(info.m_code, info.m_codeInfo);
		gMessageRouter->Broadcast(CodeRewardResultMsg, true, &info);
	}
	else
	{
		BroadcastCodeRewardResultFailed(gMessageRouter);
	}
}

static void BroadcastWechatRewardResultFailed(MessageRouter* i_router)
{
	i_router->Broadcast(WechatRewardResultMsg, false, (S2C_WechatShareResult*)NULL);
}

void INetworkMsgProcess::OnRequestWechatReward(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		S2C_WechatShareResult info;
		info.SerializeJson(i_data.msg);
		gMessageRouter->Broadcast(WechatRewardResultMsg, true, &info);
	}
	else
	{
		BroadcastWechatRewardResultFailed(gMessageRouter);
	}
}

void INetworkMsgProcess::OnRequestChallengeReward(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		gMessageRouter->Broadcast(ChallengeRewardMsg, std::string(i_data.msg));
	}
	else
	{
		ShowErrorMessage(INetworkErrorData(i_data.msg));
	}
}

void INetworkMsgProcess::onRequestPvPUpgradeCompleteGem(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		S2C_PVP128Data info;
		info.SerializeJson(i_data.msg);
		gMessageRouter->Broadcast(PVPCompleteUpgradeGemSuccessMsg, info.m_gem);
	}
	else
	{
		ShowPVPErrorMessage(INetworkErrorData(i_data.msg));
	}
}

void INetworkMsgProcess::onRequestSubPvpCoin(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		S2C_SubPvpCoinData info;
		info.SerializeJson(i_data.msg);
		gMessageRouter->Broadcast(SubPvpCoinMsg, info.m_leftPvpCoin, info.m_leftPvpMetal);
	}
	else
	{
		ShowPVPErrorMessage(INetworkErrorData(i_data.msg));
	}
}

void INetworkMsgProcess::onRequestAchievementReward(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		S2C_AchieveInfo info;
		info.SerializeJson(i_data.msg);
		gMessageRouter->Broadcast(AchievementRewardMsg, info.m_achieveID, info.m_targetCount);
	}
	else
	{
		ShowErrorMessage(INetworkErrorData(i_data.msg));
	}
}

void INetworkMsgProcess::onRequestPVPTrainingZombie(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		S2C_PVP_TrainingZombie info;
		info.SerializeJson(i_data.msg);
		PVPManager::GetInstancePtr()->RefreshTrainingDatas(&info);
	}
	else
	{
		ShowPVPErrorMessage(INetworkErrorData(i_data.msg));
	}
	Sexy::OutputDebugStrF("[P13]/[P14] onRequestPVPTrainingZombie %s\n", i_data.msg.c_str());
}

void INetworkMsgProcess::onSendPVP_Ping(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		gMessageRouter->Post(PVPPingMsg, false);
	}
	else if (i_data.erro == 25508)
	{
		gMessageRouter->Post(PVPPingMsg, true);
	}
	else
	{
		ShowPVPErrorMessage(INetworkErrorData(i_data.msg));
	}
	Sexy::OutputDebugStrF("[P6] onSendPVP_Ping %s\n", i_data.msg.c_str());
}

void INetworkMsgProcess::OnICloudRequestPlatformGift(const NetWorkMsg& i_data)
{
	Sexy::OutputDebugStrF("OnICloudRequestPlatformGift data error = %d msg = %s", i_data.erro, i_data.msg.c_str());
	if (i_data.erro == 0)
	{
		S2C_PlatformGiftData info;
		if (info.SerializeJson(i_data.msg))
		{
			gMessageRouter->Post(PlatformGiftListMsg, true, &info);
		}
	}
}

void INetworkMsgProcess::removeRequestMsg(const std::string& i_msgId)
{
	m_msgMgr.erase(i_msgId);
}

void INetworkMsgProcess::OnICloudRequestBindingThirdPartPlatforms(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		gLawnApp->GetMainMenu()->GetAccountBindDialog()->OnBindingSuccess();
	}
	else
	{
		gLawnApp->GetMainMenu()->GetAccountBindDialog()->OnBindingFailed(i_data.erro);
	}
}

void INetworkMsgProcess::OnICloudRequestUnboundThirdPartPlatforms(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		gLawnApp->GetMainMenu()->GetAccountBindDialog()->OnUnboundSuccess();
	}
	else
	{
		gLawnApp->GetMainMenu()->GetAccountBindDialog()->OnUnboundFailed(i_data.erro);
	}
}

void INetworkMsgProcess::OnICloudRequestBuyItem(const NetWorkMsg& i_data)
{
	Sexy::OutputDebugStrF("INetworkMsgProcess::OnICloudRequestBuyItem %d ", i_data.erro);
	if (i_data.erro == 0)
	{
		S2C_BuyZMatchShopData info;
		if (info.SerializeJson(i_data.msg))
		{
			ZMatchShopMgr::GetInstancePtr()->BuyFinish(info);
		}
	}
}

void INetworkMsgProcess::OnICloudRequestGetNewPVPShopData(const NetWorkMsg& i_data)
{
	Sexy::OutputDebugStrF("INetworkMsgProcess::OnICloudRequestGetNewPVPShopData %d ", i_data.erro);
	if (i_data.erro == 0)
	{
		Network_NewPVPShopData info;
		if (info.SerializeJson(i_data.msg))
		{
			NewPVPShopMgr::GetInstancePtr()->loadData(info);
		}
	}
}

void INetworkMsgProcess::OnICloudRequestGetZMatchShopData(const NetWorkMsg& i_data)
{
	Sexy::OutputDebugStrF("INetworkMsgProcess::OnICloudRequestGetZMatchShopData %d ", i_data.erro);
	if (i_data.erro == 0)
	{
		ZMatch_ShopData info;
		if (info.SerializeJson(i_data.msg))
		{
			ADManager::GetInstance().SetADWatchCount(ADType_Joust_Store, info.m_adTimes);
			ZMatchShopMgr::GetInstancePtr()->loadData(info);
		}
	}
}

void INetworkMsgProcess::OnICloudRequestGetPVZ1ModeShopData(const NetWorkMsg& i_data)
{
	Sexy::OutputDebugStrF("INetworkMsgProcess::OnICloudRequestGetPVZ1ModeShopData %d ", i_data.erro);
	if (i_data.erro == 0)
	{
		PVZ1ModeShopData info;
		if (info.SerializeJson(i_data.msg))
		{
			PVZ1ModeShopMgr::GetInstancePtr()->loadData(info);
		}
	}
}

void INetworkMsgProcess::OnICloudRequestGetRiftShopData(const NetWorkMsg& i_data)
{
	Sexy::OutputDebugStrF("INetworkMsgProcess::OnICloudRequestGetRiftShopData %d ", i_data.erro);
	if (i_data.erro == 0)
	{
		RiftaShopData info;
		if (info.SerializeJson(i_data.msg))
		{
			ADManager::GetInstance().SetADWatchCount(ADType_Rift_Store, info.m_adTimes);
			RiftShopMgr::GetInstancePtr()->loadData(info);
		}
	}
}

void INetworkMsgProcess::OnICloudRequestBillingPoint(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		S2C_BillingReward info;
		if (info.SerializeJson(i_data.msg))
		{
			if (!info.billList.empty())
			{
				gMessageRouter->Post(BillingRewardMsg, true, &info);
			}
		}
	}
}

static void PostLimitLotteryCrystalBuyFailed(MessageRouter* i_router)
{
	i_router->Post(LimitLotteryCrystalBuyMsg, false, (S2C_LimitLotteryCrystalBuy*)NULL);
}

void INetworkMsgProcess::OnICloudRequestBuyLimitLotteryCrystal(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		S2C_LimitLotteryCrystalBuy info;
		if (info.SerializeJson(i_data.msg))
		{
			gMessageRouter->Post(LimitLotteryCrystalBuyMsg, true, &info);
		}
	}
	else
	{
		PostLimitLotteryCrystalBuyFailed(gMessageRouter);
	}
}

static void PostLimitLotteryCupShopFailed(MessageRouter* i_router)
{
	i_router->Post(LimitLotteryCupShopMsg, false, (S2C_S2C_LimitLotteryCupShop*)NULL);
}

void INetworkMsgProcess::OnICloudRequestBuyLimitLotteryCupShop(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		S2C_S2C_LimitLotteryCupShop info;
		if (info.SerializeJson(i_data.msg))
		{
			gMessageRouter->Post(LimitLotteryCupShopMsg, true, &info);
		}
	}
	else
	{
		PostLimitLotteryCupShopFailed(gMessageRouter);
	}
}

static void PostPiggyBankRewardFailed(MessageRouter* i_router)
{
	i_router->Post(PiggyBankRewardMsg, false, (S2C_PiggyBankReward*)NULL);
}

void INetworkMsgProcess::OnICloudRequestConsumeAndReceive(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		S2C_PiggyBankReward info;
		if (info.SerializeJson(i_data.msg))
		{
			gMessageRouter->Post(PiggyBankRewardMsg, true, &info);
		}
	}
	else
	{
		PostPiggyBankRewardFailed(gMessageRouter);
	}
}

static void PostLimitLotteryRewardFailed(MessageRouter* i_router)
{
	i_router->Post(LimitLotteryRewardMsg, false, (S2C_LimitLotteryReward*)NULL);
}

void INetworkMsgProcess::OnICloudRequestGetLimitLottery(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		S2C_LimitLotteryReward info;
		if (info.SerializeJson(i_data.msg))
		{
			gMessageRouter->Post(LimitLotteryRewardMsg, true, &info);
		}
	}
	else if (i_data.erro != 40114)
	{
		PostLimitLotteryRewardFailed(gMessageRouter);
	}
}

void INetworkMsgProcess::OnICloudRequestGetUnlockWorldCupTeam(const NetWorkMsg& i_data)
{
	Sexy::OutputDebugStrF("INetworkMsgProcess::OnICloudRequestGetUnlockWorldCupTeam %d ", i_data.erro);
	if (i_data.erro == 0)
	{
		S2C_unLockWorldTeam info;
		if (info.SerializeJson(i_data.msg))
		{
			WorldCupManager::GetInstancePtr()->setIsUnLockByTeamID(info.m_nTeamID, true);
			gMessageRouter->Post(UnlockWorldCupTeamMsg, true);
		}
	}
}

void INetworkMsgProcess::onRequestSummeryLottery(const NetWorkMsg& i_data)
{
	S2C_SummeryLotteryData info;
	if (i_data.erro == 0)
	{
		info.SerializeJson(i_data.msg);
	}
	gMessageRouter->Broadcast(SummeryLotteryMsg, i_data.erro, info);
}

void INetworkMsgProcess::onRequestSummeryLottery2018(const NetWorkMsg& i_data)
{
	S2C_SummeryLotteryData2018 info;
	if (i_data.erro == 0)
	{
		info.SerializeJson(i_data.msg);
	}
	gMessageRouter->Broadcast(SummeryLottery2018Msg, i_data.erro == 0, info);
}

void INetworkMsgProcess::OnRequestRankListEffect(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		S2C_RankListEffect info;
		info.SerializeJson(i_data.msg);
		if (info.rankListType == BATTLEZ_RANK_LIST)
		{
			gMessageRouter->Post(BattleZRankListEffectMsg, info.playerIdList);
		}
	}
}

void INetworkMsgProcess::onRequestPVPTrainingFinishGems(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		S2C_PVP_TrainingFinishGems info;
		info.SerializeJson(i_data.msg);
		gMessageRouter->Broadcast(PVPTrainingFinishGemsMsg, info.m_Gems);
	}
	else
	{
		ShowPVPErrorMessage(INetworkErrorData(i_data.msg));
	}
	Sexy::OutputDebugStrF("[P6] onRequestPVPTrainingFinishGems %s\n", i_data.msg.c_str());
}

static void BroadcastStaticConfigFailed(MessageRouter* i_router, int i_error)
{
	i_router->Broadcast(StaticConfigMsg, i_error, (const S2C_StaticConfig*)NULL);
}

void INetworkMsgProcess::OnRequestStaticConfig(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		S2C_StaticConfig info;
		info.SerializeJson(i_data.msg);
		gMessageRouter->Broadcast(StaticConfigMsg, i_data.erro, &info);
	}
	else
	{
		BroadcastStaticConfigFailed(gMessageRouter, i_data.erro);
		ShowErrorMessage(INetworkErrorData(i_data.msg));
	}
}

void INetworkMsgProcess::OnICloudRequestTransferThirdPartPlatforms(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		S2C_ICloud_GetStatusThirdPart info;
		info.SerializeJson(i_data.msg);
		LoginSDKMgr::GetInstancePtr()->setSinaSDKUUID(info.m_sinaUUID);
		LoginSDKMgr::GetInstancePtr()->setWechatSDKUUID(info.m_wechatUUID);
		LoginSDKMgr::GetInstancePtr()->setTencentUUID(info.m_tencentUUID);
		gLawnApp->GetMainMenu()->GetAccountBindDialog()->OnTransferSuccess();
	}
	else
	{
		gLawnApp->GetMainMenu()->GetAccountBindDialog()->OnTransferFailed(i_data.erro);
	}
}

void INetworkMsgProcess::onRequestPVPTrainingSell(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		S2C_PVP_TrainingZombie info;
		info.SerializeJson(i_data.msg);
		PVPManager::GetInstancePtr()->RefreshTrainingDatas(&info);
		gMessageRouter->Broadcast(PVPTrainingSellMsg, true);
	}
	else
	{
		ShowPVPErrorMessage(INetworkErrorData(i_data.msg));
	}
	Sexy::OutputDebugStrF("[P6] onRequestPVPTrainingSell %s\n", i_data.msg.c_str());
}

void INetworkMsgProcess::onRequestBossChallengeLevelEnd(const NetWorkMsg& i_data)
{
	S2C_BossChallengeLevelEndData info;
	if (i_data.erro == 0)
	{
		info.SerializeJson(i_data.msg);
	}
	gMessageRouter->Broadcast(BossChallengeLevelEndMsg, i_data.erro, &info);
	ActivityManager::GetInstancePtr()->Request(Activity_BossChallenge, true, 0);
}

void INetworkMsgProcess::onRequestPVPPlantInfos(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		gMessageRouter->Post(SavePVPPlayerInfoMsg, true, 0);
	}
	else
	{
		ShowPVPErrorMessage(INetworkErrorData(i_data.msg));
	}
	Sexy::OutputDebugStrF("[P5] onRequestPVPPlantInfos %s\n", i_data.msg.c_str());
}

void INetworkMsgProcess::onRequestBossChallengeReward(const NetWorkMsg& i_data)
{
	S2C_BossChallengteReward info;
	if (i_data.erro == 0)
	{
		info.SerializeJson(i_data.msg);
		PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
		profile->SetGems(info.m_playerInfo.m_Gems);
		profile->SetGiveGems(info.m_playerInfo.m_freeGem);
		profile->AddCoins(info.m_coin);
	}
	gMessageRouter->Broadcast(BossChallengeRewardMsg, i_data.erro, &info);
	ActivityManager::GetInstancePtr()->Request(Activity_BossChallenge, true, 0);
}

void INetworkMsgProcess::onRequestCompletePVPUpgrade(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		S2C_PVPCompleteUpgradeData info;
		info.SerializeJson(i_data.msg);
		gMessageRouter->Broadcast(PVPCompleteUpgradeMsg, &info);
	}
	else if (i_data.erro != 20710)
	{
		ShowPVPErrorMessage(INetworkErrorData(i_data.msg));
	}
	else
	{
		gLawnApp->ShowGemStoreConfirm(STORE_TYPE_GEM, true);
	}
}

void INetworkMsgProcess::OnRequestLanternRiddlesCompelete(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		S2C_LanternRiddlesResult info;
		if (info.SerializeJson(i_data.msg))
		{
			gMessageRouter->Broadcast(LanternRiddlesResultMsg, info);
		}
	}
	else
	{
		ShowErrorMessage(INetworkErrorData(i_data.msg));
	}
}

void INetworkMsgProcess::OnICloudRequestUnlockNewAvatar(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		Sexy::StructuredData data;
		if (!StringHelper::ReadJson(i_data.msg, &data))
			return;
		gMessageRouter->Post(UnlockNewAvatarMsg, true, data.IntegerForPath("$.d.di", -1));
	}
	else
	{
		gMessageRouter->Post(UnlockNewAvatarMsg, false, -1);
	}
}

void INetworkMsgProcess::OnRequestDangerRoomBoostEnd(const NetWorkMsg& i_data)
{
	if (i_data.erro != 0)
	{
		ShowErrorMessage(INetworkErrorData(i_data.msg));
	}
	else
	{
		S2C_DangerRoomBoostSync info;
		info.SerializeJson(i_data.msg);
		PlayerInfo* profile = ProfileUtils::Profile();
		profile->SetGems(info.m_playerInfo.m_Gems);
		profile->SetGiveGems(info.m_playerInfo.m_freeGem);
		info.m_record.Decompress();
		DangerRoomManager::GetInstancePtr()->SetRecord(info.m_record);
		gMessageRouter->Broadcast(DangerRoomBoostEndMsg);
	}
}

void INetworkMsgProcess::OnRequestSecretAreaReward(const NetWorkMsg& i_data)
{
	New_S2C_BuySecretAreaReward info;
	info.SerializeJson(i_data.msg);
	if (i_data.erro != 0)
		return;
	int rewardIndex = UISecretAreaReward::GetSingletonPtr()->Current_num;
	std::string worldPrefix = UnchartedModeNetworkMgr::GetInstancePtr()->GetPrefixWorld();
	UnchartedModeNetworkMgr::GetInstancePtr()->OnObtainStarReward(worldPrefix, rewardIndex);
	gMessageRouter->Broadcast(BuySecretAreaRewardMsg, true, &info);
}

void INetworkMsgProcess::OnICloudRequestArtifactEquip(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
		Sexy::StructuredData data;
		if (StringHelper::ReadJson(i_data.msg, &data))
		{
			int artifactId = data.IntegerForPath("$.d.i", 0);
			profile->SetCurrentArtifact(artifactId);
			if (artifactId == 0)
			{
				gMessageRouter->Post(UnEquipArtifactMsg, 0);
			}
			else
			{
				gMessageRouter->Post(EquipArtifactMsg, artifactId);
			}
		}
	}
}

void INetworkMsgProcess::OnICloudRequestGetSpringBuyPlant(const NetWorkMsg& i_data)
{
	Sexy::OutputDebugStrF("INetworkMsgProcess::OnICloudRequestGetSpringBuyPlant %d ", i_data.erro);
	if (i_data.erro == 0)
	{
		S2C_buyPlantSpringReward info;
		if (info.SerializeJson(i_data.msg))
		{
			gMessageRouter->Post(SpringBuyPlantMsg, true, info.plantID);
		}
	}
	else if (i_data.erro == 45011)
	{
		gMessageRouter->Post(SpringBuyPlantMsg, false, 0);
	}
}

void INetworkMsgProcess::onRequestBeginPVPUpgrade(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		S2C_PVPBeinUpgradeData info;
		info.SerializeJson(i_data.msg);
		PVPManager::GetInstancePtr()->SetPVPMedal(info.m_medal);
		PVPManager::GetInstancePtr()->SetPVPCoin(info.m_coin);
		gMessageRouter->Broadcast(BeginPVPUpgradeMsg);
	}
	else if (i_data.erro != 20710)
	{
		ShowPVPErrorMessage(INetworkErrorData(i_data.msg));
	}
	else
	{
		gLawnApp->ShowGemStoreConfirm(STORE_TYPE_GEM, true);
	}
}

void INetworkMsgProcess::onRequestPVPChangeEnemy(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		S2C_PVP_ChangeEnemy info;
		info.SerializeJson(i_data.msg);
		if (info.m_mapInfo.zoneId != -1)
		{
			if (info.m_mapInfo.occupyname == L"")
			{
				info.m_mapInfo.occupyname = TodStringTranslate(L"[PVP_MAP_NEW_NAME]");
			}
			PVPManager::GetInstance().AddPVPMapData(info.m_mapInfo);
		}
		else if (info.m_mapPVPInfo.zoneId != -1)
		{
			PVPManager::GetInstance().AddPVPMapPVPData(info.m_mapPVPInfo);
		}
	}
}

void INetworkMsgProcess::onRequestUserHeadshot(const NetWorkMsg& i_data)
{
	AutoLock lock(std::function<void()>(nullptr), [this]() { m_requestUserHeadshotCallback = nullptr; });
	if (i_data.erro == 0)
	{
		if (m_requestUserHeadshotCallback)
		{
			m_requestUserHeadshotCallback->process(true);
		}
	}
	else if (m_requestUserHeadshotCallback)
	{
		m_requestUserHeadshotCallback->process(false);
	}
}

void INetworkMsgProcess::onRequestPVPUpgradeCancel(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		Sexy::StructuredData data;
		if (StringHelper::ReadJson(i_data.msg, &data))
		{
			int gems = data.IntegerForPath("$.d.ag", -1);
			if (gems > -1)
			{
				PVPManager::GetInstancePtr()->SetPVPCoin(gems);
			}
			int medals = data.IntegerForPath("$.d.am", -1);
			if (medals > -1)
			{
				PVPManager::GetInstancePtr()->SetPVPMedal(medals);
			}
		}
		PVPManager::GetInstancePtr()->GetLabData().SetUpgradeItem(LabItem_None, 0, 0);
	}
	else
	{
		ShowErrorMessage(INetworkErrorData(i_data.msg));
	}
}

void INetworkMsgProcess::OnICloudRequestCollectionEquip(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
		Sexy::StructuredData data;
		if (StringHelper::ReadJson(i_data.msg, &data))
		{
			int collectionId = data.IntegerForPath("$.d.i", 0);
			int equip = data.IntegerForPath("$.d.t", 1);
			profile->SetCollectionState(collectionId, equip != 0);
			gMessageRouter->Post(EquipCollectionMsg, collectionId, 0);
		}
	}
}

void INetworkMsgProcess::ShowPvpDialog(const SexyString& i_title, const SexyString& i_detail)
{
	UIMessageBox* box = UISingletonDialog<UIMessageBox>::ShowDialog();
	if (box != nullptr)
	{
		box->SetMessage(TodStringTranslate(i_detail), TodStringTranslate(i_title));
		box->SetShowType(UIMessageBox::Type_ShowOK | UIMessageBox::Type_ShowCancel);
		box->SetBackground(std::string("IMAGE_UI_DIALOG_ASSET_BG_LIGHT_PURPLE"));
		box->SetBackgroundDarken(true, 0.5f);
	}
}

void INetworkMsgProcess::OnICloudRequestChargeRewardID(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		gMessageRouter->Post(CRChargeRewardPlantIDMsg, true);
	}
	else if (i_data.erro == 24001)
	{
		HintUI* hint = gLawnApp->CreateHintUI();
		if (hint != nullptr)
		{
			hint->Default1Init();
			hint->SetTitleString(L"[NATIONDAY_7DAYS_AWARD_OUT_TITLE]");
			hint->SetContentString(L"[NATIONDAY_7DAYS_AWARD_OUT_DES]");
			hint->ShowHintUI();
		}
	}
}

void INetworkMsgProcess::OnICloudRequestPlantTrial(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		S2C_ICloud_PlantTrialInfo info;
		info.SerializeJson(i_data.msg);
		PlayerInfo* profile = ProfileUtils::Profile();
		gMessageRouter->Post(PlantTrialMsg);
		if (profile != nullptr)
		{
			int oldGems = profile->GetNumGems(false);
			int newGems = info.m_playerInfo.m_Gems;
			profile->SetGems(newGems);
			if (gLawnApp->GetActivityConfig() != nullptr && gLawnApp->GetActivityConfig()->IsAnyConsumptionTopicValid())
			{
				profile->AddConsumptionGems(oldGems - newGems);
			}
		}
	}
	else
	{
		gLawnApp->ShowGemStoreConfirm(STORE_TYPE_GEM, false);
	}
}

void INetworkMsgProcess::OnICloudRequestChangePlant(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		S2C_PlantLevel info;
		info.SerializeJson(i_data.msg);
		PlayerInfo* profile = ProfileUtils::Profile();
		if (profile != nullptr)
		{
			std::string plantName = PlantChipNameMapperServerID::GetInstance().GetNameForId(info.m_plantChipInfo.objectId);
			profile->SetPlantPieceCount(plantName, info.m_plantChipInfo.quantity, true, true, true, true);
			profile->UnlockPlant(plantName, false);
			profile->SetPlantStarLevel(plantName, info.m_plantLevelInfo.level + 1, false, true);
			gMessageRouter->Post(ChangePlantSuccessMsg, plantName);
		}
	}
}

void INetworkMsgProcess::OnICloudRequestGetStateThirdPartPlatforms(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		S2C_ICloud_GetStatusThirdPart info;
		info.SerializeJson(i_data.msg);
		LoginSDKMgr::GetInstancePtr()->setSinaSDKUUID(info.m_sinaUUID);
		LoginSDKMgr::GetInstancePtr()->setWechatSDKUUID(info.m_wechatUUID);
		LoginSDKMgr::GetInstancePtr()->setTencentUUID(info.m_tencentUUID);
		LoginSDKMgr::GetInstancePtr()->setIsReceivedBindingData(true);
	}
	else
	{
		gLawnApp->ShowMessageDialogNoCallback(std::string("[ERRORV234_TITLE]"), std::string("[ERRORV234_DESC]"));
	}
}

static void BroadcastDailySignWithTWFailed(MessageRouter* i_router)
{
	i_router->Broadcast(DailySignWithTWMsg, false, (const S2C_DailySignWithTW*)NULL);
}

void INetworkMsgProcess::OnRequestDailySignWithTW(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		S2C_DailySignWithTW info;
		info.SerializeJson(i_data.msg);
		gMessageRouter->Broadcast(DailySignWithTWMsg, true, &info);
	}
	else
	{
		gLawnApp->ShowMessageDialogNoCallback(std::string("[ERRORV225_TITLE]"), std::string("[ERRORV225_DESC]"));
		BroadcastDailySignWithTWFailed(gMessageRouter);
	}
}

void INetworkMsgProcess::OnICloudRequestGetChristmasChargeReward(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		CDFReceiveReward reward;
		if (reward.SerializeJson(i_data.msg))
		{
			ChristmasChargeManager::GetInstancePtr()->addAward(reward);
		}
	}
	else if (i_data.erro == 28035)
	{
		HintUI* hint = gLawnApp->CreateHintUI();
		if (hint != nullptr)
		{
			hint->Default1Init();
			hint->SetTitleString(L"[NATIONDAY_7DAYS_AWARD_OUT_TITLE]");
			hint->SetContentString(L"[STORE_PRODUCT_ACTIVITY_ONLYONCE]");
			hint->ShowHintUI();
		}
	}
}

void INetworkMsgProcess::OnICloudRequestWeeklyRechargeReward(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		NewYearRewardData reward;
		if (reward.SerializeJson(i_data.msg))
		{
			NewYearChargeManager::GetInstancePtr()->addAward(reward);
		}
	}
	else if (i_data.erro == 28035)
	{
		HintUI* hint = gLawnApp->CreateHintUI();
		if (hint != nullptr)
		{
			hint->Default1Init();
			hint->SetTitleString(L"[NATIONDAY_7DAYS_AWARD_OUT_TITLE]");
			hint->SetContentString(L"[STORE_PRODUCT_ACTIVITY_ONLYONCE]");
			hint->ShowHintUI();
		}
	}
}

void INetworkMsgProcess::onRequestPVPCompensationNoticeInfos(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		S2C_CompensationNoticeInfo info;
		info.SerializeJson(i_data.msg);
		if (info.m_type == 2)
		{
			PVPManager::GetInstancePtr()->SetPVPMedal(PVPManager::GetInstancePtr()->GetPVPMedal() + info.m_medalNum);
			PVPManager::GetInstancePtr()->SetPVPCoin(PVPManager::GetInstancePtr()->GetPVPCoin() + info.m_coinNum);
		}
		else if (info.m_type == 1)
		{
			if (info.m_resourceNum != 0 || info.m_coinNum != 0 || info.m_medalNum != 0)
			{
				gMessageRouter->Broadcast(PVPCompensationNoticeMsg, info.m_resourceNum, info.m_coinNum, info.m_medalNum);
			}
		}
	}
	else
	{
		ShowPVPErrorMessage(INetworkErrorData(i_data.msg));
	}
}

void INetworkMsgProcess::OnICloudRequestGet7DaysLoginReward(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		S2C_7DaysLoginReward reward;
		if (reward.SerializeJson(i_data.msg))
		{
			gMessageRouter->Post(LoginReward7DaysMsg, true, &reward);
		}
	}
	else if (i_data.erro == 21619)
	{
		HintUI* hint = gLawnApp->CreateHintUI();
		if (hint != nullptr)
		{
			hint->Default1Init();
			hint->SetTitleString(L"[NATIONDAY_7DAYS_AWARD_OUT_TITLE]");
			hint->SetContentString(L"[NATIONDAY_7DAYS_AWARD_OUT_DES]");
			hint->ShowHintUI();
		}
	}
}

void INetworkMsgProcess::OnICloudRequestGetChristmasLoginReward(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		S2C_7DaysLoginReward reward;
		if (reward.SerializeJson(i_data.msg))
		{
			gMessageRouter->Post(LoginReward7DaysMsg, true, &reward);
		}
	}
	else if (i_data.erro == 21619)
	{
		HintUI* hint = gLawnApp->CreateHintUI();
		if (hint != nullptr)
		{
			hint->Default1Init();
			hint->SetTitleString(L"[NATIONDAY_7DAYS_AWARD_OUT_TITLE]");
			hint->SetContentString(L"[NATIONDAY_7DAYS_AWARD_OUT_DES]");
			hint->ShowHintUI();
		}
	}
}

void INetworkMsgProcess::OnICloudRequestGetSpringLoginReward(const NetWorkMsg& i_data)
{
	if (i_data.erro == 0)
	{
		S2C_7DaysLoginSpringReward reward;
		if (reward.SerializeJson(i_data.msg))
		{
			gMessageRouter->Post(LoginRewardSpringMsg, true, &reward);
		}
	}
	else if (i_data.erro == 10201)
	{
		HintUI* hint = gLawnApp->CreateHintUI();
		if (hint != nullptr)
		{
			hint->Default1Init();
			hint->SetTitleString(L"[NATIONDAY_7DAYS_AWARD_OUT_TITLE]");
			hint->SetContentString(L"[NATIONDAY_7DAYS_AWARD_OUT_DES]");
			hint->ShowHintUI();
		}
	}
}

void INetworkMsgProcess::OnICloudRequestBuyZMatchTicket(const NetWorkMsg& i_data)
{
	Sexy::OutputDebugStrF("INetworkMsgProcess::OnICloudRequestBuyZMatchTicket %d ", i_data.erro);
	if (i_data.erro == 0)
	{
		gMessageRouter->Post(BuyZMatchTicketMsg, true);
	}
	else if (i_data.erro == 45011)
	{
		UIMessageBox* box = UISingletonDialog<UIMessageBox>::ShowDialog();
		if (box != nullptr)
		{
			box->SetShowType(UIMessageBox::Type_ShowOK);
			box->SetMessage(std::string("[ZMATCHSHOP_BUYTIMES_LIMIT]"), std::string("[REVIVE_TIP]"));
			box->SetTextFont(117);
			box->SetTitleFont(117);
			box->SetTextColor(Sexy::Color(Sexy::Color::White));
		}
	}
}

void INetworkMsgProcess::onRequestUserName(const NetWorkMsg& i_data)
{
	AutoLock lock(std::function<void()>(nullptr), [this]() { m_requestUserNameCallback = nullptr; });
	if (i_data.erro == 0)
	{
		S2C_ICloud_GetUserInfo info;
		info.SerializeJson(i_data.msg);
		PlayerInfo* profile = ProfileUtils::Profile();
		if (profile != nullptr)
		{
			profile->SetGems(info.m_playerInfo.m_Gems);
		}
		if (m_requestUserNameCallback)
		{
			m_requestUserNameCallback->process(true);
		}
	}
	else if (m_requestUserNameCallback)
	{
		m_requestUserNameCallback->process(false);
	}
}

void INetworkMsgProcess::onRequestUserInfo(const NetWorkMsg& i_data)
{
	AutoLock lock(std::function<void()>(nullptr), [this]() { m_requestUserInfoCallback = nullptr; });
	if (i_data.erro == 0)
	{
		S2C_ICloud_GetUserInfo info;
		info.SerializeJson(i_data.msg);
		PlayerInfo* profile = ProfileUtils::Profile();
		if (profile != nullptr)
		{
			profile->SetGems(info.m_playerInfo.m_Gems);
		}
		if (m_requestUserInfoCallback)
		{
			m_requestUserInfoCallback->process(true);
		}
		gMessageRouter->Post(DeliverySendMsg, true);
	}
	else
	{
		if (m_requestUserInfoCallback)
		{
			m_requestUserInfoCallback->process(false);
		}
		gMessageRouter->Post(DeliverySendMsg, false);
	}
}
