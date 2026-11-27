//
//  JavaClass.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include "SexyAppFramework/drivers/app/android/JavaBound.h"

/////////////// Lifecycle ///////////////

bool JavaClass::init(JNIEnv* env, const char* javaClassName)
{
	mEnv = env;
	jclass aClass = env->FindClass(javaClassName);
	if (aClass)
	{
		jclass aGlobalClass = (jclass)env->NewGlobalRef(aClass);
		env->DeleteLocalRef(aClass);
		mClass = aGlobalClass;
		mDebugName = javaClassName;
		return true;
	}
	JavaException::CheckAndClear(env);
	return false;
}

/////////////// Accessors ///////////////

bool JavaClass::valid() const
{
	return mClass != NULL;
}
