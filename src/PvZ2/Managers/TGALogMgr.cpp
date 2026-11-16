//
//  TGALogMgr.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-04.
//

#include "SexyAppFramework/Common.h"

#include <algorithm>
#include <sstream>

#include "TGALogMgr.h"

#include "Cheats.h"
#include "DNode/DString.h"
#include "LawnApp.h"
#include "NameMapper.h"
#include "PlayerInfo.h"
#include "ProfileMgr.h"
#include "PVZDB.h"
#include "ServerConfig.h"
#include "TimeUtil.h"
#include "TutorialMgr.h"
#include "LogCollector/LogCollector.h"
#include "logServer/LogServer.h"
#include "SexyAppFramework/SexyAppBase.h"
#include "SexyAppFramework/drivers/app/android/JavaInterface.h"

/////////////// construction ///////////////

TGALogMgr::TGALogMgr()
{
	m_url = "";
	m_logId = "";
	m_sendMsg = "";
	m_logMsg = "";
	init();
	m_onlineEndTime = PVZ_EOT();
	m_onlineStartTime = PVZ_T();
}

TGALogMgr::~TGALogMgr()
{
}

void TGALogMgr::init()
{
	Sexy::RtDbTable* table = PVZDB::GetInstance().GetTable(PVZDB::TABLE_SERVER_CONFIG);
	if (table)
	{
		Sexy::RtObject* obj = table->GetObjectForId(table->GetIdForAlias(Sexy::RtName(_S("TGALogConfig"))));
		if (obj)
		{
			TGALogConfig* config = obj->CastChecked<TGALogConfig>();
			if (config)
				m_url = config->ShippingURL;
		}
	}
}

/////////////// message plumbing ///////////////

void TGALogMgr::appendMsg(const std::string& i_msg, bool i_last)
{
	m_sendMsg += i_msg;
	if (!i_last)
		m_sendMsg += "|";
}

bool TGALogMgr::needWriteLog()
{
	return false;
}

void TGALogMgr::writeLog(const std::string& i_msg)
{
	m_logMsg.append(i_msg);
	m_logMsg += "\n";

	std::string dir = "";
	dir = Android::Resources::GetExternalFilesDirectory((Sexy::AndroidAppDriver*)gLawnApp);
	std::string path = dir + "/" + "log_output.txt";

	Sexy::Buffer buffer;
	buffer.WriteBytes((const uchar*)m_logMsg.c_str(), m_logMsg.length());
	Sexy::gSexyAppBase->WriteBytesToFileEnd(path, buffer.GetDataPtr(), buffer.GetDataLen());
	m_logMsg.clear();
}

void TGALogMgr::requestSendMsg()
{
	Sexy::StructuredData data;
	data.BeginObject();
	data.AddString("url", m_url);
	data.BeginObject("postData");
	data.AddString("key", m_logId);
	data.AddString("message", m_sendMsg);
	data.EndObject();
	data.EndObject();
	Sexy::NetworkServiceManager::DefaultNetworkServiceManager()->MakeRequest(&data, this, this);
}

void TGALogMgr::sendMsg()
{
	if (needWriteLog())
		m_logMsg = m_sendMsg + "|";

	requestSendMsg();
	m_sendMsg.clear();
	m_logId.clear();
}

void TGALogMgr::sendLog(const DValue& value)
{
	if (value.isDValueVector() && !CheatManager::GetInstancePtr()->GetToggleValue("DisableTGALog"))
	{
		LogServer::Instance();

		DValueVector v = value.asDValueVector();
		for (int i = 0; i < v.size(); ++i)
		{
			bool last = i == v.size() - 1;
			appendMsg(v[i].asString(), last);
		}

		sendMsg();
	}
}

void TGALogMgr::Log(const std::string& i_logId, const std::vector<std::string>& i_params)
{
	m_logId = i_logId;

	Log_TGA log;
	DValue value;
	log.getLogInfo(m_logId, value).getBasicInfo(value).getOtherInfo(i_params, value);
	sendLog(value);
}

void TGALogMgr::UseLevelItem(const std::string& i_item, int i_freeGem, int i_useGem)
{
	std::vector<std::string> params;
	params.push_back(i_item);
	DString level = ProfileMgr::GetInstance().GetCurrentProfile()->GetCurrentLevel();
	params.push_back(level);
	std::string mode = BehaviorLog::getModeString();
	params.push_back(mode);
	params.push_back(DString(abs(i_freeGem)));
	params.push_back(DString(abs(i_useGem)));
	Log("10005", params);
}

/////////////// online session ///////////////

void TGALogMgr::UpdateFrame()
{
	UpdateOnlineLog();
}

void TGALogMgr::StartOnlineLog()
{
	m_onlineStartTime = PVZ_T();
}

void TGALogMgr::UpdateOnlineLog()
{
	if (TimeUtil::CheckTimeEclapse(600.0f, m_onlineStartTime))
	{
		TGAOnlineData info;
		info._time = "10";
		LogOnline(info);
		m_onlineStartTime = PVZ_T();
	}
}

/////////////// network callbacks ///////////////

void TGALogMgr::ServiceRequestCompleted(const Sexy::StructuredData* i_response, const void* i_context)
{
	if (!needWriteLog() || this != i_context)
		return;

	Sexy::StructuredData::Integer code = i_response->IntegerForPath("$.statusCode", -1);
	if (code == -1 || code == 200)
	{
		std::string response;
		response = i_response->StringForPath("$.code", "");
		writeLog(response);
	}
	else
	{
		ServiceRequestFailed(i_response, i_context);
	}
}

void TGALogMgr::ServiceRequestFailed(const Sexy::StructuredData* i_response, const void* i_context)
{
	if (!needWriteLog())
		return;

	if (this == i_context)
		writeLog("failed response");
}

/////////////// segments ///////////////

std::string TGALogMgr::GetSegForId(int i_logId, int i_index)
{
	std::vector<CustomSegment> segments;
	std::map<int, std::vector<CustomSegment> >::iterator it = m_segments.find(i_logId);
	if (it != m_segments.end())
		segments = (*it).second;

	if (segments.empty())
		return "";

	for (CustomSegment seg : segments)
	{
		if (seg.index == i_index)
			return seg.value;
	}
	return "";
}

void TGALogMgr::clearSegments(int i_id)
{
	std::map<int, std::vector<CustomSegment> >::iterator it = m_segments.find(i_id);
	if (it != m_segments.end())
		(*it).second.clear();
}

void TGALogMgr::LogSegments(int i_logId, int i_index, const std::string& i_param)
{
	m_segments[i_logId].push_back(CustomSegment(i_index, i_param));
}

void TGALogMgr::LogForLogin(const std::string& i_logId, const std::vector<std::string>& i_params)
{
	m_logId = i_logId;

	Log_TGA log;
	DValue value;
	log.getLogInfo(m_logId, value).getBasicInfoForLogin(value).getOtherInfo(i_params, value);
	sendLog(value);
}

void TGALogMgr::LogHeroPlant(const TGAHeroPlantData& i_info)
{
}

