//
//  util.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-04.
//

#include "SexyAppFramework/Common.h"

#include "SexyAppFramework/SexyAppBase.h"
#include "drivers/app/android/JavaInterface.h"

JavaVM* g_JavaVM;

namespace Android
{
	namespace Util
	{
		struct Globals
		{
			JavaVM* mJVM;
			void* pad;
			jobject mGame;
			jobject mGLView;
			jobject mHttp;
			jobject mFacebook;
			jobject mPackageManager;
			jmethodID mGetElapsedRealtime;
			jmethodID mStartPNS;
			jmethodID mOpenSystemSetting;
			jmethodID mNotifyDecompressStage;
			jmethodID mIsAutosmoking;
			jmethodID mGetUUIDString;
			jmethodID mGetPackageName;
		};
		Globals sGlobals __attribute__((weak));

		static JNIEnv* GetEnv(JavaVM* jvm)
		{
			JNIEnv* env;
			if (jvm)
				jvm->GetEnv((void**)&env, JNI_VERSION_1_6);
			return env;
		}

		static jobject GetGlobalRef(jobject* ref, JNIEnv* env)
		{
			if (env->IsSameObject(*ref, NULL))
				return NULL;
			return *ref;
		}

	}
}

/////////////// Android::Util ///////////////

JNIEnv* Android::Util::GetJNIEnv()
{
	if (&sGlobals)
		return GetEnv(sGlobals.mJVM);
	return NULL;
}

JavaVM* Android::Util::GetJVM()
{
	return ::g_JavaVM;
}

jobject Android::Util::GetGameObject(JNIEnv* pEnv)
{
	return GetGlobalRef(&sGlobals.mGame, pEnv);
}

jobject Android::Util::GetGLViewObject(JNIEnv* pEnv)
{
	return GetGlobalRef(&sGlobals.mGLView, pEnv);
}

jobject Android::Util::GetHttpObject(JNIEnv* pEnv)
{
	return GetGlobalRef(&sGlobals.mHttp, pEnv);
}

jobject Android::Util::GetFacebookObject(JNIEnv* pEnv)
{
	return GetGlobalRef(&sGlobals.mFacebook, pEnv);
}

jobject Android::Util::GetPackageManagerObject(JNIEnv* pEnv)
{
	return GetGlobalRef(&sGlobals.mPackageManager, pEnv);
}

bool Android::Util::Util_MonitorEnter(jobject o)
{
	JNIEnv* env = GetJNIEnv();
	return env && env->MonitorEnter(o) == 0;
}

bool Android::Util::Util_MonitorExit(jobject o)
{
	JNIEnv* env = GetJNIEnv();
	return env && env->MonitorExit(o) == 0;
}

long Android::Util::GetElapsedRealtime()
{
	JNIEnv* env = GetJNIEnv();
	if (env)
		return env->CallLongMethod(GetGameObject(env), sGlobals.mGetElapsedRealtime);
}

bool Android::Util::IsAutosmoking()
{
	JNIEnv* env = GetJNIEnv();
	return env && env->CallBooleanMethod(GetGameObject(env), sGlobals.mIsAutosmoking) != 0;
}

void Android::Util::UI_DeserializeBackButtonEvent(uint8_t*& cursor)
{
	cursor += 0x10;
}

void Android::Util::UI_DeserializeLongPressEvent(uint8_t*& cursor, Sexy::Point& pt)
{
	const int* p = (const int*)cursor;
	pt.mX = p[1];
	pt.mY = p[2];
	cursor += 0x10;
}

void Android::Util::UI_DeserializeFlickEvent(uint8_t*& cursor, Sexy::Point& pt, double& vx, double& vy)
{
	const uint8_t* p = cursor;
	pt.mX = *(const int*)(p + 4);
	pt.mY = *(const int*)(p + 8);
	vx = *(const double*)(p + 0xc);
	vy = *(const double*)(p + 0x14);
	cursor += 0x20;
}

void Android::Util::UI_DeserializePinchEvent(uint8_t*& cursor, Sexy::Point& pt, float& a, float& b)
{
	const uint8_t* p = cursor;
	pt.mX = *(const int*)(p + 4);
	pt.mY = *(const int*)(p + 8);
	a = *(const float*)(p + 0xc);
	b = *(const float*)(p + 0x10);
	cursor += 0x20;
}

bool Android::Util::UI_DeserializeTouchEvent(uint8_t*& cursor, Sexy::Touch& touch)
{
	touch.event = NULL;
	uint8_t* p = cursor;
	uint8_t* next = p + 0x30;
	touch.ident = *(const int*)(p + 4);
	touch.location.mX = *(const int*)(p + 8);
	touch.location.mY = *(const int*)(p + 0xc);
	touch.previousLocation.mX = *(const int*)(p + 0x10);
	touch.previousLocation.mY = *(const int*)(p + 0x14);
	touch.tapCount = *(const int*)(p + 0x18);
	touch.timestamp = *(const double*)(p + 0x1c);
	touch.phase = (Sexy::TouchPhase)*(const int*)(p + 0x24);
	cursor = next;
	return true;
}

