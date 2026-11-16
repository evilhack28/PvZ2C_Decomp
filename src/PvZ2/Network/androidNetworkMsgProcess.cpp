//
//  androidNetworkMsgProcess.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-20.
//

#include "SexyAppFramework/Common.h"

#include "gameNetWork/androidNetworkMsgProcess.h"
#include "gameNetWork/events/NetWorkEvent.h"
#include "gameNetWork/HttpRequest.h"
#include "gameNetWork/NetworkMgr.h"
#include "gameNetWork/ACNetworkData.h"
#include "gameNetWork/pcpEncrypty/PCPEncrypt.h"
#include "LawnApp.h"
#include "MainMenu.h"
#include "AuthMgr.h"
#include "DefineIDMgr.h"
#include "PurchaseBroker.h"
#include "PurchaseMgr.h"
#include "ProfileMgr.h"
#include "ProfileUtils.h"
#include "PlayerInfo.h"
#include "IdentifierMgr.h"
#include "ActivityConfig.h"
#include "NameMapper.h"
#include "ChristmasAccessory.h"
#include "ChristmasGoldenEgg.h"
#include "PVP/PVPManager.h"
#include "PVZ2UIDialog.h"
#include "UIMessageBox.h"
#include "UIEditor/StringHelper.h"
#include "TodLib/TodStringFile.h"
#include "Social/SocialMgr.h"
#include "Board.h"
#include "SettingsDialog.h"
#include "DNode/DString.h"
#include "UserInfo.h"
#include "MysteryCrystal.h"
#include "ADManager.h"
#include "NameMapperEnum.h"
#include "TGALogMgr.h"
#include "MD5.h"
#include "GameCommon.h"
#include "PrimeText_Game.h"
#include "SexyAppFramework/drivers/app/android/JavaInterface.h"

/////////////// Helpers ///////////////

#define SetNumParam(params, key, stream, value) \
	do \
	{ \
		stream.str(""); \
		stream << (value); \
		params[key] = stream.str(); \
	} while (0)

template<typename T>
std::string androidNetworkMsgProcess::getArrayByVector(const std::vector<T>& i_list)
{
	std::string result("");
	result += "[";
	std::stringstream stream;
	for (typename std::vector<T>::const_iterator it = i_list.begin(); it != i_list.end(); ++it)
	{
		stream.str("");
		stream << *it;
		result += stream.str();
		result += ",";
	}
	result.erase(result.end() - 1);
	result += "]";
	return result;
}

/////////////// Lifecycle ///////////////

androidNetworkMsgProcess::androidNetworkMsgProcess()
	: m_downloadProfileRetry(0)
	, m_retryRequestTimes(5)
	, m_syncProfileRetry(0)
	, m_retrySyncProfileTimes(2)
{
	m_pHttpRequest = NULL;
	m_bCanUpLoadProfile = true;
	m_bShouldBindUniqueID = false;
	m_bBindForUUID = false;
}

androidNetworkMsgProcess::~androidNetworkMsgProcess()
{
	if (m_pHttpRequest != NULL)
	{
		delete m_pHttpRequest;
		m_pHttpRequest = NULL;
	}
}

/////////////// Initialization ///////////////

void androidNetworkMsgProcess::Initialize()
{
	m_pHttpRequest = new HttpRequest();
	m_ICIoudState = INIT;
	m_nCloudLoginCount = 0;
	m_UserId = "";
	m_sk = "";
	isNetworkBusy = false;
	LoadCache();
	RegistFunHandle(m_pktID.ID_GET_FRIEDN_LIST, androidNetworkMsgProcess, NetWorkMsg, OnRequestFriendList);
	RegistFunHandle(m_pktID.ID_FRIEND_GIFT_LIST, androidNetworkMsgProcess, NetWorkMsg, OnRequestFrindGiftList);
	RegistFunHandle(m_pktID.ID_BORROW_FRIEND_PLANT, androidNetworkMsgProcess, NetWorkMsg, OnRequestFriedBorrowPlant);
	RegistFunHandle(m_pktID.ID_BORROWED_FRIEND_PLANT_LIST, androidNetworkMsgProcess, NetWorkMsg, OnRequestFriendBorrowedPlantList);
	RegistFunHandle(m_pktID.ID_FRESH_GEMS_COUNT, androidNetworkMsgProcess, NetWorkMsg, OnRequestFreshGems);
	RegistFunHandle(m_pktID.ID_FRESH_SURPOT_PLANT, androidNetworkMsgProcess, NetWorkMsg, OnRequestSurportPlant);
	RegistFunHandle(m_pktID.ID_PLAYERIFO, androidNetworkMsgProcess, NetWorkMsg, OnRquestPlayerInfo);
	RegistFunHandle(m_pktID.ID_SENT_GIFT, androidNetworkMsgProcess, NetWorkMsg, OnRquestSendGift);
	RegistFunHandle(m_pktID.ID_LOGIN, androidNetworkMsgProcess, NetWorkMsg, OnRequestLogin);
	RegistFunHandle(m_pktID.ID_HEART_BEAT, androidNetworkMsgProcess, NetWorkMsg, OnRequestHeartBeat);
	RegistFunHandle(m_pktID.ID_GET_PROFILE, androidNetworkMsgProcess, NetWorkMsg, OnRequestProfile);
	RegistFunHandle(m_pktID.ID_ACCEPT_GIFT, androidNetworkMsgProcess, NetWorkMsg, OnRequestAcceptFriendGitf);
	RegistFunHandle(m_pktID.ID_UPDATE_PROFILE, androidNetworkMsgProcess, NetWorkMsg, OnRequestUpdateProfile);
	RegistFunHandle(m_pktID.ID_LEVEL_SCORE, androidNetworkMsgProcess, NetWorkMsg, OnRequestUpdateLevelScore);
	RegistFunHandle(m_pktID.ID_FRIEND_LEADERBOAD, androidNetworkMsgProcess, NetWorkMsg, OnRequestFriendLeaderBoard);
	RegistFunHandle(m_pktID.ID_TODAY_SENT_GIFT_LIST, androidNetworkMsgProcess, NetWorkMsg, OnRequestTodaySendGiftList);
	RegistFunHandle(m_pktID.ID_INCREASE_GEMS, androidNetworkMsgProcess, NetWorkMsg, OnRequestIncreaseGems);
	RegistFunHandle(m_pktID.ID_RAND_REWARD, androidNetworkMsgProcess, NetWorkMsg, OnRequestRandReward);
	RegistFunHandle(m_pktID.ID_TLOG, androidNetworkMsgProcess, NetWorkMsg, OnRequestSendTLog);
	RegistFunHandle(m_pktID.ID_ADD_FRIEND_SHIP, androidNetworkMsgProcess, NetWorkMsg, OnRequestAddFriendShip);
	RegistFunHandle(m_pktID.ID_LAUNCH_SAVE_FINISH, androidNetworkMsgProcess, NetWorkMsg, OnRequestLaunchSave);
	RegistFunHandle(m_pktID.ID_ICLOUD_SILENCE_LOGIN, androidNetworkMsgProcess, NetWorkMsg, OnICloudRequstLogin);
	RegistFunHandle(m_pktID.ID_ICLOUD_GET_PROFILE, androidNetworkMsgProcess, NetWorkMsg, OnICloudRequestGetProfile);
	RegistFunHandle(m_pktID.ID_ICLOUD_UPLOAD_PROFILE, androidNetworkMsgProcess, NetWorkMsg, OnICloudRequestUpLoadProfile);
	RegistFunHandle(m_pktID.ID_ICLOUD_GET_PROFILE_MD5, androidNetworkMsgProcess, NetWorkMsg, OnICloudRequestProfileMd5);
	RegistFunHandle(m_pktID.ID_ICLOUD_UPLOAD_COMPRESSED_PROFILE, androidNetworkMsgProcess, NetWorkMsg, OnICloudRequestUpLoadProfile);
	RegistFunHandle(m_pktID.ID_TIME_LEVEL_MSG_ID_LIST, androidNetworkMsgProcess, NetWorkMsg, OnRequestTimeLevelList);
	RegistFunHandle(m_pktID.ID_TIME_LEVEL_MSG_ID_NODE, androidNetworkMsgProcess, NetWorkMsg, OnRequestStartTimeLevelCD);
	RegistFunHandle(m_pktID.ID_DANGER_ROOM_UPLOAD_RANK, androidNetworkMsgProcess, NetWorkMsg, OnUploadDangerRoomRank);
	RegistFunHandle(m_pktID.ID_DANGER_ROOM_REQUEST_RANK, androidNetworkMsgProcess, NetWorkMsg, OnRequestDangerRoomRank);
	RegistFunHandle(m_pktID.ID_GET_REDPACK_RANK_BOARD, androidNetworkMsgProcess, NetWorkMsg, OnRequestGetRedPackLeaderBoard);
	RegistFunHandle(m_pktID.ID_UUID_BIND, androidNetworkMsgProcess, NetWorkMsg, onRequestUUIDBind);
	RegistFunHandle(m_pktID.ID_UUID_LOGIN, androidNetworkMsgProcess, NetWorkMsg, onRequestUUIDLogin);
	RegistFunHandle(m_pktID.ID_UUID_INIT, androidNetworkMsgProcess, NetWorkMsg, onRequestUUIDInit);
	RegistFunHandle(m_pktID.ID_UUID_CHECK, androidNetworkMsgProcess, NetWorkMsg, onRequestUUIDCheck);
	RegistFunHandle(m_pktID.ID_PURCHASE_INIT, androidNetworkMsgProcess, NetWorkMsg, onInitPurchaseOrder);
	RegistFunHandle(m_pktID.ID_REQUEST_UPDATE_CHARGE_INFO, androidNetworkMsgProcess, NetWorkMsg, OnRequestUpdateChargeInfo);
	RegistFunHandle(m_pktID.ID_PURCHASE_LOST, androidNetworkMsgProcess, NetWorkMsg, OnRequestLostPurchaseOrder);
	RegistFunHandle(m_pktID.ID_REQUEST_ADS_REWARD, androidNetworkMsgProcess, NetWorkMsg, onRequestADSReward);
	RegistFunHandle(m_pktID.ID_REQUEST_ACLOG, androidNetworkMsgProcess, NetWorkMsg, onRequestACLog);
	RegistFunHandle(m_pktID.ID_REQUEST_SYNC_PLAYER_DATA, androidNetworkMsgProcess, NetWorkMsg, onRequestSyncPlayerData);
	RegistFunHandle(m_pktID.ID_REQUEST_DOWNLOAD_PLAYER_DATA, androidNetworkMsgProcess, NetWorkMsg, onRequestDownloadPlayerData);
	RegistFunHandle(m_pktID.ID_ICLOUD_REQUEST_SYNC_CACHED_OBJECTS, androidNetworkMsgProcess, NetWorkMsg, OnICloudRequestSyncCachedObjects);
	RegistFunHandle(m_pktID.ID_ICLOUD_REQUEST_GET_EXPLORE_TEAM_STATUS, androidNetworkMsgProcess, NetWorkMsg, OnICloudRequestGetExploreTeamStatus);
	RegistFunHandle(m_pktID.ID_ICLOUD_REQUEST_GET_EXPLORE_PLANT_STATUS, androidNetworkMsgProcess, NetWorkMsg, OnICloudRequestGetExplorePlantStatus);
	RegistFunHandle(m_pktID.ID_ICLOUD_REQUEST_START_EXPLORE, androidNetworkMsgProcess, NetWorkMsg, OnICloudRequestStartExplore);
	RegistFunHandle(m_pktID.ID_ICLOUD_REQUEST_STOP_EXPLORE, androidNetworkMsgProcess, NetWorkMsg, OnICloudRequestStopExplore);
	RegistFunHandle(m_pktID.ID_ICLOUD_REQUEST_GET_EXPLORE_REWARD, androidNetworkMsgProcess, NetWorkMsg, OnICloudRequestCalcExploreReward);
	RegistFunHandle(m_pktID.ID_ICLOUD_REQUEST_OPEN_EXPLORE_SURPRISE_BOX, androidNetworkMsgProcess, NetWorkMsg, OnICloudRequestOpenExploreSurpriseBox);
	RegistFunHandle(m_pktID.ID_ICLOUD_REQUEST_RECOVER_EXPLORE_PLANT, androidNetworkMsgProcess, NetWorkMsg, OnICloudRequestRecoverExplorePlant);
	RegistFunHandle(m_pktID.ID_ICLOUD_REQUEST_CHRISTMAS_LOTTERY, androidNetworkMsgProcess, NetWorkMsg, OnICloudRequestChristmasLottery);
	RegistFunHandle(m_pktID.ID_ICLOUD_GET_CHARGE_REWARD, androidNetworkMsgProcess, NetWorkMsg, OnICloudRequestChargeReward);
	RegistFunHandle(m_pktID.ID_ICOUD_BIND_UNIQUE_ID, androidNetworkMsgProcess, NetWorkMsg, OnICloudRequestBindingUniqueID);
	m_random = 0;
	m_UserId = GetNetworkCacheQueue()->getUserID();
	m_sk = GetNetworkCacheQueue()->getSessionKey();
	gMessageRouter->Subscribe(&Message::RequestRank, Sexy::Delegate0(Sexy::MakeDelegate(*this, &androidNetworkMsgProcess::OnRequestRanks)));
	gMessageRouter->Subscribe(&Message::RequestACLog, Sexy::MakeDelegate(*this, &androidNetworkMsgProcess::RequestACLog));
}

/////////////// Login ///////////////

static int UIScaleNum(int i_num)
{
	return ((ScaledApp*)gSexyApp)->UIScaleNum(i_num);
}

