//
//  JavaMethodBase.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include "SexyAppFramework/drivers/app/android/JavaBound.h"

/////////////// Accessors ///////////////

bool JavaMethodBase::valid()
{
	return mID != NULL;
}

/////////////// Lifecycle ///////////////

bool JavaMethodBase::init(JNIEnv* env, const JavaClass& javaClass, const char* name, const char* signature)
{
	mEnv = env;
	if (javaClass)
	{
		mID = env->GetMethodID(javaClass, name, signature);
		JavaException::CheckAndClear(env);
		mDebugName = javaClass.name();
		mDebugName += ".";
		mDebugName += name;
		mDebugName += signature;
	}
	return mID != NULL;
}
