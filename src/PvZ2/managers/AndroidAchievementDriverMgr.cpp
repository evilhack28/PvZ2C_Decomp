//
//  AndroidAchievementDriverMgr.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-04.
//

#include "SexyAppFramework/Common.h"

#include <android/log.h>
#include <functional>

#include "AndroidAchievementDriverMgr.h"

JavaMethod<void> AndroidAchievementDriverMgr::JavaInitialize;
JavaMethod<void> AndroidAchievementDriverMgr::JavaDoSetAchievement;
JavaMethod<void> AndroidAchievementDriverMgr::JavaDoQueryAllAchievement;
std::function<void(bool)> AndroidAchievementDriverMgr::m_SetAchievementCallback;
std::function<void(std::vector<AchievementInfo>)> AndroidAchievementDriverMgr::m_QueryAllAchievementCallback;

/////////////// INewAchievementDriver ///////////////

INewAchievementDriver* INewAchievementDriver::CreateNewAchievementDriver()
{
	return new AndroidAchievementDriverMgr();
}

/////////////// AndroidAchievementDriverMgr ///////////////

AndroidAchievementDriverMgr::AndroidAchievementDriverMgr()
{
	__android_log_print(ANDROID_LOG_INFO, "AndroidAchievementDriverMgr", "Let's get retarded!");

	ConstructJava(Android::Util::GetJNIEnv(), "com/popcap/SexyAppFramework/AndroidAchievementDriverManager", "(J)V", this);
}

AndroidAchievementDriverMgr::~AndroidAchievementDriverMgr()
{
}

void AndroidAchievementDriverMgr::BindJavaMethods(JNIEnv* env, const JavaClass& javaClass)
{
	JavaInitialize.init(env, javaClass, "Initialize", "()V");
	JavaDoSetAchievement.init(env, javaClass, "DoSetAchievement", "(Ljava/lang/String;ID)V");
	JavaDoQueryAllAchievement.init(env, javaClass, "DoQueryAllAchievement", "()V");
}

void AndroidAchievementDriverMgr::BindNativeMethods(JNIEnv* env, const JavaClass& javaClass)
{
	JNINativeMethod methods[] =
	{
		{ "Native_SetAchievementCallback", "(I)V", (void*)SetAchievementCallback },
		{ "Native_QueryAllAchievementCallback", "(I)V", (void*)QueryAllAchievementCallback },
	};

	javaClass.registerNatives(methods, 2);
}

void AndroidAchievementDriverMgr::Initialize()
{
	__android_log_print(ANDROID_LOG_VERBOSE, "AndroidAchievementDriverMgr", "Initialize");

	JavaInitialize(Android::Util::GetJNIEnv(), mJavaObject);
}

void AndroidAchievementDriverMgr::QueryAllAchievementCallback(JNIEnv* env, jobject javaObject, jint result)
{
	__android_log_print(ANDROID_LOG_VERBOSE, "AndroidAchievementDriverMgr", "QueryAllAchievementCallback");
}

void AndroidAchievementDriverMgr::SetAchievementCallback(JNIEnv* env, jobject javaObject, jint result)
{
	__android_log_print(ANDROID_LOG_VERBOSE, "AndroidAchievementDriverMgr", "SetAchievementCallback");

	if (m_SetAchievementCallback)
	{
		m_SetAchievementCallback(result == 0);
	}
}

void AndroidAchievementDriverMgr::SetAchievement(const std::string& i_id, int i_type, double i_value, std::function<void(bool)> i_callback)
{
	__android_log_print(ANDROID_LOG_VERBOSE, "AndroidAchievementDriverMgr", "SetAchievement");

	JNIEnv* env = Android::Util::GetJNIEnv();
	jstring id = env->NewStringUTF(i_id.c_str());
	JavaDoSetAchievement(env, mJavaObject, id, i_type, i_value);
	env->DeleteLocalRef(id);

	m_SetAchievementCallback = i_callback;
}

void AndroidAchievementDriverMgr::QueryAllAchievement(std::function<void(std::vector<AchievementInfo>)> i_callback)
{
	__android_log_print(ANDROID_LOG_VERBOSE, "AndroidAchievementDriverMgr", "QueryAllAchievement");

	JavaDoQueryAllAchievement(Android::Util::GetJNIEnv(), mJavaObject);

	m_QueryAllAchievementCallback = i_callback;
}