bool androidNetworkMsgProcess::ICloudRequstLogin(const std::string& defineId)
{
	if (gLawnApp->IsServiceAvailable((ServiceFlags)0x4000000))
	{
		MainMenu* mainMenu = gLawnApp->GetMainMenu();
		if (EA_UNLIKELY(mainMenu != NULL && !mainMenu->CheckConfigFile("dynamic.rsb")))
		{
			PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(UIScaleNum(400), UIScaleNum(250));
			dialog->SetHeaderLabel(SexyString(L"[MD5_CHECK_FAILED_TITLE]"));
			dialog->SetFooterLabel(SexyString(L"[MD5_CHECK_FAILED_DESC]"));
			dialog->SetHeaderFont(PrimeText_Game::Typeface_FZShaoEr_28_Outline->Typeface(), PrimeText_Game::Color_Generic_Title);
			dialog->SetFooterFont(PrimeText_Game::Typeface_FZCuYuan_19_HardShadow->Typeface(), Sexy::Color(Sexy::Color::White));
			dialog->AddButton(SexyString(L"[BUTTON_OK]"), Sexy::Delegate0(Sexy::MakeDelegate(gLawnApp->GetMainMenu(), &MainMenu::OnCheckMD5Failed)));
			return false;
		}
	}

	if (m_ICIoudState == Send_Request)
		return false;
	if (m_nCloudLoginCount > 3)
		return false;
	m_nCloudLoginCount++;

	std::stringstream stream;
	stream << GetRandom();

	ParaMap params;
	params["req"] = m_pktID.ID_ICLOUD_SILENCE_LOGIN;
	params["di"] = defineId;
	params["t"] = AuthMgr::GetInstance().GetToken();
	params["li"] = DefineIDMgr::GetInstance().GetNewUserDefineID();
	params["head"] = ProfileMgr::GetInstance().GetPurchaseBroker()->GetTWRequestHead();
	params["r"] = stream.str();
	params["s"] = GetClientSignature(defineId);
	if (gLawnApp->IsAndroidSDKInitEnd() == 1 && gLawnApp->GetAndroidSDKInitStatus() == 0)
		params["oi"] = ProfileMgr::GetInstance().GetPurchaseBroker()->GetUniqueID().c_str();

	std::string fullVersionString = Sexy::StrFormat("%s.%d", PVPManager::GetInstancePtr()->GetProductVersion().c_str(), Android::Info::SysGetProductVersionCode());
	params["cv"] = fullVersionString;
	Sexy::OutputDebugStrF("androidNetworkMsgProcess::ICloudRequstLogin %d, fullVersionString = %s", Android::Info::SysGetProductVersionCode(), fullVersionString.c_str());

	SetNumParam(params, "ci", stream, gLawnApp->GetPlatform());

	m_ICIoudState = Send_Request;
	Sexy::OutputDebugStrF("NetworkMsgProcess m_ICIoudState = Send_Request");
	SendHttpRequest(params, true);
	return true;
}

void androidNetworkMsgProcess::OnRequestRanks()
{
}

bool androidNetworkMsgProcess::CheckUseACLogKey()
{
	return true;
}

void androidNetworkMsgProcess::OnRquestSendGift(const NetWorkMsg& data)
{
}

void androidNetworkMsgProcess::RequestLaunchSave(const std::string& pf, const std::string& pfkey)
{
}

void androidNetworkMsgProcess::OnRequestFriendList(const NetWorkMsg& data)
{
}

void androidNetworkMsgProcess::OnRequestLaunchSave(const NetWorkMsg& data)
{
}

void androidNetworkMsgProcess::OnRequestRandReward(const NetWorkMsg& data)
{
}

void androidNetworkMsgProcess::OnRequestAddFriendShip(const NetWorkMsg& data)
{
}

void androidNetworkMsgProcess::OnRequestFrindGiftList(const NetWorkMsg& data)
{
}

void androidNetworkMsgProcess::OnRequestUpdateProfile(const NetWorkMsg& data)
{
}

void androidNetworkMsgProcess::OnRequestFriedBorrowPlant(const NetWorkMsg& data)
{
}

void androidNetworkMsgProcess::OnRequestStartTimeLevelCD(const NetWorkMsg& data)
{
}

void androidNetworkMsgProcess::OnRequestUpdateLevelScore(const NetWorkMsg& data)
{
}

void androidNetworkMsgProcess::OnRequestFriendLeaderBoard(const NetWorkMsg& data)
{
}

void androidNetworkMsgProcess::OnRequestTodaySendGiftList(const NetWorkMsg& data)
{
}

void androidNetworkMsgProcess::OnRequestFriendBorrowedPlantList(const NetWorkMsg& data)
{
}

void androidNetworkMsgProcess::Login(const std::string& token, const std::string& defineId, int plantFormId, const std::string& refreshToken)
{
}

/////////////// Requests ///////////////

void androidNetworkMsgProcess::RequestProfile()
{
	ParaMap params;
	params["req"] = m_pktID.ID_GET_PROFILE;
	params["ui"] = m_UserId;
	params["sk"] = m_sk;
	SendHttpRequest(params);
}

void androidNetworkMsgProcess::RequestPlayInfo()
{
	ParaMap params;
	params["req"] = m_pktID.ID_PLAYERIFO;
	params["ui"] = m_UserId;
	params["sk"] = m_sk;
	SendHttpRequest(params);
}

void androidNetworkMsgProcess::RequestFrindGiftList()
{
	ParaMap params;
	params["req"] = m_pktID.ID_FRIEND_GIFT_LIST;
	params["ui"] = m_UserId;
	params["sk"] = m_sk;
	SendHttpRequest(params);
}

void androidNetworkMsgProcess::RequestAddFriendShip()
{
	ParaMap params;
	params["req"] = m_pktID.ID_ADD_FRIEND_SHIP;
	params["ui"] = m_UserId;
	params["sk"] = m_sk;
	SendHttpRequest(params);
}

void androidNetworkMsgProcess::RequestRandReward()
{
	ParaMap params;
	params["req"] = m_pktID.ID_RAND_REWARD;
	params["ui"] = m_UserId;
	params["sk"] = m_sk;
	SendHttpRequest(params);
}

void androidNetworkMsgProcess::RequestTodaySendGiftList()
{
	ParaMap params;
	params["req"] = m_pktID.ID_TODAY_SENT_GIFT_LIST;
	params["ui"] = m_UserId;
	params["sk"] = m_sk;
	SendHttpRequest(params);
}

void androidNetworkMsgProcess::HttpReqFriends()
{
	ParaMap params;
	params["req"] = m_pktID.ID_GET_FRIEDN_LIST;
	params["ui"] = m_UserId;
	params["sk"] = m_sk;
	SendHttpRequest(params);
}

void androidNetworkMsgProcess::RequestBorrowedPlantList()
{
	ParaMap params;
	params["req"] = m_pktID.ID_BORROWED_FRIEND_PLANT_LIST;
	params["ui"] = m_UserId;
	params["sk"] = m_sk;
	SendHttpRequest(params);
}

void androidNetworkMsgProcess::RequestLostPurchaseOrder()
{
	ParaMap params;
	params["req"] = m_pktID.ID_PURCHASE_LOST;
	params["ui"] = m_UserId;
	params["sk"] = m_sk;
	SendHttpRequest(params, true);
}

void androidNetworkMsgProcess::RequestTimeLevelList(int iID)
{
	ParaMap params;
	std::stringstream stream;
	stream << iID;
	params["req"] = m_pktID.ID_TIME_LEVEL_MSG_ID_LIST;
	params["ui"] = m_UserId;
	params["sk"] = m_sk;
	params["ci"] = stream.str();
	if (isSessionKeyValid())
		SendHttpRequest(params);
}

void androidNetworkMsgProcess::RequestIncreaseGems(int wayId)
{
	std::stringstream stream;
	stream << wayId;
	ParaMap params;
	params["req"] = m_pktID.ID_INCREASE_GEMS;
	params["ui"] = m_UserId;
	params["sk"] = m_sk;
	params["wi"] = stream.str();
	SendHttpRequest(params);
}

void androidNetworkMsgProcess::RequestStartTimeLevelCD(int iID)
{
	ParaMap params;
	std::stringstream stream;
	stream << iID;
	params["req"] = m_pktID.ID_TIME_LEVEL_MSG_ID_NODE;
	params["ui"] = m_UserId;
	params["sk"] = m_sk;
	params["ci"] = stream.str();
	SendHttpRequest(params);
}

void androidNetworkMsgProcess::RequestFriendLeaderBoard(int lvlId)
{
	std::stringstream stream;
	stream << lvlId;
	ParaMap params;
	params["req"] = m_pktID.ID_FRIEND_LEADERBOAD;
	params["ui"] = m_UserId;
	params["sk"] = m_sk;
	params["si"] = stream.str();
	SendHttpRequest(params);
}

void androidNetworkMsgProcess::RequestDangerRoomRank(int i_preRank)
{
	ParaMap params;
	std::stringstream stream;
	stream << i_preRank;
	params["req"] = m_pktID.ID_DANGER_ROOM_REQUEST_RANK;
	params["ui"] = m_UserId;
	params["sk"] = m_sk;
	params["pr"] = stream.str();
	SendHttpRequest(params, true);
}

void androidNetworkMsgProcess::RequestUpdateProfile(const std::string& profile, const std::string& md5)
{
	ParaMap params;
	params["req"] = m_pktID.ID_UPDATE_PROFILE;
	params["ui"] = m_UserId;
	params["sk"] = m_sk;
	params["pr"] = profile;
	params["m"] = md5;
	SendHttpRequest(params);
}

void androidNetworkMsgProcess::InitPurchaseOrder(const std::string& i_sku)
{
	ParaMap params;
	params["req"] = m_pktID.ID_PURCHASE_INIT;
	params["ui"] = m_UserId;
	params["sk"] = m_sk;
	params["dpi"] = i_sku;
	SendHttpRequest(params, true);
}

void androidNetworkMsgProcess::RequestAcceptFriendGitf(const std::string& senderIdArray)
{
	ParaMap params;
	params["req"] = m_pktID.ID_ACCEPT_GIFT;
	params["ui"] = m_UserId;
	params["sk"] = m_sk;
	params["si"] = senderIdArray;
	SendHttpRequest(params);
}

void androidNetworkMsgProcess::RequestSendTLog(const std::string& jsonText)
{
	ParaMap params;
	params["req"] = m_pktID.ID_TLOG;
	params["ui"] = m_UserId;
	params["sk"] = m_sk;
	params["tl"] = jsonText;
	SendHttpRequest(params);
}

void androidNetworkMsgProcess::BorrowFriendPlant(unsigned int friendId)
{
	ParaMap params;
	std::stringstream stream;
	stream << friendId;
	params["req"] = m_pktID.ID_BORROW_FRIEND_PLANT;
	params["ui"] = m_UserId;
	params["sk"] = m_sk;
	params["fi"] = stream.str();
	SendHttpRequest(params);
}

void androidNetworkMsgProcess::SendGift(int giftType, int receverId)
{
	ParaMap params;
	std::stringstream stream;
	stream << receverId;
	params["req"] = m_pktID.ID_SENT_GIFT;
	params["ui"] = m_UserId;
	params["sk"] = m_sk;
	params["ri"] = stream.str();
	SetNumParam(params, "gti", stream, giftType);
	SendHttpRequest(params);
}

void androidNetworkMsgProcess::FreshGems(int gemsCount, const std::string& pf, const std::string& pfkey)
{
	ParaMap params;
	std::stringstream stream;
	stream << gemsCount;
	params["req"] = m_pktID.ID_FRESH_GEMS_COUNT;
	params["ui"] = m_UserId;
	params["sk"] = m_sk;
	params["gd"] = stream.str();
	params["pf"] = pf;
	params["pk"] = pfkey;
	SendHttpRequest(params);
}

void androidNetworkMsgProcess::RequestGetRedPackLeaderBoard()
{
	ParaMap params;
	params["req"] = m_pktID.ID_GET_REDPACK_RANK_BOARD;
	params["ui"] = m_UserId;
	params["sk"] = m_sk;
	_NetworkEventConfig config;
	params["exurl"] = config.ExtraURL;
	SendHttpRequest(params);
}

/////////////// UUID ///////////////

void androidNetworkMsgProcess::RequestUUIDBind()
{
	ParaMap params;
	params["req"] = m_pktID.ID_UUID_BIND;
	std::string defineId = DefineIDMgr::GetInstance().GetUserDefineID();
	params["di"] = defineId;
	params["uuid"] = IdentifierMgr::GetInstance().GetUUID();
	params["at"] = IdentifierMgr::GetInstance().GetAccessToken();
	params["pack"] = Android::Util::GetPackageName();
	SendHttpRequest(params);
}

void androidNetworkMsgProcess::RequestUUIDCheck()
{
	ParaMap params;
	params["req"] = m_pktID.ID_UUID_CHECK;
	params["uuid"] = IdentifierMgr::GetInstance().GetUUID();
	params["at"] = IdentifierMgr::GetInstance().GetAccessToken();
	params["ver"] = gLawnApp->mProductVersion.empty() ? std::string("1.7.5") : gLawnApp->mProductVersion;
	SendHttpRequest(params);
}

void androidNetworkMsgProcess::RequestUUIDInit()
{
	ParaMap params;
	params["req"] = m_pktID.ID_UUID_INIT;
	std::string mac("00:00:00:00:00:00");
	Android::Diag::GetPrimaryMACAddress(mac);
	std::string defineId = DefineIDMgr::GetInstance().GetUserDefineID();
	params["di"] = defineId;
	params["ma"] = gLawnApp->GetDeviceMODEL();
	params["ver"] = gLawnApp->mProductVersion.empty() ? std::string("1.7.5") : gLawnApp->mProductVersion;
	params["pack"] = Android::Util::GetPackageName();
	if (mac.length() != 0)
		params["mac"] = mac;
	SendHttpRequest(params);
}

void androidNetworkMsgProcess::RequestUUIDLogin()
{
	if (m_ICIoudState == Send_Request)
		return;
	if (m_nCloudLoginCount > 3)
		return;
	m_nCloudLoginCount++;

	ParaMap params;
	params["req"] = m_pktID.ID_UUID_LOGIN;
	params["uuid"] = IdentifierMgr::GetInstance().GetUUID();

	std::stringstream stream;
	stream << GetRandom();
	params["r"] = stream.str();
	params["s"] = GetClientSignature(IdentifierMgr::GetInstance().GetUUID());
	params["cv"] = PVPManager::GetInstancePtr()->GetProductVersion();
	params["ci"] = PurchaseMgr::GetInstance().GetChannelId();
	if (gLawnApp->IsAndroidSDKInitEnd() == 1 && gLawnApp->GetAndroidSDKInitStatus() == 0)
	{
		std::string uniqueId = ProfileMgr::GetInstance().GetPurchaseBroker()->GetUniqueID();
		params["oi"] = uniqueId.c_str();
	}

	m_ICIoudState = Send_Request;
	SendHttpRequest(params, true);
}

