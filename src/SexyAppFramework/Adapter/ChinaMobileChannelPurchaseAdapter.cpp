//
//  ChinaMobileChannelPurchaseAdapter.cpp
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

ChinaMobileChannelPurchaseAdapter::ChinaMobileChannelPurchaseAdapter()
{
	__android_log_print(ANDROID_LOG_INFO, "ChinaMobileChannelPurchase", "Let's get retarded!");
	ConstructJava(Android::Util::GetJNIEnv(), "com/popcap/purchase/ChinaMobileChannel/ChinaMobileChannelPurchase", "(J)V", this);
	m_restoreAudioOnResume = true;
}

ChinaMobileChannelPurchaseAdapter::~ChinaMobileChannelPurchaseAdapter()
{
}

void ChinaMobileChannelPurchaseAdapter::Initialize()
{
	IPurchaseAdapter::Initialize();
	__android_log_print(ANDROID_LOG_VERBOSE, "ChinaMobileChannelPurchase", "Initialize");
	JavaInitializeSDK(Android::Util::GetJNIEnv(), mJavaObject);
}

void ChinaMobileChannelPurchaseAdapter::OnResume()
{
	IPurchaseAdapter::OnResume();
	__android_log_print(ANDROID_LOG_VERBOSE, "ChinaMobileChannelPurchase", "OnResume");
	JNIEnv* env = Android::Util::GetJNIEnv();
	if (m_restoreAudioOnResume && (gLawnApp->GetPlatform() == PLATFORM_CHINA_MOBILE || gLawnApp->GetPlatform() == PLATFORM_CHINA_MOBILE_HD))
	{
		m_restoreAudioOnResume = false;
		if (JavaIsMusicEnable(env, mJavaObject))
		{
			gLawnApp->SetMusicVolume(0.85);
			gLawnApp->SetSfxVolume(0.85);
		}
		else
		{
			gLawnApp->SetMusicVolume(0);
			gLawnApp->SetSfxVolume(0);
		}
	}
	JavaOnResume(env, mJavaObject);
}

bool ChinaMobileChannelPurchaseAdapter::ExitGame()
{
	JavaOnExit(Android::Util::GetJNIEnv(), mJavaObject);
	return true;
}

bool ChinaMobileChannelPurchaseAdapter::LaunchMoreGamesWebpage()
{
	JavaLaunchMoreGamesWebpage(Android::Util::GetJNIEnv(), mJavaObject);
	return true;
}

/////////////// Accessors ///////////////

bool ChinaMobileChannelPurchaseAdapter::CanPay()
{
	return true;
}

std::string ChinaMobileChannelPurchaseAdapter::GetPurchasePlatform()
{
	return "ChinaMobileChannel";
}

SexyString ChinaMobileChannelPurchaseAdapter::GetAboutContentStringId()
{
	return L"[";
}

int ChinaMobileChannelPurchaseAdapter::GetTodayRechargeMax()
{
	return 100;
}

int ChinaMobileChannelPurchaseAdapter::GetMonthRechargeMax()
{
	return 300;
}

/////////////// Purchase ///////////////

