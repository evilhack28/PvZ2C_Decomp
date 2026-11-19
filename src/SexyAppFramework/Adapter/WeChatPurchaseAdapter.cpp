//
//  WeChatPurchaseAdapter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include "drivers/app/android/JavaInterface.h"
#include "PurchaseAdapters.h"
#include "SocialMgr.h"
#include "WGPlatform.h"

using namespace Sexy;

std::string WeChatPurchaseAdapter::mproductId;

/////////////// Lifecycle ///////////////

WeChatPurchaseAdapter::WeChatPurchaseAdapter()
{
	__android_log_print(ANDROID_LOG_INFO, "WeChatMMPurchase", "Let's get retarded!");
	ConstructJava(Android::Util::GetJNIEnv(), "com/popcap/purchase/WeChat/WeChatPurchase", "(J)V", this);
}

WeChatPurchaseAdapter::~WeChatPurchaseAdapter()
{
}

void WeChatPurchaseAdapter::Initialize()
{
	IPurchaseAdapter::Initialize();
	__android_log_print(ANDROID_LOG_VERBOSE, "WeChatPurchase", "Initialize");
	JavaInitializeSDK(Android::Util::GetJNIEnv(), mJavaObject);
}

/////////////// Accessors ///////////////

bool WeChatPurchaseAdapter::CanPay()
{
	return true;
}

std::string WeChatPurchaseAdapter::GetPurchasePlatform()
{
	return "WeChat";
}

SexyString WeChatPurchaseAdapter::GetAboutContentStringId()
{
	return L"[";
}

int WeChatPurchaseAdapter::GetTodayRechargeMax()
{
	return 999999;
}

int WeChatPurchaseAdapter::GetMonthRechargeMax()
{
	return 9999999;
}

/////////////// Java setters ///////////////

void WeChatPurchaseAdapter::SetPf(const std::string& pf)
{
	__android_log_print(ANDROID_LOG_VERBOSE, "WeChatPurchase", "SetPf");
	JNIEnv* env = Android::Util::GetJNIEnv();
	jstring javaString = env->NewStringUTF(pf.c_str());
	JavaSetPf(env, mJavaObject, javaString);
	env->DeleteLocalRef(javaString);
}

void WeChatPurchaseAdapter::SetPfKey(const std::string& pfKey)
{
	__android_log_print(ANDROID_LOG_VERBOSE, "WeChatPurchase", "SetPfKey");
	JNIEnv* env = Android::Util::GetJNIEnv();
	jstring javaString = env->NewStringUTF(pfKey.c_str());
	JavaSetPfKey(env, mJavaObject, javaString);
	env->DeleteLocalRef(javaString);
}

void WeChatPurchaseAdapter::SetResId(const std::string& resId)
{
	__android_log_print(ANDROID_LOG_VERBOSE, "WeChatPurchase", "SetResId");
	JNIEnv* env = Android::Util::GetJNIEnv();
	jstring javaString = env->NewStringUTF(resId.c_str());
	JavaSetResId(env, mJavaObject, javaString);
	env->DeleteLocalRef(javaString);
}

void WeChatPurchaseAdapter::SetSaveValue(const std::string& saveValue)
{
	__android_log_print(ANDROID_LOG_VERBOSE, "WeChatPurchase", "SetSaveValue");
	JNIEnv* env = Android::Util::GetJNIEnv();
	jstring javaString = env->NewStringUTF(saveValue.c_str());
	JavaSetSaveValue(env, mJavaObject, javaString);
	env->DeleteLocalRef(javaString);
}

void WeChatPurchaseAdapter::SetUserId(const std::string& userId)
{
	__android_log_print(ANDROID_LOG_VERBOSE, "WeChatPurchase", "SetUserId");
	JNIEnv* env = Android::Util::GetJNIEnv();
	jstring javaString = env->NewStringUTF(userId.c_str());
	JavaSetUserId(env, mJavaObject, javaString);
	env->DeleteLocalRef(javaString);
}

void WeChatPurchaseAdapter::SetUserKey(const std::string& userKey)
{
	__android_log_print(ANDROID_LOG_VERBOSE, "WeChatPurchase", "SetUserKey");
	JNIEnv* env = Android::Util::GetJNIEnv();
	jstring javaString = env->NewStringUTF(userKey.c_str());
	JavaSetUserKey(env, mJavaObject, javaString);
	env->DeleteLocalRef(javaString);
}