void androidNetworkMsgProcess::RequestUpdateLevelScore(int lvlId, int lvlStar, unsigned long time, const std::string& formationData)
{
	std::stringstream stream;
	stream << lvlId;
	ParaMap params;
	params["req"] = m_pktID.ID_LEVEL_SCORE;
	params["ui"] = m_UserId;
	params["sk"] = m_sk;
	params["si"] = stream.str();
	SetNumParam(params, "s", stream, lvlStar);
	SetNumParam(params, "t", stream, time);
	params["f"] = formationData;
	SendHttpRequest(params);
}

void androidNetworkMsgProcess::RequestUpdateChargeInfo(const std::string& productId, bool isRestore, int objectId)
{
	ParaMap params;
	params["req"] = m_pktID.ID_REQUEST_UPDATE_CHARGE_INFO;
	params["ui"] = m_UserId;
	params["sk"] = m_sk;
	params["ver_"] = PVPManager::GetInstancePtr()->GetProductVersion();
	PaymentResultInfo paymentInfo(gLawnApp->GetPaymentResultInfo());
	params["r"] = paymentInfo.orderId;
	params["oi"] = "";
	params["ci"] = "";
	params["pt"] = "";
	std::stringstream stream;
	stream.str("");
	if (objectId > 0)
	{
		stream << objectId;
		params["obi"] = stream.str();
	}
	params["pdi"] = productId;
	SendHttpRequest(params, true);
}

/////////////// AC log ///////////////

void androidNetworkMsgProcess::RequestACLog(S2C_ACLog& acLog)
{
	Sexy::OutputDebugStrF("ACLog - RequestACLog enter");
	std::string json;
	if (!acLog.SerializeObjToJson(json, "d"))
	{
		Sexy::OutputDebugStrF("ACLog - RequestACLog to json error");
		return;
	}

	std::string ac;
	if (CheckUseACLogKey())
		ac = EncryptString(json.c_str(), json.length(), m_aclk.c_str());
	else
		ac = json;

	ParaMap params;
	params["req"] = m_pktID.ID_REQUEST_ACLOG;
	params["ui"] = m_UserId;
	params["sk"] = m_sk;
	params["ac"] = ac;
	SendHttpRequest(params);

	PlayerInfo* playerInfo = ProfileUtils::Profile();
	if (playerInfo != NULL)
	{
		playerInfo->PushACLog(acLog);
		playerInfo->SerializeACLog(m_aclk);
	}
	Sexy::OutputDebugStrF("ACLog - RequestACLog, json : %s", json.c_str());
	Sexy::OutputDebugStrF("ACLog - RequestACLog, ac : %s, key : %s", ac.c_str(), m_aclk.c_str());
}

bool androidNetworkMsgProcess::RequestADSReward()
{
	ParaMap params;
	params["req"] = m_pktID.ID_REQUEST_ADS_REWARD;
	params["ui"] = m_UserId;
	std::stringstream stream;
	SetNumParam(params, "pi", stream, ProfileMgr::GetInstance().GetCurrentProfile()->GetProfileId());
	params["sk"] = m_sk;
	stream.str("");
	ProfileMgr::GetInstance().GetCurrentProfile()->increaseUploadKey();
	stream << ProfileMgr::GetInstance().GetCurrentProfile()->getUploadKey();
	params["uk"] = stream.str();
	SendHttpRequest(params, true);
	return true;
}

bool androidNetworkMsgProcess::RequestDownloadPlayerData()
{
	Sexy::OutputDebugStrF("ACLog - RequestDownloadPlayerData enter");
	bool result = IsLogined();
	if (result)
	{
		std::stringstream stream;
		stream << GetRandom();
		ParaMap params;
		params["req"] = m_pktID.ID_REQUEST_DOWNLOAD_PLAYER_DATA;
		params["ui"] = m_UserId;
		params["sk"] = m_sk;
		result = isSessionKeyValid();
		if (result)
		{
			SendHttpRequest(params, true);
			Sexy::OutputDebugStrF("ACLog - RequestDownloadPlayerData Send");
		}
	}
	return result;
}

SyncProfileResult androidNetworkMsgProcess::RequestSyncPlayerData()
{
	Sexy::OutputDebugStrF("ACLog - RequestSyncPlayerData enter");
	PlayerInfo* playerInfo = ProfileUtils::Profile();
	if (playerInfo == NULL)
	{
		Sexy::OutputDebugStrF("ACLog - RequestSyncPlayerData, strProfileData error : no profile");
		return E_SYNC_PROFILE_PROFILE_ERROR;
	}

	std::string profileData;
	std::string md5;
	std::string summary;
	playerInfo->UpdateDeltaDataForServer();
	playerInfo->GetDeltaDataForServer(profileData, md5, summary);
	playerInfo->SerializeACLog(m_aclk);

	unsigned long compressedSize = 0x19000;
	unsigned char* compressed = new unsigned char[compressedSize];
	std::string encoded = std::string("\"") + base64_url_safe((const unsigned char*)profileData.c_str(), profileData.length()) + std::string("\"");
	SyncProfileResult result = E_SYNC_PROFILE_SK_INVALID;
	if (gzcompress((unsigned char*)encoded.c_str(), encoded.length(), compressed, &compressedSize) == 0)
	{
		ParaMap params;
		params["req"] = m_pktID.ID_REQUEST_SYNC_PLAYER_DATA;
		params["ui"] = m_UserId;
		params["sk"] = m_sk;
		params["pr"] = base64_url_safe(compressed, (unsigned int)compressedSize);
		params["m"] = md5;
		params["s"] = base64_url_safe((const unsigned char*)summary.c_str(), summary.length());
		bool sessionValid = isSessionKeyValid();
		if (sessionValid)
		{
			SendHttpRequest(params, true);
			Sexy::OutputDebugStrF("ACLog - RequestSyncPlayerData, strProfileData : %s", profileData.c_str());
		}
		result = sessionValid ? E_SYNC_PROFILE_SUCCESS : E_SYNC_PROFILE_SK_INVALID;
	}
	delete[] compressed;
	return result;
}

/////////////// Http ///////////////

void androidNetworkMsgProcess::SendHttpRequest(ParaMap& params, bool bWait, const std::string& i_hint, bool bPause, bool bFlush)
{
	params["pi"] = params["ui"];
	ParaMap::iterator it = params.find("req");
	std::string req = it->second;
	if (bWait)
		gLawnApp->ShowNetConnectingUI(i_hint);

	std::string json;
	it = params.begin();
	json = "{";
	while (it != params.end())
	{
		if (it->first != "req")
		{
			if (__builtin_expect(!!(it->first != "exurl"), 1))
			{
				json += "\"";
				json += it->first;
				json += "\":";
				if (IsJsonObj(it->second))
				{
					json += it->second;
				}
				else
				{
					json += "\"";
					json += it->second;
					json += "\"";
				}
				json += ",";
			}
		}
		++it;
	}
	json = json.substr(0, json.length() - 1);
	json += "}";

	int msgId = GetMsgID(req);
	std::string content = PCPEncryptSendDataStr(json.c_str(), json.length(), msgId, req);
	if (params.find("exurl") != params.end())
		m_pHttpRequest->StartRequest(req, content, params["exurl"]);
	else
		m_pHttpRequest->StartRequest(req, content);
}

/////////////// Danger room ///////////////

void androidNetworkMsgProcess::UploadDangerRoomRank(int score, int weight, int currentLevel, int currentWave, int result, int levelTime, int currentScore)
{
	ParaMap params;
	std::stringstream stream;
	stream << score;
	params["req"] = m_pktID.ID_DANGER_ROOM_UPLOAD_RANK;
	params["ui"] = m_UserId;
	params["sk"] = m_sk;
	params["s"] = stream.str();
	SetNumParam(params, "w", stream, weight);
	SetNumParam(params, "t", stream, currentLevel);
	SetNumParam(params, "a", stream, currentWave);
	SetNumParam(params, "i", stream, result);
	SetNumParam(params, "spt", stream, levelTime);
	SetNumParam(params, "lss", stream, currentScore);
	SendHttpRequest(params, true);
}

/////////////// Identification ///////////////

void androidNetworkMsgProcess::UploadIdentification(const std::string& idcard, const std::string& name, bool logStatus)
{
	ParaMap params;
	params["req"] = m_pktID.ID_UPLOAD_IDENTIFICATION;
	params["ui"] = m_UserId;
	std::stringstream stream;
	stream.str("");
	PlayerInfo* playerInfo = ProfileMgr::GetInstance().GetCurrentProfile();
	stream << playerInfo->GetProfileId();
	params["pi"] = stream.str();
	params["sk"] = m_sk;
	params["i"] = idcard;
	params["n"] = name;
	if (logStatus)
	{
		bool isBind = IdentifierMgr::GetInstance().IsBind();
		std::string defineId = DefineIDMgr::GetInstance().GetUserDefineID();
		if (defineId.empty())
			defineId = DefineIDMgr::GetInstance().GetNewUserDefineID();
		std::string uuid = IdentifierMgr::GetInstance().GetUUID();
		params["did"] = isBind ? uuid : defineId;
		int rechargeCurrency = playerInfo->GetNumRechargeCurrency();
		params["ps"] = std::to_string(rechargeCurrency);
	}
	SendHttpRequest(params, true);
}

/////////////// Christmas ///////////////

bool androidNetworkMsgProcess::ICloudRequestGetAccessoryStat(int i_option)
{
	if (gLawnApp->GetRealBeijingTime() < 1)
	{
		if (i_option == 1)
		{
			gMessageRouter->Post(&Message::GotChristmasAccessoryStat, false);
			return true;
		}
		gMessageRouter->Post(&Message::RefreshChristmasAccessoryStat, false);
		return true;
	}
	PlayerInfo* playerInfo = ProfileMgr::GetInstance().GetCurrentProfile();
	if (playerInfo != NULL)
		playerInfo->DailyRefreshChristmasAccessoryInfo();
	if (i_option == 1)
	{
		gMessageRouter->Post(&Message::GotChristmasAccessoryStat, (bool)i_option);
		return true;
	}
	gMessageRouter->Post(&Message::RefreshChristmasAccessoryStat, true);
	return true;
}

bool androidNetworkMsgProcess::ICloudRequestGetGoldenEggStat(int i_option)
{
	if (gLawnApp->GetRealBeijingTime() < 1)
	{
		if (i_option == 1)
		{
			gMessageRouter->Post(&Message::GotGoldenEggStat, false);
			return true;
		}
		gMessageRouter->Post(&Message::RefreshGoldenEggStat, false);
		return true;
	}
	PlayerInfo* playerInfo = ProfileMgr::GetInstance().GetCurrentProfile();
	if (playerInfo != NULL)
		playerInfo->DailyRefreshGoldenEggInfo();
	if (i_option == 1)
	{
		gMessageRouter->Post(&Message::GotGoldenEggStat, (bool)i_option);
		return true;
	}
	gMessageRouter->Post(&Message::RefreshGoldenEggStat, true);
	return true;
}

bool androidNetworkMsgProcess::ICloudRequestAccessoryStatBuy(int i_type)
{
	bool success = false;
	if (gLawnApp->GetRealBeijingTime() > 0)
	{
		PlayerInfo* playerInfo = ProfileMgr::GetInstance().GetCurrentProfile();
		ActivityConfig* activityConfig = gLawnApp->GetActivityConfig();
		if (__builtin_expect(!!(playerInfo != NULL && activityConfig != NULL), 1))
		{
			int chances = playerInfo->GetChristmasAccessoryChances(i_type);
			if (chances <= 0)
			{
				gMessageRouter->Post(&Message::ChristmasAccessoryBought, false);
				return false;
			}
			int remainingChances = chances - 1;
			int index1 = playerInfo->GetChristmasAccessoryIndex(i_type, 0);
			int index2 = playerInfo->GetChristmasAccessoryIndex(i_type, 1);
			int objectId1 = activityConfig->GetChristmasAccessoryIdByIndex(i_type, index1).objectId;
			int objectId2 = activityConfig->GetChristmasAccessoryIdByIndex(i_type, index2).objectId;
			int quantity1 = activityConfig->GetChristmasAccessoryIdByIndex(i_type, index1).quantity;
			int quantity2 = activityConfig->GetChristmasAccessoryIdByIndex(i_type, index2).quantity;
			if (__builtin_expect(!!(PlantAccessoryPieceMapper::GetInstance().ContainsId(objectId1)), 0))
			{
				playerInfo->AddAccessoryPieceCount(PlantAccessoryPieceMapper::GetInstance().GetNameForId(objectId1), quantity1, true);
				if (gLawnApp->IsAccessoryBonusUIValid())
					gLawnApp->GetAccessoryBonusUI()->AddBonus(objectId1, quantity1, 1);
			}
			if (__builtin_expect(!!(PlantAccessoryPieceMapper::GetInstance().ContainsId(objectId2)), 0))
			{
				playerInfo->AddAccessoryPieceCount(PlantAccessoryPieceMapper::GetInstance().GetNameForId(objectId2), quantity2, true);
				if (gLawnApp->IsAccessoryBonusUIValid())
					gLawnApp->GetAccessoryBonusUI()->AddBonus(objectId2, quantity2, 2);
			}
			std::vector<int> indexList;
			indexList.clear();
			for (int i = 2; i >= 1; i--)
				indexList.push_back(activityConfig->RollChristmasAccessoryIndex(i_type));
			playerInfo->ResetChristmasAccessoryIndex(i_type, indexList, false);
			playerInfo->SetChristmasAccessoryChances(i_type, remainingChances, false);
			playerInfo->SAVE_PROFILE();
		}
		success = true;
	}
	gMessageRouter->Post(&Message::ChristmasAccessoryBought, success);
	return true;
}

