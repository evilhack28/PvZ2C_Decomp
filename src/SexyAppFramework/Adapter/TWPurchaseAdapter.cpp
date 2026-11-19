//
//  TWPurchaseAdapter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include "drivers/app/android/JavaInterface.h"
#include "PurchaseAdapters.h"
#include "LawnApp.h"
#include "AuthMgr.h"
#include "MainMenu.h"
#include "TGALogMgr.h"
#include "MetricsCollector.h"
#include "DefineIDMgr.h"
#include "IdentifierMgr.h"
#include "NetworkMgr.h"
#include "PurchaseMgr.h"
#include "gameNetWork/NetworkMsgProcess.h"

using namespace Sexy;

std::map<std::string, std::string> TWPurchaseAdapter::PayCodeMapHD;
std::map<std::string, std::string> TWPurchaseAdapter::PayCodeMap;
std::string TWPurchaseAdapter::m_payCode;
JavaMethod<void> TWPurchaseAdapter::JavaInitializeSDK;
JavaMethod<void> TWPurchaseAdapter::JavaRequestPay;
JavaMethod<void> TWPurchaseAdapter::JavaQueryOrder;
JavaMethod<void> TWPurchaseAdapter::JavaOnExit;
JavaMethod<jstring> TWPurchaseAdapter::JavaGetDeclare;
JavaMethod<void> TWPurchaseAdapter::JavaRequestValidationPay;
JavaMethod<unsigned char> TWPurchaseAdapter::JavaNeedPurchaseWhite;
JavaMethod<unsigned char> TWPurchaseAdapter::JavaNeedShowChannelActivity;
JavaMethod<jstring> TWPurchaseAdapter::JavaGetChannelID;
JavaMethod<jstring> TWPurchaseAdapter::JavaGetUniqueID;
JavaMethod<jstring> TWPurchaseAdapter::JavaGetUniqueCharacterID;
JavaMethod<jstring> TWPurchaseAdapter::JavaGetChannelUpdateUrl;
JavaMethod<jstring> TWPurchaseAdapter::JavaGetTWRequestHead;
JavaMethod<jstring> TWPurchaseAdapter::JavaGetDeviceID;
JavaMethod<jstring> TWPurchaseAdapter::JavaGetSignature;
JavaMethod<void> TWPurchaseAdapter::JavaCheckRedeemOrders;
JavaMethod<jint> TWPurchaseAdapter::JavaGetRedeemOrders;
JavaMethod<void> TWPurchaseAdapter::JavaSetIDs;
JavaMethod<void> TWPurchaseAdapter::JavaShowGameCommunity;
JavaMethod<void> TWPurchaseAdapter::JavaConsume;
JavaMethod<void> TWPurchaseAdapter::JavaCheckSpecialRedeem;
JavaMethod<void> TWPurchaseAdapter::JavaCheckGameCenterStatus;
JavaMethod<jstring> TWPurchaseAdapter::JavaGetGameCenterUrl;

/////////////// Lifecycle ///////////////

TWPurchaseAdapter::~TWPurchaseAdapter()
{
}

/////////////// Accessors ///////////////

bool TWPurchaseAdapter::CanPay()
{
	return true;
}

std::string TWPurchaseAdapter::GetPurchasePlatform()
{
	return "TW";
}

int TWPurchaseAdapter::GetTodayRechargeMax()
{
	return 100;
}

int TWPurchaseAdapter::GetMonthRechargeMax()
{
	return 300;
}

SexyString TWPurchaseAdapter::GetAboutContentStringId()
{
	return UTF8StringToSexyString(GetDeclare());
}

bool TWPurchaseAdapter::NeedShowDialog()
{
	return true;
}

bool TWPurchaseAdapter::NeedPurchaseWhite()
{
	return JavaNeedPurchaseWhite(Android::Util::GetJNIEnv(), mJavaObject);
}

std::string TWPurchaseAdapter::GetChannelID()
{
	JNIEnv* env = Android::Util::GetJNIEnv();
	jstring jChannelId = JavaGetChannelID(env, mJavaObject);
	const char* chars = env->GetStringUTFChars(jChannelId, NULL);
	std::string channelId(chars);
	env->ReleaseStringUTFChars(jChannelId, chars);
	return channelId;
}

void TWPurchaseAdapter::CheckRedeemOrders()
{
	JavaCheckRedeemOrders(Android::Util::GetJNIEnv(), mJavaObject);
}