void WeChatPurchaseAdapter::SetSessionId(const std::string& sessionId)
{
	__android_log_print(ANDROID_LOG_VERBOSE, "WeChatPurchase", "SetSessionId");
	JNIEnv* env = Android::Util::GetJNIEnv();
	jstring javaString = env->NewStringUTF(sessionId.c_str());
	JavaSetSessionId(env, mJavaObject, javaString);
	env->DeleteLocalRef(javaString);
}

void WeChatPurchaseAdapter::SetSessionType(const std::string& sessionType)
{
	__android_log_print(ANDROID_LOG_VERBOSE, "WeChatPurchase", "SetSessionType");
	JNIEnv* env = Android::Util::GetJNIEnv();
	jstring javaString = env->NewStringUTF(sessionType.c_str());
	JavaSetSessionType(env, mJavaObject, javaString);
	env->DeleteLocalRef(javaString);
}

/////////////// Purchase ///////////////

void WeChatPurchaseAdapter::GetProductCode(const std::string& productId, std::string& productCode)
{
	if (productId == "com.popcap.ios.chs.PVZ2.diamonds3" || productId == "com.popcap.ios.chs.PVZ2.diamonds.newer.present")
		SetSaveValue("6");
	else if (productId == "com.popcap.ios.chs.PVZ2.diamonds4")
		SetSaveValue("30");
	else if (productId == "com.popcap.ios.chs.PVZ2.diamonds5")
		SetSaveValue("68");
	else if (productId == "com.popcap.ios.chs.PVZ2.diamonds6")
		SetSaveValue("128");
}

void WeChatPurchaseAdapter::RequestPay(const std::string& productId, const std::string& orderNumber)
{
	std::string productCode;
	mproductId = productId;
	GetProductCode(productId, productCode);
	RequestLaunchSave();
}

void WeChatPurchaseAdapter::RequestLaunchSave()
{
	SetSaveValue("60");
	SetPayParam();
	JavaLaunchSave(Android::Util::GetJNIEnv(), mJavaObject);
}

void WeChatPurchaseAdapter::SetPayParam()
{
	const AuthInfo& authInfo = SocialMgr::GetInstance().GetAuthInfo();
	SetUserId(authInfo.openId);
	SetUserKey(authInfo.userKey);
	SetSessionId(authInfo.sessionId);
	SetSessionType(authInfo.sessionType);

	std::string pf = WGPlatform::GetInstance()->WGGetPf();
	std::string pfKey = WGPlatform::GetInstance()->WGGetPfKey();
	pf = easytolower(pf);
	SetPf(pf);
	SetPfKey(pfKey);
}

/////////////// Java ///////////////

void WeChatPurchaseAdapter::BindJavaMethods(JNIEnv* env, const JavaClass& javaClass)
{
	JavaInitializeSDK.init(env, javaClass, "InitializeSDK", "()V");
	JavaRequestPay.init(env, javaClass, "RequestPay", "(Ljava/lang/String;)V");
	JavaSetResId.init(env, javaClass, "SetResId", "(I)V");
	JavaSetSaveValue.init(env, javaClass, "SetSaveValue", "(Ljava/lang/String;)V");
	JavaLaunchSave.init(env, javaClass, "LaunchRechargeView", "()V");
	JavaSetUserId.init(env, javaClass, "SetUserId", "(Ljava/lang/String;)V");
	JavaSetUserKey.init(env, javaClass, "SetUserKey", "(Ljava/lang/String;)V");
	JavaSetSessionId.init(env, javaClass, "SetSessionId", "(Ljava/lang/String;)V");
	JavaSetSessionType.init(env, javaClass, "SetSessionType", "(Ljava/lang/String;)V");
	JavaSetPf.init(env, javaClass, "SetPf", "(Ljava/lang/String;)V");
	JavaSetPfKey.init(env, javaClass, "SetPfkey", "(Ljava/lang/String;)V");
}

void WeChatPurchaseAdapter::BindNativeMethods(JNIEnv* env, const JavaClass& javaClass)
{
	JNINativeMethod methods[] =
	{
		{ "FirePaymentComplete", "(JI)V", (void*)PaymentHook },
	};

	javaClass.registerNatives(methods, 1);
}

void WeChatPurchaseAdapter::PaymentHook(JNIEnv* env, jobject javaObject, jlong nativeObject, jint resultCode)
{
	IPurchaseAdapter* adapter = (IPurchaseAdapter*)nativeObject;
	switch (resultCode)
	{
	case BILLING_RESULT_SUCCESS:
		AndroidAppDriver::StaticEnqueueCallback(*adapter, &IPurchaseAdapter::OnPaymentComplete, mproductId);
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
