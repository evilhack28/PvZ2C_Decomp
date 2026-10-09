//
//  Debug.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "SexyAppFramework/Common.h"

#include "drivers/app/android/JavaInterface.h"

namespace Android
{
	namespace DEBUG
	{
		struct Globals { char pad[0x70]; jmethodID mPauseInJava; };
		static Globals* volatile sGlobals;
	}
}

/////////////// Android::DEBUG ///////////////

bool Android::DEBUG::Register(JNIEnv* InEnv, jclass InGameClass)
{
	Globals* aGlobals = sGlobals;
	aGlobals->mPauseInJava = InEnv->GetMethodID(InGameClass, "DEBUG_PauseInJava", "(Ljava/lang/String;I)V");
	return aGlobals->mPauseInJava != NULL;
}

void Android::DEBUG::PauseInJava(char const* InFileName, int InLineNo)
{
	JNIEnv* env = Android::Util::GetJNIEnv();
	if (env)
	{
		jstring fileName = env->NewStringUTF(InFileName);
		jobject gameObject = Android::Util::GetGameObject(env);
		env->CallVoidMethod(gameObject, sGlobals->mPauseInJava, fileName, InLineNo);
		env->DeleteLocalRef(fileName);
	}
}