/////////////// loggers ///////////////

void TGALogMgr::LogNoviceSevenDays(TGANoviceSevenDaysData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	if (TutorialMgr::GetInstancePtr() && TutorialMgr::GetInstancePtr()->GetNeedTutorial())
		params.push_back("1");
	else
		params.push_back("2");
	params.push_back(i_info._day);
	params.push_back(i_info._taskId);
	params.push_back(i_info._award);
	Log(DString(TGA_LOG_NOVICESEVENDAYS_TASK), params);
}

void TGALogMgr::LogJoust(int i_step, TGALogJoustData i_info)
{
	std::vector<std::string> params;
	params.push_back(DString(i_step));
	params.push_back(i_info._matchLevel);
	params.push_back(i_info._battleResult);
	params.push_back(i_info._freeGems);
	params.push_back(i_info._payGems);
	params.push_back(i_info._useZCoins);
	params.push_back(i_info._buyChallengeTimes);
	params.push_back(i_info._buyChallengeCost);
	params.push_back(i_info._buyPlantID);
	params.push_back(i_info._buyPlantCount);
	params.push_back(i_info._reward);
	for (int i = 0; i < 8; ++i)
		params.push_back(i_info._plantOnBoard[i]);
	params.push_back(i_info._artifactId);
	Log(DString(TGA_LOG_JOUST_ID), params);
}

void TGALogMgr::LogPlayerSurvey(TGAPlayerSurveyData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);

	for (const std::string& answer : i_info._answers)
		params.push_back(answer);

	params.push_back(i_info._rewards);
	Log(DString(TGA_LOG_PLAYER_SURVEY), params);
}

void TGALogMgr::LogAccountRemove(TGAAccountRemove i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	Log(DString(TGA_LOG_ACCOUNT_REMOVE), params);
}

void TGALogMgr::LogAdsLottery(TGAAdsLotteryData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._reward);
	Log(DString(TGA_LOG_ADS_LOTTERY), params);
}

void TGALogMgr::LogAnniversaryNurturingData(const TGAAnniversaryNurturingData& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._plantId);
	params.push_back(i_info._growthValue);
	params.push_back(i_info._taskId);
	params.push_back(i_info._goodsId);
	params.push_back(i_info._diamondsConsumedNum);
	params.push_back(i_info._reward);
	Log(DString(TGA_LOG_ANNIVERSARY_NURTURING), params);
}

void TGALogMgr::LogAnniversaryTreasure(TGAAnniversaryTreasureData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._isFree);
	params.push_back(i_info._theAwardInfo);
	params.push_back(i_info._getFreeGems);
	params.push_back(i_info._getPaidGems);
	params.push_back(i_info._useFreeGems);
	params.push_back(i_info._usePaidGems);
	params.push_back(i_info._poolNumber);
	params.push_back(i_info._rewardType);
	params.push_back(i_info._rewardInfo);
	Log(DString(TGA_LOG_ANNIVERSARY_TREASURE), params);
}

void TGALogMgr::LogAppLaunch(TGAAppLaunch i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	LogForLogin(DString(TGA_LOG_LAUNCH_APP), params);
}

void TGALogMgr::LogArborDay(const TGAArborDay& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._kettleNum);
	params.push_back(i_info._kettleChange);
	params.push_back(i_info._reward);
	params.push_back(i_info._taskID);
	params.push_back(i_info._useGem);
	params.push_back(i_info._freeGem);
	Log(DString(TGA_LOG_ARBORDAY), params);
}

void TGALogMgr::LogArtifactCultivation(const TGArtifactCultivation& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._content);
	params.push_back(i_info._levelupMat);
	params.push_back(i_info._rankupMat);
	params.push_back(i_info._artifactId);
	params.push_back(i_info._levelorRank);
	Log(DString(TGA_LOG_ARTIFACT_CULTIVATION), params);
}

void TGALogMgr::LogArtifactPresent(TGAArtifactPresentData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._artifactId);
	params.push_back(i_info._price);
	params.push_back(i_info._sku);
	params.push_back(i_info._rewards);
	Log(DString(TGA_LOG_ARTIFACT_PRESENT), params);
}

void TGALogMgr::LogBag(TGABagData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	Log(DString(TGA_LOG_BAG), params);
}

void TGALogMgr::LogBattleOrderInfo(const TGABattleOrderData& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._level);
	params.push_back(i_info._exp);
	params.push_back(i_info._privilege);
	params.push_back(i_info._gemNumber);
	params.push_back(i_info._gemChange);
	params.push_back(i_info._award);
	params.push_back(i_info._taskId);
	params.push_back(i_info._sku);
	params.push_back(i_info._price);
	Log(DString(TGA_LOG_BATTLE_ORDER), params);
}

void TGALogMgr::LogBossChallenge(TGABossChallengeData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._materialNum);
	params.push_back(i_info._buyGemCost);
	params.push_back(i_info._buyMaterialNum);
	params.push_back(i_info._levelID);
	params.push_back(i_info._result);
	params.push_back(i_info._getMaterialCount);
	params.push_back(i_info._itemID);
	params.push_back(i_info._itemCount);
	params.push_back(i_info._luckyMaxItemID);
	params.push_back(i_info._luckyMaxItemCount);
	params.push_back(i_info._lotteryTimes);
	params.push_back(i_info._artifactId);
	Log(DString(TGA_LOG_BOSS_CHALLENGE_ID), params);
}

void TGALogMgr::LogCallofWishDaily(const TGACallofWishDaily& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._price);
	params.push_back(i_info._key);
	params.push_back(i_info._award);
	Log(DString(TGA_LOG_CALL_OF_WISH_DAILY), params);
}

void TGALogMgr::LogCallofWishDraw(const TGACallofWishDraw& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._callTimes);
	params.push_back(i_info._useTicket);
	params.push_back(i_info._useFreeGem);
	params.push_back(i_info._useGem);
	params.push_back(i_info._award);
	params.push_back(i_info._wishPlantId);
	Log(DString(TGA_LOG_CALL_OF_WISH_DRAW), params);
}

void TGALogMgr::LogCallofWishGift(const TGACallofWishGift& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._index);
	params.push_back(i_info._callTimes);
	params.push_back(i_info._award);
	Log(DString(TGA_LOG_CALL_OF_WISH_GIFT), params);
}

void TGALogMgr::LogCallofWishLimit(const TGACallofWishLimit& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._price);
	params.push_back(i_info._key);
	params.push_back(i_info._award);
	Log(DString(TGA_LOG_CALL_OF_WISH_LIMIT), params);
}

void TGALogMgr::LogCallofWishTask(const TGACallofWishTask& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._taskId);
	params.push_back(i_info._activity);
	params.push_back(i_info._gotTicket);
	params.push_back(i_info._award);
	Log(DString(TGA_LOG_CALL_OF_WISH_TASK), params);
}

void TGALogMgr::LogCallofWishTrain(const TGACallofWishTrain& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._index);
	params.push_back(i_info._award);
	Log(DString(TGA_LOG_CALL_OF_WISH_TRAIN), params);
}

