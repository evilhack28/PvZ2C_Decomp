//
//  PurchaseBroker.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PurchaseBroker.h"
#include "TimeMgr.h"
#include "LawnApp.h"
#include "iosExtras.h"
#include "UINameAuthentication.h"
#include "DNode/DNodeWidget.h"
#include "gameNetWork/NetworkData.h"
#include "TodLib/TodStringFile.h"
#include "SexyAppFramework/drivers/app/android/JavaInterface.h"
#include "gameNetWork/PacketID.h"
#include <sstream>
#include "PurchaseAdapters.h"
#include "PurchaseItemWidget.h"
#include "LogCollector/LogCollector.h"
#include "GameCommon.h"
#include "GeneralTaskMgr.h"
#include "UILimitGroupBuy.h"
#include "WorldMap_AcFirstRechargeButton.h"
#include "SexyAppFramework/PropertiesParser.h"
#include "PurchaseMgr.h"
#include "ActivityManager.h"
#include "UIRechargeReward.h"
#include "TGALogMgr.h"
#include "NameMapperEnum.h"
#include "ProfileMgr.h"
#include "UIDoubleFestivalActivity.h"
#include "RechargeDailySignActivity.h"
#include "DiscountShopActivity.h"
#include "FirstRechargeExtra.h"
#include "MonthlyCardSpecial.h"
#include "DangerRoomSpecialOfferExtra.h"
#include "PVZ2UnchartedModeNetworkMgr.h"
#include "WorldMap_LevelPackageButton.h"
#include "UICornucopia.h"
#include "UIPartyAssist.h"
#include "TalkingGame/talking_game.h"
#include "gameNetWork/NetworkMgr.h"
#include "SexyAppFramework/drivers/purchase/android/AndroidPurchaseDriver.h"

void PurchaseBroker::PurchaseDriverPaymentDeferred(IPurchaseDriver* merch, const std::string& productId)
{
}

/////////////// Android purchase driver forwarders ///////////////

#define DRIVER ((AndroidPurchaseDriver*)m_purchaseDriver)

void PurchaseBroker::LaunchSave()
{
	DRIVER->StartRecharge();
}

void PurchaseBroker::CheckGameCenterStatus()
{
	if (m_purchaseDriver)
		DRIVER->CheckGameCenterStatus();
}

void PurchaseBroker::Consume(const std::string& i_payCode, const std::string& i_orderNumber)
{
	if (m_purchaseDriver)
		DRIVER->Consume(i_payCode, i_orderNumber);
}

bool PurchaseBroker::ExitGame()
{
	if (m_purchaseDriver)
		return DRIVER->ExitGame();
}

void PurchaseBroker::OnAppResumeFocus()
{
	if (m_purchaseDriver)
		DRIVER->OnResume();
}

bool PurchaseBroker::NeedPurchaseWhite()
{
	if (m_purchaseDriver)
		return DRIVER->NeedPurchaseWhite();
	return true;
}

bool PurchaseBroker::NeedShowChannelActivity()
{
	if (m_purchaseDriver)
		return DRIVER->NeedShowChannelActivity();
	return true;
}

bool PurchaseBroker::validateRetry()
{
	return PVZ_RealT() > m_waitingCD;
}

bool PurchaseBroker::LaunchMoreGamesWebpage()
{
	if (m_purchaseDriver)
		return DRIVER->LaunchMoreGamesWebpage();
}

void PurchaseBroker::ConfirmDelivery(const std::string& i_receiptId)
{
	m_purchaseDriver->ConfirmDelivery(i_receiptId);
}

void PurchaseBroker::CheckRedeemOrders()
{
	if (m_purchaseDriver)
		DRIVER->CheckRedeemOrders();
}

void PurchaseBroker::ShowGameCommunity()
{
	if (m_purchaseDriver)
		DRIVER->ShowGameCommunity();
}

bool PurchaseBroker::validateTimeout()
{
	return PVZ_RealT() > m_waitingResultTime;
}

void PurchaseBroker::DoValidationPayment(const std::string& i_orderId, const std::string& i_userId)
{
	if (m_purchaseState == PURCHASESTATE_WaitingForResponse)
		DRIVER->RequestValidationPayment(m_paymentInfo.m_requestedSku, i_orderId, i_userId);
}

void PurchaseBroker::onDialogButtonPressed()
{
	gLawnApp->KillPVZ2Dialog();
	m_bShowDialog = false;
	gMessageRouter->Post(Message::PurchaseDialogClosed);
}

void PurchaseBroker::onLostPurchaseDialogButtonPressed()
{
	gLawnApp->KillPVZ2Dialog();
	PurchaseMgr::GetInstance().TryRetreiveLostOrders();
}

std::string PurchaseBroker::GetChannelID()
{
	if (m_purchaseDriver)
		return DRIVER->GetChannelID();
	return "";
}

std::string PurchaseBroker::GetUniqueID()
{
	if (m_purchaseDriver)
	{
		std::string id = DRIVER->GetUniqueID();
		TodHesitationTrace("PurchaseBroker::GetUniqueID:m_purchaseDriver = %s", id.c_str());
		return DRIVER->GetUniqueID();
	}
	return "";
}

std::string PurchaseBroker::GetUniqueCharacterID()
{
	if (m_purchaseDriver)
		return DRIVER->GetUniqueCharacterID();
	return "";
}

std::string PurchaseBroker::GetDeviceID()
{
	if (m_purchaseDriver)
		return DRIVER->GetDeviceID();
	return "";
}

std::string PurchaseBroker::GetSignature()
{
	if (m_purchaseDriver)
		return DRIVER->GetSignature();
	return "";
}

std::string PurchaseBroker::GetGameCenterUrl()
{
	if (m_purchaseDriver)
		return DRIVER->GetGameCenterUrl();
	return "";
}

std::string PurchaseBroker::GetTWRequestHead()
{
	if (m_purchaseDriver)
		return DRIVER->GetTWRequestHead();
	return "";
}

std::string PurchaseBroker::GetPurchasePlatform()
{
	if (m_purchaseDriver)
		return DRIVER->GetPurchasePlatform();
	return "no-purchase-drvier";
}

std::string PurchaseBroker::GetChannelUpdateUrl()
{
	OutputDebugStrF("PurchaseBroker::GetChannelUpdateUrl %d", m_purchaseDriver != NULL);
	if (m_purchaseDriver)
		return DRIVER->GetChannelUpdateUrl();
	return "";
}

int PurchaseBroker::GetRechargeBundleObjectID()
{
	return UserPrefs::GetInt("rechargeBundleObjectID", 0);
}

void PurchaseBroker::SetRechargeBundleObjectID(int objectID)
{
	UserPrefs::SetInt("rechargeBundleObjectID", objectID);
	UserPrefs::Synchronize();
}

int PurchaseBroker::GetArtifactPresentBundleObjectID()
{
	return UserPrefs::GetInt("artifactPresentBundleObjectID", 0);
}

