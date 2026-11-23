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

		std::string GetUserDataFolder(Sexy::AndroidAppDriver*)
		{
			JNIEnv* env = Util::GetJNIEnv();
			if (!env)
				return "";
			jstring folder = (jstring)env->CallObjectMethod(Util::GetGameObject(env), gJavaResources->mGetUserDataFolder);
			std::string result;
			if (folder)
			{
				Util::StringFromJString(env, result, folder);
				env->DeleteLocalRef(folder);
			}
			return result;
		}

		std::string GetResourceFolder(Sexy::AndroidAppDriver*)
		{
			JNIEnv* env = Util::GetJNIEnv();
			if (!env)
				return "";
			jstring folder = (jstring)env->CallObjectMethod(Util::GetGameObject(env), gJavaResources->mGetResourceFolder);
			std::string result;
			if (folder)
			{
				Util::StringFromJString(env, result, folder);
				env->DeleteLocalRef(folder);
			}
			return result;
		}

		std::string GetCacheDataFolder(Sexy::AndroidAppDriver*)
		{
			JNIEnv* env = Util::GetJNIEnv();
			if (!env)
				return "";
			jstring folder = (jstring)env->CallObjectMethod(Util::GetGameObject(env), gJavaResources->mGetCacheDataFolder);
			std::string result;
			if (folder)
			{
				Util::StringFromJString(env, result, folder);
				env->DeleteLocalRef(folder);
			}
			return result;
		}

		std::string GetAppSupportDataFolder(Sexy::AndroidAppDriver*)
		{
			JNIEnv* env = Util::GetJNIEnv();
			if (!env)
				return "";
			jstring folder = (jstring)env->CallObjectMethod(Util::GetGameObject(env), gJavaResources->mGetAppSupportDataFolder);
			std::string result;
			if (folder)
			{
				Util::StringFromJString(env, result, folder);
				env->DeleteLocalRef(folder);
			}
			return result;
		}

		std::string GetExternalStorageDirectory(Sexy::AndroidAppDriver*)
		{
			JNIEnv* env = Util::GetJNIEnv();
			if (!env)
				return "";
			jstring folder = (jstring)env->CallObjectMethod(Util::GetGameObject(env), gJavaResources->mGetExternalStorageDirectory);
			std::string result;
			if (folder)
			{
				Util::StringFromJString(env, result, folder);
				env->DeleteLocalRef(folder);
			}
			return result;
		}

		std::string GetExternalFilesDirectory(Sexy::AndroidAppDriver*)
		{
			JNIEnv* env = Util::GetJNIEnv();
			if (!env)
				return "";
			jstring folder = (jstring)env->CallObjectMethod(Util::GetGameObject(env), gJavaResources->mGetExternalFilesDirectory);
			std::string result;
			if (folder)
			{
				Util::StringFromJString(env, result, folder);
				env->DeleteLocalRef(folder);
			}
			return result;
		}

		bool GetAssetFileInfo(const std::string& InFilename, std::string& outAssetPath, long& outOffset, long& outLength)
		{
			JNIEnv* env = Util::GetJNIEnv();
			if (!env)
				return false;
			jstring name = env->NewStringUTF(InFilename.c_str());
			jlongArray info = env->NewLongArray(2);
			jstring path = (jstring)env->CallObjectMethod(Util::GetGameObject(env), gJavaResources->mGetAssetFileInfo, name, info);
			if (path)
			{
				Util::StringFromJString(env, outAssetPath, path);
				env->DeleteLocalRef(path);
				jlong* values = (jlong*)env->GetPrimitiveArrayCritical(info, NULL);
				outOffset = values[0];
				outLength = values[1];
				env->ReleasePrimitiveArrayCritical(info, values, JNI_ABORT);
			}
			env->DeleteLocalRef(info);
			env->DeleteLocalRef(name);
			return true;
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