void TGALogMgr::LogCardGame(const TGACardGameData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._level);
	params.push_back(i_info._result);
	params.push_back(i_info._cardId);
	params.push_back(i_info._star);
	params.push_back(i_info._reward);
	Log(DString(TGA_LOG_CARD_GAME), params);
}

void TGALogMgr::LogCarnivalData(const TGACarnivalData& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._material);
	params.push_back(i_info._materialChange);
	params.push_back(i_info._buyBundleID);
	params.push_back(i_info._buyBundleTimes);
	params.push_back(i_info._award);
	Log(DString(TGA_LOG_CARNIVAL), params);
}

void TGALogMgr::LogClearProfile(const TGAClearProfileData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._oldUserID);
	params.push_back(i_info._newUserID);
	Log(DString(TGA_LOG_CLEAR_PROFILE), params);
}

void TGALogMgr::LogCoin(int coins, int freeGems, int payGems)
{
	std::vector<std::string> params;
	params.push_back(DString(coins));
	params.push_back(DString(freeGems));
	params.push_back(DString(payGems));
	Log(DString(TGA_LOG_COIN_ID), params);
}

void TGALogMgr::LogConsumeReceive(TGAConsumeReceiveData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._gemsAmt);
	params.push_back(i_info._plantPieceId);
	params.push_back(i_info._plantPieceAmt);
	params.push_back(i_info._activityId);
	params.push_back(i_info._abtestId);
	Log(DString(TGA_LOG_CONSUMERECEIVE_ID), params);
}

void TGALogMgr::LogConsumeReceiveExtra(TGAConsumeReceiveData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._gemsAmt);
	params.push_back(i_info._plantPieceId);
	params.push_back(i_info._plantPieceAmt);
	params.push_back(i_info._activityId);
	params.push_back(i_info._abtestId);
	Log(DString(TGA_LOG_CONSUMERECEIVE_EXTRA_ID), params);
}

void TGALogMgr::LogCornucopiaData(const TGACornucopiaData& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._tickets);
	params.push_back(i_info._emblems);
	params.push_back(i_info._level);
	params.push_back(i_info._taskId);
	params.push_back(i_info._gachaType);
	params.push_back(i_info._reward);
	Log(DString(TGA_LOG_CORNUCOPIA), params);
}

void TGALogMgr::LogCrack(TGACrackData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._freeGems);
	params.push_back(i_info._paidGems);
	params.push_back(i_info._content);
	Log(DString(TGA_LOG_CRACK_ID), params);
}

void TGALogMgr::LogCustomLevelAD(const TGACustomLevelADData& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._level);
	params.push_back(i_info._viewId);
	params.push_back(i_info._viewType);
	params.push_back(i_info._authorId);
	Log(DString(TGA_LOG_CUSTOM_LEVEL_AD), params);
}

void TGALogMgr::LogCustomLevelShare(const TGACustomLevelShareData& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._level);
	params.push_back(i_info._self);
	params.push_back(i_info._platform);
	params.push_back(i_info._result);
	params.push_back(i_info._reward);
	Log(DString(TGA_LOG_CUSTOM_LEVEL_SHARE), params);
}

void TGALogMgr::LogCustomVoting(TGACustomVoting i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._plantId);
	params.push_back(i_info._tNumber);
	params.push_back(i_info._reward);
	Log(DString(TGA_LOG_CUSTOM_VOTING), params);
}

void TGALogMgr::LogDailyRechargeReward(TGADailyRechargeReward i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._buyItemID);
	params.push_back(i_info._cost);
	params.push_back(i_info._plantChipId);
	params.push_back(i_info._plantChipamount);
	params.push_back(i_info._avatarChipId);
	params.push_back(i_info._avatarChipamount);
	Log(DString(TGA_LOG_DAILY_RECHARGE_ID), params);
}

void TGALogMgr::LogDailySign(int totalSignDays, int basicSignDays, std::string bonus)
{
	std::vector<std::string> params;
	params.push_back(DString(totalSignDays));
	params.push_back(DString(basicSignDays));
	params.push_back(bonus);
	Log(DString(TGA_LOG_DAILY_SIGN_ID), params);
}

void TGALogMgr::LogDailySignActivity(TGADailySignActivity i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._signDays);
	params.push_back(i_info._rewards);
	Log(DString(TGA_LOG_DAILYSIGN_ACTIVITY_ID), params);
}

void TGALogMgr::LogDangerRoomSpecialOffer(TGADangerRoomSpecialOfferData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._bundleId);
	params.push_back(i_info._plantId);
	params.push_back(i_info._price);
	Log(DString(TGA_LOG_DANGERROOM_SPECIAL_OFFER_ID), params);
}

void TGALogMgr::LogDaveKitchenData(const TGADaveKitchenData& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._exchangeContent);
	params.push_back(i_info._bundleId);
	params.push_back(i_info._costValue);
	params.push_back(i_info._taskId);
	params.push_back(i_info._taskReward);
	Log(DString(TGA_LOG_DAVEKITCHEN), params);
}

void TGALogMgr::LogDaveTreasure(int i_step, TGALogDaveTreasureData i_info)
{
	std::vector<std::string> params;
	params.push_back(DString(i_step));
	params.push_back(i_info._itemID);
	params.push_back(i_info._cost);
	params.push_back(i_info._sumItemType);
	params.push_back(i_info._sumItemLevel);
	params.push_back(i_info._missionType);
	params.push_back(i_info._missionID);
	params.push_back(i_info._missionItemID);
	params.push_back(i_info._sumItemReward);
	Log(DString(TGA_LOG_DAVE_TREASURE_ID), params);
}

void TGALogMgr::LogDebugInfo(const TGADebugInfoData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._info);
	Log(DString(TGA_LOG_DEBUG_INFO), params);
}

void TGALogMgr::LogDecorateData(const TGALogPlantDecorate& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._exchange_avatar);
	params.push_back(i_info._exchange_accessory);
	params.push_back(i_info._exchange_avatar_pieces_count);
	params.push_back(i_info._buy_cost);
	params.push_back(i_info._sold_cost);
	params.push_back(i_info._levelup_accessory_level);
	params.push_back(i_info._levelup_accessory_consume);
	Log(DString(TGA_LOG_PLANT_DECORATE), params);
}

void TGALogMgr::LogDiamond(std::string description, int useFreeGem, int usePayGem, int getFreeGem, int getPayGem)
{
	std::vector<std::string> params;
	params.push_back(description);
	params.push_back(DString(useFreeGem));
	params.push_back(DString(usePayGem));
	params.push_back(DString(getFreeGem));
	params.push_back(DString(getPayGem));
	Log(DString(TGA_LOG_DIAMOND_ID), params);
}

void TGALogMgr::LogDiscountShop(TGADiscountShopData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._reward);
	params.push_back(i_info._freeGems);
	params.push_back(i_info._paidGems);
	Log(DString(TGA_LOG_DISCOUNT_SHOP_ACTIVITY), params);
}

