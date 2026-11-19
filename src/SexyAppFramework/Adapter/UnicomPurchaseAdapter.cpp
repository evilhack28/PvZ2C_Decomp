//
//  UnicomPurchaseAdapter.cpp
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

UnicomPurchaseAdapter::UnicomPurchaseAdapter()
{
	__android_log_print(ANDROID_LOG_INFO, "UnicomPurchase", "Let's get retarded!");
	ConstructJava(Android::Util::GetJNIEnv(), "com/popcap/purchase/Unicom/UnicomPurchase", "(J)V", this);
}

UnicomPurchaseAdapter::~UnicomPurchaseAdapter()
{
}

void UnicomPurchaseAdapter::Initialize()
{
	IPurchaseAdapter::Initialize();
	__android_log_print(ANDROID_LOG_VERBOSE, "UnicomPurchase", "Initialize");
	JNIEnv* env = Android::Util::GetJNIEnv();
	std::string appId = "";
	PlatformType platform = gLawnApp->GetPlatform();
	if (platform == PLATFORM_CHINA_UNICOM)
		appId = "903865228220130726145458058600";
	else if (platform == PLATFORM_CHINA_UNICOM_HD)
		appId = "903865228220130907091022285400";
	jstring javaAppId = env->NewStringUTF(appId.c_str());
	JavaInitializeSDK(env, mJavaObject, javaAppId);
	env->DeleteLocalRef(javaAppId);
}

/////////////// Accessors ///////////////

bool UnicomPurchaseAdapter::CanPay()
{
	return true;
}

bool UnicomPurchaseAdapter::NeedShowDialog()
{
	return true;
}

std::string UnicomPurchaseAdapter::GetPurchasePlatform()
{
	return "Unicom";
}

SexyString UnicomPurchaseAdapter::GetAboutContentStringId()
{
	return L"[";
}

int UnicomPurchaseAdapter::GetTodayRechargeMax()
{
	return 300;
}

int UnicomPurchaseAdapter::GetMonthRechargeMax()
{
	return 500;
}

/////////////// Purchase ///////////////

void UnicomPurchaseAdapter::RequestPay(const std::string& productId, const std::string& orderNumber)
{
	IPurchaseAdapter::RequestPay(productId, orderNumber);
	__android_log_print(ANDROID_LOG_VERBOSE, "UnicomPurchase", "RequestPay( %s )", productId.c_str());
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
	JNIEnv* env = Android::Util::GetJNIEnv();
	jstring javaName = env->NewStringUTF(info.productName.c_str());
	jstring javaPrice = env->NewStringUTF(price.c_str());
	jstring javaCode = env->NewStringUTF(info.productCode.c_str());
	JavaRequestPay(env, mJavaObject, javaName, javaPrice, javaCode);
	env->DeleteLocalRef(javaName);
	env->DeleteLocalRef(javaPrice);
	env->DeleteLocalRef(javaCode);
}

/////////////// Java ///////////////

void UnicomPurchaseAdapter::BindJavaMethods(JNIEnv* env, const JavaClass& javaClass)
{
	JavaInitializeSDK.init(env, javaClass, "InitSDK", "(Ljava/lang/String;)V");
	JavaRequestPay.init(env, javaClass, "RequestPay", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
}

void UnicomPurchaseAdapter::BindNativeMethods(JNIEnv* env, const JavaClass& javaClass)
{
	JNINativeMethod methods[] =
	{
		{ "FirePaymentComplete", "(JI)V", (void*)PaymentHook },
	};

	javaClass.registerNatives(methods, 1);
}

void UnicomPurchaseAdapter::PaymentHook(JNIEnv* env, jobject javaObject, jlong nativeObject, jint resultCode)
{
	__android_log_print(ANDROID_LOG_VERBOSE, "UnicomPurchase", "PaymentHook( %d )", resultCode);

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