void PurchaseBroker::SetArtifactPresentBundleObjectID(int objectID)
{
	UserPrefs::SetInt("artifactPresentBundleObjectID", objectID);
	UserPrefs::Synchronize();
}

SexyString PurchaseBroker::GetAboutContentStringId()
{
	if (m_purchaseDriver)
		return DRIVER->GetAboutContentStringId();
	return L"";
}

IPurchaseAdapter* PurchaseBroker::GetPurchaseAdapter(PurchaseChannel i_purchaseChannel)
{
	switch (i_purchaseChannel)
	{
	case PURCHASE_CHINAMOBILE:
		if (m_bChinaMobilePurchase)
			return new ChinaMobileChannelPurchaseAdapter();
		break;
	case PURCHASE_CHINAMOBILE_MM:
		if (m_bChinaMobileMMPurchase)
			return new ChinaMobileMMChannelPurchaseAdapter();
		break;
	}
	return NULL;
}

IPurchaseAdapter* PurchaseBroker::CreatePurchaseAdapter()
{
	IPurchaseAdapter* adapter;
	Buffer buffer;
	std::string archive;
	std::string path = gLawnApp->mFileDriver->GetLoadDataPath() + "PurchaseChannel.xml";
	long offset = 0;
	long size = 0;
	if (__builtin_expect(Android::Resources::GetAssetFileInfo(path, archive, offset, size), 0))
		goto readbody;
readfail:
	TodHesitationTrace("PurchaseBroker::CreatePurchaseAdapter read config file failed");
	adapter = new TWPurchaseAdapter();
	goto done;
readbody:
	{
		uchar* data = new uchar[size];
		FILE* fp = fopen(archive.c_str(), "rb");
		if (fp)
		{
			fseek(fp, offset, SEEK_SET);
			if (fread(data, 1, size, fp) == (size_t)size)
			{
				buffer.Clear();
				buffer.SetData(data, size);
				fclose(fp);
				delete[] data;
				PropertiesParser parser(gLawnApp);
				if (!parser.ParsePropertiesBuffer(buffer))
				{
					TodHesitationTrace("PurchaseBroker::CreatePurchaseAdapter parse config file failed");
					adapter = NULL;
				}
				else
				{
					bool wechat = gLawnApp->GetBoolean("WechatPurchase", false);
					bool unicom = gLawnApp->GetBoolean("UnicomPurchase", false);
					unsigned char telecom = gLawnApp->GetBoolean("TelecomPurchase", false);
					m_bChinaMobilePurchase = gLawnApp->GetBoolean("ChinaMobilePurchase", false);
					m_bChinaMobileMMPurchase = gLawnApp->GetBoolean("ChinaMobileMMPurchase", false);
					bool qq = gLawnApp->GetBoolean("QQGameCenterPurchase", false);
					bool multi = gLawnApp->GetBoolean("MultiPurchase", false);
					bool wideband = gLawnApp->GetBoolean("UnicomWidebandPurchase", false);
					unsigned char unicom3 = gLawnApp->GetBoolean("Unicom3ChannelPurchase", false);
					m_bTWPurchase = gLawnApp->GetBoolean("TWPurchase", false);
					unsigned int card = Android::Diag::GetMobileCardType();
					if (!multi)
					{
						if (wechat)
							{ adapter = new WeChatPurchaseAdapter(); goto parserEnd; }
						if (m_bTWPurchase)
							{ adapter = new TWPurchaseAdapter(); goto parserEnd; }
						if (m_bChinaMobilePurchase)
							{ adapter = new ChinaMobilePurchaseAdapter(); goto parserEnd; }
						if (unicom3 < telecom)
						{
							if (card & 4)
								{ adapter = new TelecomPurchaseAdapter(); goto parserEnd; }
							if (unicom && (card & 2))
								goto unicomChannel;
							if (m_bChinaMobileMMPurchase && (card & 1))
								goto mmChannel;
							goto nullAdapter;
						}
						if (unicom3 < (unsigned char)m_bChinaMobileMMPurchase)
							{ adapter = new ChinaMobileMMPurchaseAdapter(); goto parserEnd; }
						if (unicom3 && unicom)
						{
							int platform = gLawnApp->GetPlatform();
							if (platform == 10)
								goto unicomChannel;
							if (gLawnApp->GetPlatform() == 2 || gLawnApp->GetPlatform() == 8)
								{ adapter = new UnicomPurchaseAdapter(); goto parserEnd; }
							goto nullAdapter;
						}
						if (qq)
						{
							card = Android::Diag::GetMobileCardType();
							if (card & 1)
								{ adapter = new QQGameCenterPurchaseAdapter(); goto parserEnd; }
							if (card & 2)
								{ adapter = new QQGameCenterUnicomPurchaseAdapter(); goto parserEnd; }
							goto nullAdapter;
						}
						if (wideband)
							{ adapter = new UnicomWidebandPurchaseAdapter(); goto parserEnd; }
						goto nullAdapter;
					}
					{
						if (card & 1)
						{
							if (m_bChinaMobileMMPurchase)
							{
								if (m_bChinaMobilePurchase)
								{
									int platform = gLawnApp->GetPlatform();
									if (m_bChinaMobileMMPurchase && (platform - 0xfU < 0x2b || platform - 0x43U < 0x70))
										InitIMSIData();
									m_purchaseChannel = GetPurchaseChannel();
									{ adapter = GetPurchaseAdapter(m_purchaseChannel); goto parserEnd; }
								}
								goto mmChannel;
							}
							if (m_bChinaMobilePurchase)
								{ adapter = new ChinaMobileChannelPurchaseAdapter(); goto parserEnd; }
							goto nullAdapter;
						}
						if (telecom && (card & 4))
							{ adapter = new TelecomChannelPurchaseAdapter(); goto parserEnd; }
						if (unicom && (card & 2))
							goto unicomChannel;
						goto nullAdapter;
					}
unicomChannel:
					adapter = new UnicomChannelPurchaseAdapter();
					goto parserEnd;
mmChannel:
					adapter = new ChinaMobileMMChannelPurchaseAdapter();
					goto parserEnd;
nullAdapter:
					adapter = NULL;
parserEnd:;
				}
				goto done;
			}
			fclose(fp);
		}
		delete[] data;
		goto readfail;
	}
done:
	return adapter;
}

void PurchaseBroker::ResetPurchaseAdapter()
{
	if (DRIVER->GetPurchaseAdapter() && m_purchaseChannel == PURCHASE_NULL)
		return;
	PurchaseChannel channel = GetPurchaseChannel();
	if (m_purchaseChannel == channel)
		return;
	m_purchaseChannel = channel;
	IPurchaseAdapter* adapter = GetPurchaseAdapter(channel);
	if (adapter)
		m_bNeedShowDialog = adapter->NeedShowDialog();
	DRIVER->SetPurchaseAdapter(adapter);
	DRIVER->Init();
}