void TGALogMgr::LogDragonTreasure(const TGADragonTreasureData& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._crystal);
	params.push_back(i_info._integral);
	params.push_back(i_info._bigAward);
	params.push_back(i_info._crystalCost);
	params.push_back(i_info._integralCost);
	params.push_back(i_info._productId);
	params.push_back(i_info._price);
	params.push_back(i_info._reward);
	Log(DString(TGA_LOG_DRAGONTREASURE), params);
}

void TGALogMgr::LogFestivalRedPacket(TGAFestivalRedPacketData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._isFree);
	params.push_back(i_info._freeGems);
	params.push_back(i_info._paidGems);
	params.push_back(i_info._content);
	Log(DString(TGA_LOG_FESTIVAL_RED_PACKET_ID), params);
}

void TGALogMgr::LogFightZodiac(TGAFightZodiac i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._crackerTotal);
	params.push_back(i_info._crackerUse);
	params.push_back(i_info._crackerBehave);
	params.push_back(i_info._zodiacHitPoint);
	params.push_back(i_info._zodiacIndex);
	params.push_back(i_info._reward);
	params.push_back(i_info._product);
	Log(DString(TGA_LOG_FIGHT_ZODIAC), params);
}

void TGALogMgr::LogFirstRecharge(TGAFirstRechargeData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._bonus);
	params.push_back(i_info._recharge);
	params.push_back(i_info._gems);
	Log(DString(TGA_LOG_FIRSTRECHARGE), params);
}

void TGALogMgr::LogFirstRechargeNew(const TGAFirstRechargeNewData& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._day);
	params.push_back(i_info._tab);
	params.push_back(i_info._reward);
	Log(DString(TGA_LOG_FIRSTRECHARGE_NEW), params);
}

void TGALogMgr::LogFoolChallenge(TGAFoolData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._isPass);
	params.push_back(i_info._eggNum);
	params.push_back(i_info._exchangeId);
	params.push_back(i_info._exchangeAmount);
	params.push_back(i_info._exchangeUseEgg);
	params.push_back(i_info._bundlePrice);
	params.push_back(i_info._bundleToolsId);
	params.push_back(i_info._bundleEggAmont);
	params.push_back(i_info._challengeAward);
	Log(DString(TGA_LOG_FOOL_CHALLENGE), params);
}

void TGALogMgr::LogGeneEnhancementData(const TGAGeneEnhancementData& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._factor);
	params.push_back(i_info._exhaust);
	params.push_back(i_info._sequence);
	params.push_back(i_info._level);
	params.push_back(i_info._currency);
	params.push_back(i_info._award);
	Log(DString(TGA_LOG_GENE_ENHANCEMENT), params);
}

void TGALogMgr::LogGetAccessory(const TGAccessoryData& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._award);
	Log(DString(TGA_LOG_EXCHANGE_ACCESSORY), params);
}

void TGALogMgr::LogGiftReturnData(const TGAGiftReturnData& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._signDay);
	params.push_back(i_info._taskIntegral);
	params.push_back(i_info._taskId);
	params.push_back(i_info._mysteriousCrystal);
	params.push_back(i_info._reward);
	Log(DString(TGA_LOG_GIFT_RETURN), params);
}

void TGALogMgr::LogGoldenEgg(const TGAGoldenEgg& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._eggIndex);
	params.push_back(i_info._jackpotSelect);
	params.push_back(i_info._hammerNum);
	params.push_back(i_info._hammerConsume);
	params.push_back(i_info._hammerGotWay);
	params.push_back(i_info._taskID);
	params.push_back(i_info._award);
	params.push_back(i_info._jackpotGot);
	Log(DString(TGA_LOG_GOLDENEGG), params);
}

void TGALogMgr::LogGroupBuy(TGAGroupBuyData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._plantId);
	params.push_back(i_info._plantQuantity);
	params.push_back(i_info._coinAmt);
	params.push_back(i_info._usedDaveAmt);
	params.push_back(i_info._freeGems);
	params.push_back(i_info._paidGems);
	params.push_back(i_info._returnGems);
	Log(DString(TGA_LOG_GROUP_BUY_ID), params);
}

void TGALogMgr::LogGrowthPackage(const TGAGrowthPackage i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._integralNum);
	params.push_back(i_info._integralChange);
	params.push_back(i_info._useMoney);
	params.push_back(i_info._objectID);
	params.push_back(i_info._reward);
	Log(DString(TGA_LOG_GROWTHPACKAGE), params);
}

void TGALogMgr::LogHappyVaseBreaker(TGAHappyVaseBreakerData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._taskInfo);
	params.push_back(i_info._taskAward);
	params.push_back(i_info._vaseAwardID);
	params.push_back(i_info._vaseAwardAmount);
	params.push_back(i_info._isBigAward);
	params.push_back(i_info._hammerUse);
	Log(DString(TGA_LOG_HAPPY_VASE_BREAKER_ID), params);
}

void TGALogMgr::LogIOSRealNameLogin()
{
	static bool s_logged = false;
	if (s_logged)
		return;

	s_logged = true;
	std::vector<std::string> params;
	Log(DString(TGA_LOG_IOS_REAL_NAME_LOGIN), params);
}

void TGALogMgr::LogGiftCodeData(const std::string& i_code, const std::string& i_reward)
{
	std::vector<std::string> params;
	params.push_back(i_code);
	params.push_back(i_reward);
	Log(DString(TGA_LOG_GIFT_CODE), params);
}

void TGALogMgr::LogExchangeAvatar(const TGAExchangeAvatarData& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._avatarId);
	params.push_back(i_info._avatarName);
	params.push_back(i_info._costType);
	params.push_back(i_info._costId);
	params.push_back(i_info._costAmount);
	params.push_back(i_info._ownedCount);
	params.push_back(i_info._source);
	params.push_back(i_info._result);
	params.push_back(i_info._reward);
	Log(DString(TGA_LOG_EXCHANGE_AVATAR), params);
}

void TGALogMgr::LogTreasurePavilion(const TGATreasurePavilionData& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._activityId);
	params.push_back(i_info._poolId);
	params.push_back(i_info._drawType);
	params.push_back(i_info._drawCount);
	params.push_back(i_info._costType);
	params.push_back(i_info._costAmount);
	params.push_back(i_info._rewardId);
	params.push_back(i_info._rewardAmount);
	Log(DString(TGA_LOG_TREASURE_PAVILION), params);
}

void TGALogMgr::LogPennyGiftBox(const TGAPennyGiftBoxData& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._boxId);
	params.push_back(i_info._boxType);
	params.push_back(i_info._costType);
	params.push_back(i_info._costAmount);
	params.push_back(i_info._rewardId);
	params.push_back(i_info._rewardAmount);
	params.push_back(i_info._openCount);
	Log(DString(TGA_LOG_PENNY_GIFT_BOX), params);
}

void TGALogMgr::LogNFSLinkage(const TGANFSLinkageData& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._taskId);
	params.push_back(i_info._progress);
	params.push_back(i_info._rewardId);
	params.push_back(i_info._rewardAmount);
	Log(DString(TGA_LOG_NFS_LINKAGE), params);
}

