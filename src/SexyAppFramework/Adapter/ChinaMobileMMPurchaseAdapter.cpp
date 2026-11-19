//
//  ChinaMobileMMPurchaseAdapter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include "drivers/app/android/JavaInterface.h"
#include "PurchaseAdapters.h"
#include "LawnApp.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

ChinaMobileMMPurchaseAdapter::ChinaMobileMMPurchaseAdapter()
{
	__android_log_print(ANDROID_LOG_INFO, "ChinaMobileMMPurchase", "Let's get retarded!");
	ConstructJava(Android::Util::GetJNIEnv(), "com/popcap/purchase/ChinaMobileMM/ChinaMobileMMPurchase", "(J)V", this);
}

ChinaMobileMMPurchaseAdapter::~ChinaMobileMMPurchaseAdapter()
{
}

void ChinaMobileMMPurchaseAdapter::Initialize()
{
	IPurchaseAdapter::Initialize();
	__android_log_print(ANDROID_LOG_VERBOSE, "ChinaMobileMMPurchase", "Initialize");
	JNIEnv* env = Android::Util::GetJNIEnv();
	std::string appId = "";
	std::string appKey = "";
	PlatformType platform = gLawnApp->GetPlatform();
	if (platform == PLATFORM_CHINA_MOBILE_MM)
	{
		appId = "300002883533";
		appKey = "8ECE02267C0529F6";
	}
	else if (platform == PLATFORM_CHINA_MOBILE_MM_SICHUAN_HD || platform == PLATFORM_CHINA_MOBILE_MM_HD)
	{
		appId = "300003374011";
		appKey = "A8AAE6BE363D69A3";
	}
	jstring javaAppId = env->NewStringUTF(appId.c_str());
	jstring javaAppKey = env->NewStringUTF(appKey.c_str());
	JavaInitializeSDK(env, mJavaObject, javaAppId, javaAppKey);
	env->DeleteLocalRef(javaAppId);
	env->DeleteLocalRef(javaAppKey);
}

/////////////// Accessors ///////////////

bool ChinaMobileMMPurchaseAdapter::CanPay()
{
	return true;
}

std::string ChinaMobileMMPurchaseAdapter::GetPurchasePlatform()
{
	return "ChinaMobileMM";
}

SexyString ChinaMobileMMPurchaseAdapter::GetAboutContentStringId()
{
	return L"[";
}

int ChinaMobileMMPurchaseAdapter::GetTodayRechargeMax()
{
	return 100;
}

int ChinaMobileMMPurchaseAdapter::GetMonthRechargeMax()
{
	return 300;
}

/////////////// Payment ///////////////