void PurchaseBroker::Init()
{
	IPurchaseAdapter* adapter = CreatePurchaseAdapter();
	if (adapter)
	{
		m_bNeedShowDialog = adapter->NeedShowDialog();
		DRIVER->SetPurchaseAdapter(adapter);
	}
	m_purchaseDriver->SetPaymentMonitor(this);
	DRIVER->Init();
}

void PurchaseBroker::EndCartInstance()
{
	if (m_cartInstanceInfo.IsCartActive)
	{
		if (!m_cartInstanceInfo.WasAnyPurchaseAttempted)
			gMessageRouter->Post(Message::CartInstanceEvent, (MagentoProductProps*)NULL);
		m_cartInstanceInfo.IsCartActive = false;
	}
}

ProductInfo PurchaseBroker::GetProductInfo(const std::string& productId)
{
	ProductInfo info;
	if (m_purchaseDriver)
		info = DRIVER->GetProductInfo(productId);
	return info;
}

PurchaseChannel PurchaseBroker::GetPurchaseChannel()
{
	int province = GetSimProvince();
	Sexy::RtDbTable* table = PVZDB::GetInstance().GetTable(PVZDB::TABLE_PURCHASE_CONFIG);
	PurchaseConfig* cfg = table->GetObjectForId(table->GetIdForAlias(Sexy::RtName(_S("PurchaseConfig"))))->CastChecked<PurchaseConfig>();
	return cfg->GetPurchaseChannel(province);
}

void PurchaseBroker::StartNewCartInstance(const std::string& i_entrySource, const std::string& i_type, const std::string& i_subType)
{
	EndCartInstance();
	m_cartInstanceInfo.IsCartActive = true;
	std::ostringstream ss(std::ios_base::out);
	ss << SexyTime();
	m_cartInstanceInfo.CartInstanceID = ss.str();
	m_cartInstanceInfo.CartEntrySource = i_entrySource;
	m_cartInstanceInfo.CartType = i_type;
	m_cartInstanceInfo.CartSubType = i_subType;
	m_cartInstanceInfo.WasAnyPurchaseAttempted = false;
	m_cartInstanceInfo.WasLastPurchaseSuccessful = false;
}

PurchaseBroker::PurchaseBroker()
{
	m_purchaseState = PURCHASESTATE_None;
	m_purchaseDriver = IPurchaseDriver::CreatePurchaseDriver("");
	m_watingTimes = 0;
	m_bShowDialog = false;
	m_bNeedShowDialog = false;
	m_bGetLostProduct = false;
	m_lostProductId = "";
	m_playerInfo = NULL;
	pvztime_t eot = PVZ_EOT();
	m_sendingRequest = false;
	m_objectId = 0;
	m_purchaseChannel = PURCHASE_NULL;
	m_bChinaMobilePurchase = false;
	m_bChinaMobileMMPurchase = false;
	m_bTWPurchase = false;
	m_waitingResultTime = eot;
	m_waitingCD = eot;
	gMessageRouter->Subscribe(Message::AppResumeFocus, Sexy::MakeDelegate(*this, &PurchaseBroker::OnAppResumeFocus));
	gMessageRouter->Subscribe(Message::MsgErrorRequest, Sexy::MakeDelegate(*this, &PurchaseBroker::onMsgError));
}

PurchaseBroker::~PurchaseBroker()
{
	gMessageRouter->Unsubscribe(this);
}

void PurchaseBroker::onMsgError(int erroId, const std::string& requestID)
{
	_PacketId ids;
	if (requestID == ids.ID_REQUEST_PAYMENT_RESULT)
		m_sendingRequest = false;
	else if (requestID == ids.ID_REQUEST_GET_LOST_PAYMENT)
		gMessageRouter->Post(Message::NotifyRetreiveLostOrderEnd);
}

void PurchaseBroker::DoOfflinePayment(const std::string& i_userId)
{
	if (m_purchaseState == PURCHASESTATE_WaitingForResponse)
		DRIVER->RequestValidationPayment(m_paymentInfo.m_requestedSku, "", i_userId);
}

int PurchaseBroker::GetSimProvince()
{
	int result = 0;
	int province = Android::Diag::GetSimProvince();
	if (province > 0)
	{
		if (province <= 31)
			result = simSNProvinceMaps[province];
	}
	else
	{
		std::string imsi = "";
		Android::Diag::GetDeviceIMSI(imsi);
		OutputDebugStrF("i_imsi = %s\n", imsi.c_str());
		if (imsi.length() > 9)
		{
			int companyCode = 0;
			std::string code = imsi.substr(5, 5);
			sscanf(code.c_str(), "%d", &companyCode);
			OutputDebugStrF("i_companyCode = %d\n", companyCode);
			result = m_provinces[companyCode];
		}
	}
	return result;
}

void PurchaseBroker::PurchaseDriverPaymentComplete(IPurchaseDriver* merch, const std::string& productId)
{
	if (!m_playerInfo)
		return;
	m_purchaseState = PURCHASESTATE_WaitingForValidate;
	if (m_paymentInfo.m_requestedSku == "")
		m_paymentInfo.m_requestedSku = productId;
	PaymentResultInfo info = gLawnApp->GetPaymentResultInfo();
	m_waitingResultTime = PVZ_RealT() + 120.0f;
	m_waitingCD = PVZ_EOT();
	validatePayment(info.payCode, info.orderId);
}

void PurchaseBroker::PurchaseDriverPaymentComplete(IPurchaseDriver* merch, const std::string& receiptId, const std::string& receipt, const std::string& productId)
{
}

void PurchaseBroker::Update()
{
	UpdateDialog();
	if (m_purchaseState == PURCHASESTATE_NeedToSendPurchase)
	{
		m_purchaseState = PURCHASESTATE_WaitingForResponse;
		m_purchaseDriver->RequestPayment(m_paymentInfo.m_requestedSku, m_paymentInfo.m_orderNumber);
	}
	else if (m_purchaseState == PURCHASESTATE_WaitingForValidate)
	{
		if (!validateTimeout())
		{
			if (!m_sendingRequest && validateRetry())
			{
				PaymentResultInfo info = gLawnApp->GetPaymentResultInfo();
				validatePayment(info.payCode, info.orderId);
			}
		}
		else if (!m_sendingRequest)
			PurchaseFailed();
	}
}

void PurchaseBroker::PurchaseFailed()
{
	if (m_playerInfo)
	{
		m_playerInfo->setLastOrderId("");
		if (m_bNeedShowDialog)
		{
			PVZ2UIDialog* dialog = gLawnApp->GetPVZ2Dialog();
			if (dialog && m_bShowDialog)
			{
				SexyString header = L"[PURCHASE_ERROR_HEADER]";
				SexyString body = L"[PURCHASE_ERROR_BODY]";
				header = L"[PURCHASE_ERROR_HEADER]";
				body = L"[PURCHASE_ERROR_BODY]";
				dialog->SetHeaderLabel(header);
				dialog->SetFooterLabel(body);
				dialog->AddButton(SexyString(L"[CONTINUE_BUTTON]"), Sexy::MakeDelegate(*this, &PurchaseBroker::onDialogButtonPressed));
			}
		}
		m_purchaseState = PURCHASESTATE_None;
	}
}