bool androidNetworkMsgProcess::ICloudRequestGoldenEggOpen(int i_index, int i_chipId)
{
	bool success = false;
	if (gLawnApp->GetRealBeijingTime() > 0)
	{
		success = true;
		PlayerInfo* playerInfo = ProfileMgr::GetInstance().GetCurrentProfile();
		ActivityConfig* activityConfig = gLawnApp->GetActivityConfig();
		if (playerInfo != NULL && activityConfig != NULL && gLawnApp->IsGoldenEggUIValid())
		{
			int hammers = playerInfo->GetGoldenEggHammers();
			if (hammers > 0)
				playerInfo->SetGoldenEggHammers(hammers - 1, false);
			GoldenEggUI* goldenEggUI = gLawnApp->GetGoldenEggUI();
			GoldenEggProbility reward = activityConfig->RollGoldenEggPieceCount();
			int objectId = playerInfo->GetGoldenEggsObjectId();
			int quantity = reward.quantity;
			bool refresh = reward.refresh;
			playerInfo->SetGoldenEggDailyReward(playerInfo->GetGoldenEggDailyReward() + quantity, false);
			goldenEggUI->AddBonus(i_index, objectId, quantity, refresh);
			std::vector<int> eggsStat = playerInfo->GetGoldenEggsStat();
			if (!refresh)
			{
				std::vector<int>::iterator it = eggsStat.begin();
				std::vector<int>::iterator end = eggsStat.end();
				if (i_index == 1)
				{
					for (; it != end; ++it)
						*it = 2;
				}
				else
				{
					for (; it != end; ++it)
						;
				}
			}
			else
			{
				std::vector<int>::iterator it = eggsStat.begin();
				std::vector<int>::iterator end = eggsStat.end();
				for (; it != end; ++it)
					*it = 1;
			}
			goldenEggUI->SetRefreshStat(eggsStat);
			playerInfo->AddCommonGachaReward(objectId, quantity, false, true);
			playerInfo->SAVE_PROFILE();
		}
	}
	gMessageRouter->Post(&Message::GoldenEggOpen, success);
	return true;
}

bool androidNetworkMsgProcess::ICloudRequestChristmasLottery()
{
	bool networkOk = gLawnApp->IsNetworkModuleOK();
	if (!networkOk)
	{
		gMessageRouter->Post(&Message::GotChristmasLottery, false, 0, 0);
	}
	else
	{
		ParaMap params;
		params["req"] = m_pktID.ID_ICLOUD_REQUEST_CHRISTMAS_LOTTERY;
		params["ui"] = m_UserId;
		std::stringstream stream;
		SetNumParam(params, "pi", stream, ProfileMgr::GetInstance().GetCurrentProfile()->GetProfileId());
		params["sk"] = m_sk;
		SendHttpRequest(params, true);
	}
	return networkOk;
}

/////////////// Explore ///////////////

bool androidNetworkMsgProcess::ICloudRequestGetExplorePlantStatus(int i_dungeonId)
{
	bool connected = gLawnApp->IsConnected();
	if (!connected)
	{
		gMessageRouter->Post(&Message::GotExplorePlantStatus, i_dungeonId, connected);
	}
	else
	{
		ParaMap params;
		params["req"] = m_pktID.ID_ICLOUD_REQUEST_GET_EXPLORE_PLANT_STATUS;
		params["ui"] = m_UserId;
		std::stringstream stream;
		SetNumParam(params, "pi", stream, ProfileMgr::GetInstance().GetCurrentProfile()->GetProfileId());
		params["sk"] = m_sk;
		stream.clear();
		SetNumParam(params, "wi", stream, i_dungeonId);
		SendHttpRequest(params, true);
	}
	return true;
}

bool androidNetworkMsgProcess::ICloudRequestGetExploreTeamStatus()
{
	if (!gLawnApp->IsConnected())
	{
		gMessageRouter->Post(&Message::OpenPlantAdventure, false);
		gMessageRouter->Post(&Message::GotExploreTeamStatus, false);
	}
	ParaMap params;
	params["req"] = m_pktID.ID_ICLOUD_REQUEST_GET_EXPLORE_TEAM_STATUS;
	params["ui"] = m_UserId;
	std::stringstream stream;
	SetNumParam(params, "pi", stream, ProfileMgr::GetInstance().GetCurrentProfile()->GetProfileId());
	params["sk"] = m_sk;
	SendHttpRequest(params, true);
	return true;
}

bool androidNetworkMsgProcess::ICloudRequestStartExplore(const std::vector<int>& i_plantList, int i_dungeonId, int i_isCost)
{
	bool connected = gLawnApp->IsConnected();
	if (!connected)
	{
		gMessageRouter->Post(&Message::StartExplore, connected);
	}
	else
	{
		ParaMap params;
		params["req"] = m_pktID.ID_ICLOUD_REQUEST_START_EXPLORE;
		params["ui"] = m_UserId;
		std::stringstream stream;
		SetNumParam(params, "pi", stream, ProfileMgr::GetInstance().GetCurrentProfile()->GetProfileId());
		stream.clear();
		SetNumParam(params, "wi", stream, i_dungeonId);
		params["sk"] = m_sk;
		params["pl"] = getArrayByVector(i_plantList);
		stream.clear();
		SetNumParam(params, "ic", stream, i_isCost);
		SendHttpRequest(params, true);
	}
	return connected;
}

bool androidNetworkMsgProcess::ICloudRequestStopExplore(int i_dungeonId, int i_flag)
{
	bool connected = gLawnApp->IsConnected();
	if (!connected)
	{
		gMessageRouter->Post(&Message::StopExplore, i_dungeonId, -1, connected);
	}
	else
	{
		ParaMap params;
		params["req"] = m_pktID.ID_ICLOUD_REQUEST_STOP_EXPLORE;
		params["ui"] = m_UserId;
		std::stringstream stream;
		SetNumParam(params, "pi", stream, ProfileMgr::GetInstance().GetCurrentProfile()->GetProfileId());
		params["sk"] = m_sk;
		stream.clear();
		SetNumParam(params, "wi", stream, i_dungeonId);
		stream.clear();
		SetNumParam(params, "f", stream, i_flag);
		SendHttpRequest(params, true);
	}
	return connected;
}

bool androidNetworkMsgProcess::ICloudRequestRecoverExplorePlant(int i_plantId, int i_flag)
{
	bool connected = gLawnApp->IsConnected();
	if (!connected)
	{
		gMessageRouter->Post(&Message::RecoverExplorePlant, connected);
	}
	else
	{
		ParaMap params;
		params["req"] = m_pktID.ID_ICLOUD_REQUEST_RECOVER_EXPLORE_PLANT;
		params["ui"] = m_UserId;
		std::stringstream stream;
		SetNumParam(params, "pi", stream, ProfileMgr::GetInstance().GetCurrentProfile()->GetProfileId());
		params["sk"] = m_sk;
		stream.clear();
		SetNumParam(params, "f", stream, i_flag);
		stream.clear();
		SetNumParam(params, "pli", stream, i_plantId);
		SendHttpRequest(params, true);
	}
	return connected;
}

bool androidNetworkMsgProcess::ICloudRequestCalcExploreReward(int i_dungeonId, bool i_ad)
{
	bool connected = gLawnApp->IsConnected();
	if (!connected)
	{
		gMessageRouter->Post(&Message::GotExploreReward, connected);
	}
	else
	{
		ParaMap params;
		params["req"] = m_pktID.ID_ICLOUD_REQUEST_GET_EXPLORE_REWARD;
		params["ui"] = m_UserId;
		std::stringstream stream;
		SetNumParam(params, "pi", stream, ProfileMgr::GetInstance().GetCurrentProfile()->GetProfileId());
		params["sk"] = m_sk;
		stream.clear();
		SetNumParam(params, "wi", stream, i_dungeonId);
		stream.clear();
		SetNumParam(params, "ad", stream, (int)i_ad);
		SendHttpRequest(params, true);
	}
	return connected;
}

bool androidNetworkMsgProcess::ICloudRequestOpenExploreSurpriseBox(int i_dungeonId)
{
	bool connected = gLawnApp->IsConnected();
	if (!connected)
	{
		gMessageRouter->Post(&Message::GotExploreSurprise, connected);
	}
	else
	{
		ParaMap params;
		params["req"] = m_pktID.ID_ICLOUD_REQUEST_OPEN_EXPLORE_SURPRISE_BOX;
		params["ui"] = m_UserId;
		std::stringstream stream;
		SetNumParam(params, "pi", stream, ProfileMgr::GetInstance().GetCurrentProfile()->GetProfileId());
		params["sk"] = m_sk;
		stream.clear();
		SetNumParam(params, "wi", stream, i_dungeonId);
		SendHttpRequest(params, true);
	}
	return connected;
}

/////////////// iCloud profile ///////////////

bool androidNetworkMsgProcess::ICloudRequestUpLoadProfile(const std::string& profile, const std::string& md5, const std::string& sumary, bool wait)
{
	bool result = false;
	if (!IsLogined())
		return false;
	if (!m_bCanUpLoadProfile)
		return false;
	unsigned long compressedSize = 0xf000;
	void* compressed = malloc(compressedSize);
	std::string encoded = std::string("\"") + base64_url_safe((const unsigned char*)profile.c_str(), profile.length()) + std::string("\"");
	if (gzcompress((unsigned char*)encoded.c_str(), encoded.length(), (unsigned char*)compressed, &compressedSize) == 0)
	{
		std::stringstream stream;
		stream << GetRandom();
		ParaMap params;
		params["req"] = m_pktID.ID_ICLOUD_UPLOAD_COMPRESSED_PROFILE;
		params["ui"] = m_UserId;
		params["sk"] = m_sk;
		params["pr"] = base64_url_safe((const unsigned char*)compressed, (unsigned int)compressedSize);
		params["m"] = md5;
		params["s"] = base64_url_safe((const unsigned char*)sumary.c_str(), sumary.length());
		result = isSessionKeyValid();
		if (result)
			SendHttpRequest(params, wait);
	}
	free(compressed);
	return result;
}

void androidNetworkMsgProcess::HeartBeat()
{
	ParaMap params;
	params["req"] = m_pktID.ID_HEART_BEAT;
	params["ui"] = m_UserId;
	SendHttpRequest(params);
}

void androidNetworkMsgProcess::OnRequestHeartBeat(const NetWorkMsg& data)
{
	NetworkMgr::Instance()->UpdateNetTime(data.msg);
}

bool androidNetworkMsgProcess::CheckACLogOpen()
{
	return !m_aclk.empty();
}

bool androidNetworkMsgProcess::CheckACLogFirstLogin()
{
	return m_oaclk.empty();
}

bool androidNetworkMsgProcess::EnableBindForUUID()
{
	return m_bBindForUUID;
}

bool androidNetworkMsgProcess::EnableBindUniqueID()
{
	return m_bShouldBindUniqueID;
}

void androidNetworkMsgProcess::RequestRanks()
{
	gMessageRouter->Post(&Message::RequestRank);
}

void androidNetworkMsgProcess::OnRequestTimeLevelList(const NetWorkMsg& data)
{
	gLawnApp->KillNetConnectingUI();
}

void androidNetworkMsgProcess::onRequestACLog(const NetWorkMsg& data)
{
	Sexy::OutputDebugStrF("ACLog - onRequestACLog: result : %d", data.erro);
}

void androidNetworkMsgProcess::InitAfterLogin()
{
	RequestBorrowedPlantList();
	UpdatePlayerSupportPlant();
}

void androidNetworkMsgProcess::OnRequestSurportPlant(const NetWorkMsg& data)
{
	Sexy::OutputDebugStrF("=============================== OnRequestSurportPlant----------[%s]\n", data.msg.c_str());
}

void androidNetworkMsgProcess::OnRequestSendTLog(const NetWorkMsg& data)
{
	Sexy::OutputDebugStrF("OnRequestSendTLog----erro:%d \n", data.erro);
	Sexy::OutputDebugStrF("OnRequestSendTLog----msg: %s \n", data.msg.c_str());
}

/////////////// Profile responses ///////////////

void androidNetworkMsgProcess::OnRequestProfile(const NetWorkMsg& data)
{
	if (data.erro == 0)
	{
		S2C_LoadPlayerProfile profile;
		profile.SerializeJson(data.msg);
		ProfileUtils::Profile();
	}
}

void androidNetworkMsgProcess::OnRquestPlayerInfo(const NetWorkMsg& data)
{
	if (data.erro == 0)
	{
		S2C_PlayerInfo info;
		info.SerializeJson(data.msg);
		PlayerInfo* playerInfo = ProfileUtils::Profile();
		if (playerInfo != NULL)
			playerInfo->SetGems(info.m_Gems);
	}
}

void androidNetworkMsgProcess::OnUploadDangerRoomRank(const NetWorkMsg& data)
{
	if (data.erro == 0)
	{
		S2C_UploadDangerRoomRank rank;
		rank.SerializeJson(data.msg);
	}
}

void androidNetworkMsgProcess::DoContinuedLoginV202ClearProfile(UIMessageBox* box, int buttonID)
{
	UISingletonDialog<UIMessageBox>::CloseDialog();
	if (buttonID != 1)
		return;
	ProfileMgr::GetInstance().ClearAllProfile();
	DoContinuedLoginV202();
}


void androidNetworkMsgProcess::OnICloudRequestGetProfile(const NetWorkMsg& data)
{
	if (data.erro == 0)
	{
		S2C_ICloud_GetProfile result;
		result.SerializeJson(data.msg);
		std::string profileJson = base64_decode_url_safe(result.m_profile.profile);
		MD5 md5(profileJson);
		bool mismatch = md5.toString() != result.m_profile.md5;
		bool success = false;
		if (!mismatch)
		{
			PlayerInfo* playerInfo = ProfileUtils::Profile();
			if (playerInfo != NULL)
			{
				PlayerInfo downloaded;
				if (!downloaded.SerializeJsonToObj(profileJson, "sd"))
					return;
				playerInfo->SetMapConversionState(MAPCONVERSION_None);
				playerInfo->UpdateDeltaDataFromServer(profileJson, result.m_profile.md5, result.m_profile.lastUpdateTime);
				playerInfo->ResetStarTotal();
			}
			success = true;
		}
		gMessageRouter->Post(&Message::SyncProfileFromServerFinish, success);
	}
	else
		gMessageRouter->Post(&Message::SyncProfileFromServerFinish, false);
}

/////////////// Cache flush ///////////////

bool androidNetworkMsgProcess::IRequestFlushCacheObjects()
{
	if (isNetworkBusy)
		return false;
	std::vector<NetworkCacheObjects>& objects = GetNetworkCacheQueue()->getCachedObjects();
	if (objects.size() == 0)
		return true;
	ICloudRequestSyncObjectListWithSource(objects);
	return true;
}

/////////////// Gem, rank and social responses ///////////////

void androidNetworkMsgProcess::OnRequestFreshGems(const NetWorkMsg& data)
{
	S2C_SubGemRequest request;
	request.SerializeJson(data.msg);
	bool success = data.erro == 0;
	if (success)
	{
		PlayerInfo* playerInfo = ProfileMgr::GetInstance().GetCurrentProfile();
		if (playerInfo != NULL)
			playerInfo->SetGems(request.m_info.mGem);
	}
	gLawnApp->WaitingGemCallBack(success);
}

