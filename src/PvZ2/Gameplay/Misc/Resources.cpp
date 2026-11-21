//
//  Resources.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-21.
//

#include "SexyAppFramework/Common.h"

#include "drivers/app/android/JavaInterface.h"

struct JavaResourcesMethods
{
	char pad[0x178];
	jmethodID mGetResourceFolder;
	jmethodID mGetUserDataFolder;
	jmethodID mGetCacheDataFolder;
	jmethodID mGetAppSupportDataFolder;
	jmethodID mGetAssetFileSize;
	jmethodID mGetAssetFileInfo;
	jmethodID mInstallApk;
	jmethodID mGetFileSystemBlockCount;
	jmethodID mGetFileSystemBlocksFree;
	jmethodID mGetFileSystemBlockSize;
	jmethodID mGetExternalStorageDirectory;
	jmethodID mGetExternalFilesDirectory;
};

extern JavaVM* g_JavaVM;

static JavaResourcesMethods* volatile gJavaResources;

namespace Android
{
	namespace Resources
	{
		/////////////// Accessors ///////////////

		long GetFileSystemBlockCount(const std::string& pathInFS)
		{
			JNIEnv* env = Util::GetJNIEnv();
			if (env)
			{
				jstring path = env->NewStringUTF(pathInFS.c_str());
				long aResult = env->CallLongMethod(Util::GetGameObject(env), gJavaResources->mGetFileSystemBlockCount, path);
				env->DeleteLocalRef(path);
				return aResult;
			}
			return -1;
		}

		long GetFileSystemBlocksFree(const std::string& pathInFS)
		{
			JNIEnv* env = Util::GetJNIEnv();
			if (env)
			{
				jstring path = env->NewStringUTF(pathInFS.c_str());
				long aResult = env->CallLongMethod(Util::GetGameObject(env), gJavaResources->mGetFileSystemBlocksFree, path);
				env->DeleteLocalRef(path);
				return aResult;
			}
			return -1;
		}

		long GetFileSystemBlockSize(const std::string& pathInFS)
		{
			JNIEnv* env = Util::GetJNIEnv();
			if (env)
			{
				jstring path = env->NewStringUTF(pathInFS.c_str());
				long aResult = env->CallLongMethod(Util::GetGameObject(env), gJavaResources->mGetFileSystemBlockSize, path);
				env->DeleteLocalRef(path);
				return aResult;
			}
			return -1;
		}

		bool InstallApk(const std::string& i_filePath)
		{
			JNIEnv* env = Util::GetJNIEnv();
			if (env)
			{
				jstring path = env->NewStringUTF(i_filePath.c_str());
				return env->CallBooleanMethod(Util::GetGameObject(env), gJavaResources->mInstallApk, path);
			}
			return false;
		}

		long GetAssetFileSize(const std::string& InFilename)
		{
			JNIEnv* env = Util::GetJNIEnv();
			if (!env)
			{
				g_JavaVM->AttachCurrentThread(&env, NULL);
				if (!env)
					return -1;
			}
			jstring name = env->NewStringUTF(InFilename.c_str());
			long aSize = env->CallLongMethod(Util::GetGameObject(env), gJavaResources->mGetAssetFileSize, name);
			env->DeleteLocalRef(name);
			return aSize;
		}
	}
}