void PurchaseBroker::UpdateDialog()
{
	if (m_purchaseState != PURCHASESTATE_None && m_bNeedShowDialog)
	{
		PVZ2UIDialog* dialog = gLawnApp->GetPVZ2Dialog();
		if (dialog && m_bShowDialog)
		{
			SexyString header;
			SexyString footer;
			if (m_lostProductId == "")
			{
				header = TodStringTranslate(L"[PURCHASE_DIALOG_HEADER]");
				footer = TodStringTranslate(L"[PURCHASE_DIALOG_BODY_CONNECT]");
			}
			else
			{
				header = TodStringTranslate(L"[PURCHASE_RESTORE_DIALOG_HEADER]");
				footer = TodStringTranslate(L"[PURCHASE_RESTORE_DIALOG_BODY_CONNECT]");
			}
			m_watingTimes = m_watingTimes % 60;
			for (int i = 0; i <= m_watingTimes; i += 10)
				footer += L".";
			m_watingTimes++;
			dialog->SetHeaderLabel(header);
			dialog->SetFooterLabel(footer);
		}
	}
}

void PurchaseBroker::requestLostPayment()
{
	std::map<std::string, std::string> params;
	DNetwork* network = DNetwork::getInstance();
	_PacketId ids;
	network->requestMsg(ids.ID_REQUEST_GET_LOST_PAYMENT, params, 30.0f, [this](const std::string& i_response)
	{
		S2C_Payment_LostPurchaseOrder data;
		if (data.SerializeJson(i_response))
			onNotifyLostPurchase(data.m_payments);
		else
			gMessageRouter->Post(Message::NotifyRetreiveLostOrderEnd);
	}, true, true, "[NET_CONNECTING]", 0);
}

void PurchaseBroker::showLostPurchaseDialog(const std::string& i_skuId)
{
	SexyString title;
	MagentoProductPropsPtr product = Magento::GetProduct(i_skuId);
	if (product.IsValid())
		title = TodStringTranslate(Sexy::UTF8StringToWString(product.Get()->GetLocalizedShortDescription()));
	PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(title, SexyString(L"[LOST_PURCHASE_DIALOG_DES]"));
	dialog->AddButton(SexyString(L"[DIALOG_STRING_OK]"), Sexy::MakeDelegate(*gLawnApp, &LawnApp::KillPVZ2Dialog));
}

void PurchaseBroker::QueryOrder(const std::string& product_id)
{
	if (m_purchaseDriver)
		m_purchaseDriver->QueryOrder(product_id);
}

int PurchaseBroker::GetRedeemOrders(std::map<std::string, RedeemInfo>& validOrders)
{
	if (m_purchaseDriver)
		return DRIVER->GetRedeemOrders(validOrders);
	return 0;
}

void PurchaseBroker::CheckSpecialRedeem()
{
	if (m_purchaseDriver)
		DRIVER->CheckSpecialRedeem();
}

void PurchaseBroker::ShowAuthIDDialog()
{
	gLawnApp->KillPVZ2Dialog();
	UINameAuthentication::ShowDialog(true);
}

void PurchaseBroker::onNotifyPurchaseValidation(const std::string& i_orderNumber, const std::string& i_skuId, const std::vector<PaymentBundleInfo>& i_bundleInfos, int i_status)
{
	OnNotifyPurchaseResult(i_status, i_orderNumber, i_skuId, i_bundleInfos);
}

void PurchaseBroker::OnNotifyPurchaseResult(int i_result, const std::string& i_orderNumber, const std::string& i_skuId, const std::vector<PaymentBundleInfo>& i_bundleInfos)
{
	if (i_result == RESULT_SUCCESS)
		PurchaseSuccessed(i_orderNumber, i_skuId, i_bundleInfos, false);
}

void PurchaseBroker::validatePayment(const std::string& i_productId, const std::string& i_orderNumber)
{
	m_sendingRequest = true;
	m_waitingCD = PVZ_RealT() + 5.0f;
	std::map<std::string, std::string> params;
	params["r"] = i_orderNumber;
	DNetwork* network = DNetwork::getInstance();
	_PacketId ids;
	network->requestMsg(ids.ID_REQUEST_PAYMENT_RESULT, params, 30.0f, [this](const std::string& i_response)
	{
		m_sendingRequest = false;
		S2C_Payment_ValidateResult data;
		if (data.SerializeJson(i_response))
			onNotifyPurchaseValidation(data.orderId, data.skuId, data.bundleInfos, data.status);
	}, true, true, "[NET_CONNECTING]", 0);
}

void PurchaseBroker::createPayment(MagentoProductProps* purchaseProps)
{
	m_waitingResultTime = PVZ_EOT();
	std::map<std::string, std::string> params;
	params["pdi"] = purchaseProps->Sku;
	DNetwork* network = DNetwork::getInstance();
	_PacketId ids;
	network->requestMsg(ids.ID_REQUEST_PAYMENT_ORDER_ID, params, 30.0f, [this, purchaseProps](const std::string& i_response)
	{
		NetworkCreatePaymentInfo data;
		if (data.SerializeJson(i_response))
			onPurchaseConfirm(purchaseProps, data.m_orderNumber);
	}, true, true, "[NET_CONNECTING]", 0);
}

void PurchaseBroker::onNotifyLostPurchase(const std::vector<NetworkPaymentInfo>& i_infos)
{
	for (std::vector<NetworkPaymentInfo>::const_iterator it = i_infos.begin(), end = i_infos.end(); it != end; ++it)
	{
		NetworkPaymentInfo info = *it;
		PurchaseSuccessed(info.orderId, info.skuId, info.bundleInfos, true);
	}
	gMessageRouter->Post(Message::NotifyRetreiveLostOrderEnd);
}

void PurchaseBroker::NDREChargeReward(int price, std::string sku_id)
{
	ActiveItem item = gActivityManager->GetActiveItem(Activity_Spring_RechargeReward);
	if (__builtin_expect(item.IsValid(), 1))
	{
		NDRechargeRewardConfig config;
		if (__builtin_expect(item.GetDataSerialized(config), 1) && __builtin_expect(item.m_bOpen, 0) && config.canAwardTimes > 0)
		{ if (__builtin_expect(price > 29, 0)) {
			NetworkMgr::Instance()->GetNewNetWorkProcess()->ICloudRequestGetRechargeReward(price);
			TGADailyRechargeReward reward;
			reward._step = DString(2).c_str();
			reward._buyItemID = sku_id;
			reward._cost = DString(price).c_str();
			TGALogMgr::GetInstance().LogDailyRechargeReward(reward);
		} }
	}
}

__attribute__((noclone)) static int UIScaleNum(int i_num)
{
	return ((ScaledApp*)gSexyApp)->UIScaleNum(i_num);
}

