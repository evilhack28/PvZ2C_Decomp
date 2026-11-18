//
//  AndroidHttpTransaction.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-18.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/drivers/http/android/AndroidHttpTransaction.h"
#include "SexyAppFramework/drivers/app/android/AndroidAppDriver.h"

#include <android/log.h>

using namespace Sexy;

JavaMethod<void> AndroidHttpTransaction::JavaSetRequestHeader;
static IHttpListener sNullListener;
JavaMethod<void> AndroidHttpTransaction::JavaSetRequestBody;
JavaMethod<void> AndroidHttpTransaction::JavaSetTimeout;
JavaMethod<void> AndroidHttpTransaction::JavaStart;
JavaMethod<jint> AndroidHttpTransaction::JavaGetStatusCode;
JavaMethod<jstring> AndroidHttpTransaction::JavaGetStatusLine;
JavaMethod<jint> AndroidHttpTransaction::JavaGetResponseLength;
JavaMethod<jstring> AndroidHttpTransaction::JavaGetResponseHeader;
JavaMethod<void> AndroidHttpTransaction::JavaRelease;

/////////////// Lifecycle ///////////////

AndroidHttpTransaction::AndroidHttpTransaction(const std::string& method, const std::string& url, uint32 responseBufferSize)
	: mListener(&sNullListener)
{
	JNIEnv* env = Android::Util::GetJNIEnv();
	jstring jMethod = env->NewStringUTF(method.c_str());
	jstring jUrl = env->NewStringUTF(url.c_str());
	ConstructJava(env, "com/popcap/SexyAppFramework/AndroidHttpTransaction", "(JLjava/lang/String;Ljava/lang/String;)V", this, jMethod, jUrl);
	env->DeleteLocalRef(jMethod);
	env->DeleteLocalRef(jUrl);
}

AndroidHttpTransaction::~AndroidHttpTransaction()
{
}

void AndroidHttpTransaction::Release()
{
	JNIEnv* env = Android::Util::GetJNIEnv();
	mListener = &sNullListener;
	JavaRelease(env, mJavaObject);
}

/////////////// Request ///////////////

void AndroidHttpTransaction::SetRequestHeader(const std::string& name, const std::string& value)
{
	__android_log_print(ANDROID_LOG_INFO, "AndroidHttpTransaction", "SetRequestHeader( name:\"%s\", value:\"%s\" )", name.c_str(), value.c_str());

	JNIEnv* env = Android::Util::GetJNIEnv();
	jstring jName = env->NewStringUTF(name.c_str());
	jstring jValue = env->NewStringUTF(value.c_str());
	JavaSetRequestHeader(env, mJavaObject, jName, jValue);
	env->DeleteLocalRef(jName);
	env->DeleteLocalRef(jValue);
}

void AndroidHttpTransaction::SetRequestBody(const void* data, size_t length)
{
	__android_log_print(ANDROID_LOG_INFO, "AndroidHttpTransaction", "SetRequestBody( length:%ld )", length);

	JNIEnv* env = Android::Util::GetJNIEnv();
	jbyteArray array = env->NewByteArray(length);
	env->SetByteArrayRegion(array, 0, length, (const jbyte*)data);
	JavaSetRequestBody(env, mJavaObject, array);
	env->DeleteLocalRef(array);
}

void AndroidHttpTransaction::SetTimeout(int seconds)
{
	__android_log_print(ANDROID_LOG_INFO, "AndroidHttpTransaction", "SetTimeout( seconds:%d )", seconds);

	JavaSetTimeout(Android::Util::GetJNIEnv(), mJavaObject, seconds);
}

void AndroidHttpTransaction::Start()
{
	__android_log_print(ANDROID_LOG_INFO, "AndroidHttpTransaction", "Start()");

	JavaStart(Android::Util::GetJNIEnv(), mJavaObject);
}

/////////////// Response ///////////////

int AndroidHttpTransaction::GetStatusCode()
{
	__android_log_print(ANDROID_LOG_INFO, "AndroidHttpTransaction", "GetStatusCode");

	int statusCode = JavaGetStatusCode(Android::Util::GetJNIEnv(), mJavaObject);
	__android_log_print(ANDROID_LOG_INFO, "AndroidHttpTransaction", "<- statusCode:%d", statusCode);
	return statusCode;
}