ProductInfo ChinaMobileMMPurchaseAdapter::GetProductInfo(const std::string& productId)
{
	__android_log_print(ANDROID_LOG_VERBOSE, "ChinaMobileMMPurchase", "GetProductInfo( %s )", productId.c_str());
	ProductInfo info = IPurchaseAdapter::GetProductInfo(productId);
	PlatformType platform = gLawnApp->GetPlatform();
	if (platform == PLATFORM_CHINA_MOBILE_MM)
	{
		if (productId == "com.popcap.ios.chs.PVZ2.diamonds3" || productId == "com.popcap.ios.chs.PVZ2.diamonds.newer.present")
			info.productCode = "30000288353301";
		else if (productId == "com.popcap.ios.chs.PVZ2.diamonds4")
			info.productCode = "30000288353302";
		else if (productId == "com.popcap.ios.chs.PVZ2.diamonds5")
			info.productCode = "30000288353303";
		else if (productId == "com.popcap.ios.chs.PVZ2.diamonds6")
			info.productCode = "30000288353304";
		else if (productId == "com.popcap.pvz2.chinamobilemm.coin100" || productId == "com.popcap.pvz2.chinamobilemm.coin500" || productId == "com.popcap.pvz2.chinamobilemm.coin1000" || productId == "com.popcap.pvz2.chinamobilemm.coin5000" || productId == "com.popcap.pvz2.chinamobilemm.egyptkey" || productId == "com.popcap.pvz2.chinamobilemm.gem5" || productId == "com.popcap.pvz2.chinamobilemm.gem10" || productId == "com.popcap.pvz2.chinamobilemm.gem50" || productId == "com.popcap.pvz2.chinamobilemm.snowpea" || productId == "com.popcap.pvz2.chinamobilemm.torchwood" || productId == "com.popcap.pvz2.chinamobilemm.peapod" || productId == "com.popcap.pvz2.chinamobilemm.kernelpult" || productId == "com.popcap.pvz2.chinamobilemm.lightningreed" || productId == "com.popcap.pvz2.chinamobilemm.coconutcannon" || productId == "com.popcap.pvz2.chinamobilemm.piratekey" || productId == "com.popcap.pvz2.chinamobilemm.melonpult" || productId == "com.popcap.pvz2.chinamobilemm.imitater" || productId == "com.popcap.pvz2.chinamobilemm.cowboykey" || productId == "com.popcap.pvz2.chinamobilemm.firegourd" || productId == "com.popcap.pvz2.chinamobilemm.peach" || productId == "com.popcap.pvz2.chinamobilemm.kongfukey")
			info.productCode = "30000288353305";
		else if (productId == "com.popcap.ios.chs.PVZ2.diamonds.newer.present.chinamobilemm")
			info.productCode = "30000288353306";
		else if (productId == "com.popcap.ios.chs.PVZ2.diamonds.gemreturn")
			info.productCode = "30000288353307";
		else if (productId == "com.popcap.ios.chs.PVZ2.money.planttrial_1")
			info.productCode = "30000288353308";
		else if (productId == "com.popcap.ios.chs.PVZ2.money.planttrial_2")
			info.productCode = "30000288353309";
		else if (productId == "com.popcap.ios.chs.PVZ2.money.planttrial_3" || productId == "com.popcap.ios.chs.PVZ2.money.planttrial_4" || productId == "com.popcap.ios.chs.PVZ2.money.planttrial_5" || productId == "com.popcap.ios.chs.PVZ2.money.planttrial_6")
			info.productCode = "30000288353324";
		else if (productId == "com.popcap.ios.chs.PVZ2.money.planttrial_7" || productId == "com.popcap.ios.chs.PVZ2.money.planttrial_8")
			info.productCode = "30000288353325";
		else if (productId == "com.popcap.ios.chs.PVZ2.money.planttrial_9" || productId == "com.popcap.ios.chs.PVZ2.money.planttrial_10" || productId == "com.popcap.ios.chs.PVZ2.money.planttrial_11" || productId == "com.popcap.ios.chs.PVZ2.money.planttrial_12" || productId == "com.popcap.ios.chs.PVZ2.money.planttrial_13" || productId == "com.popcap.ios.chs.PVZ2.money.planttrial_14" || productId == "com.popcap.ios.chs.PVZ2.money.planttrial_15" || productId == "com.popcap.ios.chs.PVZ2.money.planttrial_16" || productId == "com.popcap.ios.chs.PVZ2.money.planttrial_17" || productId == "com.popcap.ios.chs.PVZ2.money.planttrial_18")
			info.productCode = "30000288353326";
		else if (productId == "com.popcap.chs.PVZ2.buy.mower")
			info.productCode = "30000288353321";
		else if (productId == "com.popcap.chs.PVZ2.buy.present")
			info.productCode = "30000288353322";
	}
	else if (platform == PLATFORM_CHINA_MOBILE_MM_SICHUAN_HD || platform == PLATFORM_CHINA_MOBILE_MM_HD)
	{
		if (productId == "com.popcap.ios.chs.PVZ2.diamonds3" || productId == "com.popcap.ios.chs.PVZ2.diamonds.newer.present")
			info.productCode = "30000337401101";
		else if (productId == "com.popcap.ios.chs.PVZ2.diamonds4")
			info.productCode = "30000337401102";
		else if (productId == "com.popcap.ios.chs.PVZ2.diamonds5")
			info.productCode = "30000337401103";
		else if (productId == "com.popcap.ios.chs.PVZ2.diamonds6")
			info.productCode = "30000337401104";
		else if (productId == "com.popcap.pvz2.chinamobilemm.coin100" || productId == "com.popcap.pvz2.chinamobilemm.coin500" || productId == "com.popcap.pvz2.chinamobilemm.coin1000" || productId == "com.popcap.pvz2.chinamobilemm.coin5000" || productId == "com.popcap.pvz2.chinamobilemm.egyptkey" || productId == "com.popcap.pvz2.chinamobilemm.gem5" || productId == "com.popcap.pvz2.chinamobilemm.gem10" || productId == "com.popcap.pvz2.chinamobilemm.gem50" || productId == "com.popcap.pvz2.chinamobilemm.snowpea" || productId == "com.popcap.pvz2.chinamobilemm.torchwood" || productId == "com.popcap.pvz2.chinamobilemm.peapod" || productId == "com.popcap.pvz2.chinamobilemm.kernelpult" || productId == "com.popcap.pvz2.chinamobilemm.lightningreed" || productId == "com.popcap.pvz2.chinamobilemm.coconutcannon" || productId == "com.popcap.pvz2.chinamobilemm.piratekey" || productId == "com.popcap.pvz2.chinamobilemm.melonpult" || productId == "com.popcap.pvz2.chinamobilemm.imitater" || productId == "com.popcap.pvz2.chinamobilemm.cowboykey" || productId == "com.popcap.pvz2.chinamobilemm.firegourd" || productId == "com.popcap.pvz2.chinamobilemm.peach" || productId == "com.popcap.pvz2.chinamobilemm.kongfukey")
			info.productCode = "30000337401105";
		else if (productId == "com.popcap.ios.chs.PVZ2.diamonds.newer.present.chinamobilemm")
			info.productCode = "30000337401106";
		else if (productId == "com.popcap.ios.chs.PVZ2.diamonds.gemreturn")
			info.productCode = "30000337401107";
		else if (productId == "com.popcap.ios.chs.PVZ2.money.planttrial_1")
			info.productCode = "30000337401108";
		else if (productId == "com.popcap.ios.chs.PVZ2.money.planttrial_2")
			info.productCode = "30000337401109";
		else if (productId == "com.popcap.ios.chs.PVZ2.money.planttrial_3" || productId == "com.popcap.ios.chs.PVZ2.money.planttrial_4" || productId == "com.popcap.ios.chs.PVZ2.money.planttrial_5" || productId == "com.popcap.ios.chs.PVZ2.money.planttrial_6")
			info.productCode = "30000337401123";
		else if (productId == "com.popcap.ios.chs.PVZ2.money.planttrial_7" || productId == "com.popcap.ios.chs.PVZ2.money.planttrial_8")
			info.productCode = "30000337401124";
		else if (productId == "com.popcap.ios.chs.PVZ2.money.planttrial_9" || productId == "com.popcap.ios.chs.PVZ2.money.planttrial_10" || productId == "com.popcap.ios.chs.PVZ2.money.planttrial_11" || productId == "com.popcap.ios.chs.PVZ2.money.planttrial_12" || productId == "com.popcap.ios.chs.PVZ2.money.planttrial_13" || productId == "com.popcap.ios.chs.PVZ2.money.planttrial_14" || productId == "com.popcap.ios.chs.PVZ2.money.planttrial_15" || productId == "com.popcap.ios.chs.PVZ2.money.planttrial_16" || productId == "com.popcap.ios.chs.PVZ2.money.planttrial_17" || productId == "com.popcap.ios.chs.PVZ2.money.planttrial_18")
			info.productCode = "30000337401125";
		else if (productId == "com.popcap.chs.PVZ2.buy.mower")
			info.productCode = "30000337401121";
		else if (productId == "com.popcap.chs.PVZ2.buy.present")
			info.productCode = "30000337401122";
	}
	return info;
}