void androidNetworkMsgProcess::OnRequestIncreaseGems(const NetWorkMsg& data)
{
	S2C_AddGemRequest request;
	request.SerializeJson(data.msg);
	bool success = data.erro == 0;
	if (success)
	{
		PlayerInfo* playerInfo = ProfileMgr::GetInstance().GetCurrentProfile();
		if (playerInfo != NULL)
			playerInfo->SetGems(request.m_info.mGem);
	}
	gLawnApp->WaitingGemCallBack(success);
}

void androidNetworkMsgProcess::OnRequestDangerRoomRank(const NetWorkMsg& data)
{
	if (data.erro == 0)
	{
		S2C_UploadDangerRoomRank rank;
		rank.SerializeJson(data.msg);
		gMessageRouter->Post(&Message::RequestDangerRoomFinish, true, rank.m_content.rank);
	}
	else
		gMessageRouter->Post(&Message::RequestDangerRoomFinish, false, 0);
}

void androidNetworkMsgProcess::OnRequestAcceptFriendGitf(const NetWorkMsg& data)
{
	if (data.erro == 0)
	{
		std::vector<int32> usedList = SocialMgr::GetInstance().GetSocialInfo()->getUsedSunList();
		int count = (int)usedList.size();
		for (int i = 0; i < count; i++)
			SocialMgr::GetInstance().GetSocialInfo()->RemoveUsedFriendSunList(usedList[i]);
		gLawnApp->m_board->AddSunMoney(count * 25);
	}
}

void androidNetworkMsgProcess::OnRequestLostPurchaseOrder(const NetWorkMsg& data)
{
	S2C_Purchase_LostPurchaseOrder order;
	order.SerializeJson(data.msg);
	gMessageRouter->Post(&Message::NotifyLostPurchaseOrder, data.erro, order);
}

void androidNetworkMsgProcess::onRequestUUIDBind(const NetWorkMsg& data)
{
	if (data.erro == 0)
	{
		S2C_UUID_BindResult result;
		result.SerializeJson(data.msg);
		gMessageRouter->Broadcast(&Message::NotifyUUIDBind, true);
	}
	else
		gMessageRouter->Broadcast(&Message::NotifyUUIDBind, false);
}

void androidNetworkMsgProcess::onRequestUUIDCheck(const NetWorkMsg& data)
{
	S2C_UUID_CheckResult result;
	result.SerializeJson(data.msg);
	gMessageRouter->Broadcast(&Message::NotifyUUIDCheck, data.erro, result.access_token);
}

/////////////// Misc responses ///////////////

void androidNetworkMsgProcess::onRequestUUIDInit(const NetWorkMsg& data)
{
	if (data.erro == 0)
	{
		S2C_UUID_InitResult result;
		result.SerializeJson(data.msg);
		gMessageRouter->Broadcast(&Message::NotifyUUIDInit, true, std::string(result.uuid), std::string(result.access_token));
	}
	else
		gMessageRouter->Broadcast(&Message::NotifyUUIDInit, false, "", "");
}

void androidNetworkMsgProcess::onInitPurchaseOrder(const NetWorkMsg& data)
{
	if (data.erro == 0)
	{
		S2C_Purchase_InitResult result;
		result.SerializeJson(data.msg);
		gMessageRouter->Post(&Message::NotifyPurchaseInit, data.erro, std::string(result.orderId), std::string(result.skuId));
	}
	else
		gMessageRouter->Post(&Message::NotifyPurchaseInit, data.erro, "", "");
}

void androidNetworkMsgProcess::OnICloudRequestProfileMd5(const NetWorkMsg& data)
{
	if (data.erro == 0)
	{
		S2C_ICloud_GetProfileMD5 result;
		result.SerializeJson(data.msg);
		PlayerInfo* playerInfo = ProfileUtils::Profile();
		if (playerInfo != NULL)
		{
			std::string summary = base64_decode_url_safe(result.m_profile.summary);
			playerInfo->UpdateDeltaDataSignFromServer(result.m_profile.md5, summary, result.m_profile.lastUpdateTime);
		}
		gMessageRouter->Post(&Message::SyncProfileSummaryFinish, true);
	}
	else
		gMessageRouter->Post(&Message::SyncProfileSummaryFinish, false);
}

void androidNetworkMsgProcess::onRequestADSReward(const NetWorkMsg& data)
{
	if (data.erro == 0)
	{
		S2C_ADSReward reward;
		reward.SerializeJson(data.msg);
		PlayerInfo* playerInfo = ProfileUtils::Profile();
		if (playerInfo != NULL)
			playerInfo->AddCommonGachaRewardList(reward.m_bonusList, false);
		gMessageRouter->Broadcast(&Message::NotifyAdsReward, S2C_ADSReward(reward));
		gMessageRouter->Broadcast(&Message::EASquareReward, "EA2World", std::vector<S2C_BonusInfo>(reward.m_bonusList));
	}
	else
		ShowErrorMessage(INetworkErrorData(data.msg));
}

std::string androidNetworkMsgProcess::GetDefineId()
{
	if (gLawnApp->IsAndroidSDKInitEnd() == 1 && gLawnApp->GetAndroidSDKInitStatus() == 0)
	{
		std::string imei;
		Android::Diag::GetDeviceIMEI(imei);
		std::string mac;
		Android::Diag::GetPrimaryMACAddress(mac);
		return imei + mac + gLawnApp->GetAppNameForiCloud();
	}
	return std::string("");
}

void androidNetworkMsgProcess::ShowClearProfileHint()
{
	UIMessageBox* box = UISingletonDialog<UIMessageBox>::ShowDialog();
	if (box)
	{
		box->SetShowType(UIMessageBox::Type_ShowOK);
		SexyString title = TodStringTranslate(L"[REVIVE_TIP]");
		SexyString message = TodStringTranslate(L"[BIND_UNIQUE_ID_CLEAR_PROFILE]");
		SexyString ok = TodStringTranslate(L"[BUTTON_OK]");
		box->SetMessage(message, title);
		box->SetBackground(StringHelper::ToImage("IMAGE_UI_DIALOG_ASSET_BG_LIGHT_GREEN", false));
		box->GetButtonOK()->mLabel = ok;
		box->GetButtonCloseNew()->SetVisible(false);
		box->SetCallback(Sexy::Delegate2<UIMessageBox*, int>(Sexy::MakeDelegate(*this, &androidNetworkMsgProcess::DoContinuedLoginV202ClearProfile)));
	}
}

/////////////// Login response ///////////////

void androidNetworkMsgProcess::OnRequestLogin(const NetWorkMsg& data)
{
	Sexy::OutputDebugStrF("===============================   OnRequestLogin----------[%s]\n", data.msg.c_str());
	S2C_AuthInfo authInfo;
	authInfo.SerializeJson(data.msg);
	SocialMgr::GetInstance().UpdateAuthInfo(authInfo);

	std::stringstream stream;
	stream << authInfo.userId;
	m_UserId = stream.str();
	m_sk = authInfo.sessionKey;

	PlayerInfo* playerInfo = ProfileUtils::Profile();
	if (playerInfo != NULL)
		playerInfo->SetProfileId(authInfo.userId);
	RequestPlayInfo();
	InitAfterLogin();
}

/////////////// Explore and lottery responses ///////////////

void androidNetworkMsgProcess::OnICloudRequestRecoverExplorePlant(const NetWorkMsg& data)
{
	if (data.erro == 0)
	{
		S2C_ExplorePlantRecover recover;
		recover.SerializeJson(data.msg);
		gMessageRouter->Post(&Message::RecoverExplorePlant, true);
	}
	else
		gMessageRouter->Post(&Message::RecoverExplorePlant, false);
}

void androidNetworkMsgProcess::OnICloudRequestChristmasLottery(const NetWorkMsg& data)
{
	if (data.erro == 0)
	{
		S2C_ChristmasLottery lottery;
		lottery.SerializeJson(data.msg);
		PlayerInfo* playerInfo = ProfileMgr::GetInstance().GetCurrentProfile();
		if (playerInfo != NULL)
		{
			playerInfo->SetNeedSave(false);
			playerInfo->SetGems(lottery.m_playerInfo.m_Gems);
			playerInfo->SetChristmasLotteryPlantIndex(lottery.m_plantIndex);
			playerInfo->SetNeedSave(true);
			playerInfo->SAVE_PROFILE();
		}
		gMessageRouter->Post(&Message::GotChristmasLottery, true, lottery.m_christmasLottery.objectId, lottery.m_christmasLottery.quantity);
	}
	else
		gMessageRouter->Post(&Message::GotChristmasLottery, false, 0, 0);
}

void androidNetworkMsgProcess::OnICloudRequestOpenExploreSurpriseBox(const NetWorkMsg& data)
{
	if (data.erro == 0)
	{
		S2C_SurpriseRewardNew reward;
		reward.SerializeJson(data.msg);
		PlayerInfo* playerInfo = ProfileMgr::GetInstance().GetCurrentProfile();
		if (playerInfo != NULL)
		{
			playerInfo->SetNeedSave(false);
			ProfileChangeItemAmount(reward.m_plantSurpriseInfo.m_objectId, reward.m_plantSurpriseInfo.m_quantity, false);
			playerInfo->SetGems(reward.m_playerInfo.m_Gems);
			playerInfo->SetNeedSave(true);
			playerInfo->SAVE_PROFILE();
		}
		gMessageRouter->Post(&Message::GotExploreSurprise, true);
	}
	else
		gMessageRouter->Post(&Message::GotExploreSurprise, false);
}

void androidNetworkMsgProcess::OnICloudRequestGetExplorePlantStatus(const NetWorkMsg& data)
{
	if (data.erro == 0)
	{
		S2C_ExplorerPlantStatus status;
		status.SerializeJson(data.msg);
		PlayerInfo* playerInfo = ProfileMgr::GetInstance().GetCurrentProfile();
		if (playerInfo != NULL)
		{
			playerInfo->SetNeedSave(false);
			playerInfo->RemoveAllAdventure(false, true, false);
			std::vector<S2C_Explore_Plant>::iterator it = status.m_plantList.begin();
			std::vector<S2C_Explore_Plant>::iterator end = status.m_plantList.end();
			for (; it != end; ++it)
			{
				S2C_Explore_Plant plant = *it;
				if (plant.status == 0)
					playerInfo->SetAdventurePlantEndTime(plant.plantId, plant.endTime, false);
				else if (plant.status == 1 || plant.status == 2)
					playerInfo->RemoveAdventurePlants(plant.plantId);
			}
			playerInfo->SetNeedSave(true);
			playerInfo->SAVE_PROFILE();
		}
		gMessageRouter->Post(&Message::GotExplorePlantStatus, status.m_dungeonId, true);
	}
	else
		gMessageRouter->Post(&Message::GotExplorePlantStatus, -1, false);
}

/////////////// Charge and binding responses ///////////////

void androidNetworkMsgProcess::OnRequestUpdateChargeInfo(const NetWorkMsg& data)
{
	if (data.erro == 0)
	{
		S2C_Purchase_ValidateResult result;
		result.SerializeJson(data.msg);
		if (result.objectId > 0)
		{
			PlayerInfo* playerInfo = ProfileUtils::Profile();
			if (playerInfo != NULL)
				gMessageRouter->Post(&Message::RechargeRewardCurrencyChanged, playerInfo->GetNumRechargeCurrency());
		}
		gMessageRouter->Post(&Message::NotifyPurchaseValidation, data.erro, std::string(result.skuId), result.status);
		Cpp2Lua("ValidateChargeFinish", result.skuId);
	}
	else
		gMessageRouter->Post(&Message::NotifyPurchaseValidation, data.erro, "", -1);
}

void androidNetworkMsgProcess::OnICloudRequestBindingUniqueID(const NetWorkMsg& data)
{
	if (data.erro == 0)
	{
		gLawnApp->GetMainMenu()->SetBindBtnEnable(false);
		m_bShouldBindUniqueID = false;
		if (m_bBindForUUID)
			IdentifierMgr::GetInstance().SetUUIDLogin(false);
		ProfileMgr::GetInstance().LoginiCloudServer();
		Sexy::OutputDebugStrF("OnICloudRequestBindingUniqueID----success");
	}
	else
	{
		std::string errorKey = Sexy::StrFormat("[PVZ_ERROR_%d]", data.erro);
		if (StringHelper::IsStringValueExist(errorKey))
		{
			UIMessageBox* box = UISingletonDialog<UIMessageBox>::ShowDialog();
			if (box != NULL)
			{
				box->SetMessage(errorKey, "[REVIVE_TIP]");
				box->SetShowType(UIMessageBox::Type_ShowOK);
				box->SetBackgroundDarken(true);
			}
		}
		Sexy::OutputDebugStrF("OnICloudRequestBindingUniqueID----error %d", data.erro);
	}
}

/////////////// Continued login ///////////////

void androidNetworkMsgProcess::DoContinuedLoginV202()
{
	GetNetworkCacheQueue()->setUserID(m_UserId);
	GetNetworkCacheQueue()->setSessionKey(m_sk);
	SaveCache();

	TGAAppLaunch launch;
	launch._step = "8";
	TGALogMgr::GetInstance().LogAppLaunch(launch);

	if (gLawnApp->CheckProfileOpen())
	{
		if (ProfileMgr::GetInstance().GetNumProfiles() == 0)
		{
			Sexy::OutputDebugStrF("ACLog - OnICloudRequstLogin No Local Profile");
			RequestDownloadPlayerData();
			goto done;
		}
		PlayerInfo* playerInfo = ProfileUtils::Profile();
		if (!playerInfo->UnserializeACLog(m_oaclk))
		{
			Sexy::OutputDebugStrF("ACLog - OnICloudRequstLogin Cheat Profile");
			RequestDownloadPlayerData();
			goto done;
		}
		if (!m_oaclk.empty())
		{
			if (RequestSyncPlayerData() == E_SYNC_PROFILE_PROFILE_ERROR)
			{
				gMessageRouter->Post(&Message::LoginiCloudServerFinish, false);
				goto done;
			}
			goto success;
		}
		ICloudRequestProfileMd5();
	}
	else if (ProfileMgr::GetInstance().GetNumProfiles() > 0)
	{
		PlayerInfo* playerInfo = ProfileUtils::Profile();
		playerInfo->ClearACLog();
		playerInfo->SerializeACLog("");
	}
success:
	gMessageRouter->Post(&Message::LoginiCloudServerFinish, true);
done:
	m_ICIoudState = Response_Success;
}

