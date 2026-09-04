//
//  AndroidShareDriverMgr.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-04.
//

#include "SexyAppFramework/Common.h"

#include <android/log.h>

#include "AndroidShareDriverMgr.h"
#include "SocialShareMgr.h"
#include "LawnApp.h"
#include "SexyAppFramework/DeviceImage.h"
#include "SexyAppFramework/IGraphicsDriver.h"
#include "SexyAppFramework/ImageLib/ImageLib.h"

JavaMethod<void> AndroidShareDriverMgr::JavaInitialize;
JavaMethod<void> AndroidShareDriverMgr::JavaDoShare;
JavaMethod<jboolean> AndroidShareDriverMgr::JavaIsClientInstalled;
JavaMethod<void> AndroidShareDriverMgr::JavaSaveImageToGallery;

/////////////// IShareDriver ///////////////

IShareDriver* IShareDriver::CreateShareDriver()
{
	return new AndroidShareDriverMgr();
}

/////////////// AndroidShareDriverMgr ///////////////

AndroidShareDriverMgr::AndroidShareDriverMgr()
{
	__android_log_print(ANDROID_LOG_INFO, "AndroidShareDriverMgr", "Let's get retarded!");

	ConstructJava(Android::Util::GetJNIEnv(), "com/popcap/SexyAppFramework/AndroidShareDriverManager", "(J)V", this);
}

AndroidShareDriverMgr::~AndroidShareDriverMgr()
{
}

bool AndroidShareDriverMgr::IsClientInstalled(SharePlatform i_platform)
{
	return true;
}

void AndroidShareDriverMgr::BindJavaMethods(JNIEnv* env, const JavaClass& javaClass)
{
	JavaInitialize.init(env, javaClass, "Initialize", "()V");
	JavaDoShare.init(env, javaClass, "DoShare", "(Ljava/lang/String;)V");
	JavaSaveImageToGallery.init(env, javaClass, "SaveImageToGallery", "(Ljava/lang/String;)V");
}

void AndroidShareDriverMgr::Initialize()
{
	__android_log_print(ANDROID_LOG_VERBOSE, "AndroidShareDriverMgr", "Initialize");

	JavaInitialize(Android::Util::GetJNIEnv(), mJavaObject);
}

void AndroidShareDriverMgr::BindNativeMethods(JNIEnv* env, const JavaClass& javaClass)
{
	JNINativeMethod methods[] =
	{
		{ "Native_ShareCallback", "(ILjava/lang/String;)V", (void*)ShareCallback },
		{ "Native_SaveCallback", "(I)V", (void*)SaveCallback },
	};

	javaClass.registerNatives(methods, 2);
}

void AndroidShareDriverMgr::SaveCallback(JNIEnv* env, jobject javaObject, jint result)
{
	__android_log_print(ANDROID_LOG_VERBOSE, "AndroidShareDriverMgr", "SaveCallback");

	SocialShareMgr::GetInstance().SaveCallback(result);
}

void AndroidShareDriverMgr::Share(SharePlatform i_platform, ScreenInfo i_info)
{
	__android_log_print(ANDROID_LOG_VERBOSE, "AndroidShareDriverMgr", "Share");

	JNIEnv* env = Android::Util::GetJNIEnv();
	jstring imagePath = env->NewStringUTF(i_info.ImagePath.c_str());
	JavaDoShare(env, mJavaObject, imagePath);
	env->DeleteLocalRef(imagePath);
}

void AndroidShareDriverMgr::SaveScreenImageToGallery(ScreenInfo i_info)
{
	__android_log_print(ANDROID_LOG_VERBOSE, "AndroidShareDriverMgr", "SaveScreenImageToGallery");

	JNIEnv* env = Android::Util::GetJNIEnv();
	jstring imagePath = env->NewStringUTF(i_info.ImagePath.c_str());
	JavaSaveImageToGallery(env, mJavaObject, imagePath);
	env->DeleteLocalRef(imagePath);
}

bool AndroidShareDriverMgr::DeleteLocalImage(ScreenInfo i_info)
{
	bool exist = gFileDriver->FileExists(i_info.ImagePath, NULL);
	if (exist)
	{
		gFileDriver->DeleteFile(i_info.ImagePath);
	}

	return exist;
}

void AndroidShareDriverMgr::ShareCallback(JNIEnv* env, jobject javaObject, jint result, jstring platform)
{
	__android_log_print(ANDROID_LOG_VERBOSE, "AndroidShareDriverMgr", "ShareCallback");

	std::string platformName;
	Android::Util::StringFromJString(env, platformName, platform);

	__android_log_print(ANDROID_LOG_VERBOSE, "AndroidShareDriverMgr", "Platform: %s", platformName.c_str());

	SocialShareMgr::GetInstance().ShareCallback(result, platformName);
}

void AndroidShareDriverMgr::SaveScreenImageToLocal(ScreenInfo i_info)
{
	DeviceImage* screenImage = gLawnApp->mGraphicsDriver->GetScreenImage();

	ImageLib::Image image;
	image.mBits = screenImage->GetBits(i_info.ScreenX, i_info.ScreenY, i_info.ScreenWidth, i_info.ScreenHeight);
	image.mWidth = i_info.ScreenWidth;
	image.mHeight = i_info.ScreenHeight;

	ImageLib::WritePNGImage(i_info.ImagePath.c_str(), &image, 0);

	screenImage->PurgeBits();
	image.mBits = NULL;
}