void ChinaMobileMMPurchaseAdapter::RequestPay(const std::string& productId, const std::string& orderNumber)
{
	IPurchaseAdapter::RequestPay(productId, orderNumber);
	__android_log_print(ANDROID_LOG_VERBOSE, "ChinaMobileMMPurchase", "RequestPay( %s )", productId.c_str());
	ProductInfo info = GetProductInfo(productId);
	__android_log_print(ANDROID_LOG_VERBOSE, "ChinaMobileMMPurchase", "RequestPayCode( %s )", info.productCode.c_str());
	JNIEnv* env = Android::Util::GetJNIEnv();
	jstring javaCode = env->NewStringUTF(info.productCode.c_str());
	JavaRequestPay(env, mJavaObject, javaCode);
	env->DeleteLocalRef(javaCode);
}

/////////////// Java ///////////////

void ChinaMobileMMPurchaseAdapter::BindJavaMethods(JNIEnv* env, const JavaClass& javaClass)
{
	JavaInitializeSDK.init(env, javaClass, "InitializeSDK", "(Ljava/lang/String;Ljava/lang/String;)V");
	JavaRequestPay.init(env, javaClass, "RequestPay", "(Ljava/lang/String;)V");
}

void ChinaMobileMMPurchaseAdapter::BindNativeMethods(JNIEnv* env, const JavaClass& javaClass)
{
	JNINativeMethod methods[] =
	{
		{ "FirePaymentComplete", "(JI)V", (void*)PaymentHook },
	};

	javaClass.registerNatives(methods, 1);
}

void ChinaMobileMMPurchaseAdapter::PaymentHook(JNIEnv* env, jobject javaObject, jlong nativeObject, jint resultCode)
{
	std::string receipt = "";
	IPurchaseAdapter* adapter = (IPurchaseAdapter*)nativeObject;
	switch (resultCode)
	{
	case BILLING_RESULT_SUCCESS:
		AndroidAppDriver::StaticEnqueueCallback(*adapter, &IPurchaseAdapter::OnPaymentComplete, receipt);
		break;
	case BILLING_RESULT_FAILED:
		AndroidAppDriver::StaticEnqueueCallback(*adapter, &IPurchaseAdapter::OnPaymentIncomplete, IPurchaseDriver::Error);
		break;
	case BILLING_RESULT_CANCELED:
		AndroidAppDriver::StaticEnqueueCallback(*adapter, &IPurchaseAdapter::OnPaymentIncomplete, IPurchaseDriver::Canceled);
		break;
	case BILLING_RESULT_ALREADY_PAID:
		AndroidAppDriver::StaticEnqueueCallback(*adapter, &IPurchaseAdapter::OnPaymentIncomplete, IPurchaseDriver::AlreadyPaid);
		break;
	}
}