void TGALogMgr::LogAccumulatedLogin(const TGAAccumulatedLoginData& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._day);
	params.push_back(i_info._rewardId);
	params.push_back(i_info._rewardAmount);
	Log(DString(TGA_LOG_ACCUMULATED_LOGIN), params);
}

void TGALogMgr::LogLuckyChest(const TGALuckyChestData& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._chestId);
	params.push_back(i_info._costType);
	params.push_back(i_info._costAmount);
	params.push_back(i_info._rewardId);
	params.push_back(i_info._rewardAmount);
	params.push_back(i_info._drawCount);
	Log(DString(TGA_LOG_LUCKY_CHEST), params);
}

void TGALogMgr::LogLuckyChestShop(const TGALuckyChestShopData& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._goodsId);
	params.push_back(i_info._costType);
	params.push_back(i_info._costAmount);
	Log(DString(TGA_LOG_LUCKY_CHEST_SHOP), params);
}

void TGALogMgr::LogPlantWars(const TGAPlantWarsData& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._levelId);
	params.push_back(i_info._result);
	params.push_back(i_info._plantId);
	params.push_back(i_info._plantLevel);
	params.push_back(i_info._useTime);
	params.push_back(i_info._score);
	params.push_back(i_info._reward);
	Log(DString(TGA_LOG_PLANT_WARS), params);
}

void TGALogMgr::LogAutumnHarvest(const TGAAutumnHarvestData& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._taskId);
	params.push_back(i_info._progress);
	params.push_back(i_info._costType);
	params.push_back(i_info._costAmount);
	params.push_back(i_info._rewardId);
	params.push_back(i_info._rewardAmount);
	Log(DString(TGA_LOG_AUTUMN_HARVEST), params);
}

void TGALogMgr::LogTourismOctoberData(const TGATourismOctoberData& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._taskId);
	params.push_back(i_info._progress);
	params.push_back(i_info._costType);
	params.push_back(i_info._costAmount);
	params.push_back(i_info._rewardId);
	params.push_back(i_info._rewardAmount);
	params.push_back(i_info._stageId);
	params.push_back(i_info._result);
	Log(DString(TGA_LOG_TOURISM_OCTOBER), params);
}

void TGALogMgr::LogToyNightData(const TGAToyNightData& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._levelId);
	params.push_back(i_info._result);
	params.push_back(i_info._toyId);
	params.push_back(i_info._toyLevel);
	params.push_back(i_info._costType);
	params.push_back(i_info._costAmount);
	params.push_back(i_info._rewardId);
	params.push_back(i_info._rewardAmount);
	Log(DString(TGA_LOG_TOY_NIGHT), params);
}

void TGALogMgr::LogMiniGameCollectionData(const TGAMiniGameCollectionData& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._gameId);
	params.push_back(i_info._result);
	params.push_back(i_info._score);
	params.push_back(i_info._rewardId);
	params.push_back(i_info._rewardAmount);
	Log(DString(TGA_LOG_MINIGAME_COLLECTION), params);
}

void TGALogMgr::LogPlantPediaData(const TGAPlantPediaData& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._plantId);
	params.push_back(i_info._pageId);
	params.push_back(i_info._reward);
	Log(DString(TGA_LOG_PLANT_PEDIA), params);
}

void TGALogMgr::LogLuckBag(TGALuckBagData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	for (int i = 0; i < 6; ++i)
		params.push_back(i_info._plantSelect[i]);
	params.push_back(i_info._plantReward[0]);
	params.push_back(i_info._plantReward[1]);
	params.push_back(i_info._price);
	Log(DString(TGA_LOG_LUCKBAG), params);
}

void TGALogMgr::LogEndless(TGALogEndlessData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._medalCost);
	params.push_back(i_info._coinCost);
	params.push_back(i_info._freeGems);
	params.push_back(i_info._payGems);
	params.push_back(i_info._purchaseID);
	params.push_back(i_info._levelID);
	params.push_back(i_info._levelResult);
	if (i_info._usedPlants.empty())
	{
		for (int i = 0; i < 8; ++i)
			params.push_back("");
	}
	else
	{
		for (std::string plant : i_info._usedPlants)
			params.push_back(plant);
	}
	params.push_back(i_info._time);
	params.push_back(i_info._artifactId);
	Log(DString(TGA_LOG_ENDLESS_ID), params);
}

void TGALogMgr::LogTransGenosis(int i_step, TGALogTransGenosisData i_info)
{
	std::vector<std::string> params;
	params.push_back(DString(i_step));
	for (int i = 0; i < 5; ++i)
		params.push_back(i_info._slots[i]);
	params.push_back(i_info._transCost);
	params.push_back(i_info._freeGems);
	params.push_back(i_info._payGems);
	params.push_back(i_info._resultPieceID);
	Log(DString(TGA_LOG_TRANSGENOSIS_ID), params);
}

void TGALogMgr::LogAD(std::string i_step, std::string i_level, int i_pos, std::string i_rewardType, std::string i_rewardQuantity)
{
	std::vector<std::string> params;
	params.push_back(DString(i_step).c_str());
	params.push_back(i_level);
	params.push_back(DString(i_pos).c_str());
	params.push_back(DString(i_rewardType).c_str());
	params.push_back(DString(i_rewardQuantity).c_str());
	Log(DString(TGA_LOG_AD_ID), params);
}

void TGALogMgr::LogAD(std::string i_step, std::string i_level, std::string placementID, std::string i_rewardType, std::string i_rewardQuantity)
{
	std::vector<std::string> params;
	params.push_back(DString(i_step).c_str());
	params.push_back(i_level);
	params.push_back(placementID);
	params.push_back(DString(i_rewardType).c_str());
	params.push_back(DString(i_rewardQuantity).c_str());
	Log(DString(TGA_LOG_AD_ID), params);
}

void TGALogMgr::LogPVZ1Mode(const TGAPVZ1ModeData& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._level);
	params.push_back(i_info._difficulty);
	params.push_back(i_info._win);
	params.push_back(i_info._time);
	if (i_info._usedPlants.empty())
	{
		for (int i = 0; i < 8; ++i)
			params.push_back("");
	}
	else
	{
		for (std::string plant : i_info._usedPlants)
			params.push_back(plant);
	}
	params.push_back(i_info._levelReward);
	params.push_back(i_info._shopReward);
	Log(DString(TGA_LOG_PVZ1MODE), params);
}

void TGALogMgr::LogCustomLevel(const TGACustomLevelData& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._playCoin);
	params.push_back(i_info._createCoin);
	params.push_back(i_info._playCoinChange);
	params.push_back(i_info._createCoinChange);
	params.push_back(i_info._worldsFilter);
	params.push_back(i_info._levelModeFilter);
	params.push_back(i_info._levelID);
	params.push_back(i_info._zanCount);
	params.push_back(i_info._caiCount);
	params.push_back(i_info._createLevelAction);
	params.push_back(i_info._createLevelMode);
	params.push_back(i_info._shopItemBuy);
	params.push_back(i_info._challengeResult);
	if (i_info._usedPlants.empty())
	{
		for (int i = 0; i < 8; ++i)
			params.push_back("");
	}
	else
	{
		for (std::string plant : i_info._usedPlants)
			params.push_back(plant);
	}
	Log(DString(TGA_LOG_CUSTOMLEVEL), params);
}

