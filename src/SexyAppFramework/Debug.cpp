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
		static jmethodID s_PauseInJavaMethodID;
	}
}

/////////////// Android::DEBUG ///////////////

bool Android::DEBUG::Register(JNIEnv* InEnv, jclass InGameClass)
{
	s_PauseInJavaMethodID = InEnv->GetMethodID(InGameClass, "DEBUG_PauseInJava", "(Ljava/lang/String;I)V");
	return s_PauseInJavaMethodID != NULL;
}

void Android::DEBUG::PauseInJava(char const* InFileName, int InLineNo)
{
	JNIEnv* env = Android::Util::GetJNIEnv();
	if (env)
	{
		jstring fileName = env->NewStringUTF(InFileName);
		jobject gameObject = Android::Util::GetGameObject(env);
		env->CallVoidMethod(gameObject, s_PauseInJavaMethodID, fileName, InLineNo);
		env->DeleteLocalRef(fileName);
	}
}