void PurchaseBroker::onPurchaseConfirm(MagentoProductProps* purchaseProps, const std::string& orderNumber)
{
	if (purchaseProps)
	{
		((Sexy::AndroidPurchaseDriver*)m_purchaseDriver)->setParam();
		talkingGame::GetInstancePtr()->onPay(purchaseProps->GetLocalizedName().c_str(), (int)purchaseProps->GetPriceInUSD(false), purchaseProps->ObjectCount, purchaseProps->GetLocalizedDescription().c_str());
		m_cartInstanceInfo.WasAnyPurchaseAttempted = true;
		m_cartInstanceInfo.WasLastPurchaseSuccessful = false;
		if (m_bNeedShowDialog)
		{
			PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(UIScaleNum(400), UIScaleNum(300));
			m_bShowDialog = true;
			dialog->SetBackgroundDarken(true, 0.5f);
			dialog->SetHeaderLabel(SexyString(L"[PURCHASE_DIALOG_HEADER]"));
		}
		m_watingTimes = 0;
		m_paymentInfo.m_orderNumber = orderNumber;
		m_paymentInfo.m_requestedSku = purchaseProps->Sku;
		m_purchaseState = PURCHASESTATE_NeedToSendPurchase;
	}
}

void PurchaseBroker::RequestPayment(const std::string& product_id, int objectId)
{
	m_playerInfo = ProfileMgr::GetInstance().GetCurrentProfile();
	if (!gLawnApp->IsServiceAvailable(Service_PayCheck) || m_playerInfo->GetNumRechargeCurrency() <= 999 || m_playerInfo->getIsAuthIDCard())
	{
		SetRechargeBundleObjectID(objectId);
		SetArtifactPresentBundleObjectID(objectId);
		if (m_purchaseState == PURCHASESTATE_None && m_playerInfo)
		{
			m_playerInfo->RefreshRechargeCurrency();
			MagentoProductPropsPtr product = Magento::GetProductPtr(product_id);
			Sexy::RtDbTable* table = PVZDB::GetInstance().GetTable(PVZDB::TABLE_PURCHASE_CONFIG);
			table->GetObjectForId(table->GetIdForAlias(Sexy::RtName(_S("PurchaseConfig"))));
			createPayment(product);
		}
	}
	else
	{
		gLawnApp->ShowMessageDialog("[PAY_CHECK_DIALOG_TITLE]", "[PAY_CHECK_DIALOG_CONTENT]", Sexy::Delegate0(Sexy::MakeDelegate(*this, &PurchaseBroker::ShowAuthIDDialog)));
	}
}

void PurchaseBroker::syncPayment(const std::string& i_productId, const std::string& i_orderNumber, const std::string& i_objectType, bool i_lostPurchase)
{
	std::string objectId = "";
	if (i_objectType == "monthlycard" || i_objectType == "rechargeBundle" || i_objectType == "artifact_present")
		objectId = DString(m_objectId).c_str();
	std::map<std::string, std::string> params;
	params["on"] = i_orderNumber;
	params["oi"] = objectId;
	DNetwork* network = DNetwork::getInstance();
	_PacketId ids;
	network->requestMsg(ids.ID_REQUEST_SYNC_PAYMENT_RESULT, params, 30.0f, [this, i_lostPurchase](const std::string& i_response)
	{
		S2C_Payment_SyncPaymentResult data;
		if (data.SerializeJson(i_response))
		{
			if (data.objectId > 0)
			{
				gMessageRouter->Post(Message::RechargeBundlePurchased, data.objectId);
				gMessageRouter->Post(Message::RechargeRewardCurrencyChanged, data.activeTotalCharge);
			}
			onSyncPayment(data.orderId, data.skuId, i_lostPurchase, data.bonusList);
		}
	}, true, true, "[NET_CONNECTING]", 0);
}

void PurchaseBroker::InitIMSIData()
{
	std::string archive;
	std::string path = gLawnApp->mFileDriver->GetLoadDataPath() + "imsin.dat";
	long offset = 0;
	long size = 0;
	if (Android::Resources::GetAssetFileInfo(path, archive, offset, size))
	{
		FILE* fp = fopen(archive.c_str(), "rb");
		fseek(fp, offset, SEEK_SET);
		char* line = new char[20];
		memset(line, 0, 20);
		m_provinces.clear();
		if (fp)
		{
			int pos = 0;
			while (pos < size)
			{
				pos++;
				unsigned char c = getc(fp);
				if (c != '\n' && pos < size)
				{
					char* p = line;
					do
					{
						*p = c;
						pos++;
						c = getc(fp);
						if (c == '\n')
							break;
						p++;
					} while (pos < size);
				}
				int province = 0;
				int value = 0;
				sscanf(line, "%d,%d", &province, &value);
				m_provinces.insert(std::make_pair(province, value));
			}
			fclose(fp);
		}
		OutputDebugStrF("m_provinces.size = %d", m_provinces.size());
		delete[] line;
	}
}

void PurchaseBroker::PurchaseDriverPaymentIncomplete(IPurchaseDriver* merch, const std::string& productId, IPurchaseDriver::CauseForIncompletion cause)
{
	if (m_playerInfo)
	{
		m_playerInfo->setLastOrderId("");
		PurchaseMgr::GetInstance().ResetPurchaseInfo();
		if (cause == IPurchaseDriver::Canceled)
		{
			if (m_bNeedShowDialog && m_bShowDialog)
			{
				gLawnApp->KillPVZ2Dialog();
				m_bShowDialog = false;
			}
			m_purchaseState = PURCHASESTATE_None;
			return;
		}
		PVZ2UIDialog* dialog;
		if (m_bNeedShowDialog && (dialog = gLawnApp->GetPVZ2Dialog()) && m_bShowDialog)
		{
			SexyString header(L"[PURCHASE_ERROR_HEADER]");
			SexyString body(L"[PURCHASE_ERROR_BODY]");
			if (cause == IPurchaseDriver::Error)
			{
				header = L"[PURCHASE_ERROR_HEADER]";
				body = L"[PURCHASE_ERROR_BODY]";
			}
			else if (cause == IPurchaseDriver::UserNotAuthorized)
			{
				header = L"[PURCHASE_ERROR_NOT_AUTHORIZED_HEADER]";
				body = L"[PURCHASE_ERROR_NOT_AUTHORIZED_BODY]";
			}
			else if (cause == IPurchaseDriver::ServiceUnavailable)
			{
				header = L"[PURCHASE_ERROR_SERVICE_UNAVAILABLE_HEADER]";
				body = L"[PURCHASE_ERROR_SERVICE_UNAVAILABLE_BODY]";
			}
			else if (cause == IPurchaseDriver::ValidateServerUnavailable || cause == IPurchaseDriver::ValidateServerError)
			{
				header = L"[PURCHASE_ERROR_HEADER]";
				body = L"[PURCHASE_ERROR_VALIDATE_BODY]";
			}
			else if (cause == IPurchaseDriver::ValidateCheat)
			{
				header = L"[PURCHASE_ERROR_HEADER]";
				body = L"[PURCHASE_CHEAT_VALIDATE_BODY]";
			}
			else if (cause == IPurchaseDriver::NoProductFound)
			{
				header = L"[PURCHASE_ERROR_SERVICE_UNAVAILABLE_HEADER]";
				body = L"[PURCHASE_ERROR_SERVICE_UNAVAILABLE_BODY]";
			}
			dialog->SetHeaderLabel(header);
			dialog->SetFooterLabel(body);
			dialog->AddButton(SexyString(L"[CONTINUE_BUTTON]"), Sexy::Delegate0(Sexy::MakeDelegate(*this, &PurchaseBroker::onDialogButtonPressed)));
		}
		m_purchaseState = PURCHASESTATE_None;
		gMessageRouter->Post(Message::CartInstanceEvent, (MagentoProductProps*)NULL);
	}
}

