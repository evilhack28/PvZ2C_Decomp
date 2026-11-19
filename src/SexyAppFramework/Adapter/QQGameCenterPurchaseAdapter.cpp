//
//  QQGameCenterPurchaseAdapter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include "drivers/app/android/JavaInterface.h"
#include "PurchaseAdapters.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

QQGameCenterPurchaseAdapter::QQGameCenterPurchaseAdapter()
{
	__android_log_print(ANDROID_LOG_INFO, "QQGameCenterPurchase", "Let's get retarded!");
	ConstructJava(Android::Util::GetJNIEnv(), "com/popcap/purchase/QQGameCenter/QQGameCenterPurchase", "(J)V", this);
}

QQGameCenterPurchaseAdapter::~QQGameCenterPurchaseAdapter()
{
}

void QQGameCenterPurchaseAdapter::Initialize()
{
	IPurchaseAdapter::Initialize();
	__android_log_print(ANDROID_LOG_VERBOSE, "QQGameCenterPurchase", "Initialize");
	JavaInitializeSDK(Android::Util::GetJNIEnv(), mJavaObject);
}

/////////////// Accessors ///////////////

bool QQGameCenterPurchaseAdapter::CanPay()
{
	return true;
}

bool QQGameCenterPurchaseAdapter::NeedShowDialog()
{
	return true;
}

std::string QQGameCenterPurchaseAdapter::GetPurchasePlatform()
{
	return "QQGameCenter";
}

SexyString QQGameCenterPurchaseAdapter::GetAboutContentStringId()
{
	return L"[";
}

int QQGameCenterPurchaseAdapter::GetTodayRechargeMax()
{
	int cardType = Android::Diag::GetMobileCardType();
	if (cardType == 1 || cardType == 4)
		return 100;
	return 300;
}

int QQGameCenterPurchaseAdapter::GetMonthRechargeMax()
{
	int cardType = Android::Diag::GetMobileCardType();
	if (cardType == 1 || cardType == 4)
		return 300;
	return 500;
}

/////////////// Purchase ///////////////

void QQGameCenterPurchaseAdapter::GetProductCode(const std::string& productId, int& productCode)
{
	if (productId == "com.popcap.ios.chs.PVZ2.diamonds3" || productId == "com.popcap.ios.chs.PVZ2.diamonds.newer.present")
		productCode = 1;
	else if (productId == "com.popcap.ios.chs.PVZ2.diamonds4")
		productCode = 2;
}

void QQGameCenterPurchaseAdapter::RequestPay(const std::string& productId, const std::string& orderNumber)
{
	IPurchaseAdapter::RequestPay(productId, orderNumber);
	__android_log_print(ANDROID_LOG_VERBOSE, "QQGameCenterPurchase", "RequestPay( %s )", productId.c_str());
	int productCode = -1;
	GetProductCode(productId, productCode);
	JNIEnv* env = Android::Util::GetJNIEnv();
	__android_log_print(ANDROID_LOG_VERBOSE, "QQGameCenterPurchase", "JavaPrePay( %d )", productCode);
	JavaRequestPay(env, mJavaObject, productCode);
}

/////////////// Java ///////////////

void QQGameCenterPurchaseAdapter::BindJavaMethods(JNIEnv* env, const JavaClass& javaClass)
{
	JavaInitializeSDK.init(env, javaClass, "InitializeSDK", "()V");
	JavaRequestPay.init(env, javaClass, "RequestPay", "(I)V");
	JavaResume.init(env, javaClass, "Resume", "()V");
	JavaDestroy.init(env, javaClass, "Destroy", "()V");
}

void QQGameCenterPurchaseAdapter::BindNativeMethods(JNIEnv* env, const JavaClass& javaClass)
{
	JNINativeMethod methods[] =
	{
		{ "FirePaymentComplete", "(JI)V", (void*)PaymentHook },
	};

	javaClass.registerNatives(methods, 1);
}

void QQGameCenterPurchaseAdapter::PaymentHook(JNIEnv* env, jobject javaObject, jlong nativeObject, jint resultCode)
{
	__android_log_print(ANDROID_LOG_VERBOSE, "QQGameCenterPurchase", "PaymentHook( %d )", resultCode);

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
