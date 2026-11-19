//
//  TelecomPurchaseAdapter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include "drivers/app/android/JavaInterface.h"
#include "PurchaseAdapters.h"
#include "LawnApp.h"
#include "TodLib/TodStringFile.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

TelecomPurchaseAdapter::TelecomPurchaseAdapter()
{
	__android_log_print(ANDROID_LOG_INFO, "TelecomPurchase", "Let's get retarded!");
	ConstructJava(Android::Util::GetJNIEnv(), "com/popcap/purchase/Telecom/TelecomPurchase", "(J)V", this);
}

TelecomPurchaseAdapter::~TelecomPurchaseAdapter()
{
}

void TelecomPurchaseAdapter::Initialize()
{
	IPurchaseAdapter::Initialize();
	__android_log_print(ANDROID_LOG_VERBOSE, "TelecomPurchase", "Initialize");
	JavaInitializeSDK(Android::Util::GetJNIEnv(), mJavaObject);
}

void TelecomPurchaseAdapter::Destory()
{
	IPurchaseAdapter::Destory();
	__android_log_print(ANDROID_LOG_VERBOSE, "TelecomPurchase", "Destory");
	JavaDestorySDK(Android::Util::GetJNIEnv(), mJavaObject);
}

bool TelecomPurchaseAdapter::LaunchMoreGamesWebpage()
{
	gLawnApp->OpenURL("http://wapgame.189.cn", false);
	return true;
}

/////////////// Accessors ///////////////

bool TelecomPurchaseAdapter::CanPay()
{
	return true;
}

bool TelecomPurchaseAdapter::NeedShowDialog()
{
	return true;
}

std::string TelecomPurchaseAdapter::GetPurchasePlatform()
{
	return "Telecom";
}

SexyString TelecomPurchaseAdapter::GetAboutContentStringId()
{
	return L"[";
}

int TelecomPurchaseAdapter::GetTodayRechargeMax()
{
	return 100;
}

int TelecomPurchaseAdapter::GetMonthRechargeMax()
{
	return 300;
}

/////////////// Purchase ///////////////

void TelecomPurchaseAdapter::RequestPay(const std::string& productId, const std::string& orderNumber)
{
	IPurchaseAdapter::RequestPay(productId, orderNumber);
	__android_log_print(ANDROID_LOG_VERBOSE, "TelecomPurchase", "RequestPay( %s )", productId.c_str());
	ProductInfo info = GetProductInfo(productId);
	std::string productName = info.productName;
	std::string tips = StrFormat(SexyStringToUTF8String(TodStringTranslate(L"[TELECOM_PURCHASE_TIPS]")).c_str(), info.productPrice, info.productName.c_str());
	std::string success = StrFormat(SexyStringToUTF8String(TodStringTranslate(L"[TELECOM_PURCHASE_SUCCESS]")).c_str(), info.productName.c_str());
	JNIEnv* env = Android::Util::GetJNIEnv();
	jstring javaName = env->NewStringUTF(productName.c_str());
	jstring javaCode = env->NewStringUTF(info.productCode.c_str());
	jstring javaTips = env->NewStringUTF(tips.c_str());
	jstring javaSuccess = env->NewStringUTF(success.c_str());
	JavaRequestPay(env, mJavaObject, javaName, javaCode, javaTips, javaSuccess);
	env->DeleteLocalRef(javaName);
	env->DeleteLocalRef(javaCode);
	env->DeleteLocalRef(javaTips);
	env->DeleteLocalRef(javaSuccess);
}

/////////////// Java ///////////////

void TelecomPurchaseAdapter::BindJavaMethods(JNIEnv* env, const JavaClass& javaClass)
{
	JavaDestorySDK.init(env, javaClass, "DestorySDK", "()V");
	JavaInitializeSDK.init(env, javaClass, "InitializeSDK", "()V");
	JavaRequestPay.init(env, javaClass, "RequestPay", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
}

void TelecomPurchaseAdapter::BindNativeMethods(JNIEnv* env, const JavaClass& javaClass)
{
	JNINativeMethod methods[] =
	{
		{ "FirePaymentComplete", "(JI)V", (void*)PaymentHook },
	};

	javaClass.registerNatives(methods, 1);
}

void TelecomPurchaseAdapter::PaymentHook(JNIEnv* env, jobject javaObject, jlong nativeObject, jint resultCode)
{
	__android_log_print(ANDROID_LOG_VERBOSE, "TelecomPurchase", "PaymentHook( %d )", resultCode);

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