void PurchaseBroker::LostPurchaseSuccessed(std::string sku_id)
{
	PlayerInfo* player = ProfileMgr::GetInstance().GetCurrentProfile();
	if (player)
	{
		gLawnApp->m_bRechargeUseMoney = true;
		player->HandlePurchase(sku_id, std::vector<PaymentBundleInfo>());
		gLawnApp->m_bRechargeUseMoney = false;
		MagentoProductPropsPtr product = NULL;
		for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_MAGENTO); it; ++it)
		{
			MagentoProductProps* props = Sexy::RtWeakPtr<Sexy::RtObject>(*it)->Cast<MagentoProductProps>();
			if (props && props->Sku == sku_id)
			{
				product = *it;
				break;
			}
		}
		PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(UIScaleNum(400), UIScaleNum(300));
		if (dialog)
		{
			SexyString header;
			SexyString body;
			header = TodStringTranslate(L"[PURCHASE_DIALOG_CONFIRMED_HEADER]");
			body = TodReplaceString(TodStringTranslate(L"[PURCHASE_COMPLETE]"), L"{PRODUCT_NAME}", TodStringTranslate(Sexy::UTF8StringToWString(product->GetLocalizedShortDescription())).c_str());
			dialog->SetHeaderLabel(header);
			dialog->SetFooterLabel(body);
			dialog->AddButton(SexyString(L"[CONTINUE_BUTTON]"), Sexy::Delegate0(Sexy::MakeDelegate(*this, &PurchaseBroker::onLostPurchaseDialogButtonPressed)));
		}
	}
}

void NationalDayChargeRewardMsg(const std::string&, const std::vector<int>&) asm("_ZN7Message23NationalDayChargeRewardERKSsRKSt6vectorIiSaIiEE");
void ObtainDaveTreasureIntegralMsg(int) asm("_ZN7Message26ObtainDaveTreasureIntegralEi");
void RichmanDiceShopBuyFinishMsg(int) asm("_ZN7Message24RichmanDiceShopBuyFinishEi");
void LimitLotteryBuyCoinMsg(int, int) asm("_ZN7Message19LimitLotteryBuyCoinEii");

#define LIMIT_LOTTERY_BUY(count, coins) 	{ 		PlayerInfo* lotteryPlayer = ProfileMgr::GetInstance().GetCurrentProfile(); 		gMessageRouter->Post(LimitLotteryBuyCoinMsg, count, coins); 		ProfileChangeItemAmount(id_coin_gold, coins, false); 		ProfileChangeItemAmount(id_mat_limitlottery_crystal, product->ObjectCount, false); 		S2C_LimitLotteryCrystalBuy crystalData; 		crystalData.leftCrystalNum = lotteryPlayer->GetMaterialNum(id_mat_limitlottery_crystal); 		gMessageRouter->Post(Message::NotifyLimitLotteryBuyCrystalFinish, true, &crystalData); 	}

void PurchaseBroker::PurchaseSuccessed(std::string orderNumber, std::string sku_id, const std::vector<PaymentBundleInfo>& i_bundleInfos, bool i_lostPurchase)
{
	PlayerInfo* player = m_playerInfo;
	if (!player)
		player = ProfileMgr::GetInstance().GetCurrentProfile();
	int vipState = player->GetMonthVIPState();
	gLawnApp->m_bRechargeUseMoney = true;
	player->HandlePurchase(sku_id, i_bundleInfos);
	gLawnApp->m_bRechargeUseMoney = false;
	m_cartInstanceInfo.WasLastPurchaseSuccessful = true;
	player->AddRechargeProductId(sku_id);
	MagentoProductPropsPtr product = NULL;
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_MAGENTO); it; ++it)
	{
		MagentoProductProps* props = Sexy::RtWeakPtr<Sexy::RtObject>(*it)->Cast<MagentoProductProps>();
		if (props && props->Sku == sku_id)
		{
			product = *it;
			break;
		}
	}
	if (product)
	{
		if (sku_id == "com.popcap.ios.chs.PVZ2.redpack1")
			BehaviorLog::inGameBehavior("2019_SPRING", { "HB_GACHA", "1" }, "");
		else if (sku_id == "com.popcap.ios.chs.PVZ2.redpack10")
			BehaviorLog::inGameBehavior("2019_SPRING", { "HB_GACHA", "12" }, "");
		if (sku_id == "com.popcap.android.chs.PVZ2.MonthlyVIPSubs30" && vipState > 0)
			goto finish;
		{
			gMessageRouter->Post(NationalDayChargeRewardMsg, sku_id, std::vector<int>());
			player->AddRechargeCurrency((int)product->GetPriceInUSD(false));
			NDREChargeReward((int)product->GetPriceInUSD(false), sku_id);
			ChristmasChargeManager::GetInstancePtr()->NewYearChargeAward();
			HappyVaseCheckBilling::GetInstancePtr()->CheckBillingPoint(sku_id);
			LimitGroupBuyManager::GetInstancePtr()->AddDaveTicket((int)product->GetPriceInUSD(false));
			gMessageRouter->Post(Message::GetOppoRechargeReward);
			ActiveItem treasure = gActivityManager->GetActiveItem(Activity_DaveTreasure);
			if (treasure.IsValid() && treasure.m_bOpen)
			{
				bool notMoney = product->ObjectPurchaseType != "money";
				if (!notMoney)
				{
					float price = product->GetPriceInUSD(notMoney);
					int amount = notMoney;
					if (!(sku_id == "com.popcap.ios.chs.PVZ2.SecretTreasure"))
						amount = (int)price * 5;
					gMessageRouter->Post(ObtainDaveTreasureIntegralMsg, amount);
				}
			}
			if (sku_id == "com.popcap.ios.chs.PVZ2.Richman1")
			{
				ProfileMgr::GetInstance().GetCurrentProfile()->AddCommonGachaReward(GachaRewardCode_Coins, 1000, false, true);
				gMessageRouter->Post(RichmanDiceShopBuyFinishMsg, 1);
			}
			else if (sku_id == "com.popcap.ios.chs.PVZ2.Richman12")
			{
				ProfileMgr::GetInstance().GetCurrentProfile()->AddCommonGachaReward(GachaRewardCode_Coins, 15000, false, true);
				gMessageRouter->Post(RichmanDiceShopBuyFinishMsg, 15);
			}
			else if (sku_id == "com.popcap.ios.chs.PVZ2.Richman88")
			{
				ProfileMgr::GetInstance().GetCurrentProfile()->AddCommonGachaReward(GachaRewardCode_Coins, 190000, false, true);
				gMessageRouter->Post(RichmanDiceShopBuyFinishMsg, 190);
			}
			else if (sku_id == "com.popcap.ios.chs.PVZ2.Richman168")
			{
				ProfileMgr::GetInstance().GetCurrentProfile()->AddCommonGachaReward(GachaRewardCode_Coins, 456000, false, true);
				gMessageRouter->Post(RichmanDiceShopBuyFinishMsg, 456);
			}
			else if (sku_id == "com.popcap.ios.chs.PVZ2.Richman248")
			{
				ProfileMgr::GetInstance().GetCurrentProfile()->AddCommonGachaReward(GachaRewardCode_Coins, 800000, false, true);
				gMessageRouter->Post(RichmanDiceShopBuyFinishMsg, 800);
			}
			sku_id == "com.popcap.ios.chs.PVZ2.NewYearLuckyBag45";
			ActiveItem firstRecharge = gActivityManager->GetActiveItem(Activity_FirstRecharge);
			bool alreadyRecharged = AcFirstRechargeManager::GetInstancePtr()->getIsAlreadyRecharge();
			if (firstRecharge.IsValid() && (unsigned char)alreadyRecharged < (unsigned char)firstRecharge.m_bOpen)
			{
				bool notMoney = product->ObjectPurchaseType != "money";
				if (!notMoney)
				{
					int price = (int)product->GetPriceInUSD(notMoney);
					if (price > 1)
					{
						TGALogMgr::GetInstance().LogSegments(TGA_LOG_FIRSTRECHARGE, notMoney, DString(price));
						NetworkMgr::Instance()->GetNewNetWorkProcess()->ICloudRequestfirstChargeSucceed(price);
					}
				}
			}
			if (sku_id == "com.popcap.pvz2.battlez.1")
				gMessageRouter->Post(Message::GLBuyZMatchTicket, true);
			else if (sku_id == "com.popcap.pvz2.battlez.6")
				gMessageRouter->Post(Message::GLBuyZMatchTicket, true);
			else if (sku_id == "com.popcap.ios.chs.PVZ2.Lottery6")
				LIMIT_LOTTERY_BUY(6, 6000)
			else if (sku_id == "com.popcap.ios.chs.PVZ2.Lottery25")
				LIMIT_LOTTERY_BUY(25, 30000)
			else if (sku_id == "com.popcap.ios.chs.PVZ2.Lottery328")
				LIMIT_LOTTERY_BUY(328, 396000)
			else if (sku_id == "com.popcap.ios.chs.PVZ2.Bank30")
				NetworkMgr::Instance()->GetNewNetWorkProcess()->RequestBuyShopItem(PIGGY_BANK_2019, 1, 1, GachaRewardCode_RMB, 30);
		}
	}