void TGALogMgr::LogFirstRecharge(int i_step, const std::map<int, int>& i_rewards)
{
	DString reward;
	std::vector<std::string> params;
	int gemCount = 0;
	params.push_back(DString(i_step));

	for (const std::pair<const int, int>& kv : i_rewards)
	{
		int id = kv.first;
		int count = kv.second;
		if (NameMapperBase::GemServerID != id)
			reward += DString(id);
		else
			gemCount = count;
	}

	params.push_back(reward);
	params.push_back(GetSegForId(TGA_LOG_FIRSTRECHARGE, 0));
	params.push_back(DString(gemCount));
	Log(DString(TGA_LOG_FIRSTRECHARGE), params);
	clearSegments(TGA_LOG_FIRSTRECHARGE);
}

void TGALogMgr::LogRechargeBundle(TGARechargeBundleData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._rechargeAmt);
	params.push_back(i_info._purchaseId);
	params.push_back(i_info._purchasePrice);
	params.push_back(i_info._coinsAmt);
	params.push_back(i_info._gemsAmt);

	for (int i = 0; i < 5; ++i)
	{
		if (i_info._plantBundles[i]._quantity != 0 && i_info._plantBundles[i]._objectId != 0)
		{
			params.push_back(DString(i_info._plantBundles[i]._objectId).c_str());
			params.push_back(DString(i_info._plantBundles[i]._quantity).c_str());
		}
		else
		{
			params.push_back("");
			params.push_back("");
		}
	}

	for (int i = 0; i < 5; ++i)
	{
		if (i_info._itemBundles[i]._quantity != 0 && i_info._itemBundles[i]._objectId != 0)
		{
			params.push_back(DString(i_info._itemBundles[i]._objectId).c_str());
			params.push_back(DString(i_info._itemBundles[i]._quantity).c_str());
		}
		else
		{
			params.push_back("");
			params.push_back("");
		}
	}

	Log(DString(TGA_LOG_RECHARGE_BUNDLE_ID), params);
}

void TGALogMgr::LogPlantAdventure(int i_step, PlantAdventureInfo i_info, int i_cd)
{
	std::vector<std::string> params;
	params.push_back(DString(i_step));
	params.push_back(DString(i_info.dungeonId));

	std::string time = "";
	if (i_cd != 0)
		time = Sexy::StrFormat("%02d:%02d:00", (i_cd / 60) % 60, i_cd % 60);
	params.push_back(time);

	std::sort(i_info.plantIdList.begin(), i_info.plantIdList.end());
	std::stringstream ss;
	ss.str("");
	for (size_t i = 0; i < i_info.plantIdList.size(); ++i)
	{
		if (i == i_info.plantIdList.size() - 1)
			ss << DString(i_info.plantIdList[i]).c_str();
		else
			ss << DString(i_info.plantIdList[i]).c_str() << ",";
	}
	params.push_back(ss.str());
	params.push_back("0");

	int price = 0;
	if (i_step == 3)
		price = 20;
	else if (i_step == 5)
		price = i_info.surprisePrice;
	params.push_back(DString(price));

	std::string chip = "";
	if (i_info.plantChipId != -1)
		chip += DString(i_info.plantChipId).c_str();
	params.push_back(chip);
	params.push_back(DString(i_info.plantChipQuantity));
	params.push_back(DString(i_info.coinBonus));
	Log("10007", params);
}

void TGALogMgr::LogInvitationData(const TGAInvitationData& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._invitationCode);
	params.push_back(i_info._coinNum);
	params.push_back(i_info._taskId);
	params.push_back(i_info._reward);
	Log(DString(TGA_LOG_INVITATION), params);
}

void TGALogMgr::LogLevelPackageData(const TGALevelPackageData& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._packageID);
	params.push_back(i_info._reward);
	params.push_back(i_info._price);
	params.push_back(i_info._worldName);
	params.push_back(i_info._worldStarsCount);
	Log(DString(TGA_LOG_LEVEL_PACKAGE), params);
	clearSegments(TGA_LOG_LEVEL_PACKAGE);
}

void TGALogMgr::LogLimitedGacha(TGALimitedGachaData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._price);
	params.push_back(i_info._freeGems);
	params.push_back(i_info._paidGems);
	params.push_back(i_info._rewards);
	Log(DString(TGA_LOG_LIMITED_GACHA_ID), params);
}

void TGALogMgr::LogLimitedLottery(TGALimitedLotteryData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._drawAmt);
	params.push_back(i_info._crystalCost);
	params.push_back(i_info._bundleId);
	params.push_back(i_info._bundlePrice);
	params.push_back(i_info._crystalAmt);
	params.push_back(i_info._itemId);
	Log(DString(TGA_LOG_LIMITED_LOTTERY_ID), params);
}

void TGALogMgr::LogLimitedSummon(const TGALimitedSummonData& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._level);
	params.push_back(i_info._price);
	params.push_back(i_info._isfree);
	params.push_back(i_info._award);
	params.push_back(i_info._skuAward);
	Log(DString(TGA_LOG_LIMITED_SUMMON), params);
}

void TGALogMgr::LogMinigame(int i_step, TGALogMinigameData i_info)
{
	std::vector<std::string> params;
	params.push_back(DString(i_step));
	params.push_back(i_info._result);
	params.push_back(i_info._coinsAward);
	params.push_back(i_info._freeGemNum);
	params.push_back(i_info._payGemNum);
	params.push_back(i_info._plantPiecesNum);
	params.push_back(i_info._changePlantPieceID);
	params.push_back(i_info._changePlantPieceNum);
	params.push_back(i_info._usedCoinsNum);
	Log(DString(TGA_LOG_MINIGAME_ID), params);
}

void TGALogMgr::LogMinorLottery(TGAMinorLotteryData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._currentLuck);
	params.push_back(i_info._afterLuck);
	params.push_back(i_info._specialId);
	params.push_back(i_info._specialQuantity);
	params.push_back(i_info._drawAmt);
	params.push_back(i_info._freeGems);
	params.push_back(i_info._paidGems);
	params.push_back(i_info._getSpecial);
	params.push_back(i_info._rewards);
	Log(DString(TGA_LOG_MINOR_LOTTERY_ID), params);
}

void TGALogMgr::LogMonthlyCardSpecial(TGAMonthlyCardSpecialData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._itemID);
	params.push_back(i_info._cost);
	Log(DString(TGA_LOG_MONTHLY_CARD_SPECIAL), params);
}

void TGALogMgr::LogMysteryStore(TGAMysteryStore i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._rewards);
	params.push_back(i_info._getType);
	params.push_back(i_info._bundleId);
	params.push_back(i_info._cost);
	Log(DString(TGA_LOG_MYSTERY_STORE), params);
	clearSegments(TGA_LOG_MYSTERY_STORE);
}