/////////////// Profile requests ///////////////

bool androidNetworkMsgProcess::ICloudRequestGetProfile()
{
	bool result = IsLogined();
	if (result)
	{
		std::stringstream stream;
		stream << GetRandom();
		ParaMap params;
		params["req"] = m_pktID.ID_ICLOUD_GET_PROFILE;
		params["ui"] = m_UserId;
		params["sk"] = m_sk;
		result = isSessionKeyValid();
		if (result)
			SendHttpRequest(params, true);
	}
	return result;
}

bool androidNetworkMsgProcess::ICloudRequestProfileMd5()
{
	bool result = IsLogined();
	if (result)
	{
		std::stringstream stream;
		stream << GetRandom();
		ParaMap params;
		params["req"] = m_pktID.ID_ICLOUD_GET_PROFILE_MD5;
		params["ui"] = m_UserId;
		params["sk"] = m_sk;
		result = isSessionKeyValid();
		if (result)
			SendHttpRequest(params, true);
	}
	return result;
}

/////////////// Sync by name ///////////////

bool androidNetworkMsgProcess::ICloudRequestSyncWithNameAndSource(const std::string& i_objectName, int i_quantity, std::string i_src, int i_level)
{
	int objectId = id_mat_Gem;
	if (i_objectName == "gems")
	{
	}
	else if (PlantChipNameMapperServerID::GetInstance().ContainsName(i_objectName) || PlantAccessoryInfoMapper::GetInstance().ContainsName(i_objectName))
		objectId = PlantChipNameMapperServerID::GetInstance().GetIdForName(i_objectName);
	else if (AvatarChipNameMapperServerID::GetInstance().ContainsName(i_objectName))
		objectId = AvatarChipNameMapperServerID::GetInstance().GetIdForName(i_objectName);
	else
	{
		objectId = 0;
		if (PlantAccessoryPieceMapper::GetInstance().ContainsName(i_objectName))
			objectId = PlantAccessoryPieceMapper::GetInstance().GetIdForName(i_objectName);
	}
	ICloudRequestSyncWithIdAndSource(objectId, i_quantity, i_src, i_level);
	return true;
}

/////////////// Object lists ///////////////

std::string androidNetworkMsgProcess::getObjectJsons(const int i_objectId, int i_quantity, std::string i_src)
{
	std::string result("");
	result += "[";
	std::stringstream stream;
	result += "{\"i\":";
	stream.str("");
	stream << i_objectId;
	result += stream.str();
	result += ",\"q\":";
	stream.str("");
	stream << i_quantity;
	result += stream.str();
	result += ",\"f\":\"";
	result += i_src;
	result += "\"}";
	result += "]";
	return result;
}

std::string androidNetworkMsgProcess::getObjectJsons(const std::vector<NetworkCacheObjects>& i_objectList)
{
	std::string result("");
	result += "[";
	std::stringstream stream;
	std::vector<NetworkCacheObjects>::const_iterator it = i_objectList.begin();
	std::vector<NetworkCacheObjects>::const_iterator end = i_objectList.end();
	for (; it != end; ++it)
	{
		const NetworkCacheObjects& object = *it;
		result += "{\"i\":";
		stream.str("");
		stream << object.objectId;
		result += stream.str();
		result += ",\"q\":";
		stream.str("");
		stream << object.quantity;
		result += stream.str();
		result += ",\"f\":\"";
		result += object.source;
		result += "\"},";
	}
	result.erase(result.end() - 1);
	result += "]";
	return result;
}

/////////////// Object sync ///////////////

bool androidNetworkMsgProcess::ICloudRequestSyncWithIdAndSource(const int i_objectId, int i_quantity, std::string i_src, int i_level)
{
	if (__builtin_expect(!!(gLawnApp->IsNetworkModuleOK()), 1))
	{
		ParaMap params;
		params["req"] = m_pktID.ID_ICLOUD_REQUEST_SYNC_CACHED_OBJECTS;
		params["ui"] = m_UserId;
		params["sk"] = m_sk;
		std::stringstream stream;
		SetNumParam(params, "pi", stream, ProfileMgr::GetInstance().GetCurrentProfile()->GetProfileId());
		params["o"] = getObjectJsons(i_objectId, i_quantity, i_src);
		stream.str("");
		ProfileMgr::GetInstance().GetCurrentProfile()->increaseUploadKey();
		stream << ProfileMgr::GetInstance().GetCurrentProfile()->getUploadKey();
		params["uk"] = stream.str();
		params["nfc"] = "1";
		SendHttpRequest(params, true);
	}
	else
	{
		GetNetworkCacheQueue()->insertCachedObject(i_objectId, i_quantity, i_src);
		SaveCache();
	}
	return true;
}

bool androidNetworkMsgProcess::ICloudRequestSyncObjectListWithSource(const std::vector<NetworkCacheObjects>& i_gemsList)
{
	bool networkOk = gLawnApp->IsNetworkModuleOK();
	bool busy = false;
	if (networkOk && !(busy = isNetworkBusy))
	{
		isNetworkBusy = true;
		ParaMap params;
		params["req"] = m_pktID.ID_ICLOUD_REQUEST_SYNC_CACHED_OBJECTS;
		params["ui"] = m_UserId;
		params["sk"] = m_sk;
		std::stringstream stream;
		SetNumParam(params, "pi", stream, ProfileMgr::GetInstance().GetCurrentProfile()->GetProfileId());
		params["o"] = getObjectJsons(i_gemsList);
		stream.str("");
		ProfileMgr::GetInstance().GetCurrentProfile()->increaseUploadKey();
		stream << ProfileMgr::GetInstance().GetCurrentProfile()->getUploadKey();
		params["uk"] = stream.str();
		params["nfc"] = "1";
		SendHttpRequest(params, true);
	}
	return networkOk;
}

void androidNetworkMsgProcess::OnICloudRequestSyncCachedObjects(const NetWorkMsg& data)
{
	isNetworkBusy = false;
	if (data.erro == 0)
	{
		S2C_SyncCachedObjectsInfo info;
		info.m_gold = 0;
		bool parsed = info.SerializeJson(data.msg);
		PlayerInfo* playerInfo = ProfileUtils::Profile();
		if (!parsed || playerInfo == NULL)
			return;
		playerInfo->SetNeedSave(false);
		playerInfo->AddCoins(info.m_gold);
		playerInfo->AddCommonGachaRewardList(info.m_bonusList, false);
		playerInfo->SetGems(info.m_gems);
		std::vector<S2C_PlantPendantInfo>::iterator it = info.m_pendantInfo.begin();
		std::vector<S2C_PlantPendantInfo>::iterator end = info.m_pendantInfo.end();
		for (; it != end; ++it)
		{
			S2C_PlantPendantInfo& pendant = *it;
			std::string name("");
			if (PlantAccessoryInfoMapper::GetInstance().ContainsId(pendant.type_id))
			{
				name = PlantAccessoryInfoMapper::GetInstance().GetNameForId(pendant.type_id);
				if (!playerInfo->HasPlantAccessoryInfos(name, pendant.pendant_id))
					playerInfo->AddPlantAccessoryInfos(name, pendant.pendant_id, true);
			}
		}
		playerInfo->SetNeedSave(true);
		playerInfo->SAVE_PROFILE();
		GetNetworkCacheQueue()->onFlushedCachedObjects(info.m_nfc != 0);
		SaveCache();
	}
}

void androidNetworkMsgProcess::OnICloudRequestStopExplore(const NetWorkMsg& data)
{
	if (data.erro == 0)
	{
		S2C_StopExplore info;
		info.SerializeJson(data.msg);
		if (info.m_flag == 5)
			ADManager::GetInstance().SetADWatchCount(ADType_PlantAdventureSkip, info.m_adCount);
		else if (info.m_flag == 7)
			ADManager::GetInstance().SetADWatchCount(ADType_PlantAdventureBonusCount, info.m_adCount);

		PlayerInfo* playerInfo = ProfileMgr::GetInstance().GetCurrentProfile();
		int dungeonId;
		int state;
		if (playerInfo == NULL)
		{
			state = -1;
			dungeonId = -1;
		}
		else
		{
			dungeonId = info.m_teamList[0].dungeonId;
			state = info.m_teamList[0].status;
			if (info.diamondLess != 0)
			{
				gMessageRouter->Post(&Message::FreeExplore, dungeonId, info.diamondLess == 1);
				return;
			}
			playerInfo->SetNeedSave(false);
			unsigned int chances = info.m_teamList[0].chances;
			unsigned int surprise = info.m_teamList[0].surprise;
			unsigned int endTime = info.m_teamList[0].exploreEndTime;
			int adventureState = playerInfo->GetPlantAdventureState(dungeonId);
			if (adventureState != 5 && state != 0)
			{
				playerInfo->FixPlantAdventureInfoByServer(dungeonId, state, chances, 0 < (int)surprise, endTime, info.m_teamList[0].plantsList, info.m_teamList[0].addChanceCount);
				if ((unsigned)(state - 2) > 1 && adventureState - 2U < 2)
					playerInfo->RemovePlantAdventureInfo(dungeonId, 0);
			}
			playerInfo->SetGems(info.m_playerInfo.m_Gems);
			playerInfo->SetNeedSave(true);
			playerInfo->SAVE_PROFILE();
		}
		gMessageRouter->Post(&Message::StopExplore, dungeonId, state, true);
	}
	else
		gMessageRouter->Post(&Message::StopExplore, -1, -1, false);
}

void androidNetworkMsgProcess::OnICloudRequestGetExploreTeamStatus(const NetWorkMsg& data)
{
	if (data.erro == 0)
	{
		S2C_ExplorerTeamStatus status;
		status.SerializeJson(data.msg);
		PlayerInfo* playerInfo = ProfileMgr::GetInstance().GetCurrentProfile();
		if (playerInfo != NULL)
		{
			playerInfo->SetNeedSave(false);
			playerInfo->RemoveAllAdventure(false, false, true);
			std::vector<PlantAdventureInfo> infos;
			std::vector<S2C_Explore_Team>::iterator it = status.m_teamList.begin();
			std::vector<S2C_Explore_Team>::iterator end = status.m_teamList.end();
			for (; it != end; ++it)
			{
				S2C_Explore_Team team = *it;
				PlantAdventureInfo info;
				int dungeonId = team.dungeonId;
				unsigned int stateOffset = team.status - 2;
				playerInfo->SetPlantAdventureState(team.dungeonId, team.status, team.chances, true, team.addChanceCount);
				if (stateOffset < 2)
				{
					info.inited = true;
					info.coinBonus = team.coins;
					info.itemBonus = team.bonusItem;
					info.plantChipId = team.plantChipId;
					info.plantChipQuantity = team.bonus;
					info.hasSurprise = 0 < team.surprise;
					info.surpriseObjectId = team.surpriseObjectId;
					info.surprisePrice = team.surprisePrice;
					info.surpriseQuantity = team.surprise;
					info.endTime = team.exploreEndTime;
					info.dungeonId = dungeonId;
					int showTime = playerInfo->GetPlantAdventureInfo(dungeonId).surpriseShowTime;
					if (showTime < 1)
						info.surpriseShowTime = info.endTime + 60 - Sexy::Rand(5400);
					else
						info.surpriseShowTime = showTime;
					info.plantIdList = team.plantsList;
					infos.push_back(info);
				}
			}
			playerInfo->RemoveAllAdventure(true, true, false);
			playerInfo->SetPlantAdventureInfos(infos);
			playerInfo->SetNeedSave(true);
			playerInfo->SAVE_PROFILE();
		}
		gMessageRouter->Post(&Message::OpenPlantAdventure, true);
		gMessageRouter->Post(&Message::GotExploreTeamStatus, true);
	}
	else
	{
		gMessageRouter->Post(&Message::OpenPlantAdventure, false);
		gMessageRouter->Post(&Message::GotExploreTeamStatus, false);
	}
}

void androidNetworkMsgProcess::OnICloudRequestCalcExploreReward(const NetWorkMsg& data)
{
	if (data.erro == 0)
	{
		S2C_ExploreReward reward;
		reward.SerializeJson(data.msg);
		PlayerInfo* playerInfo = ProfileMgr::GetInstance().GetCurrentProfile();
		if (playerInfo != NULL)
		{
			playerInfo->SetNeedSave(false);
			unsigned int state = reward.m_teamList[0].status;
			unsigned int chances = reward.m_teamList[0].chances;
			unsigned int dungeonId = reward.m_teamList[0].dungeonId;
			unsigned int surprise = reward.m_teamList[0].surprise;
			unsigned int endTime = reward.m_teamList[0].exploreEndTime;
			int adventureState = playerInfo->GetPlantAdventureState(dungeonId);
			playerInfo->AddCoins(reward.m_teamList[0].coins);
			ADManager::GetInstance().SetADWatchCount(ADType_PlantAdventureBonusReward, reward.m_adCount);
			int crystalId = MaterialItemMapper::GetInstance().GetIdForName("mat_mystery_crystal");
			int crystalBonus = reward.m_teamList[0].bonusItem;
			if (0 < crystalBonus)
			{
				int amount = MysteryCrystalMgr::GetInstance().GetRealDropAmount(crystalBonus);
				MysteryCrystalMgr::GetInstance().AddToCurrentGained(amount);
				if (MysteryCrystalMgr::GetInstance().CanAwards(amount))
					ProfileChangeItemAmount(crystalId, amount, false);
			}
			if (adventureState != 5 && state != 0)
			{
				playerInfo->FixPlantAdventureInfoByServer(dungeonId, state, chances, 0 < (int)surprise, endTime, reward.m_teamList[0].plantsList, reward.m_teamList[0].addChanceCount);
				if (state - 2 > 1 && adventureState - 2U < 2)
					playerInfo->RemovePlantAdventureInfo(dungeonId, 0);
			}
			playerInfo->AddCommonGachaRewardList(reward.m_plantChipInfo, false);
			playerInfo->SetNeedSave(true);
			playerInfo->SAVE_PROFILE();
		}
		gMessageRouter->Post(&Message::GotExploreReward, true);
	}
	else
		gMessageRouter->Post(&Message::GotExploreReward, false);
}