finish:
	if (!m_bNeedShowDialog)
	{
		gMessageRouter->Post(Message::PurchaseDialogClosed);
	}
	else
	{
		PVZ2UIDialog* dialog = gLawnApp->GetPVZ2Dialog();
		if (dialog && m_bShowDialog)
		{
			SexyString header;
			SexyString body;
			if (m_lostProductId == "")
			{
				header = TodStringTranslate(L"[PURCHASE_DIALOG_CONFIRMED_HEADER]");
				if (player->IsShowRechargeDoubleDialog())
				{
					body = Sexy::StrFormat(TodStringTranslate(L"[PURCHASE_DOUBLE_COMPLETE]").c_str(), TodStringTranslate(Sexy::UTF8StringToWString(product->GetLocalizedShortDescription())).c_str());
					player->SetShowRechargeDoubleDialog(false);
				}
				else
				{
					body = TodReplaceString(TodStringTranslate(L"[PURCHASE_COMPLETE]"), L"{PRODUCT_NAME}", SexyString(TodStringTranslate(Sexy::UTF8StringToWString(product->GetLocalizedShortDescription())).c_str()));
				}
			}
			else
			{
				header = TodStringTranslate(L"[PURCHASE_RESTORE_DIALOG_HEADER]");
				body = TodReplaceString(TodStringTranslate(L"[PURCHASE_RESTORE_DIALOG_DESC]"), L"{PRODUCT_NAME}", SexyString(TodStringTranslate(Sexy::UTF8StringToWString(product->GetLocalizedShortDescription())).c_str()));
			}
			dialog->SetHeaderLabel(header);
			dialog->SetFooterLabel(body);
			dialog->AddButton(SexyString(L"[CONTINUE_BUTTON]"), Sexy::Delegate0(Sexy::MakeDelegate(*this, &PurchaseBroker::onDialogButtonPressed)));
			if (PurchaseItemWidget::SupportsProduct(product))
			{
				PurchaseItemWidget* widget = new PurchaseItemWidget(product);
				int h = dialog->mHeight;
				static_cast<Sexy::Widget*>(widget)->Resize(Sexy::Rect(0, h / 4, dialog->mWidth, h / 2));
				dialog->SetContents(widget);
			}
		}
	}
	m_purchaseState = PURCHASESTATE_None;
	PurchaseMgr::GetInstance().ResetPurchaseInfo();
	std::string objectType = "";
	if (product)
		objectType = product->ObjectType;
	syncPayment(sku_id, orderNumber, objectType, i_lostPurchase);
	TGALogPurchaseData data;
	data._itemID = sku_id;
	if (product)
		data._cost = DString(product->GetPriceInUSD(false)).c_str();
	data._firstPayItem = m_paymentInfo.m_orderNumber;
	data._totalPay = DString(player->GetNumRechargeCurrency()).c_str();
	TGALogMgr::GetInstance().LogPurchase(data);
	TGALogMgr::GetInstance().clearSegments(TGA_LOG_PURCHASE_ID);
}

static std::vector<PaymentBundleInfo> sNoBundleInfos;