ProductInfo ChinaMobileChannelPurchaseAdapter::GetProductInfo(const std::string& productId)
{
	ProductInfo info = IPurchaseAdapter::GetProductInfo(productId);
	if (productId == "com.popcap.ios.chs.PVZ2.diamonds3" || productId == "com.popcap.ios.chs.PVZ2.diamonds.newer.present")
		info.productCode = "000";
	else if (productId == "com.popcap.ios.chs.PVZ2.diamonds4")
		info.productCode = "001";
	else if (productId == "com.popcap.ios.chs.PVZ2.diamonds5")
		info.productCode = "002";
	else if (productId == "com.popcap.ios.chs.PVZ2.diamonds6")
		info.productCode = "003";
	else if (productId == "com.popcap.ios.chs.PVZ2.diamonds.gemreturn")
		info.productCode = "006";
	else if (productId == "com.popcap.ios.chs.PVZ2.money.planttrial_1")
		info.productCode = "007";
	else if (productId == "com.popcap.ios.chs.PVZ2.money.planttrial_2")
		info.productCode = "008";
	else if (productId == "com.popcap.ios.chs.PVZ2.money.planttrial_3" || productId == "com.popcap.ios.chs.PVZ2.money.planttrial_4" || productId == "com.popcap.ios.chs.PVZ2.money.planttrial_5" || productId == "com.popcap.ios.chs.PVZ2.money.planttrial_6")
		info.productCode = "022";
	else if (productId == "com.popcap.ios.chs.PVZ2.money.planttrial_7" || productId == "com.popcap.ios.chs.PVZ2.money.planttrial_8")
		info.productCode = "023";
	else if (productId == "com.popcap.ios.chs.PVZ2.money.planttrial_9" || productId == "com.popcap.ios.chs.PVZ2.money.planttrial_10" || productId == "com.popcap.ios.chs.PVZ2.money.planttrial_11" || productId == "com.popcap.ios.chs.PVZ2.money.planttrial_12" || productId == "com.popcap.ios.chs.PVZ2.money.planttrial_13" || productId == "com.popcap.ios.chs.PVZ2.money.planttrial_14" || productId == "com.popcap.ios.chs.PVZ2.money.planttrial_15" || productId == "com.popcap.ios.chs.PVZ2.money.planttrial_16" || productId == "com.popcap.ios.chs.PVZ2.money.planttrial_17" || productId == "com.popcap.ios.chs.PVZ2.money.planttrial_18")
		info.productCode = "024";
	else if (productId == "com.popcap.chs.PVZ2.buy.mower")
		info.productCode = "020";
	else if (productId == "com.popcap.chs.PVZ2.buy.present")
		info.productCode = "021";
	else if (productId == "com.popcap.chs.PVZ2.buy.1000coins")
		info.productCode = "022";
	else if (productId == "com.popcap.chs.PVZ2.buy.2000coins")
		info.productCode = "023";
	else if (productId == "com.popcap.chs.PVZ2.buy.3000coins")
		info.productCode = "024";
	return info;
}

void ChinaMobileChannelPurchaseAdapter::RequestPay(const std::string& productId, const std::string& orderNumber)
{
	IPurchaseAdapter::RequestPay(productId, orderNumber);
	__android_log_print(ANDROID_LOG_VERBOSE, "ChinaMobileChannelPurchase", "RequestPay( %s )", productId.c_str());
	ProductInfo info = GetProductInfo(productId);
	JNIEnv* env = Android::Util::GetJNIEnv();
	jstring javaCode = env->NewStringUTF(info.productCode.c_str());
	JavaRequestPay(env, mJavaObject, javaCode);
	env->DeleteLocalRef(javaCode);
}

/////////////// Java ///////////////

void ChinaMobileChannelPurchaseAdapter::BindJavaMethods(JNIEnv* env, const JavaClass& javaClass)
{
	JavaInitializeSDK.init(env, javaClass, "InitializeSDK", "()V");
	JavaOnResume.init(env, javaClass, "OnResume", "()V");
	JavaRequestPay.init(env, javaClass, "RequestPay", "(Ljava/lang/String;)V");
	JavaOnExit.init(env, javaClass, "OnExit", "()V");
	JavaIsMusicEnable.init(env, javaClass, "IsMusicEnable", "()Z");
	JavaLaunchMoreGamesWebpage.init(env, javaClass, "LaunchMoreGamesWebpage", "()V");
}

void ChinaMobileChannelPurchaseAdapter::BindNativeMethods(JNIEnv* env, const JavaClass& javaClass)
{
	JNINativeMethod methods[] =
	{
		{ "FirePaymentComplete", "(JI)V", (void*)PaymentHook },
		{ "Native_ExitGame", "(J)V", (void*)ExitGameHook },
	};

	javaClass.registerNatives(methods, 2);
}

void ChinaMobileChannelPurchaseAdapter::ExitGameHook(JNIEnv* env, jobject javaObject, jlong nativeObject)
{
	__android_log_print(ANDROID_LOG_VERBOSE, "ChinaMobileChannelPurchase", "ExitGameHook");
	gLawnApp->onConfirmExitGame();
}

void ChinaMobileChannelPurchaseAdapter::PaymentHook(JNIEnv* env, jobject javaObject, jlong nativeObject, jint resultCode)
{
	__android_log_print(ANDROID_LOG_VERBOSE, "ChinaMobileChannelPurchase", "PaymentHook( %d )", resultCode);

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