bool Android::Util::UI_DeserializeKeyEvent(uint8_t*& cursor, AndroidKeyEvent& key)
{
	const uint8_t* p = cursor;
	key.mA = *(const int*)(p + 4);
	key.mB = *(const int*)(p + 8);
	key.mC = *(const int*)(p + 0xc);
	key.mE = *(const long long*)(p + 0x14);
	key.mF = *(const int*)(p + 0x18);
	cursor += 0x20;
	return true;
}

void Android::Util::StartPNS(int version)
{
	JNIEnv* env = GetJNIEnv();
	if (env)
		env->CallVoidMethod(GetGameObject(env), sGlobals.mStartPNS, version);
}

void Android::Util::OpenSystemSetting()
{
	JNIEnv* env = GetJNIEnv();
	if (env)
		env->CallVoidMethod(GetGameObject(env), sGlobals.mOpenSystemSetting);
}

void Android::Util::NotifyDecompressStage()
{
	JNIEnv* env = GetJNIEnv();
	if (env)
		env->CallVoidMethod(GetGameObject(env), sGlobals.mNotifyDecompressStage);
}

bool Android::Util::StringFromJString(JNIEnv* InEnv, std::string& outStr, jstring jsStr)
{
	bool ok = false;
	if (jsStr != NULL)
	{
		const char* chars = InEnv->GetStringUTFChars(jsStr, NULL);
		if (chars)
		{
			outStr.assign(chars);
			ok = true;
		}
		InEnv->ReleaseStringUTFChars(jsStr, chars);
	}
	return ok;
}

bool Android::Util::WStringFromJString(JNIEnv* InEnv, std::wstring& outStr, jstring jsStr)
{
	bool ok = false;
	if (jsStr != NULL)
	{
		jsize len = InEnv->GetStringLength(jsStr);
		const jchar* chars = InEnv->GetStringCritical(jsStr, NULL);
		if (chars)
		{
			outStr = std::wstring((const wchar_t*)chars, len);
			ok = true;
		}
		InEnv->ReleaseStringCritical(jsStr, chars);
	}
	return ok;
}

std::string Android::Util::GetUUIDString()
{
	std::string result("");
	JNIEnv* env = GetJNIEnv();
	if (env)
	{
		jstring js = (jstring)env->CallObjectMethod(GetGameObject(env), sGlobals.mGetUUIDString);
		if (js)
		{
			if (!StringFromJString(env, result, js))
				result = "";
			env->DeleteLocalRef(js);
		}
	}
	return result;
}

std::string Android::Util::GetPackageName()
{
	std::string result("");
	JNIEnv* env = GetJNIEnv();
	if (env)
	{
		jstring js = (jstring)env->CallObjectMethod(GetGameObject(env), sGlobals.mGetPackageName);
		if (js)
		{
			if (!StringFromJString(env, result, js))
				result = "";
			env->DeleteLocalRef(js);
		}
	}
	return result;
}

bool Android::Util::Register(JNIEnv* env, jclass cls)
{
	sGlobals.mGetUUIDString = env->GetMethodID(cls, "Util_GetUUIDString", "()Ljava/lang/String;");
	if (sGlobals.mGetUUIDString != 0)
	{
		sGlobals.mGetPackageName = env->GetMethodID(cls, "Util_GetPackageName", "()Ljava/lang/String;");
		if (sGlobals.mGetPackageName != 0)
		{
			sGlobals.mGetElapsedRealtime = env->GetMethodID(cls, "Util_GetElapsedRealtime", "()J");
			if (sGlobals.mGetElapsedRealtime != 0)
			{
				sGlobals.mStartPNS = env->GetMethodID(cls, "Util_StartPNS", "(I)V");
				if (sGlobals.mStartPNS != 0)
				{
					sGlobals.mOpenSystemSetting = env->GetMethodID(cls, "Util_OpenSystemSetting", "()V");
					if (sGlobals.mOpenSystemSetting != 0)
					{
						sGlobals.mNotifyDecompressStage = env->GetMethodID(cls, "Util_NotifyDecompressStage", "()V");
						if (sGlobals.mNotifyDecompressStage != 0)
						{
							sGlobals.mIsAutosmoking = env->GetMethodID(cls, "Util_IsAutosmoking", "()Z");
							return sGlobals.mIsAutosmoking != 0;
						}
					}
				}
			}
		}
	}
	return false;
}
