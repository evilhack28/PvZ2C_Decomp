//
//  UnicomWidebandPurchaseAdapter.cpp
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

UnicomWidebandPurchaseAdapter::UnicomWidebandPurchaseAdapter()
{
	__android_log_print(ANDROID_LOG_INFO, "UnicomWidebandPurchase", "Let's get retarded!");
	ConstructJava(Android::Util::GetJNIEnv(), "com/popcap/purchase/UnicomWideband/UnicomWidebandPurchase", "(J)V", this);
}

UnicomWidebandPurchaseAdapter::~UnicomWidebandPurchaseAdapter()
{
}

void UnicomWidebandPurchaseAdapter::Initialize()
{
	IPurchaseAdapter::Initialize();
	__android_log_print(ANDROID_LOG_VERBOSE, "UnicomWidebandPurchase", "Initialize");
	JavaInitializeSDK(Android::Util::GetJNIEnv(), mJavaObject);
}

/////////////// Accessors ///////////////

bool UnicomWidebandPurchaseAdapter::CanPay()
{
	return true;
}

bool UnicomWidebandPurchaseAdapter::NeedShowDialog()
{
	return true;
}

std::string UnicomWidebandPurchaseAdapter::GetPurchasePlatform()
{
	return "UnicomWideband";
}

SexyString UnicomWidebandPurchaseAdapter::GetAboutContentStringId()
{
	return L"[";
}

int UnicomWidebandPurchaseAdapter::GetTodayRechargeMax()
{
	return 300;
}

int UnicomWidebandPurchaseAdapter::GetMonthRechargeMax()
{
	return 500;
}

/////////////// Purchase ///////////////

ProductInfo UnicomWidebandPurchaseAdapter::GetProductInfo(const std::string& productId)
{
	ProductInfo info = IPurchaseAdapter::GetProductInfo(productId);
	PlatformType platform = gLawnApp->GetPlatform();
	if (platform == PLATFORM_CHINA_UNICOM_WIDEBAND)
	{
		if (productId == "com.popcap.ios.chs.PVZ2.diamonds3" || productId == "com.popcap.ios.chs.PVZ2.diamonds.newer.present")
			info.productCode = "0102111001";
		else if (productId == "com.popcap.ios.chs.PVZ2.diamonds4")
			info.productCode = "0110111001";
		else if (productId == "com.popcap.ios.chs.PVZ2.diamonds5")
			info.productCode = "0120111001";
		else if (productId == "com.popcap.ios.chs.PVZ2.diamonds6")
			info.productCode = "0130111001";
	}
	else if (platform == PLATFORM_CHINA_UNICOM_WIDEBAND_HD)
	{
		if (productId == "com.popcap.ios.chs.PVZ2.diamonds3" || productId == "com.popcap.ios.chs.PVZ2.diamonds.newer.present")
			info.productCode = "0102111002";
		else if (productId == "com.popcap.ios.chs.PVZ2.diamonds4")
			info.productCode = "0110111002";
		else if (productId == "com.popcap.ios.chs.PVZ2.diamonds5")
			info.productCode = "0120111002";
		else if (productId == "com.popcap.ios.chs.PVZ2.diamonds6")
			info.productCode = "0130111002";
	}
	return info;
}

void UnicomWidebandPurchaseAdapter::RequestPay(const std::string& productId, const std::string& orderNumber)
{
	IPurchaseAdapter::RequestPay(productId, orderNumber);
	__android_log_print(ANDROID_LOG_VERBOSE, "UnicomWidebandPurchase", "RequestPay( %s )", productId.c_str());
	ProductInfo info = GetProductInfo(productId);
	if (info.productCode == "")
	{
		OnPaymentIncomplete(IPurchaseDriver::Error);
		return;
	}

	std::string price;
	std::stringstream stream(std::ios_base::out | std::ios_base::in);
	stream << info.productPrice;
	stream >> price;
	std::string appId;
	PlatformType platform = gLawnApp->GetPlatform();
	if (platform == PLATFORM_CHINA_UNICOM_WIDEBAND)
		appId = "200639";
	else if (platform == PLATFORM_CHINA_UNICOM_WIDEBAND_HD)
		appId = "200640";
	else
	{
		OnPaymentIncomplete(IPurchaseDriver::Error);
		return;
	}

	JNIEnv* env = Android::Util::GetJNIEnv();
	jstring javaAppId = env->NewStringUTF(appId.c_str());
	jstring javaName = env->NewStringUTF(info.productName.c_str());
	jstring javaPrice = env->NewStringUTF(price.c_str());
	jstring javaCode = env->NewStringUTF(info.productCode.c_str());
	JavaRequestPay(env, mJavaObject, javaAppId, javaName, javaPrice, javaCode);
	env->DeleteLocalRef(javaName);
	env->DeleteLocalRef(javaPrice);
	env->DeleteLocalRef(javaAppId);
	env->DeleteLocalRef(javaCode);
}

/////////////// Java ///////////////

void UnicomWidebandPurchaseAdapter::BindJavaMethods(JNIEnv* env, const JavaClass& javaClass)
{
	JavaInitializeSDK.init(env, javaClass, "InitSDK", "()V");
	JavaRequestPay.init(env, javaClass, "RequestPay", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
}

void UnicomWidebandPurchaseAdapter::BindNativeMethods(JNIEnv* env, const JavaClass& javaClass)
{
	JNINativeMethod methods[] =
	{
		{ "FirePaymentComplete", "(JI)V", (void*)PaymentHook },
	};

	javaClass.registerNatives(methods, 1);
}

void UnicomWidebandPurchaseAdapter::PaymentHook(JNIEnv* env, jobject javaObject, jlong nativeObject, jint resultCode)
{
	__android_log_print(ANDROID_LOG_VERBOSE, "UnicomWidebandPurchase", "PaymentHook( %d )", resultCode);

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
