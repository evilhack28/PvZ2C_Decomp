//
//  QQGameCenterUnicomPurchaseAdapter.cpp
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

QQGameCenterUnicomPurchaseAdapter::QQGameCenterUnicomPurchaseAdapter()
{
	__android_log_print(ANDROID_LOG_INFO, "QQGameCenterUnicomPurchase", "Let's get retarded!");
	ConstructJava(Android::Util::GetJNIEnv(), "com/popcap/purchase/QQGameCenterUnicom/QQGameCenterUnicomPurchase", "(J)V", this);
}

QQGameCenterUnicomPurchaseAdapter::~QQGameCenterUnicomPurchaseAdapter()
{
}

void QQGameCenterUnicomPurchaseAdapter::Initialize()
{
	IPurchaseAdapter::Initialize();
	__android_log_print(ANDROID_LOG_VERBOSE, "QQGameCenterUnicomPurchase", "Initialize");
	JavaInitializeSDK(Android::Util::GetJNIEnv(), mJavaObject);
}

/////////////// Accessors ///////////////

bool QQGameCenterUnicomPurchaseAdapter::CanPay()
{
	return true;
}

bool QQGameCenterUnicomPurchaseAdapter::NeedShowDialog()
{
	return true;
}

std::string QQGameCenterUnicomPurchaseAdapter::GetPurchasePlatform()
{
	return "QQGameCenter";
}

SexyString QQGameCenterUnicomPurchaseAdapter::GetAboutContentStringId()
{
	return L"[";
}

int QQGameCenterUnicomPurchaseAdapter::GetTodayRechargeMax()
{
	int cardType = Android::Diag::GetMobileCardType();
	if (cardType == 1 || cardType == 4)
		return 100;
	return 300;
}

int QQGameCenterUnicomPurchaseAdapter::GetMonthRechargeMax()
{
	int cardType = Android::Diag::GetMobileCardType();
	if (cardType == 1 || cardType == 4)
		return 300;
	return 500;
}

/////////////// Purchase ///////////////

void QQGameCenterUnicomPurchaseAdapter::GetProductCode(const std::string& productId, int& productCode)
{
	PlatformType platform = gLawnApp->GetPlatform();
	if (platform == PLATFORM_QQ_HD)
	{
		if (productId == "com.popcap.ios.chs.PVZ2.diamonds.newer.present")
			productCode = 20000;
		else if (productId == "com.popcap.ios.chs.PVZ2.diamonds3")
			productCode = 20001;
		else if (productId == "com.popcap.ios.chs.PVZ2.diamonds4")
			productCode = 20002;
	}
	else if (platform == PLATFORM_QQ)
	{
		if (productId == "com.popcap.ios.chs.PVZ2.diamonds.newer.present")
			productCode = 20000;
		else if (productId == "com.popcap.ios.chs.PVZ2.diamonds3")
			productCode = 20001;
		else if (productId == "com.popcap.ios.chs.PVZ2.diamonds4")
			productCode = 20002;
	}
}

void QQGameCenterUnicomPurchaseAdapter::RequestPay(const std::string& productId, const std::string& orderNumber)
{
	IPurchaseAdapter::RequestPay(productId, orderNumber);
	__android_log_print(ANDROID_LOG_VERBOSE, "QQGameCenterUnicomPurchase", "RequestPay( %s )", productId.c_str());
	int productCode = -1;
	GetProductCode(productId, productCode);
	JNIEnv* env = Android::Util::GetJNIEnv();
	__android_log_print(ANDROID_LOG_VERBOSE, "QQGameCenterUnicomPurchase", "JavaPrePay( %d )", productCode);
	bool isHD = gLawnApp->GetPlatform() == PLATFORM_QQ_HD;
	JavaRequestPay(env, mJavaObject, productCode, isHD);
}

/////////////// Java ///////////////

void QQGameCenterUnicomPurchaseAdapter::BindJavaMethods(JNIEnv* env, const JavaClass& javaClass)
{
	JavaInitializeSDK.init(env, javaClass, "InitializeSDK", "()V");
	JavaRequestPay.init(env, javaClass, "RequestPay", "(II)V");
	JavaResume.init(env, javaClass, "Resume", "()V");
	JavaDestroy.init(env, javaClass, "Destroy", "()V");
}

void QQGameCenterUnicomPurchaseAdapter::BindNativeMethods(JNIEnv* env, const JavaClass& javaClass)
{
	JNINativeMethod methods[] =
	{
		{ "FirePaymentComplete", "(JI)V", (void*)PaymentHook },
	};

	javaClass.registerNatives(methods, 1);
}

void QQGameCenterUnicomPurchaseAdapter::PaymentHook(JNIEnv* env, jobject javaObject, jlong nativeObject, jint resultCode)
{
	__android_log_print(ANDROID_LOG_VERBOSE, "QQGameCenterUnicomPurchase", "PaymentHook( %d )", resultCode);

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