void TGALogMgr::LogNewPVP(TGANewPVPData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._selfMatchingScore);
	params.push_back(i_info._rank);
	params.push_back(i_info._levelTime);
	params.push_back(i_info._oppoentMatchingScore);
	params.push_back(i_info._endTurn);
	params.push_back(i_info._selectedPlants);
	params.push_back(i_info._area);
	params.push_back(i_info._endResult);
	params.push_back(i_info._endRank);
	params.push_back(i_info._upgradeSun);
	params.push_back(i_info._upgradeSunTurn);
	params.push_back(i_info._addPlant);
	params.push_back(i_info._addZombie);
	params.push_back(i_info._selectedZombies);
	params.push_back(i_info._selectedZombiesDmg);
	params.push_back(i_info._zombieUpgradeSpeed);
	params.push_back(i_info._zombieUpgradeHP);
	params.push_back(i_info._zombieUpgradeBerserk);
	params.push_back(i_info._oppoentZombieMergeCount);
	params.push_back(i_info._oppoentZombieMergeHighestLevel);
	params.push_back(i_info._reward);
	params.push_back(i_info._selfProfileId);
	params.push_back(i_info._oppoentProfileId);
	params.push_back(i_info._taskLevel);
	params.push_back(i_info._taskExp);
	params.push_back(i_info._isAdv);
	params.push_back(i_info._coinAmount);
	params.push_back(i_info._coinAmountDelta);
	params.push_back(i_info._taskId);
	params.push_back(i_info._buyItem);
	Log(DString(TGA_LOG_NEW_PVP), params);
}

void TGALogMgr::LogNewPVPPlus(TGANewPVPPlusData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._reward);
	params.push_back(i_info._cost);
	params.push_back(i_info._coinCost);
	params.push_back(i_info._inBattleZombies);
	params.push_back(i_info._levelUpId);
	params.push_back(i_info._levelUpLevel);
	Log(DString(TGA_LOG_NEW_PVP_PLUS), params);
}

void TGALogMgr::LogNewRecallBank(TGANewRecallBankData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._rewardId);
	params.push_back(i_info._selectId);
	params.push_back(i_info._rewardNumber);
	params.push_back(i_info._gemNumber);
	Log(DString(TGA_LOG_NEWRECALL_BANK), params);
}

void TGALogMgr::LogNewRecallBundle(TGANewRecallBundleData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._bundleId);
	params.push_back(i_info._rewards);
	params.push_back(i_info._gemNumber);
	params.push_back(i_info._price);
	Log(DString(TGA_LOG_NEWRECALL_BUNDLE), params);
}

void TGALogMgr::LogNewRecallSign(TGANewRecallSignData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._day);
	Log(DString(TGA_LOG_NEWRECALL_SIGN), params);
}

void TGALogMgr::LogNewYearGoodsData(const TGANewYearGoodsData& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._price);
	params.push_back(i_info._goods);
	Log(DString(TGA_LOG_NEWYEAR_GOODS), params);
}

void TGALogMgr::LogNewplayerCollectiontData(const TGANewplayerCollectionData& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._newplayer);
	params.push_back(i_info._signdays);
	params.push_back(i_info._specialgift_item_id);
	params.push_back(i_info._specialgift_cost);
	params.push_back(i_info._discount_cost);
	params.push_back(i_info._rewards);
	Log(DString(TGA_LOG_NEWPLAYER_COLLECTION), params);
}

void TGALogMgr::LogNewuserPresent(int i_step, std::string presentID, std::string description, int price)
{
	std::vector<std::string> params;
	params.push_back(DString(i_step));
	params.push_back(presentID);
	params.push_back(description);
	params.push_back(DString(price));
	Log(DString(TGA_LOG_NEWUSER_PRESENT_ID), params);
}

void TGALogMgr::LogOneYuanRedPacket(TGAOneYuanRedPacketData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._buyAmount);
	params.push_back(i_info._price);
	params.push_back(i_info._openAmount);
	params.push_back(i_info._rewards);
	Log(DString(TGA_LOG_ONE_YUAN_RED_PACKET_ID), params);
	clearSegments(TGA_LOG_ONE_YUAN_RED_PACKET_ID);
}

void TGALogMgr::LogOnline(const TGAOnlineData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._time);
	Log(DString(TGA_LOG_ONLINE), params);
}

void TGALogMgr::LogPVZ1Achievement(const TGAPVZ1Achievement& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._process);
	params.push_back(i_info._coin);
	params.push_back(i_info._taskId);
	params.push_back(i_info._award);
	Log(DString(TGA_LOG_PVZ1ACHIEVEMNET), params);
}

void TGALogMgr::LogPartyAssistData(const TGAPartyAssistData& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._tickets);
	params.push_back(i_info._currentLevel);
	params.push_back(i_info._item_id);
	params.push_back(i_info._task_id);
	params.push_back(i_info._reward);
	Log(DString(TGA_LOG_PARTY_ASSIST), params);
}

void TGALogMgr::LogPennyClassroom(const TGAPennyClassroomData& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._coin);
	params.push_back(i_info._coinChange);
	params.push_back(i_info._levelName);
	params.push_back(i_info._bonus);
	params.push_back(i_info._passLevel);
	Log(DString(TGA_LOG_PENNYCLASSROOM), params);
}

void TGALogMgr::LogPennyPursuit(TGAPennyPursuitData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._levelId);
	params.push_back(i_info._difficulty);
	params.push_back(i_info._isPass);
	params.push_back(i_info._award);
	params.push_back(i_info._freeGemReward);
	params.push_back(i_info._paidGemReward);
	params.push_back(i_info._freeGemUse);
	params.push_back(i_info._paidGemUse);
	params.push_back(i_info._rank);
	params.push_back(i_info._coinUse);
	params.push_back(i_info._time);
	params.push_back(i_info._artifactId);
	Log(DString(TGA_LOG_PENNY_PURSUIT), params);
}

void TGALogMgr::LogPennyTreasure(int i_step, TGALogPennyTreasureData i_info)
{
	std::vector<std::string> params;
	params.push_back(DString(i_step));
	params.push_back(i_info._gachaType);
	params.push_back(i_info._isFree);
	params.push_back(i_info._gachaTimes);
	params.push_back(i_info._freeGems);
	params.push_back(i_info._payGems);
	params.push_back(i_info._gachaItemDescription);
	Log(DString(TGA_LOG_PENNY_TREASURE_ID), params);
}

void TGALogMgr::LogPigBank(TGAPigBankData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._price);
	params.push_back(i_info._gems);
	params.push_back(i_info._day);
	Log(DString(TGA_LOG_PIGGYBANK_ID), params);
}

void TGALogMgr::LogPlantInfo(TGAPlantData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._plantLevel);
	params.push_back(i_info._plantId);
	Log(DString(TGA_LOG_PLANTINFO_REFRESH_ID), params);
}