std::string TWPurchaseAdapter::GetDeclare()
{
	JNIEnv* env = Android::Util::GetJNIEnv();
	jstring jValue = JavaGetDeclare(env, mJavaObject);
	const char* chars = env->GetStringUTFChars(jValue, NULL);
	std::string value(chars);
	env->ReleaseStringUTFChars(jValue, chars);
	return value;
}

std::string TWPurchaseAdapter::GetUniqueCharacterID()
{
	JNIEnv* env = Android::Util::GetJNIEnv();
	jstring jValue = JavaGetUniqueCharacterID(env, mJavaObject);
	const char* chars = env->GetStringUTFChars(jValue, NULL);
	std::string value(chars);
	env->ReleaseStringUTFChars(jValue, chars);
	return value;
}

std::string TWPurchaseAdapter::GetUniqueID()
{
	JNIEnv* env = Android::Util::GetJNIEnv();
	jstring jValue = JavaGetUniqueID(env, mJavaObject);
	const char* chars = env->GetStringUTFChars(jValue, NULL);
	std::string value(chars);
	env->ReleaseStringUTFChars(jValue, chars);
	return value;
}

std::string TWPurchaseAdapter::GetChannelUpdateUrl()
{
	TodHesitationTrace("TWPurchaseAdapter::GetChannelUpdateUrl");
	JNIEnv* env = Android::Util::GetJNIEnv();
	jstring jValue = JavaGetChannelUpdateUrl(env, mJavaObject);
	const char* chars = env->GetStringUTFChars(jValue, NULL);
	std::string value(chars);
	env->ReleaseStringUTFChars(jValue, chars);
	return value;
}

std::string TWPurchaseAdapter::GetTWRequestHead()
{
	TodHesitationTrace("TWPurchaseAdapter::GetTWRequestHead");
	JNIEnv* env = Android::Util::GetJNIEnv();
	jstring jValue = JavaGetTWRequestHead(env, mJavaObject);
	const char* chars = env->GetStringUTFChars(jValue, NULL);
	std::string value(chars);
	env->ReleaseStringUTFChars(jValue, chars);
	return value;
}

std::string TWPurchaseAdapter::GetDeviceID()
{
	TodHesitationTrace("TWPurchaseAdapter::GetDeviceID");
	JNIEnv* env = Android::Util::GetJNIEnv();
	jstring jValue = JavaGetDeviceID(env, mJavaObject);
	const char* chars = env->GetStringUTFChars(jValue, NULL);
	std::string value(chars);
	env->ReleaseStringUTFChars(jValue, chars);
	return value;
}

std::string TWPurchaseAdapter::GetSignature()
{
	TodHesitationTrace("TWPurchaseAdapter::GetSignature");
	JNIEnv* env = Android::Util::GetJNIEnv();
	jstring jValue = JavaGetSignature(env, mJavaObject);
	const char* chars = env->GetStringUTFChars(jValue, NULL);
	std::string value(chars);
	env->ReleaseStringUTFChars(jValue, chars);
	return value;
}

std::string TWPurchaseAdapter::GetGameCenterUrl()
{
	TodHesitationTrace("TWPurchaseAdapter::GetGameCenterUrl");
	JNIEnv* env = Android::Util::GetJNIEnv();
	jstring jValue = JavaGetGameCenterUrl(env, mJavaObject);
	const char* chars = env->GetStringUTFChars(jValue, NULL);
	std::string value(chars);
	env->ReleaseStringUTFChars(jValue, chars);
	return value;
}

bool TWPurchaseAdapter::NeedShowChannelActivity()
{
	return JavaNeedShowChannelActivity(Android::Util::GetJNIEnv(), mJavaObject);
}

/////////////// Purchase ///////////////

bool TWPurchaseAdapter::ExitGame()
{
	JavaOnExit(Android::Util::GetJNIEnv(), mJavaObject);
	return true;
}

void TWPurchaseAdapter::ShowGameCommunity()
{
	JavaShowGameCommunity(Android::Util::GetJNIEnv(), mJavaObject);
}

void TWPurchaseAdapter::Consume(const std::string& i_payCode, const std::string& i_orderNumber)
{
	__android_log_print(ANDROID_LOG_VERBOSE, "TWPurchase", "Consume( %s, %s )", i_payCode.c_str(), i_orderNumber.c_str());
	JNIEnv* env = Android::Util::GetJNIEnv();
	jstring jPayCode = env->NewStringUTF(i_payCode.c_str());
	jstring jOrderNumber = env->NewStringUTF(i_orderNumber.c_str());
	JavaConsume(env, mJavaObject, jPayCode, jOrderNumber);
	env->DeleteLocalRef(jPayCode);
	env->DeleteLocalRef(jOrderNumber);
}

