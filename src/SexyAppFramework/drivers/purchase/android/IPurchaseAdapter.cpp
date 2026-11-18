//
//  IPurchaseAdapter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-18.
//
/////////////// Lifecycle ///////////////

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/drivers/purchase/android/IPurchaseAdapter.h"

namespace Sexy
{

IPurchaseAdapter::IPurchaseAdapter()
{
	mPurchaseDriver = NULL;
	mProductId = "";
}

IPurchaseAdapter::~IPurchaseAdapter()
{
}

void IPurchaseAdapter::Initialize()
{
}

void IPurchaseAdapter::Destory()
{
}

void IPurchaseAdapter::OnResume()
{
}

/////////////// Payment ///////////////

bool IPurchaseAdapter::ExitGame()
{
	return false;
}

bool IPurchaseAdapter::LaunchMoreGamesWebpage()
{
	return false;
}

bool IPurchaseAdapter::NeedShowDialog()
{
	return false;
}

ProductInfo IPurchaseAdapter::GetProductInfo(const std::string& productId)
{
	return ProductInfo();
}

void IPurchaseAdapter::RequestPay(const std::string& productId, const std::string& orderNumber)
{
	mProductId = productId;
}

void IPurchaseAdapter::QueryOrder(const std::string& productId)
{
}

void IPurchaseAdapter::RequestLaunchSave()
{
}

void IPurchaseAdapter::SetPayParam()
{
}

void IPurchaseAdapter::SetPurchaseDriver(AndroidPurchaseDriver* purchaseDriver)
{
	mPurchaseDriver = purchaseDriver;
}

void IPurchaseAdapter::OnPaymentComplete(const std::string& receipt)
{
	if (mPurchaseDriver)
		mPurchaseDriver->OnPaymentComplete(mProductId);
}

void IPurchaseAdapter::OnPaymentIncomplete(const IPurchaseDriver::CauseForIncompletion& cause)
{
	if (mPurchaseDriver)
		mPurchaseDriver->OnPaymentIncomplete(mProductId, cause);
}

}
