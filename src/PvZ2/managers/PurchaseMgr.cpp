//
//  PurchaseMgr.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PurchaseMgr.h"
#include "LawnApp.h"
#include "PVZ2UIDialog.h"
#include "MagentoService.h"
#include "TodLib/TodStringFile.h"
#include "TodLib/TodCommon.h"
#include "PrimeText_Game.h"
#include "ProfileMgr.h"
#include "PurchaseBroker.h"
#include "gameNetWork/NetworkMgr.h"
#include "gameNetWork/NetworkMsgProcess.h"
#include "gameNetWork/NetworkData.h"

/////////////// Lifecycle ///////////////

PurchaseMgr::PurchaseMgr()
{
	m_orderId = "";
	m_channelId = "";
	m_productId = "";
	m_validateState = NOT_IN_VALIDATION;
	m_requestLostOrders = false;
	m_isOnlinePay = false;
	gMessageRouter->Subscribe(Message::MsgError, Sexy::MakeDelegate(*this, &PurchaseMgr::onNetworkError));
	gMessageRouter->Subscribe(Message::NotifyPurchaseInit, Sexy::MakeDelegate(*this, &PurchaseMgr::onNotifyPurchaseInit));
	gMessageRouter->Subscribe(Message::NotifyPurchaseValidation, Sexy::MakeDelegate(*this, &PurchaseMgr::onNotifyPurchaseValidation));
	gMessageRouter->Subscribe(Message::NotifyLostPurchaseOrder, Sexy::MakeDelegate(*this, &PurchaseMgr::onNotifyLostPurchaseOrder));
}

PurchaseMgr::~PurchaseMgr()
{
	gMessageRouter->Unsubscribe(this);
}

/////////////// Accessors ///////////////

void PurchaseMgr::SetOrderId(const std::string& i_orderId)
{
	if (m_orderId == "")
		m_orderId = i_orderId;
}

void PurchaseMgr::SetChannelId(const std::string& i_channelId)
{
	if (m_channelId == "")
		m_channelId = i_channelId;
}

const std::string& PurchaseMgr::GetChannelId()
{
	return m_channelId;
}

/////////////// Logic ///////////////

void PurchaseMgr::onNetworkError(int erroId)
{
}

void PurchaseMgr::InitPurchaseOrder(const std::string& i_sku)
{
	m_productId = i_sku;
	NetworkMgr::Instance()->GetNewNetWorkProcess()->InitPurchaseOrder(i_sku);
}

void PurchaseMgr::ValidatePurchaseOrder(const std::string& i_sku, bool isRestore)
{
	m_productId = i_sku;
	NetworkMgr::Instance()->GetNewNetWorkProcess()->RequestUpdateChargeInfo(i_sku, isRestore, 0);
}

void PurchaseMgr::ResetPurchaseInfo()
{
	m_orderId = "";
	m_channelId = "";
	m_productId = "";
	m_validateState = NOT_IN_VALIDATION;
}

void PurchaseMgr::DoValidateAgain()
{
	gLawnApp->KillPVZ2Dialog();
	m_validateState = SECOND_TRY;
	ValidatePurchaseOrder(m_productId, false);
}

void PurchaseMgr::RequestLostPurchaseOrder()
{
	NetworkMgr::Instance()->GetNewNetWorkProcess()->RequestLostPurchaseOrder();
}

void PurchaseMgr::FinishRetreiveLostOrders()
{
	m_requestLostOrders = false;
	m_lostOrders.clear();
	ResetPurchaseInfo();
}

void PurchaseMgr::onNotifyLostPurchaseOrder(int i_errorCode, const S2C_Purchase_LostPurchaseOrder& i_order)
{
	if (i_errorCode == 0)
	{
		m_lostOrders = i_order.m_infos;
		TryRetreiveLostOrders();
	}
	else
	{
		gMessageRouter->Post(&Message::NotifyPurchaseResult, false, "", i_errorCode);
	}
}

void PurchaseMgr::onNotifyPurchaseInit(int i_errorCode, const std::string& i_orderId, const std::string& i_skuId)
{
	if (i_errorCode == 0)
	{
		ProfileMgr::GetInstance().GetPurchaseBroker()->DoValidationPayment(i_orderId, NetworkMgr::Instance()->GetNetWorkProcess()->INetworkMsgProcess::GetPlayUserId());
	}
	else
	{
		gMessageRouter->Post(&Message::NotifyPurchaseResult, false, std::string(i_skuId), i_errorCode);
	}
}

void PurchaseMgr::onNotifyPurchaseValidation(int i_errorCode, const std::string& i_skuId, int i_status)
{
	gLawnApp->KillPVZ2Dialog();
	if (i_errorCode == 0)
	{
		if (i_status == RESULT_SUCCESS)
			gMessageRouter->Post(&Message::NotifyPurchaseResult, true, i_skuId, i_errorCode);
		else if (i_status != RESULT_PENDING || m_validateState == SECOND_TRY)
			gMessageRouter->Post(&Message::NotifyPurchaseResult, false, i_skuId, i_errorCode);
		else if (m_validateState == FIRST_TRY)
			TryValidateAgain();
	}
	else
		gMessageRouter->Post(&Message::NotifyPurchaseResult, false, i_skuId, i_errorCode);
}

void PurchaseMgr::TryValidateAgain()
{
	PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(SexyString(L"[VALIDATE_FIRST_FAILED_TITLE]"), SexyString(L"[VALIDATE_FIRST_FAILED_TEXT]"));
	dialog->AddButton(SexyString(L"[DIALOG_STRING_OK]"), Sexy::Delegate0(Sexy::MakeDelegate(*this, &PurchaseMgr::DoValidateAgain)));
}

static int UIScaleNum(int i_num)
{
	return ((ScaledApp*)gSexyApp)->UIScaleNum(i_num);
}

void PurchaseMgr::TryRetreiveLostOrders()
{
	if (!m_lostOrders.empty())
	{
		PurchaseOrderInfo info = *m_lostOrders.data();
		m_orderId = info.orderId;
		m_channelId = info.channelId;
		m_productId = info.skuId;
		m_lostOrders.erase(m_lostOrders.begin());
		m_requestLostOrders = true;
		MagentoProductPropsPtr product = Magento::GetProductPtr(m_productId);
		if (!product.IsValid())
			return;
		PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(UIScaleNum(400), UIScaleNum(300));
		dialog->SetHeaderLabel(SexyString(L"[PURCHASE_RESTORE_DIALOG_HEADER]"));
	SexyString footer = TodReplaceString(L"[PURCHASE_RESTORE_DIALOG_DESC]", L"{PRODUCT_NAME}", TodStringTranslate(Sexy::UTF8StringToWString(product.Get()->GetLocalizedShortDescription())).c_str());
		dialog->SetFooterLabel(footer);
		dialog->SetBackgroundDarken(true, 0.5f);
		ValidatePurchaseOrder(m_productId, true);
	}
	else
		FinishRetreiveLostOrders();
}
