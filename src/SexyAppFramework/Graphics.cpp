//
//  Graphics.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-03.
//

#include "SexyAppFramework/Common.h"

#include "drivers/app/android/JavaInterface.h"
#include "drivers/app/android/AndroidAppDriver.h"

struct JavaGraphicsGlobals
{
	char pad0[0x18];
	char pad1[0x1c0];
	jmethodID mGetGLViewSysFBO;
	jmethodID mIsOpenGLES20;
	jmethodID mGetScreenSizeInPixels;
	jmethodID mGetScreenSizeInPoints;
	jmethodID mGetGLViewScaleFactor;
	jmethodID mSetGLViewScaleFactor;
	jmethodID mCanSetGLViewScaleFactor;
};

static bool gSurfaceCreated;
static Sexy::AndroidAppDriver* volatile gAndroidAppDriver;
static JavaGraphicsGlobals* volatile gJavaGraphics;

/////////////// Android::Graphics ///////////////

bool Android::Graphics::RegisterCallbacks(JNIEnv* InEnv, jclass InGraphicsClass)
{
	JNINativeMethod methods[] =
	{
		{ (char*)"Native_onSurfaceCreated", (char*)"()V", (void*)Native_onSurfaceCreated },
		{ (char*)"Native_onSurfaceChanged", (char*)"(II)V", (void*)Native_onSurfaceChanged },
		{ (char*)"Native_onDrawFrame", (char*)"()V", (void*)Native_onDrawFrame },
	};

	return InEnv->RegisterNatives(InGraphicsClass, methods, 3) == 0;
}

bool Android::Graphics::Register(JNIEnv* InEnv, jclass InGraphicsClass)
{
	JavaGraphicsGlobals* aGlobals;
	jmethodID aMethod;

	aGlobals = gJavaGraphics;
	aMethod = InEnv->GetMethodID(InGraphicsClass, "Graphics_GetGLViewSysFBO", "()I");
	aGlobals->mGetGLViewSysFBO = aMethod;
	if (aMethod != NULL)
	{
		aGlobals = gJavaGraphics;
		aMethod = InEnv->GetMethodID(InGraphicsClass, "Graphics_IsOpenGLES20", "()Z");
		aGlobals->mIsOpenGLES20 = aMethod;
		if (aMethod != NULL)
		{
			aGlobals = gJavaGraphics;
			aMethod = InEnv->GetMethodID(InGraphicsClass, "Graphics_GetScreenSizeInPixels", "([I)V");
			aGlobals->mGetScreenSizeInPixels = aMethod;
			if (aMethod != NULL)
			{
				aGlobals = gJavaGraphics;
				aMethod = InEnv->GetMethodID(InGraphicsClass, "Graphics_GetScreenSizeInPoints", "([I)V");
				aGlobals->mGetScreenSizeInPoints = aMethod;
				if (aMethod != NULL)
				{
					aGlobals = gJavaGraphics;
					aMethod = InEnv->GetMethodID(InGraphicsClass, "Graphics_GetGLViewScaleFactor", "()F");
					aGlobals->mGetGLViewScaleFactor = aMethod;
					if (aMethod != NULL)
					{
						aGlobals = gJavaGraphics;
						aMethod = InEnv->GetMethodID(InGraphicsClass, "Graphics_SetGLViewScaleFactor", "(F)V");
						aGlobals->mSetGLViewScaleFactor = aMethod;
						if (aMethod != NULL)
						{
							aGlobals = gJavaGraphics;
							aMethod = InEnv->GetMethodID(InGraphicsClass, "Graphics_CanSetGLViewScaleFactor", "()Z");
							aGlobals->mCanSetGLViewScaleFactor = aMethod;
								return aMethod != NULL;
						}
					}
				}
			}
		}
	}
	return false;
}

void Android::Graphics::Native_onSurfaceCreated(JNIEnv* env, jobject viewObj)
{
	Sexy::SexyAppBase* aApp = gAndroidAppDriver->mApp;
	aApp->SetMainThreadToCurrent();
	if (!gSurfaceCreated)
	{
		gAndroidAppDriver->GetProductVersionCode();
		gSurfaceCreated = true;
		aApp->Init();
		aApp->Start();
	}
	gAndroidAppDriver->HandleAndroidSurfaceCreated();
}

void Android::Graphics::Native_onSurfaceChanged(JNIEnv* env, jobject viewObj, jint InWidth, jint InHeight)
{
	gAndroidAppDriver->HandleAndroidSurfaceChange(InWidth, InHeight);
}

