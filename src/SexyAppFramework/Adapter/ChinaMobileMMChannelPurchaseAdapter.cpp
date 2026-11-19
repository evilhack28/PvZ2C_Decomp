//
//  ChinaMobileMMChannelPurchaseAdapter.cpp
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

ChinaMobileMMChannelPurchaseAdapter::ChinaMobileMMChannelPurchaseAdapter()
{
	__android_log_print(ANDROID_LOG_INFO, "ChinaMobileMMChannelPurchaseAdapter", "Let's get retarded!");
	ConstructJava(Android::Util::GetJNIEnv(), "com/popcap/purchase/ChinaMobileMMChannel/ChinaMobileMMChannelPurchase", "(J)V", this);
}

ChinaMobileMMChannelPurchaseAdapter::~ChinaMobileMMChannelPurchaseAdapter()
{
}

void ChinaMobileMMChannelPurchaseAdapter::Initialize()
{
	IPurchaseAdapter::Initialize();
	__android_log_print(ANDROID_LOG_VERBOSE, "ChinaMobileMMPurchase", "Initialize");
	JNIEnv* env = Android::Util::GetJNIEnv();
	std::string appId = "";
	std::string appKey = "";
	PlatformType platform = gLawnApp->GetPlatform();
	if ((platform > PLATFORM_THIRD_CHANNEL_START && platform < PLATFORM_THIRD_CHANNEL_END) || platform == PLATFORM_CHINA_TELECOM || platform == PLATFORM_CHINA_MOBILE_MM)
	{
		appId = "300002883533";
		appKey = "8ECE02267C0529F6";
	}
	else if ((platform >= PLATFORM_91_HD && platform <= PLATFORM_THIRD_CHANNEL_HD_END) || platform == PLATFORM_CHINA_MOBILE_MM_HD)
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

bool ChinaMobileMMChannelPurchaseAdapter::CanPay()
{
	return true;
}

std::string ChinaMobileMMChannelPurchaseAdapter::GetPurchasePlatform()
{
	return "ChinaMobileMM";
}

SexyString ChinaMobileMMChannelPurchaseAdapter::GetAboutContentStringId()
{
	return L"[";
}

int ChinaMobileMMChannelPurchaseAdapter::GetTodayRechargeMax()
{
	return 100;
}

int ChinaMobileMMChannelPurchaseAdapter::GetMonthRechargeMax()
{
	return 300;
}

/////////////// Payment ///////////////

void ChinaMobileMMChannelPurchaseAdapter::RequestPay(const std::string& productId, const std::string& orderNumber)
{
	IPurchaseAdapter::RequestPay(productId, orderNumber);
	__android_log_print(ANDROID_LOG_VERBOSE, "ChinaMobileMMChannelPurchaseAdapter", "RequestPay( %s )", productId.c_str());
	ProductInfo info = GetProductInfo(productId);
	JNIEnv* env = Android::Util::GetJNIEnv();
	jstring javaCode = env->NewStringUTF(info.productCode.c_str());
	JavaRequestPay(env, mJavaObject, javaCode);
	env->DeleteLocalRef(javaCode);
}

/////////////// Java ///////////////

void ChinaMobileMMChannelPurchaseAdapter::BindJavaMethods(JNIEnv* env, const JavaClass& javaClass)
{
	JavaInitializeSDK.init(env, javaClass, "InitializeSDK", "(Ljava/lang/String;Ljava/lang/String;)V");
	JavaRequestPay.init(env, javaClass, "RequestPay", "(Ljava/lang/String;)V");
}

void ChinaMobileMMChannelPurchaseAdapter::BindNativeMethods(JNIEnv* env, const JavaClass& javaClass)
{
	JNINativeMethod methods[] =
	{
		{ "FirePaymentComplete", "(JI)V", (void*)PaymentHook },
	};

	javaClass.registerNatives(methods, 1);
}

void ChinaMobileMMChannelPurchaseAdapter::PaymentHook(JNIEnv* env, jobject javaObject, jlong nativeObject, jint resultCode)
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