std::string AndroidHttpTransaction::GetStatusLine()
{
	__android_log_print(ANDROID_LOG_INFO, "AndroidHttpTransaction", "GetStatusLine");

	JNIEnv* env = Android::Util::GetJNIEnv();
	jstring jStatusLine = JavaGetStatusLine(env, mJavaObject);
	std::string statusLine;
	Android::Util::StringFromJString(env, statusLine, jStatusLine);
	__android_log_print(ANDROID_LOG_INFO, "AndroidHttpTransaction", "<- statusLine:\"%s\"", statusLine.c_str());
	return statusLine;
}

int AndroidHttpTransaction::GetResponseLength()
{
	__android_log_print(ANDROID_LOG_INFO, "AndroidHttpTransaction", "GetResponseLength");

	int responseLength = JavaGetResponseLength(Android::Util::GetJNIEnv(), mJavaObject);
	__android_log_print(ANDROID_LOG_INFO, "AndroidHttpTransaction", "<- responseLength:%d", responseLength);
	return responseLength;
}

std::string AndroidHttpTransaction::GetResponseHeader(const std::string& key)
{
	JNIEnv* env = Android::Util::GetJNIEnv();
	env->PushLocalFrame(1);
	jstring jKey = env->NewStringUTF(key.c_str());
	jstring jValue = JavaGetResponseHeader(env, mJavaObject, jKey);
	std::string value;
	Android::Util::StringFromJString(env, value, jValue);
	env->PopLocalFrame(NULL);
	__android_log_print(ANDROID_LOG_INFO, "AndroidHttpTransaction", "<- responseHeader:\"%s\"", value.c_str());
	return value;
}

/////////////// Java ///////////////

void AndroidHttpTransaction::BindJavaMethods(JNIEnv* env, const JavaClass& javaClass)
{
	JavaSetRequestHeader.init(env, javaClass, "SetRequestHeader", "(Ljava/lang/String;Ljava/lang/String;)V");
	JavaSetRequestBody.init(env, javaClass, "SetRequestBody", "([B)V");
	JavaSetTimeout.init(env, javaClass, "SetTimeout", "(I)V");
	JavaStart.init(env, javaClass, "Start", "()V");
	JavaGetStatusCode.init(env, javaClass, "GetStatusCode", "()I");
	JavaGetStatusLine.init(env, javaClass, "GetStatusLine", "()Ljava/lang/String;");
	JavaGetResponseLength.init(env, javaClass, "GetResponseLength", "()I");
	JavaGetResponseHeader.init(env, javaClass, "GetResponseHeader", "(Ljava/lang/String;)Ljava/lang/String;");
	JavaRelease.init(env, javaClass, "Release", "()V");
}

void AndroidHttpTransaction::BindNativeMethods(JNIEnv* env, const JavaClass& javaClass)
{
	JNINativeMethod methods[] =
	{
		{ "HttpReceivedResponse", "(J)V", (void*)OnReceivedResponseHook },
		{ "HttpReceivedData", "(J[BI)V", (void*)OnReceivedDataHook },
		{ "HttpTransactionComplete", "(J)V", (void*)OnTransactionCompleteHook },
		{ "HttpTransactionError", "(J)V", (void*)OnTransactionErrorHook },
		{ "HttpTransactionCleanup", "(J)V", (void*)OnTransactionCleanupHook },
	};

	env->RegisterNatives(javaClass, methods, 5);
	JavaException::CheckAndClear(env);
}

void AndroidHttpTransaction::OnReceivedResponseHook(JNIEnv* env, jobject javaObject, jlong nativeTransaction)
{
	__android_log_print(ANDROID_LOG_INFO, "AndroidHttpTransaction", "OnReceivedResponseHook");

	AndroidHttpTransaction* transaction = (AndroidHttpTransaction*)nativeTransaction;
	AndroidAppDriver::StaticEnqueueCallback(Delegate0(MakeDelegate(*transaction, &AndroidHttpTransaction::OnReceivedResponse)));
}