void androidNetworkMsgProcess::OnICloudRequestStartExplore(const NetWorkMsg& data)
{
	if (data.erro == 0)
	{
		S2C_ExplorerStart start;
		start.SerializeJson(data.msg);
		if (start.needGems == 1)
		{
			gMessageRouter->Post(&Message::NeedRecoverExplorePlant, start.gemCost);
			return;
		}
		Sexy::SRand(time(NULL));
		PlayerInfo* playerInfo = ProfileMgr::GetInstance().GetCurrentProfile();
		if (playerInfo != NULL && playerInfo->CanStartNewPlantAdventure())
		{
			playerInfo->SetNeedSave(false);
			playerInfo->SetGems(start.m_playerInfo.m_Gems);
			std::vector<S2C_Explore_Team>::iterator it = start.m_teamList.begin();
			std::vector<S2C_Explore_Team>::iterator end = start.m_teamList.end();
			for (; it != end; ++it)
			{
				S2C_Explore_Team team = *it;
				int surprisePrice = team.surprisePrice;
				int coins = team.coins;
				int surprise = team.surprise;
				int surpriseObjectId = team.surpriseObjectId;
				int bonus = team.bonus;
				int plantChipId = team.plantChipId;
				int status = team.status;
				int chances = team.chances;
				int dungeonId = team.dungeonId;
				unsigned int endTime = team.exploreEndTime;
				int itemBonus = 0;
				if (MysteryCrystalMgr::GetInstance().CanAwards(team.bonusItem))
					itemBonus = team.bonusItem;
				PlantAdventureInfo info;
				info.dungeonId = dungeonId;
				info.coinBonus = coins;
				info.plantChipId = plantChipId;
				info.plantChipQuantity = bonus;
				info.surpriseObjectId = surpriseObjectId;
				info.surprisePrice = surprisePrice;
				info.surpriseQuantity = surprise;
				info.hasSurprise = 0 < surprise;
				info.inited = true;
				info.itemBonus = itemBonus;
				info.surpriseShowTime = Sexy::Rand(5400);
				info.endTime = endTime;
				info.surpriseShowTime = (endTime + 60) - info.surpriseShowTime;
				std::vector<int>::iterator plant = team.plantsList.begin();
				std::vector<int>::iterator plantEnd = team.plantsList.end();
				for (; plant != plantEnd; ++plant)
					info.plantIdList.push_back(*plant);
				playerInfo->AddPlantAdventureInfo(info);
				int adventureState = playerInfo->GetPlantAdventureState(dungeonId);
				if (adventureState != 5 && status != 0)
				{
					playerInfo->FixPlantAdventureInfoByServer(dungeonId, status, chances, 0 < surprise, endTime, team.plantsList, team.addChanceCount);
					if (status - 2U > 1 && adventureState - 2U < 2)
						playerInfo->RemovePlantAdventureInfo(dungeonId, 0);
				}
			}
			playerInfo->SetNeedSave(true);
			playerInfo->SAVE_PROFILE();
		}
		gMessageRouter->Post(&Message::StartExplore, true);
	}
	else
		gMessageRouter->Post(&Message::StartExplore, false);
}

void androidNetworkMsgProcess::OnICloudRequestUpLoadProfile(const NetWorkMsg& data)
{
	if (data.erro == 0)
	{
		m_bCanUpLoadProfile = true;
		ProfileMgr::GetInstance().SaveResult(true);
		gMessageRouter->Post(&Message::SyncProfileToServerFinish, true);
		return;
	}
	if (data.erro == 45014)
	{
		PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(UIScaleNum(400), UIScaleNum(250));
		dialog->SetHeaderLabel(SexyString(L"[REVIVE_TIP]"));
		dialog->SetFooterLabel(SexyString(L"[PVZ_LOGIN_LOW_VERSION]"));
		dialog->SetHeaderFont(PrimeText_Game::Typeface_FZShaoEr_28_Outline->Typeface(), PrimeText_Game::Color_Generic_Title);
		dialog->SetFooterFont(PrimeText_Game::Typeface_FZCuYuan_19_HardShadow->Typeface(), Sexy::Color(Sexy::Color::White));
		dialog->SetBackgroundDarken(true);
		dialog->AddButton(SexyString(L"[PVZ_LOGIN_GO_UPDATE]"), Sexy::Delegate0(Sexy::MakeDelegate(*gLawnApp, &LawnApp::OnHandleUpdateGame)));
		dialog->SetAlwaysExist(true);
		return;
	}
	m_bCanUpLoadProfile = false;
	ProfileMgr::GetInstance().SaveResult(false);
	gMessageRouter->Post(&Message::SyncProfileToServerFinish, false);
}

/////////////// Account binding ///////////////

void androidNetworkMsgProcess::ICloudRequestBindingUniqueID(const std::string& platform_id, const std::string& uniqueID)
{
	ParaMap params;
	params["req"] = m_pktID.ID_ICOUD_BIND_UNIQUE_ID;
	params["di"] = DefineIDMgr::GetInstance().GetNewUserDefineID();
	params["ui"] = m_UserId;
	params["sk"] = m_sk;
	params["pi"] = "";
	params["t"] = "";
	params["oi"] = uniqueID.c_str();
	if (m_bBindForUUID)
		params["uuid"] = IdentifierMgr::GetInstance().GetUUID();
	SendHttpRequest(params);
}

/////////////// Red pack leaderboard ///////////////

void androidNetworkMsgProcess::OnRequestGetRedPackLeaderBoard(const NetWorkMsg& data)
{
	if (data.erro == 0)
	{
		S2C_ICloud_RedPackLeaderBoard board;
		Sexy::StructuredData json;
		if (!StringHelper::ReadJson(data.msg, &json))
			return;
		const Sexy::StructuredData::Value* root = json.ValueForPath("$.d");
		if (root == NULL)
			return;
		const Sexy::StructuredData::Value* list = root->ArrayForName("ny5rpprl");
		board.m_selfInRank = root->IntegerForName("sir", 0);
		for (const Sexy::StructuredData::Value* it = list->ChildrenBegin(); it != list->ChildrenEnd(); it = it->Next())
		{
			if (it != NULL)
			{
				S2C_RedPack_Public entry;
				entry.m_score = it->StringForName("s", "");
				entry.m_name = it->StringForName("n", "");
				entry.m_rank = it->IntegerForName("r", 0);
				board.m_redPackLeaderBoard.push_back(entry);
			}
			__asm__ volatile("" ::: "memory");
		}
		gMessageRouter->Post(&Message::ProcessRedPackLeaderBoardInfo, &board);
	}
}

void androidNetworkMsgProcess::onRequestDownloadPlayerData(const NetWorkMsg& data)
{
	if (data.erro == 0)
	{
		S2C_ICloud_GetProfile result;
		result.SerializeJson(data.msg);
		std::string profileJson = base64_decode_url_safe(result.m_profile.profile);
		MD5 md5(profileJson);
		if (md5.toString() != result.m_profile.md5)
		{
			if (m_downloadProfileRetry < m_retryRequestTimes)
			{
				m_downloadProfileRetry++;
				RequestDownloadPlayerData();
				Sexy::OutputDebugStrF("ACLog - onRequestDownloadPlayerData: retry");
			}
			else
			{
				m_ICIoudState = Response_Error;
				ShowErrorMessage(INetworkErrorData(90000));
				Sexy::OutputDebugStrF("ACLog - onRequestDownloadPlayerData: retry failed");
			}
		}
		else
		{
			PlayerInfo* playerInfo = ProfileUtils::Profile();
			if (playerInfo == NULL)
			{
				playerInfo = ProfileMgr::GetInstance().CreateProfileFromServer(profileJson);
				Sexy::OutputDebugStrF("ACLog - onRequestDownloadPlayerData: CreateProfileFromServer");
			}
			else
			{
				playerInfo->SetMapConversionState(MAPCONVERSION_None);
				playerInfo->UpdateDeltaDataFromServer(profileJson, result.m_profile.md5, result.m_profile.lastUpdateTime);
				playerInfo->ResetStarTotal();
				ProfileMgr::GetInstance().setCurrentProfileIndex(playerInfo->GetProfileIndex());
			}
			playerInfo->SerializeACLog(m_aclk);
			playerInfo->SAVE_PROFILE();
			S2C_ACLog::ClearLogIndex();
			m_downloadProfileRetry = 0;
			m_ICIoudState = Response_Success;
			m_syncProfileRetry = 0;
			gMessageRouter->Post(&Message::LoginiCloudServerFinish, true);
			Sexy::OutputDebugStrF("ACLog - onRequestDownloadPlayerData: sync profile successfully");
		}
	}
	else if (data.erro == 75504)
	{
		if (ProfileMgr::GetInstance().GetNumProfiles() > 0)
		{
			gLawnApp->RemoveAllCaches();
			ShowErrorMessage(INetworkErrorData(90001));
		}
		m_ICIoudState = Response_Success;
		m_downloadProfileRetry = 0;
		m_syncProfileRetry = 0;
		gMessageRouter->Post(&Message::LoginiCloudServerFinish, false);
		Sexy::OutputDebugStrF("ACLog - onRequestDownloadPlayerData: error : 75504");
	}
	else
	{
		m_downloadProfileRetry = 0;
		m_syncProfileRetry = 0;
		m_ICIoudState = Response_Error;
		ShowErrorMessage(INetworkErrorData(data.erro));
		Sexy::OutputDebugStrF("ACLog - onRequestDownloadPlayerData: error : %d", data.erro);
	}
}

void androidNetworkMsgProcess::OnICloudRequestChargeReward(const NetWorkMsg& data)
{
	if (EA_UNLIKELY(data.erro != 0))
	{
		gMessageRouter->Post(&Message::FirstRechargePackageGot);
		return;
	}
	S2C_ICloud_GetChargeRewardInfo info;
	info.SerializeJson(data.msg);
	PlayerInfo* playerInfo = ProfileUtils::Profile();
	if (playerInfo != NULL)
	{
		playerInfo->SetNeedSave(false);
		std::map<int, int> rewards;
		std::vector<S2C_BonusInfo>::iterator it = info.m_bonusList.begin();
		std::vector<S2C_BonusInfo>::iterator end = info.m_bonusList.end();
		for (; it != end; ++it)
		{
			S2C_BonusInfo& bonus = *it;
			int objectId = bonus.objectId;
			int quantity = bonus.quantity;
			if (OtherServerNameMapper::GetInstance().IsServerCoin(objectId))
				playerInfo->AddCoins(quantity);
			else if (OtherServerNameMapper::GetInstance().IsServerCuke(objectId))
				playerInfo->ModifyPowerupUses("poweruptacticalcuke", quantity);
			else if (objectId == 25330)
				UserInfo::getInstance()->unlockHeadShotId(25330);
			else
				ProfileChangeItemAmount(objectId, quantity, false);
			rewards[objectId] = quantity;
		}
		const wchar_t* title;
		if (info.m_typeId == 3)
		{
			gMessageRouter->Post(&Message::RechargeRewardGot, 1, info.m_chargeNum, rewards);
			title = L"[RECHARGE_PACKAGE_FIRST_RECHARGE_TITLE]";
			goto showBox;
		}
		if (info.m_typeId == 4)
		{
			gMessageRouter->Post(&Message::TotalRechargePackageGot, true, &info);
			title = L"[RECHARGE_PACKAGE_REWARD_TITLE]";
showBox:
			gLawnApp->ShowServerBoxOpenUI(rewards, SexyString(title));
		}
		playerInfo->SetGems(info.m_playerInfo.m_Gems);
		playerInfo->SetNeedSave(true);
		playerInfo->SAVE_PROFILE();
		if (gLawnApp->IsCoinStoreShowing())
			gMessageRouter->Post(&Message::RechargeCurrencyChanged);
	}
}

/////////////// Charge reward ///////////////

bool androidNetworkMsgProcess::ICloudRequestChargeReward(int i_type, int i_index, int i_select_index)
{
	ParaMap params;
	params["req"] = m_pktID.ID_ICLOUD_GET_CHARGE_REWARD;
	params["ui"] = m_UserId;
	params["sk"] = m_sk;
	std::stringstream stream;
	SetNumParam(params, "pi", stream, ProfileMgr::GetInstance().GetCurrentProfile()->GetProfileId());
	stream.clear();
	SetNumParam(params, "m", stream, ProfileMgr::GetInstance().GetCurrentProfile()->GetLastPurchaseReceiptMD5());
	stream.clear();
	SetNumParam(params, "t", stream, i_type);
	stream.clear();
	SetNumParam(params, "i", stream, i_index);
	stream.clear();
	SetNumParam(params, "rv", stream, gLawnApp->m_localRsbVersion);
	if (i_select_index != -1)
	{
		stream.clear();
		SetNumParam(params, "s", stream, i_select_index);
	}
	SendHttpRequest(params, true);
	return true;
}

/////////////// Player data sync ///////////////

