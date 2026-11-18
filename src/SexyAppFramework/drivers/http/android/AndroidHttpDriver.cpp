//
//  AndroidHttpDriver.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-18.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/drivers/http/android/AndroidHttpDriver.h"
#include "SexyAppFramework/drivers/http/android/AndroidHttpTransaction.h"

#include <android/log.h>

using namespace Sexy;

JavaMethod<jint> AndroidHttpDriver::JavaGetNetworkStatus;

/////////////// Lifecycle ///////////////

AndroidHttpDriver::AndroidHttpDriver()
	: mNetworkStatus(NET_REACHABILITY_UNKNOWN)
{
	JNIEnv* env = Android::Util::GetJNIEnv();
	AttachJava(env, "com/popcap/SexyAppFramework/AndroidHttpProxy", Android::Util::GetHttpObject(env));
	GetNetworkStatus();
}

AndroidHttpDriver::~AndroidHttpDriver()
{
}

void AndroidHttpDriver::Update()
{
	HttpTransactions transactions = mHttpTransactions;
	for (HttpTransactions::iterator it = transactions.begin(); it != transactions.end(); ++it)
		(*it)->Update();
}

/////////////// Transactions ///////////////

IHttpTransaction* AndroidHttpDriver::CreateHttpTransaction(const std::string& method, const std::string& url, uint32 responseBufferSize)
{
	__android_log_print(ANDROID_LOG_INFO, "AndroidHttpDriver", "CreateHttpTransaction( \"%s\", \"%s\" )", method.c_str(), url.c_str());
	return new AndroidHttpTransaction(method, url, responseBufferSize);
}

/////////////// Network status ///////////////

IHttpDriver::NetworkStatus AndroidHttpDriver::GetNetworkStatus()
{
	mNetworkStatus = (NetworkStatus)JavaGetNetworkStatus(Android::Util::GetJNIEnv(), mJavaObject);
	return mNetworkStatus;
}

void AndroidHttpDriver::AddNetworkStatusListener(INetworkStatusListener* listener)
{
	mNetworkStatusListeners.insert(listener);
	listener->NetworkStatusChanged(mNetworkStatus);
}

void AndroidHttpDriver::RemoveNetworkStatusListener(INetworkStatusListener* listener)
{
	mNetworkStatusListeners.erase(listener);
}

/////////////// Java ///////////////

void AndroidHttpDriver::BindJavaMethods(JNIEnv* env, const JavaClass& javaClass)
{
	JavaGetNetworkStatus.init(env, javaClass, "GetNetworkStatus", "()I");
}