void AndroidHttpTransaction::OnReceivedDataHook(JNIEnv* env, jobject javaObject, jlong nativeTransaction, jbyteArray data, jint dataSize)
{
	__android_log_print(ANDROID_LOG_INFO, "AndroidHttpTransaction", "OnReceivedDataHook( %d )", dataSize);

	if (JavaException::CheckAndClear(env))
		return;

	AndroidHttpTransaction* transaction = (AndroidHttpTransaction*)nativeTransaction;
	ReceivedDataCallback* callback = transaction->CreateReceivedDataCallback(dataSize);
	env->GetByteArrayRegion(data, 0, dataSize, (jbyte*)callback->data);
	if (JavaException::CheckAndClear(env))
		transaction->ReleaseReceivedDataCallback(callback);
	else
		AndroidAppDriver::StaticEnqueueCallback(*callback);
}

void AndroidHttpTransaction::OnTransactionCompleteHook(JNIEnv* env, jobject javaObject, jlong nativeTransaction)
{
	__android_log_print(ANDROID_LOG_INFO, "AndroidHttpTransaction", "OnTransactionCompleteHook");

	AndroidHttpTransaction* transaction = (AndroidHttpTransaction*)nativeTransaction;
	AndroidAppDriver::StaticEnqueueCallback(Delegate0(MakeDelegate(*transaction, &AndroidHttpTransaction::OnTransactionComplete)));
}

void AndroidHttpTransaction::OnTransactionErrorHook(JNIEnv* env, jobject javaObject, jlong nativeTransaction)
{
	__android_log_print(ANDROID_LOG_INFO, "AndroidHttpTransaction", "OnTransactionErrorHook");

	AndroidHttpTransaction* transaction = (AndroidHttpTransaction*)nativeTransaction;
	AndroidAppDriver::StaticEnqueueCallback(Delegate0(MakeDelegate(*transaction, &AndroidHttpTransaction::OnTransactionError)));
}

void AndroidHttpTransaction::OnTransactionCleanupHook(JNIEnv* env, jobject javaObject, jlong nativeTransaction)
{
	__android_log_print(ANDROID_LOG_INFO, "AndroidHttpTransaction", "OnTransactionCleanupHook");

	AndroidHttpTransaction* transaction = (AndroidHttpTransaction*)nativeTransaction;
	AndroidAppDriver::StaticEnqueueCallback(Delegate0(MakeDelegate(*transaction, &AndroidHttpTransaction::OnTransactionCleanup)));
}

/////////////// Callbacks ///////////////

AndroidHttpTransaction::ReceivedDataCallback* AndroidHttpTransaction::CreateReceivedDataCallback(size_t dataSize)
{
	ReceivedDataCallback* callback = new ReceivedDataCallback();
	callback->dataSize = dataSize;
	callback->data = new char[dataSize];
	callback->transaction = this;
	return callback;
}

void AndroidHttpTransaction::ReleaseReceivedDataCallback(ReceivedDataCallback* callback)
{
	delete[] callback->data;
	delete callback;
}

void AndroidHttpTransaction::OnReceivedResponse()
{
	mListener->HttpReceivedResponse(this);
}

void AndroidHttpTransaction::OnReceivedData(void* data, size_t dataSize)
{
	mListener->HttpReceivedData(this, data, dataSize);
}

void AndroidHttpTransaction::OnTransactionComplete()
{
	mListener->HttpTransactionComplete(this);
}

void AndroidHttpTransaction::OnTransactionError()
{
	mListener->HttpTransactionError(this);
}

void AndroidHttpTransaction::OnTransactionCleanup()
{
	delete this;
}

/////////////// Accessors ///////////////

void AndroidHttpTransaction::SetListener(IHttpListener* listener)
{
	mListener = listener;
}

void AndroidHttpTransaction::SetUserData(void* userData)
{
	mUserData = userData;
}

void* AndroidHttpTransaction::GetUserData()
{
	return mUserData;
}

void AndroidHttpTransaction::SetSlackCertificateValidation(bool slack)
{
}

void AndroidHttpTransaction::SetBasicAuth(const std::string& username, const std::string& password)
{
}

void AndroidHttpTransaction::Update()
{
}

std::string AndroidHttpTransaction::GetRequestUrl()
{
	return std::string();
}

std::string AndroidHttpTransaction::GetSerializedRequest()
{
	return "AndroidHttpTransaction::GetSerializedRequest not implemented";
}

std::string AndroidHttpTransaction::GetErrorMessage()
{
	return std::string();
}
