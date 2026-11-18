//
//  AndroidPurchaseDriver.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-18.
//
/////////////// Lifecycle ///////////////

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/drivers/purchase/android/AndroidPurchaseDriver.h"
#include "SexyAppFramework/drivers/purchase/android/IPurchaseAdapter.h"

namespace Sexy
{

AndroidPurchaseDriver::AndroidPurchaseDriver()
{
	mPurchaseAdapter = NULL;
}

AndroidPurchaseDriver::~AndroidPurchaseDriver()
{
	if (mPurchaseAdapter)
	{
		mPurchaseAdapter->Destory();
		delete mPurchaseAdapter;
		mPurchaseAdapter = NULL;
	}
}

void AndroidPurchaseDriver::SetPurchaseAdapter(IPurchaseAdapter *purchaseAdapter)
{
	if (mPurchaseAdapter)
	{
		mPurchaseAdapter->Destory();
		delete mPurchaseAdapter;
	}
	mPurchaseAdapter = purchaseAdapter;
	if (mPurchaseAdapter)
		mPurchaseAdapter->SetPurchaseDriver(this);
}

IPurchaseAdapter* AndroidPurchaseDriver::GetPurchaseAdapter()
{
	return mPurchaseAdapter;
}

void AndroidPurchaseDriver::Init()
{
	if (mPurchaseAdapter)
		mPurchaseAdapter->Initialize();
}

void AndroidPurchaseDriver::OnResume()
{
	if (mPurchaseAdapter)
		mPurchaseAdapter->OnResume();
}

/////////////// Payment ///////////////

void AndroidPurchaseDriver::SetPaymentMonitor(IPaymentMonitor* monitor)
{
	mPaymentMonitor = monitor;
}

void AndroidPurchaseDriver::Refresh(const StructuredData* productIds, RefreshCallback callback)
{
	mRefreshCallback = callback;
}

bool AndroidPurchaseDriver::CanMakePayments()
{
	if (mPurchaseAdapter)
		return mPurchaseAdapter->CanPay();
	return false;
}

bool AndroidPurchaseDriver::HasCatalogData()
{
	return false;
}

bool AndroidPurchaseDriver::GetProduct(const std::string& productId, Product* product)
{
	return false;
}

bool AndroidPurchaseDriver::ProductTypeIsSupported(ProductType prodType)
{
	return true;
}

void AndroidPurchaseDriver::RequestPayment(const std::string& productId, const std::string& orderNumber)
{
	if (mPurchaseAdapter)
		mPurchaseAdapter->RequestPay(productId, orderNumber);
}

void AndroidPurchaseDriver::RestorePurchases(RestoreCallback callback)
{
	mRestoreCallback = callback;
}

void AndroidPurchaseDriver::ConfirmDelivery(const std::string& receiptId)
{
}

bool AndroidPurchaseDriver::HasUnconfirmedPayments()
{
	return false;
}

void AndroidPurchaseDriver::StartItemPurchase()
{
}

void AndroidPurchaseDriver::StartRecharge()
{
	if (mPurchaseAdapter)
		mPurchaseAdapter->RequestLaunchSave();
}

void AndroidPurchaseDriver::setParam()
{
	if (mPurchaseAdapter)
		mPurchaseAdapter->SetPayParam();
}

void AndroidPurchaseDriver::OnPaymentComplete(const std::string& productId)
{
	if (mPaymentMonitor)
		mPaymentMonitor->PurchaseDriverPaymentComplete(this, productId);
}

void AndroidPurchaseDriver::OnPaymentComplete(const std::string& receiptId, const std::string& receipt, const std::string& productId)
{
	if (mPaymentMonitor)
		mPaymentMonitor->PurchaseDriverPaymentComplete(this, receiptId, receipt, productId);
}

void AndroidPurchaseDriver::OnPaymentIncomplete(const std::string& productId, const IPurchaseDriver::CauseForIncompletion& cause)
{
	if (mPaymentMonitor)
		mPaymentMonitor->PurchaseDriverPaymentIncomplete(this, productId, cause);
}

void AndroidPurchaseDriver::RequestValidationPayment(const std::string& productId, const std::string& i_orderId, const std::string& i_userId)
{
	if (mPurchaseAdapter)
		mPurchaseAdapter->RequestValidationPayment(productId, i_orderId, i_userId);
}

void AndroidPurchaseDriver::QueryOrder(const std::string& productId)
{
	if (mPurchaseAdapter)
		mPurchaseAdapter->QueryOrder(productId);
}

void AndroidPurchaseDriver::Consume(const std::string& i_payCode, const std::string& i_orderNumber)
{
	if (mPurchaseAdapter)
		mPurchaseAdapter->Consume(i_payCode, i_orderNumber);
}

/////////////// Queries ///////////////

bool AndroidPurchaseDriver::ExitGame()
{
	if (mPurchaseAdapter)
		return mPurchaseAdapter->ExitGame();
	return false;
}

bool AndroidPurchaseDriver::LaunchMoreGamesWebpage()
{
	if (mPurchaseAdapter)
		return mPurchaseAdapter->LaunchMoreGamesWebpage();
	return false;
}

int AndroidPurchaseDriver::GetTodayRechargeMax()
{
	if (mPurchaseAdapter)
		return mPurchaseAdapter->GetTodayRechargeMax();
	return 999999;
}

int AndroidPurchaseDriver::GetMonthRechargeMax()
{
	if (mPurchaseAdapter)
		return mPurchaseAdapter->GetMonthRechargeMax();
	return 999999;
}

std::string AndroidPurchaseDriver::GetPurchasePlatform()
{
	if (mPurchaseAdapter)
		return mPurchaseAdapter->GetPurchasePlatform();
	return "no-purchase-adapter";
}

bool AndroidPurchaseDriver::NeedShowDialog()
{
	if (mPurchaseAdapter)
		return mPurchaseAdapter->NeedShowDialog();
	return false;
}

SexyString AndroidPurchaseDriver::GetAboutContentStringId()
{
	if (mPurchaseAdapter)
		return mPurchaseAdapter->GetAboutContentStringId();
	return L"";
}

bool AndroidPurchaseDriver::NeedPurchaseWhite()
{
	if (mPurchaseAdapter)
		return mPurchaseAdapter->NeedPurchaseWhite();
	return true;
}

bool AndroidPurchaseDriver::NeedShowChannelActivity()
{
	if (mPurchaseAdapter)
		return mPurchaseAdapter->NeedShowChannelActivity();
	return true;
}

std::string AndroidPurchaseDriver::GetChannelID()
{
	if (mPurchaseAdapter)
		return mPurchaseAdapter->GetChannelID();
	return "";
}

std::string AndroidPurchaseDriver::GetUniqueID()
{
	if (mPurchaseAdapter)
		return mPurchaseAdapter->GetUniqueID();
	return "";
}

std::string AndroidPurchaseDriver::GetUniqueCharacterID()
{
	if (mPurchaseAdapter)
		return mPurchaseAdapter->GetUniqueCharacterID();
	return "";
}

std::string AndroidPurchaseDriver::GetDeviceID()
{
	if (mPurchaseAdapter)
		return mPurchaseAdapter->GetDeviceID();
	return "";
}

std::string AndroidPurchaseDriver::GetSignature()
{
	if (mPurchaseAdapter)
		return mPurchaseAdapter->GetSignature();
	return "";
}

std::string AndroidPurchaseDriver::GetGameCenterUrl()
{
	if (mPurchaseAdapter)
		return mPurchaseAdapter->GetGameCenterUrl();
	return "";
}

std::string AndroidPurchaseDriver::GetChannelUpdateUrl()
{
	OutputDebugStrF("AndroidPurchaseDriver::GetChannelUpdateUrl mPurchaseAdapter = %d", mPurchaseAdapter != NULL);
	if (mPurchaseAdapter)
		return mPurchaseAdapter->GetChannelUpdateUrl();
	return "";
}

std::string AndroidPurchaseDriver::GetTWRequestHead()
{
	OutputDebugStrF("AndroidPurchaseDriver::GetTWRequestHead mPurchaseAdapter = %d", mPurchaseAdapter != NULL);
	if (mPurchaseAdapter)
		return mPurchaseAdapter->GetTWRequestHead();
	return "";
}

int AndroidPurchaseDriver::GetRedeemOrders(std::map<std::string, RedeemInfo>& validOrders)
{
	if (mPurchaseAdapter)
		return mPurchaseAdapter->GetRedeemOrders(validOrders);
	return 0;
}

void AndroidPurchaseDriver::CheckRedeemOrders()
{
	if (mPurchaseAdapter)
		mPurchaseAdapter->CheckRedeemOrders();
}

void AndroidPurchaseDriver::CheckSpecialRedeem()
{
	if (mPurchaseAdapter)
		mPurchaseAdapter->CheckSpecialRedeem();
}

void AndroidPurchaseDriver::CheckGameCenterStatus()
{
	if (mPurchaseAdapter)
		mPurchaseAdapter->CheckGameCenterStatus();
}

void AndroidPurchaseDriver::ShowGameCommunity()
{
	if (mPurchaseAdapter)
		mPurchaseAdapter->ShowGameCommunity();
}

ProductInfo AndroidPurchaseDriver::GetProductInfo(const std::string& productId)
{
	ProductInfo aInfo;
	if (mPurchaseAdapter)
		aInfo = mPurchaseAdapter->GetProductInfo(productId);
	return aInfo;
}

}