void TGALogMgr::LogPlantLevelup(int i_step, TGALogPlantLevelupData i_info)
{
	std::vector<std::string> params;
	params.push_back(DString(i_step));
	params.push_back(i_info._plantID);
	params.push_back(i_info._level);
	params.push_back(i_info._usePlantPiecesCount);
	params.push_back(i_info._levelupCoinsCost);
	params.push_back(i_info._levelupNutritionCost);
	params.push_back(i_info._levelupFreeGemsCost);
	params.push_back(i_info._levelupPayGemCost);
	params.push_back(i_info._levelupSpecialPieceCost);
	Log(DString(TGA_LOG_PLANT_LEVELUP_ID), params);
}

void TGALogMgr::LogPlantSpecialOffer(TGAPlantSpecialOfferData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._bundleId);
	params.push_back(i_info._cost);
	params.push_back(i_info._getCoins);
	params.push_back(i_info._getGems);
	params.push_back(i_info._plantId);
	params.push_back(i_info._avatarId);
	Log(DString(TGA_LOG_PLANT_SPECIAL_OFFER_ID), params);
}

void TGALogMgr::LogPlantTrial(int i_step, int id, int freeGems, int payGems, int payCost)
{
	std::vector<std::string> params;
	params.push_back(DString(i_step));
	params.push_back(DString(id));
	params.push_back(DString(freeGems));
	params.push_back(DString(payGems));
	params.push_back(DString(payCost));
	Log(DString(TGA_LOG_PLANT_TRIAL_ID), params);
}

void TGALogMgr::LogPlayerReturn(const TGAPlayerReturnData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._day);
	Log(DString(TGA_LOG_PLAYER_RETURN), params);
}

void TGALogMgr::LogPurchase(TGALogPurchaseData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._itemID);
	params.push_back(i_info._cost);
	params.push_back(i_info._description);
	params.push_back(i_info._firstPayTime);
	params.push_back(i_info._firstPayCost);
	params.push_back(i_info._firstPayItem);
	params.push_back(i_info._firstPayLevel);
	params.push_back(i_info._totalPay);
	Log(DString(TGA_LOG_PURCHASE_ID), params);
}

void TGALogMgr::LogRechargeDailySign(TGARechargeDailySignData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._day);
	params.push_back(i_info._reward);
	params.push_back(i_info._gems);
	Log(DString(TGA_LOG_RECHARGE_DAILYSIGN_ACTIVITY), params);
}

void TGALogMgr::LogRechargeReward(int i_step, TGALogRechargeRewardData i_info)
{
	std::vector<std::string> params;
	params.push_back(DString(i_step));
	params.push_back(i_info._buyItemID);
	params.push_back(i_info._cost);
	params.push_back(i_info._gemsReward);
	params.push_back(i_info._plantPieceID);
	params.push_back(i_info._plantPieceNum);
	params.push_back(i_info._getPlantPieceID);
	params.push_back(i_info._getPlantPieceNum);
	Log(DString(TGA_LOG_RECHARGE_REWARD_ID), params);
}

void TGALogMgr::LogRenaissanceChallenge(TGARenaissanceChallengeData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._itemID);
	params.push_back(i_info._itemCount);
	params.push_back(i_info._levelID);
	params.push_back(i_info._result);
	params.push_back(i_info._artifactId);
	Log(DString(TGA_LOG_RENAISSANCE_CHALLENGE_ID), params);
}

void TGALogMgr::LogRichMan(TGARichManData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._getCoins);
	params.push_back(i_info._useCoins);
	params.push_back(i_info._useDices);
	params.push_back(i_info._rollNum);
	params.push_back(i_info._buyDices);
	params.push_back(i_info._buyDicesCost);
	params.push_back(i_info._getItemId);
	params.push_back(i_info._getItemQuantity);
	Log(DString(TGA_LOG_RICHMAN_ID), params);
	clearSegments(TGA_LOG_RICHMAN_ID);
}

void TGALogMgr::LogScrollbanner(TGAScrollbannerData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	Log(DString(TGA_LOG_SCROLLBANNER), params);
}

void TGALogMgr::LogSecretGacha(TGASecretGacha i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._plantId);
	params.push_back(i_info._cost);
	params.push_back(i_info._rewards);
	Log(DString(TGA_LOG_SECRET_GACHA_ID), params);
}

void TGALogMgr::LogSecretStore(TGASecretStore i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._isFree);
	params.push_back(i_info._bundleId);
	params.push_back(i_info._cost);
	params.push_back(i_info._rewards);
	params.push_back(i_info._getGems);
	Log(DString(TGA_LOG_SECRET_STORE), params);
}

void TGALogMgr::LogTenYearsData(const TGATenYearsData& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._sharedPage);
	params.push_back(i_info._reward);
	Log(DString(TGA_LOG_TEN_YEARS), params);
}

void TGALogMgr::LogTravelLog(int i_step, TGALogTravelLogData i_info)
{
	std::vector<std::string> params;
	params.push_back(DString(i_step));
	params.push_back(i_info._missionType);
	params.push_back(i_info._missionID);
	params.push_back(i_info._levelID);
	params.push_back(i_info._result);
	params.push_back(i_info._jumpToWorldID);
	params.push_back(i_info._missionReward);
	Log(DString(TGA_LOG_TRAVEL_LOG_ID), params);
}

void TGALogMgr::LogTutorial(TGATutorialData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._id);
	params.push_back(i_info._reward);
	Log(DString(TGA_LOG_TUTORIAL), params);
}

void TGALogMgr::LogUncharted(const TGAUnchartedData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._star);
	params.push_back(i_info._starChange);
	params.push_back(i_info._challengeSuccessNum);
	params.push_back(i_info._level);
	params.push_back(i_info._win);
	params.push_back(i_info._reward);
	params.push_back(i_info._is_battleorder);
	params.push_back(i_info._task_id);
	params.push_back(i_info._star_select);
	params.push_back(i_info._world_type);
	params.push_back(i_info._is_first_pass);
	params.push_back(i_info._use_hero);
	params.push_back(i_info._pass_time);
	params.push_back(i_info._boost_choose_cards_pool);
	params.push_back(i_info._boost_choose_card);
	params.push_back(i_info._hero_plant_skill);
	params.push_back(i_info._plant_board_record);
	Log(DString(TGA_LOG_UNCHARTED_MODE), params);
}

void TGALogMgr::LogVaseBreaker(TGAVaseBreakerData i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._levelId);
	params.push_back(i_info._result);
	params.push_back(i_info._usedSkill);
	params.push_back(i_info._coinAmt);
	params.push_back(i_info._plantPieceId);
	params.push_back(i_info._plantPieceAmt);
	Log(DString(TGA_LOG_VASEBREAKER_ID), params);
}

void TGALogMgr::LogWishingPoolData(const TGAWishingPoolData& i_info)
{
	std::vector<std::string> params;
	params.push_back(i_info._step);
	params.push_back(i_info._reward);
	params.push_back(i_info._price);
	params.push_back(i_info._lotteryType);
	Log(DString(TGA_LOG_WISHINGPOOL), params);
}