void TWPurchaseAdapter::QueryOrder(const std::string& productId)
{
	__android_log_print(ANDROID_LOG_VERBOSE, "TWPurchase", "QueryOrder( %s )", productId.c_str());
	ProductInfo info = GetProductInfo(productId);
	JNIEnv* env = Android::Util::GetJNIEnv();
	jstring jProductCode = env->NewStringUTF(info.productCode.c_str());
	JavaQueryOrder(env, mJavaObject, jProductCode);
	env->DeleteLocalRef(jProductCode);
}

void TWPurchaseAdapter::CheckSpecialRedeem()
{
	__android_log_print(ANDROID_LOG_VERBOSE, "TWPurchase", "CheckSpecialRedeem!!!");
	JavaCheckSpecialRedeem(Android::Util::GetJNIEnv(), mJavaObject);
}

void TWPurchaseAdapter::CheckGameCenterStatus()
{
	JavaCheckGameCenterStatus(Android::Util::GetJNIEnv(), mJavaObject);
}

/////////////// Hooks ///////////////

void TWPurchaseAdapter::ExitGameHook(JNIEnv* env, jobject javaObject, jlong nativeObject)
{
	__android_log_print(ANDROID_LOG_VERBOSE, "TWPurchase", "ExitGameHook");
	gLawnApp->onConfirmExitGame();
}

void TWPurchaseAdapter::CallCertificationHook(JNIEnv* env, jobject javaObject, unsigned char i_authed, unsigned char i_illegal)
{
	AuthMgr::GetInstance().SetAuthInfo(i_authed != 0, i_illegal != 0);
}

void TWPurchaseAdapter::CheckSpecialRedeemHook(JNIEnv* env, jobject javaObject, unsigned char i_success)
{
	gMessageRouter->Post(Message::CheckRedeemFinished, i_success);
}

void TWPurchaseAdapter::CheckGameCenterStatusHook(JNIEnv* env, jobject javaObject, unsigned char i_success)
{
	gMessageRouter->Post(Message::CheckGameCenterFinished, i_success);
}

/////////////// Java ///////////////