void androidNetworkMsgProcess::onRequestSyncPlayerData(const NetWorkMsg& data)
{
	if (data.erro == 0)
	{
		PlayerInfo* playerInfo = ProfileUtils::Profile();
		if (playerInfo != NULL)
			playerInfo->ClearACLog();
		gMessageRouter->Post(&Message::LoginiCloudServerFinish, true);
		m_downloadProfileRetry = 0;
		m_syncProfileRetry = 0;
		m_ICIoudState = Response_Success;
		ProfileMgr::GetInstance().SaveResult(true);
		S2C_ACLog::ClearLogIndex();
		Sexy::OutputDebugStrF("ACLog - onRequestSyncPlayerData: upload successfully");
	}
	else if (data.erro == 75000)
	{
		if (m_downloadProfileRetry < m_retryRequestTimes)
		{
			RequestDownloadPlayerData();
			ProfileMgr::GetInstance().SaveResult(false);
			ShowErrorMessage(INetworkErrorData(data.erro));
			Sexy::OutputDebugStrF("ACLog - onRequestSyncPlayerData: error : 75000");
		}
	}
	else if (data.erro == 75012)
	{
		RequestDownloadPlayerData();
		ProfileMgr::GetInstance().SaveResult(false);
		ShowErrorMessage(INetworkErrorData(data.erro));
		Sexy::OutputDebugStrF("ACLog - onRequestSyncPlayerData: error : 75012");
	}
	else if (data.erro == 75011)
	{
		unsigned char retry = m_syncProfileRetry;
		m_syncProfileRetry = retry + 1;
		if (m_retrySyncProfileTimes <= retry)
		{
			if (data.erro == 45014)
			{
				PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(UIScaleNum(400), UIScaleNum(250));
				dialog->SetHeaderLabel(SexyString(L"[REVIVE_TIP]"));
				dialog->SetFooterLabel(SexyString(L"[PVZ_LOGIN_LOW_VERSION]"));
				dialog->SetHeaderFont(PrimeText_Game::Typeface_FZShaoEr_28_Outline->Typeface(), PrimeText_Game::Color_Generic_Title);
				dialog->SetFooterFont(PrimeText_Game::Typeface_FZCuYuan_19_HardShadow->Typeface(), Sexy::Color(Sexy::Color::White));
				dialog->SetBackgroundDarken(true);
				dialog->AddButton(SexyString(L"[PVZ_LOGIN_GO_UPDATE]"), Sexy::Delegate0(Sexy::MakeDelegate(*gLawnApp, &LawnApp::OnHandleUpdateGame)));
				dialog->SetAlwaysExist(true);
			}
			else
			{
				m_syncProfileRetry = 0;
				ShowErrorMessage(INetworkErrorData(90002));
				ProfileMgr::GetInstance().SaveResult(false);
				Sexy::OutputDebugStrF("ACLog - onRequestSyncPlayerData: error : 90002");
			}
		}
		else
		{
			S2C_ProfileSync sync;
			sync.SerializeJson(data.msg);
			Sexy::OutputDebugStrF("ACLog - onRequestSyncPlayerData, aclog : %s", sync.strMissLogs.c_str());
			PlayerInfo* playerInfo = ProfileUtils::Profile();
			if (playerInfo != NULL)
			{
				ACLogProfile profile;
				if (CheckUseACLogKey())
				{
					std::string json;
					json = DecryptString(sync.strMissLogs.c_str(), sync.strMissLogs.length(), m_aclk.c_str());
					Sexy::OutputDebugStrF("ACLog - onRequestSyncPlayerData, aclog json : %s, key : %s", json.c_str(), m_aclk.c_str());
					if (!profile.SerializeJsonToObj(json, "ml"))
						Sexy::OutputDebugStrF("ACLog - onRequestSyncPlayerData, aclog json to object error : %s");
					sync.missLogs = profile.logList;
				}
				std::vector<S2C_ACLog>::iterator it = sync.missLogs.begin();
				std::vector<S2C_ACLog>::iterator end = sync.missLogs.end();
				for (; it != end; ++it)
				{
					S2C_ACLog log = *it;
					Sexy::OutputDebugStrF("ACLog - onRequestSyncPlayerData, push ac log");
					playerInfo->PushACLog(log);
				}
				playerInfo->SerializeACLog(m_aclk);
				RequestSyncPlayerData();
			}
			Sexy::OutputDebugStrF("ACLog - onRequestSyncPlayerData: error : 75011");
		}
	}
	else
	{
		m_downloadProfileRetry = 0;
		m_syncProfileRetry = 0;
		ShowErrorMessage(INetworkErrorData(data.erro));
		ProfileMgr::GetInstance().SaveResult(false);
		Sexy::OutputDebugStrF("ACLog - onRequestSyncPlayerData: error : %d", data.erro);
	}
}

/////////////// UUID login ///////////////

void androidNetworkMsgProcess::onRequestUUIDLogin(const NetWorkMsg& data)
{
	if (data.erro == 0)
	{
		SettingsDialog::SetHaveSendV202(true);
		S2C_ICloud_LoginResult result;
		result.SerializeJson(data.msg);
		std::stringstream stream;
		stream << result.m_UserId;
		m_UserId = stream.str();
		m_sk = result.m_sk;
		m_aclk = result.m_NewKey;
		m_oaclk = result.m_OldKey;
		m_useACLogKey = result.m_encrypt;
		m_bShouldBindUniqueID = result.m_bindUniqueID;
		m_bBindForUUID = true;
		ProfileMgr::GetInstance().SetSaveInterval(result.m_saveInterval);
		SettingsDialog::SetEncryptIndex(result.m_idEncryptIndex);
		if (GetServerSignature() != result.m_signature)
		{
			m_UserId = "";
			m_sk = "";
		}
		Sexy::OutputDebugStrF("INetworkMsgProcess::onRequestUUIDLogin erro = [%d], userid = [%s]", data.erro, m_UserId.c_str());
		Sexy::OutputDebugStrF("\nINIT SERVERTIME BY LOGIN = [%ld]\n", result.m_serverTime);
		gLawnApp->InitServerTimeOffset(result.m_serverTime);
		gLawnApp->SetProfileCreatedTime(result.m_createdTime);
		if (0 < result.m_PlayerReturnDays)
		{
			TGAPlayerReturnData returnData;
			returnData._day = DString(result.m_PlayerReturnDays).c_str();
			TGALogMgr::GetInstance().LogPlayerReturn(returnData);
		}
		GetNetworkCacheQueue()->setUserID(m_UserId);
		GetNetworkCacheQueue()->setSessionKey(m_sk);
		SaveCache();
		if (gLawnApp->CheckProfileOpen())
		{
			if (ProfileMgr::GetInstance().GetNumProfiles() == 0)
			{
				Sexy::OutputDebugStrF("ACLog - OnICloudRequstLogin No Local Profile");
				RequestDownloadPlayerData();
			}
			else
			{
				PlayerInfo* playerInfo = ProfileUtils::Profile();
				if (!playerInfo->UnserializeACLog(m_oaclk))
				{
					Sexy::OutputDebugStrF("ACLog - OnICloudRequstLogin Cheat Profile");
					RequestDownloadPlayerData();
				}
				else if (m_oaclk.empty())
				{
					ICloudRequestProfileMd5();
					gMessageRouter->Post(&Message::LoginiCloudServerFinish, true);
					m_ICIoudState = Response_Success;
				}
				else if (RequestSyncPlayerData() == E_SYNC_PROFILE_PROFILE_ERROR)
				{
					gMessageRouter->Post(&Message::LoginiCloudServerFinish, false);
					m_ICIoudState = Response_Error;
				}
				else
				{
					gMessageRouter->Post(&Message::LoginiCloudServerFinish, true);
					m_ICIoudState = Response_Success;
				}
			}
		}
		else
		{
			gMessageRouter->Post(&Message::LoginiCloudServerFinish, true);
			m_ICIoudState = Response_Success;
		}
		gMessageRouter->Broadcast(&Message::NotifyUUIDLogin, true);
	}
	else if (data.erro == 20507)
	{
		SettingsDialog::SetIsACheatProfile(true);
		PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(UIScaleNum(400), UIScaleNum(250));
		std::string uid = GetEncryptIDString(GetNetworkCacheQueue()->getUserID(), SettingsDialog::GetEncryptIndex());
		SexyString uidText = Sexy::ToWString(uid);
		SexyString footer = TodReplaceString(TodStringTranslate(L"[PVZ_LOGIN_CHEAT_ERROR]"), L"{UID}", uidText);
		dialog->SetHeaderLabel(SexyString(L"[REVIVE_TIP]"));
		dialog->SetFooterLabel(footer);
		dialog->SetHeaderFont(PrimeText_Game::Typeface_FZShaoEr_28_Outline->Typeface(), PrimeText_Game::Color_Generic_Title);
		dialog->SetFooterFont(PrimeText_Game::Typeface_FZCuYuan_19_HardShadow->Typeface(), Sexy::Color(Sexy::Color::White));
		dialog->SetBackgroundDarken(true);
		dialog->AddButton(SexyString(L"[BUTTON_OK]"), Sexy::Delegate0(Sexy::MakeDelegate(*gLawnApp, &LawnApp::KillPVZ2Dialog)));
	}
	else
	{
		if (data.erro == 45014)
		{
			PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(UIScaleNum(400), UIScaleNum(250));
			dialog->SetHeaderLabel(SexyString(L"[REVIVE_TIP]"));
			dialog->SetFooterLabel(SexyString(L"[PVZ_LOGIN_LOW_VERSION]"));
			dialog->SetHeaderFont(PrimeText_Game::Typeface_FZShaoEr_28_Outline->Typeface(), PrimeText_Game::Color_Generic_Title);
			dialog->SetFooterFont(PrimeText_Game::Typeface_FZCuYuan_19_HardShadow->Typeface(), Sexy::Color(Sexy::Color::White));
			dialog->SetBackgroundDarken(true);
			dialog->AddButton(SexyString(L"[PVZ_LOGIN_GO_UPDATE]"), Sexy::Delegate0(Sexy::MakeDelegate(*gLawnApp, &LawnApp::OnHandleUpdateGame)));
			dialog->SetAlwaysExist(true);
			return;
		}
		Sexy::OutputDebugStrF("INetworkMsgProcess::onRequestUUIDLogin erro = [%d]", data.erro);
		gMessageRouter->Post(&Message::LoginiCloudServerFinish, false);
		m_ICIoudState = Response_Error;
		gMessageRouter->Broadcast(&Message::NotifyUUIDLogin, false);
	}
	RequestTimeLevelList();
}

void androidNetworkMsgProcess::OnICloudRequstLogin(const NetWorkMsg& data)
{
	if (data.erro == 0)
	{
		SettingsDialog::SetHaveSendV202(true);
		S2C_ICloud_LoginResult result;
		result.SerializeJson(data.msg);
		std::stringstream stream;
		stream << result.m_UserId;
		m_UserId = stream.str();
		m_sk = result.m_sk;
		m_aclk = result.m_NewKey;
		m_oaclk = result.m_OldKey;
		m_useACLogKey = result.m_encrypt;
		m_bShouldBindUniqueID = result.m_bindUniqueID;
		ProfileMgr::GetInstance().SetSaveInterval(result.m_saveInterval);
		SettingsDialog::SetEncryptIndex(result.m_idEncryptIndex);
		if (!result.m_stageURL.empty())
			NetworkEventConfig::SetStageURL(result.m_stageURL);
		if (GetServerSignature() != result.m_signature)
		{
			m_UserId = "";
			m_sk = "";
		}
		gLawnApp->InitServerTimeOffset(result.m_serverTime);
		gLawnApp->SetProfileCreatedTime(result.m_createdTime);
		gLawnApp->SetIsNewUser(result.m_isNewUser);
		Sexy::OutputDebugStrF("adnroid v202 Load Rsb newuser %d", result.m_isNewUser);
		if (result.m_isNewUser || 0 < result.m_PlayerReturnDays)
		{
			TGAPlayerReturnData returnData;
			returnData._day = DString(result.m_PlayerReturnDays).c_str();
			TGALogMgr::GetInstance().LogPlayerReturn(returnData);
		}
		std::string cachedUserId = GetNetworkCacheQueue()->getUserID();
		if (m_UserId != cachedUserId && cachedUserId != "")
		{
			TGAClearProfileData clearData;
			clearData._oldUserID = cachedUserId;
			clearData._newUserID = m_UserId;
			TGALogMgr::GetInstance().LogClearProfile(clearData);
			ShowClearProfileHint();
		}
		else
			DoContinuedLoginV202();
	}
	else if (data.erro == 20507)
	{
		SettingsDialog::SetIsACheatProfile(true);
		PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(UIScaleNum(400), UIScaleNum(250));
		std::string uid = GetEncryptIDString(GetNetworkCacheQueue()->getUserID(), SettingsDialog::GetEncryptIndex());
		SexyString uidText = Sexy::ToWString(uid);
		SexyString footer = TodReplaceString(TodStringTranslate(L"[PVZ_LOGIN_CHEAT_ERROR]"), L"{UID}", uidText);
		dialog->SetHeaderLabel(SexyString(L"[REVIVE_TIP]"));
		dialog->SetFooterLabel(footer);
		dialog->SetHeaderFont(PrimeText_Game::Typeface_FZShaoEr_28_Outline->Typeface(), PrimeText_Game::Color_Generic_Title);
		dialog->SetFooterFont(PrimeText_Game::Typeface_FZCuYuan_19_HardShadow->Typeface(), Sexy::Color(Sexy::Color::White));
		dialog->SetBackgroundDarken(true);
		dialog->AddButton(SexyString(L"[BUTTON_OK]"), Sexy::Delegate0(Sexy::MakeDelegate(*gLawnApp, &LawnApp::KillPVZ2Dialog)));
	}
	else
	{
		if (data.erro == 20532)
		{
			PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(UIScaleNum(400), UIScaleNum(250));
			dialog->SetHeaderLabel(SexyString(L"[REVIVE_TIP]"));
			dialog->SetFooterLabel(SexyString(L"[PVZ_LOGIN_ERROR_TOKEN]"));
			dialog->SetHeaderFont(PrimeText_Game::Typeface_FZShaoEr_28_Outline->Typeface(), PrimeText_Game::Color_Generic_Title);
			dialog->SetFooterFont(PrimeText_Game::Typeface_FZCuYuan_19_HardShadow->Typeface(), Sexy::Color(Sexy::Color::White));
			dialog->SetBackgroundDarken(true);
			dialog->AddButton(SexyString(L"[BUTTON_OK]"), Sexy::Delegate0(Sexy::MakeDelegate(*gLawnApp, &LawnApp::KillPVZ2Dialog)));
			return;
		}
		if (data.erro == 45014)
		{
			PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(UIScaleNum(400), UIScaleNum(250));
			dialog->SetHeaderLabel(SexyString(L"[REVIVE_TIP]"));
			dialog->SetFooterLabel(SexyString(L"[PVZ_LOGIN_LOW_VERSION]"));
			dialog->SetHeaderFont(PrimeText_Game::Typeface_FZShaoEr_28_Outline->Typeface(), PrimeText_Game::Color_Generic_Title);
			dialog->SetFooterFont(PrimeText_Game::Typeface_FZCuYuan_19_HardShadow->Typeface(), Sexy::Color(Sexy::Color::White));
			dialog->SetBackgroundDarken(true);
			dialog->AddButton(SexyString(L"[PVZ_LOGIN_GO_UPDATE]"), Sexy::Delegate0(Sexy::MakeDelegate(*gLawnApp, &LawnApp::OnHandleUpdateGame)));
			dialog->SetAlwaysExist(true);
			return;
		}
		gMessageRouter->Post(&Message::LoginiCloudServerFinish, false);
		m_ICIoudState = Response_Error;
	}
	RequestTimeLevelList();
}
