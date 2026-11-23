//
//  JavaBase.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-22.
//

#include "SexyAppFramework/Common.h"

#include "SexyAppFramework/drivers/app/android/JavaBound.h"
#include "SexyAppFramework/drivers/app/android/JavaInterface.h"

/////////////// Lifecycle ///////////////

JavaBase::JavaBase()
	: mJavaObject(NULL)
{
}

JavaBase::~JavaBase()
{
	if (mJavaObject)
		Android::Util::GetJNIEnv()->DeleteGlobalRef(mJavaObject);
}

/////////////// Java binding ///////////////

void JavaBase::InitJava(JNIEnv* env, JavaClass& javaClass, const char* javaClassName)
{
	if (javaClass.valid())
		return;
	javaClass.init(env, javaClassName);
	if (javaClass.valid())
	{
		BindJavaMethods(env, javaClass);
		BindNativeMethods(env, javaClass);
	}
}

void JavaBase::BindJavaMethods(JNIEnv* env, const JavaClass& javaClass)
{
}

void JavaBase::BindNativeMethods(JNIEnv* env, const JavaClass& javaClass)
{
}

void JavaBase::ConstructJavaObject(JNIEnv* env, const JavaClass& javaClass, const JavaMethodBase& ctor, va_list args)
{
	__android_log_print(ANDROID_LOG_INFO, "JavaBase", "New %s", ctor.name().c_str());
	jobject localRef = env->NewObjectV(javaClass, ctor, args);
	if (localRef)
	{
		jobject globalRef = env->NewGlobalRef(localRef);
		env->DeleteLocalRef(localRef);
		if (mJavaObject)
		{
			__android_log_print(ANDROID_LOG_WARN, "JavaBase", "mJavaObject already defined what are you doing!");
			env->DeleteGlobalRef(mJavaObject);
		}
		mJavaObject = globalRef;
		__android_log_print(ANDROID_LOG_INFO, "JavaBase", "mJavaObject <- %p", globalRef);
	}
	JavaException::CheckAndClear(env);
}

void JavaBase::AttachJavaObject(JNIEnv* env, jobject localObjectRef)
{
	if (localObjectRef)
	{
		jobject globalRef = env->NewGlobalRef(localObjectRef);
		if (mJavaObject)
		{
			__android_log_print(ANDROID_LOG_WARN, "JavaBase", "mJavaObject already defined what are you doing!");
			env->DeleteGlobalRef(mJavaObject);
		}
		mJavaObject = globalRef;
		__android_log_print(ANDROID_LOG_INFO, "JavaBase", "mJavaObject:%p <- AttachJavaObject( localObjectRef:%p )", globalRef, localObjectRef);
	}
}