void TWPurchaseAdapter::BindJavaMethods(JNIEnv* env, const JavaClass& javaClass)
{
	JavaInitializeSDK.init(env, javaClass, "InitializeSDK", "(Ljava/lang/String;)V");
	JavaRequestPay.init(env, javaClass, "RequestPay", "(Ljava/lang/String;Ljava/lang/String;)V");
	JavaQueryOrder.init(env, javaClass, "QueryOrder", "(Ljava/lang/String;)V");
	JavaOnExit.init(env, javaClass, "OnExit", "()V");
	JavaGetDeclare.init(env, javaClass, "GetDeclare", "()Ljava/lang/String;");
	JavaRequestValidationPay.init(env, javaClass, "RequestValidationPay", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
	JavaNeedPurchaseWhite.init(env, javaClass, "NeedPurchaseWhite", "()Z");
	JavaNeedShowChannelActivity.init(env, javaClass, "NeedShowChannelActivity", "()Z");
	JavaGetChannelID.init(env, javaClass, "GetChannelID", "()Ljava/lang/String;");
	JavaGetUniqueID.init(env, javaClass, "GetUniqueID", "()Ljava/lang/String;");
	JavaGetUniqueCharacterID.init(env, javaClass, "GetUniqueCharacterID", "()Ljava/lang/String;");
	JavaGetChannelUpdateUrl.init(env, javaClass, "GetChannelUpdateUrl", "()Ljava/lang/String;");
	JavaGetTWRequestHead.init(env, javaClass, "GetTWRequestHead", "()Ljava/lang/String;");
	JavaGetDeviceID.init(env, javaClass, "GetDeviceID", "()Ljava/lang/String;");
	JavaGetSignature.init(env, javaClass, "GetSignature", "()Ljava/lang/String;");
	JavaCheckRedeemOrders.init(env, javaClass, "CheckRedeemOrders", "()V");
	JavaGetRedeemOrders.init(env, javaClass, "GetRedeemOrders", "(Ljava/util/ArrayList;Ljava/util/ArrayList;Ljava/util/ArrayList;)I");
	JavaSetIDs.init(env, javaClass, "SetIDs", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
	JavaShowGameCommunity.init(env, javaClass, "ShowGameCommunity", "()V");
	JavaConsume.init(env, javaClass, "Consume", "(Ljava/lang/String;Ljava/lang/String;)V");
	JavaCheckSpecialRedeem.init(env, javaClass, "CheckSpecialRedeem", "()V");
	JavaCheckGameCenterStatus.init(env, javaClass, "CheckGameCenterStatus", "()V");
	JavaGetGameCenterUrl.init(env, javaClass, "GetGameCenterUrl", "()Ljava/lang/String;");
}

void TWPurchaseAdapter::BindNativeMethods(JNIEnv* env, const JavaClass& javaClass)
{
	JNINativeMethod methods[] =
	{
		{ "FirePaymentComplete", "(JILjava/lang/String;Ljava/lang/String;)V", (void*)PaymentHook },
		{ "FireValidationPaymentComplete", "(JILjava/lang/String;Ljava/lang/String;Ljava/lang/String;Z)V", (void*)ValidationPaymentHook },
		{ "Native_ExitGame", "(J)V", (void*)ExitGameHook },
		{ "Native_SDKInitStart", "(J)V", (void*)SDKInitStartHook },
		{ "Native_SDKInitEnd", "(JI)V", (void*)SDKInitEndHook },
		{ "Native_SDKLoginStart", "(J)V", (void*)SDKLoginStartHook },
		{ "Native_SDKLoginEnd", "(JILjava/lang/String;)V", (void*)SDKLoginEndHook },
		{ "Native_SDKQueryOrder", "(Ljava/lang/String;I)V", (void*)SDKQueryOrderHook },
		{ "Native_CallCertification", "(ZZ)V", (void*)CallCertificationHook },
		{ "Native_CheckSpecialRedeem", "(Z)V", (void*)CheckSpecialRedeemHook },
		{ "Native_CheckGameCenterStatus", "(Z)V", (void*)CheckGameCenterStatusHook },
		{ "Native_GetGameCenterUrl", "(Ljava/lang/String;)V", (void*)GetGameCenterUrlHook },
	};

	javaClass.registerNatives(methods, 12);
}

void TWPurchaseAdapter::SDKInitStartHook(JNIEnv* env, jobject javaObject, jlong nativeObject)
{
	__android_log_print(ANDROID_LOG_VERBOSE, "TWPurchase", "SDKInitStartHook");
	gMessageRouter->Post(Message::AndroidSDKInit, 0, 0);
}

void TWPurchaseAdapter::SDKLoginStartHook(JNIEnv* env, jobject javaObject, jlong nativeObject)
{
	__android_log_print(ANDROID_LOG_VERBOSE, "TWPurchase", "SDKLoginStartHook");
	TGAAppLaunch launch;
	launch._step = "4";
	TGALogMgr::GetInstance().LogAppLaunch(launch);
	gMessageRouter->Post(Message::AndroidSDKLogin, 0, 0);
}

void TWPurchaseAdapter::SDKInitEndHook(JNIEnv* env, jobject javaObject, jlong nativeObject, jint resultCode)
{
	__android_log_print(ANDROID_LOG_VERBOSE, "TWPurchase", "SDKInitEndHook");
	if (resultCode == 1)
		AuthMgr::GetInstance().SetNoAuth(true);
	TGAAppLaunch launch;
	launch._step = "3";
	TGALogMgr::GetInstance().LogAppLaunch(launch);
	gMessageRouter->Post(Message::AndroidSDKInit, 1, resultCode);
}

void TWPurchaseAdapter::SDKLoginEndHook(JNIEnv* env, jobject javaObject, jlong nativeObject, jint resultCode, jstring jToken)
{
	__android_log_print(ANDROID_LOG_VERBOSE, "TWPurchase", "SDKLoginEndHook");
	TGAAppLaunch launch;
	launch._step = "5";
	TGALogMgr::GetInstance().LogAppLaunch(launch);
	gMessageRouter->Post(Message::AndroidSDKLogin, 1, resultCode);
	gLawnApp->SetLoginSuccess(resultCode == 0);
	std::string token;
	Android::Util::StringFromJString(env, token, jToken);
	AuthMgr::GetInstance().SetToken(token);
}

void TWPurchaseAdapter::SDKQueryOrderHook(JNIEnv* env, jobject javaObject, jstring jOrderId, jint resultCode)
{
	__android_log_print(ANDROID_LOG_VERBOSE, "TWPurchase", "SDKQueryOrderHook");
	std::string orderId;
	Android::Util::StringFromJString(env, orderId, jOrderId);
	gMessageRouter->Post(Message::AndroidSDKQueryOrder, orderId, resultCode);
}

void TWPurchaseAdapter::GetGameCenterUrlHook(JNIEnv* env, jobject javaObject, jstring jUrl)
{
	std::string url;
	Android::Util::StringFromJString(env, url, jUrl);
	__android_log_print(ANDROID_LOG_VERBOSE, "TWPurchase", "GetGameCenterUrl( %s )", url.c_str());
	gMessageRouter->Post(Message::GetGameCenterUrlFinished, url);
}

void TWPurchaseAdapter::SetIDsInTwSDK(bool i_enabled)
{
	if (i_enabled)
	{
		JNIEnv* env = Android::Util::GetJNIEnv();
		jstring jDefineId = env->NewStringUTF(DefineIDMgr::GetInstance().GetNewUserDefineID().c_str());
		jstring jUserId = env->NewStringUTF(NetworkMgr::Instance()->GetNewNetWorkProcess()->INetworkMsgProcess::GetPlayUserId().c_str());
		jstring jUUID = env->NewStringUTF(IdentifierMgr::GetInstance().GetUUID().c_str());
		JavaSetIDs(env, mJavaObject, jDefineId, jUserId, jUUID);
		env->DeleteLocalRef(jDefineId);
		env->DeleteLocalRef(jUserId);
		env->DeleteLocalRef(jUUID);
	}
}

/////////////// Purchase ///////////////

void TWPurchaseAdapter::Initialize()
{
	IPurchaseAdapter::Initialize();
	__android_log_print(ANDROID_LOG_VERBOSE, "TWPurchase", "Initialize");
	JNIEnv* env = Android::Util::GetJNIEnv();
	std::string channelId = "";
	if (gLawnApp->IsPlatformHD())
		channelId = "109";
	else
		channelId = "108";
	jstring jChannelId = env->NewStringUTF(channelId.c_str());
	JavaInitializeSDK(env, mJavaObject, jChannelId);
	TGAAppLaunch launch;
	launch._step = "2";
	TGALogMgr::GetInstance().LogAppLaunch(launch);
	gMessageRouter->Subscribe(&Message::LoginiCloudServerFinish, Sexy::MakeDelegate(*this, &TWPurchaseAdapter::SetIDsInTwSDK));
}

std::string TWPurchaseAdapter::GetSkuFromPayCode(const std::string& i_payCode)
{
	if (gLawnApp->IsPlatformHD())
	{
		if (i_payCode == "40010907")
			return "planttrial_special";
		std::map<std::string, std::string>::iterator it = PayCodeMapHD.begin();
		while (it != PayCodeMapHD.end())
		{
			if (it->second == i_payCode)
				return it->first;
			++it;
		}
	}
	else
	{
		if (i_payCode == "40010807")
			return "planttrial_special";
		std::map<std::string, std::string>::iterator it = PayCodeMap.begin();
		while (it != PayCodeMap.end())
		{
			if (it->second == i_payCode)
				return it->first;
			++it;
		}
	}
	return "";
}

int TWPurchaseAdapter::GetRedeemOrders(std::map<std::string, RedeemInfo>& validOrders)
{
	JNIEnv* env = Android::Util::GetJNIEnv();
	jclass listClass = env->FindClass("java/util/ArrayList");
	jmethodID listCtor = env->GetMethodID(listClass, "<init>", "()V");
	jobject keyList = env->NewObject(listClass, listCtor, "");
	jobject payCodeList = env->NewObject(listClass, listCtor, "");
	jobject orderNumberList = env->NewObject(listClass, listCtor, "");
	int count = JavaGetRedeemOrders(env, mJavaObject, keyList, payCodeList, orderNumberList);
	if (count > 0)
	{
		jmethodID listGet = env->GetMethodID(listClass, "get", "(I)Ljava/lang/Object;");
		for (int i = 0; i < count; i++)
		{
			jstring jKey = (jstring)env->CallObjectMethod(keyList, listGet, i);
			jstring jPayCode = (jstring)env->CallObjectMethod(payCodeList, listGet, i);
			jstring jOrderNumber = (jstring)env->CallObjectMethod(orderNumberList, listGet, i);
			std::string key;
			std::string payCode;
			std::string orderNumber;
			Android::Util::StringFromJString(env, key, jKey);
			Android::Util::StringFromJString(env, payCode, jPayCode);
			Android::Util::StringFromJString(env, orderNumber, jOrderNumber);
			PaymentResultInfo info;
			info.payCode = payCode;
			gLawnApp->SetPaymentResultInfo(info);
			RedeemInfo redeemInfo;
			redeemInfo.payCode = GetSkuFromPayCode(payCode);
			redeemInfo.orderNumber = orderNumber;
			validOrders.insert(std::make_pair(key, redeemInfo));
			env->DeleteLocalRef(jKey);
			env->DeleteLocalRef(jPayCode);
			env->DeleteLocalRef(jOrderNumber);
		}
	}
	return count;
}

void TWPurchaseAdapter::RequestPay(const std::string& productId, const std::string& orderNumber)
{
	IPurchaseAdapter::RequestPay(productId, orderNumber);
	__android_log_print(ANDROID_LOG_VERBOSE, "TWPurchase", "RequestPay( %s )", productId.c_str());
	ProductInfo info = GetProductInfo(productId);
	m_payCode = info.productCode;
	TGALogMgr::GetInstance().LogSegments(10025, 0, m_payCode);
	JNIEnv* env = Android::Util::GetJNIEnv();
	jstring jProductCode = env->NewStringUTF(info.productCode.c_str());
	jstring jOrderNumber = env->NewStringUTF(orderNumber.c_str());
	JavaRequestPay(env, mJavaObject, jProductCode, jOrderNumber);
	env->DeleteLocalRef(jProductCode);
	env->DeleteLocalRef(jOrderNumber);
}

void TWPurchaseAdapter::RequestValidationPayment(const std::string& productId, const std::string& i_orderId, const std::string& i_userId)
{
	IPurchaseAdapter::RequestPay(productId, i_orderId);
	std::string orderKey = productId + "_" + i_userId;
	__android_log_print(ANDROID_LOG_VERBOSE, "TWPurchase", "RequestValidationPay( %s )", productId.c_str());
	ProductInfo info = GetProductInfo(productId);
	JNIEnv* env = Android::Util::GetJNIEnv();
	jstring jProductCode = env->NewStringUTF(info.productCode.c_str());
	jstring jOrderId = env->NewStringUTF(i_orderId.c_str());
	jstring jOrderKey = env->NewStringUTF(orderKey.c_str());
	JavaRequestValidationPay(env, mJavaObject, jProductCode, jOrderId, jOrderKey);
	env->DeleteLocalRef(jProductCode);
	env->DeleteLocalRef(jOrderId);
	env->DeleteLocalRef(jOrderKey);
}

/////////////// Payment hooks ///////////////

void TWPurchaseAdapter::PaymentHook(JNIEnv* env, jobject javaObject, jlong nativeObject, jint resultCode, jstring jOrderId, jstring jPayType)
{
	__android_log_print(ANDROID_LOG_VERBOSE, "TWPurchase", "PaymentHook( %d )", resultCode);
	std::string orderId;
	Android::Util::StringFromJString(env, orderId, jOrderId);
	std::string payType;
	Android::Util::StringFromJString(env, payType, jPayType);
	__android_log_print(ANDROID_LOG_VERBOSE, "TWPurchase", "PayOrderId: %s, PayTypeId: %s", orderId.c_str(), payType.c_str());

	std::stringstream stream;
	stream << resultCode;
	PaymentResultInfo info;
	info.resultCode = stream.str();
	info.orderId = orderId;
	info.payType = payType;
	info.payCode = m_payCode;
	gLawnApp->SetPaymentResultInfo(info);

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

void TWPurchaseAdapter::ValidationPaymentHook(JNIEnv* env, jobject javaObject, jlong nativeObject, jint resultCode, jstring jOrderId, jstring jPayType, jstring jChannelId, unsigned char i_isOnlinePay)
{
	std::string orderId;
	Android::Util::StringFromJString(env, orderId, jOrderId);
	std::string payType;
	Android::Util::StringFromJString(env, payType, jPayType);
	std::string channelId;
	Android::Util::StringFromJString(env, channelId, jChannelId);

	std::stringstream stream;
	stream << resultCode;
	PaymentResultInfo info;
	info.resultCode = stream.str();
	info.orderId = orderId;
	info.payType = payType;
	gLawnApp->SetPaymentResultInfo(info);
	PurchaseMgr::GetInstance().SetOrderId(orderId);
	PurchaseMgr::GetInstance().SetChannelId(channelId);
	PurchaseMgr::GetInstance().SetIsOnlinePay(i_isOnlinePay != 0);

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