void PurchaseBroker::OnNotifyPurchaseResult(bool i_success, const std::string& i_skuId, int i_errorCode)
{
	if (i_success)
	{
		if (PurchaseMgr::GetInstance().IsRetreivingLostOrders())
			LostPurchaseSuccessed(i_skuId);
		else
			PurchaseSuccessed(i_skuId, "", sNoBundleInfos, false);
	}
	else if (!PurchaseMgr::GetInstance().IsRetreivingLostOrders())
	{
		if (m_playerInfo)
		{
			m_playerInfo->setLastOrderId("");
			PurchaseMgr::GetInstance().ResetPurchaseInfo();
			PVZ2UIDialog* dialog;
			if (m_bNeedShowDialog && (dialog = gLawnApp->GetPVZ2Dialog()) && m_bShowDialog)
			{
				SexyString header(L"[PURCHASE_ERROR_HEADER]");
				SexyString body(L"[PURCHASE_ERROR_BODY]");
				if (i_errorCode == 20531)
				{
					header = L"[PURCHASE_FULL_ERROR_HEADER]";
					body = L"[PURCHASE_FULL_ERROR_BODY]";
				}
				else
				{
					header = L"[PURCHASE_ERROR_HEADER]";
					body = L"[PURCHASE_ERROR_BODY]";
				}
				dialog->SetHeaderLabel(header);
				dialog->SetFooterLabel(body);
				dialog->AddButton(SexyString(L"[CONTINUE_BUTTON]"), Sexy::Delegate0(Sexy::MakeDelegate(*this, &PurchaseBroker::onDialogButtonPressed)));
			}
			m_purchaseState = PURCHASESTATE_None;
		}
	}
	else
	{
		PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(UIScaleNum(400), UIScaleNum(300));
		if (dialog)
		{
			SexyString header(L"[RESTORE_LOST_ERROR_HEADER]");
			SexyString body(L"[RESTORE_LOST_ERROR_BODY]");
			header = L"[RESTORE_LOST_ERROR_HEADER]";
			body = L"[RESTORE_LOST_ERROR_BODY]";
			dialog->SetHeaderLabel(header);
			dialog->SetFooterLabel(body);
			dialog->AddButton(SexyString(L"[CONTINUE_BUTTON]"), Sexy::Delegate0(Sexy::MakeDelegate(*this, &PurchaseBroker::onLostPurchaseDialogButtonPressed)));
		}
	}
}

// not declared by Message in this unit
void NewPVPShopBuyChestMsg(int, std::vector<S2C_BonusInfo>&) asm("_ZN7Message18NewPVPShopBuyChestEiRSt6vectorI13S2C_BonusInfoSaIS1_EE");
void NewPVPBattlePassExtrarewardsMsg(const std::vector<S2C_BonusInfo>&, int) asm("_ZN7Message28NewPVPBattlePassExtrarewardsERKSt6vectorI13S2C_BonusInfoSaIS1_EEi");
void NewPVPBattlePassBuyPrivilegeMsg(const std::vector<S2C_BonusInfo>&) asm("_ZN7Message28NewPVPBattlePassBuyPrivilegeERKSt6vectorI13S2C_BonusInfoSaIS1_EE");

void PurchaseBroker::onSyncPayment(const std::string& i_orderNumber, const std::string& i_skuId, bool i_lostPurchase, std::vector<S2C_BonusInfo> bonuslist)
{
	ProductInfo info = GetProductInfo(i_skuId);
	Consume(info.productCode, i_orderNumber);
	if (i_lostPurchase)
		showLostPurchaseDialog(i_skuId);
	NewYearChargeManager::GetInstancePtr()->CheckChargeAward();
	RechargeDailySignActivityManager::GetInstancePtr()->RequestNetwork();
	DiscountShopActivityManager::GetInstancePtr()->RequestNetwork();
	FirstRechargeExtraManager::GetInstancePtr()->RequestNetwork();
	MonthlyCardSpecialManager::GetInstancePtr()->RequestNetwork();
	if (i_skuId.find("DangerRoomSpecialOfferExtra", 0) != std::string::npos)
		DangerRoomSpecialOfferExtraManager::GetInstancePtr()->RequestNetwork();
	else if (i_skuId == "com.popcap.ios.chs.PVZ2.NewRecallBank18")
	{
		TGANewRecallBankData data;
		data._step = std::to_string(2);
		TGALogMgr::GetInstance().LogNewRecallBank(data);
		std::vector<std::pair<int, int>> activities;
		activities.push_back(std::pair<int, int>((int)Activity_NewRecall_Bank, 1));
		NetworkMgr::Instance()->GetNewNetWorkProcess()->RequestActivityList(activities, 0, true);
	}
	else if (i_skuId == "com.popcap.ios.chs.PVZ2.TimeMystery45")
		UnchartedModeNetworkMgr::GetInstancePtr()->RequestNetwork();
	else if (i_skuId == "com.popcap.ios.chs.PVZ2.EasterEgg06")
	{
		std::vector<std::pair<int, int>> activities;
		activities.push_back(std::pair<int, int>((int)Activity_NewPlayerSpecialGift, 1));
		NetworkMgr::Instance()->GetNewNetWorkProcess()->RequestActivityList(activities, 0, true);
	}
	else if (i_skuId == "com.popcap.ios.chs.PVZ2.DuelChest3")
		gMessageRouter->Post(NewPVPShopBuyChestMsg, 1, bonuslist);
	else if (i_skuId == "com.popcap.ios.chs.PVZ2.DuelChest4")
		gMessageRouter->Post(NewPVPShopBuyChestMsg, 0, bonuslist);
	else if (i_skuId.find("com.popcap.ios.chs.PVZ2.LevelPackage_", 0) != std::string::npos)
	{
		WorldLevelPackageManager::GetInstancePtr()->ResetInitRequest();
		WorldLevelPackageManager::GetInstancePtr()->RequestNetwork(true);
	}
	else if (i_skuId == "com.popcap.ios.chs.PVZ2.newpvpbattlepass45")
	{
		std::vector<S2C_BonusInfo> rewards;
		for (std::vector<S2C_BonusInfo>::iterator it = bonuslist.begin(), end = bonuslist.end(); it != end; ++it)
		{
			int objectId = (*it).objectId;
			int quantity = (*it).quantity;
			if (quantity != 0)
			{
				S2C_BonusInfo reward;
				reward.objectId = objectId;
				reward.quantity = quantity;
				rewards.push_back(reward);
			}
		}
		gMessageRouter->Post(NewPVPBattlePassExtrarewardsMsg, rewards, 3);
	}
	else if (i_skuId == "com.popcap.ios.chs.PVZ2.newpvpbattlepass78")
	{
		std::vector<S2C_BonusInfo> rewards;
		for (std::vector<S2C_BonusInfo>::iterator it = bonuslist.begin(), end = bonuslist.end(); it != end; ++it)
		{
			int objectId = (*it).objectId;
			int quantity = (*it).quantity;
			if (quantity != 0)
			{
				S2C_BonusInfo reward;
				reward.objectId = objectId;
				reward.quantity = quantity;
				rewards.push_back(reward);
			}
		}
		gMessageRouter->Post(NewPVPBattlePassExtrarewardsMsg, rewards, 4);
	}
	else if (i_skuId.find("com.popcap.ios.chs.PVZ2.TreasureBowl", 0) != std::string::npos)
		CornucopiaMgr::GetInstancePtr()->RequestNetwork();
	else if (i_skuId.find("com.popcap.ios.chs.PVZ2.PartyEpsActivity", 0) != std::string::npos)
		PartyAssistMgr::GetInstancePtr()->RequestNetwork();
	else if (i_skuId == "com.popcap.ios.chs.PVZ2.newpvpbattlepass68")
		gMessageRouter->Post(NewPVPBattlePassBuyPrivilegeMsg, bonuslist);
}