void Android::Graphics::Native_onDrawFrame(JNIEnv* env, jobject viewObj)
{
	gAndroidAppDriver->DisplayLinkUpdateAppStep();
}

void Android::Graphics::GetScreenSizeInPixels(Sexy::AndroidAppDriver* pDriver, int* outWidth, int* outHeight)
{
	JNIEnv* env = Android::Util::GetJNIEnv();
	if (env)
	{
		jintArray anArray = env->NewIntArray(2);
		env->CallVoidMethod(Android::Util::GetGLViewObject(env), gJavaGraphics->mGetScreenSizeInPixels, anArray);
		jint* aData = (jint*)env->GetPrimitiveArrayCritical(anArray, NULL);
		if (aData)
		{
			*outWidth = aData[0];
			*outHeight = aData[1];
		}
		else
		{
			*outWidth = -1;
			*outHeight = -1;
		}
		env->ReleasePrimitiveArrayCritical(anArray, aData, JNI_ABORT);
		env->DeleteLocalRef(anArray);
	}
}

void Android::Graphics::GetScreenSizeInPoints(int* pOutWidth, int* pOutHeight)
{
	JNIEnv* env = Android::Util::GetJNIEnv();
	if (env)
	{
		jintArray anArray = env->NewIntArray(2);
		env->CallVoidMethod(Android::Util::GetGLViewObject(env), gJavaGraphics->mGetScreenSizeInPoints, anArray);
		jint* aData = (jint*)env->GetPrimitiveArrayCritical(anArray, NULL);
		if (aData)
		{
			*pOutWidth = aData[0];
			*pOutHeight = aData[1];
		}
		else
		{
			*pOutWidth = -1;
			*pOutHeight = -1;
		}
		env->ReleasePrimitiveArrayCritical(anArray, aData, JNI_ABORT);
		env->DeleteLocalRef(anArray);
	}
}

void Android::Graphics::GetGLViewSize(Sexy::AndroidAppDriver* pDriver, int* outWidth, int* outHeight)
{
	GetScreenSizeInPoints(outWidth, outHeight);
	float aScale = GetGLViewScaleFactor(pDriver);
	if (aScale != 1.0f)
	{
		*outWidth = (int)(aScale * *outWidth);
		*outHeight = (int)(aScale * *outHeight);
	}
}

void Android::Graphics::SetGLViewContext(Sexy::AndroidAppDriver* pDriver)
{
}

bool Android::Graphics::IsOpenGLES20(Sexy::AndroidAppDriver* theAppDriver)
{
	JNIEnv* env = Android::Util::GetJNIEnv();
	if (env)
		return env->CallBooleanMethod(Android::Util::GetGLViewObject(env), gJavaGraphics->mIsOpenGLES20) != 0;
	return false;
}

bool Android::Graphics::CanSetGLViewScaleFactor(Sexy::AndroidAppDriver* theAppDriver)
{
	JNIEnv* env = Android::Util::GetJNIEnv();
	if (env)
		return env->CallBooleanMethod(Android::Util::GetGLViewObject(env), gJavaGraphics->mCanSetGLViewScaleFactor) != 0;
	return false;
}

void Android::Graphics::SetGLViewScaleFactor(Sexy::AndroidAppDriver* theAppDriver, float theScale)
{
	JNIEnv* env = Android::Util::GetJNIEnv();
	if (env)
		env->CallVoidMethod(Android::Util::GetGLViewObject(env), gJavaGraphics->mSetGLViewScaleFactor, theScale);
}

float Android::Graphics::GetGLViewScaleFactor(Sexy::AndroidAppDriver* theAppDriver)
{
	if (!CanSetGLViewScaleFactor(theAppDriver))
		return 1.0f;
	JNIEnv* env = Android::Util::GetJNIEnv();
	if (env)
		return env->CallFloatMethod(Android::Util::GetGLViewObject(env), gJavaGraphics->mGetGLViewScaleFactor);
	return 0.0f;
}

uint32 Android::Graphics::GetGLViewSysFBO(Sexy::AndroidAppDriver* theAppDriver)
{
	JNIEnv* env = Android::Util::GetJNIEnv();
	if (env)
		return env->CallIntMethod(Android::Util::GetGLViewObject(env), gJavaGraphics->mGetGLViewSysFBO);
	return 0;
}

void Android::Graphics::SetLoadingContext(Sexy::AndroidAppDriver* theAppDriver)
{
}
