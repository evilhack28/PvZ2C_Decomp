//
//  Config.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-03.
//

#include "SexyAppFramework/Common.h"

#include "drivers/app/android/JavaInterface.h"

struct JavaConfigGlobals
{
	char pad[0x80];
	jmethodID mKeyExists;
	jmethodID mReadString;
	jmethodID mReadStringEx;
	jmethodID mReadInteger;
	jmethodID mReadBoolean;
	jmethodID mWriteString;
	jmethodID mWriteInteger;
	jmethodID mWriteBoolean;
	jmethodID mEraseKey;
};

static JavaConfigGlobals* volatile gJavaConfig;

//////////////// Android::Config ///////////////

bool Android::Config::Register(JNIEnv* InEnv, jclass InGameClass)
{
	JavaConfigGlobals* aGlobals;
	jmethodID aMethod;

	aGlobals = gJavaConfig;
	aMethod = InEnv->GetMethodID(InGameClass, "Config_ConfigKeyExists", "(Ljava/lang/String;)Z");
	aGlobals->mKeyExists = aMethod;
	if (aMethod != NULL)
	{
		aGlobals = gJavaConfig;
		aMethod = InEnv->GetMethodID(InGameClass, "Config_ConfigEraseKey", "(Ljava/lang/String;)V");
		aGlobals->mEraseKey = aMethod;
		if (aMethod != NULL)
		{
			aGlobals = gJavaConfig;
			aMethod = InEnv->GetMethodID(InGameClass, "Config_ConfigReadString", "(Ljava/lang/String;)Ljava/lang/String;");
			aGlobals->mReadString = aMethod;
			if (aMethod != NULL)
			{
				aGlobals = gJavaConfig;
				aMethod = InEnv->GetMethodID(InGameClass, "Config_ConfigReadStringEx", "(Ljava/lang/String;)Ljava/lang/String;");
				aGlobals->mReadStringEx = aMethod;
				if (aMethod != NULL)
				{
					aGlobals = gJavaConfig;
					aMethod = InEnv->GetMethodID(InGameClass, "Config_ConfigReadInteger", "(Ljava/lang/String;)I");
					aGlobals->mReadInteger = aMethod;
					if (aMethod != NULL)
					{
						aGlobals = gJavaConfig;
						aMethod = InEnv->GetMethodID(InGameClass, "Config_ConfigReadBoolean", "(Ljava/lang/String;)Z");
						aGlobals->mReadBoolean = aMethod;
						if (aMethod != NULL)
						{
							aGlobals = gJavaConfig;
							aMethod = InEnv->GetMethodID(InGameClass, "Config_ConfigWriteString", "(Ljava/lang/String;Ljava/lang/String;)Z");
							aGlobals->mWriteString = aMethod;
							if (aMethod != NULL)
							{
								aGlobals = gJavaConfig;
								aMethod = InEnv->GetMethodID(InGameClass, "Config_ConfigWriteInteger", "(Ljava/lang/String;I)Z");
								aGlobals->mWriteInteger = aMethod;
								if (aMethod != NULL)
								{
									aGlobals = gJavaConfig;
									aMethod = InEnv->GetMethodID(InGameClass, "Config_ConfigWriteBoolean", "(Ljava/lang/String;Z)Z");
									aGlobals->mWriteBoolean = aMethod;
									return aMethod != NULL;
								}
							}
						}
					}
				}
			}
		}
	}
	return false;
}

bool Android::Config::InitConfig()
{
	return true;
}

bool Android::Config::ConfigReadUTF8String(std::string const& theKeyName, std::string& theString)
{
	JNIEnv* env = Android::Util::GetJNIEnv();
	if (env)
	{
		jstring key = env->NewStringUTF(theKeyName.c_str());
		jobject gameObject = Android::Util::GetGameObject(env);
		jstring str = (jstring)env->CallObjectMethod(gameObject, gJavaConfig->mReadString, key);
		bool ret = false;
		if (str)
		{
			if (!Android::Util::StringFromJString(env, theString, str))
				theString = "";
			ret = true;
			env->DeleteLocalRef(str);
		}
		env->DeleteLocalRef(key);
		return ret;
	}
	return false;
}

bool Android::Config::ConfigReadUTF8StringEx(std::string const& theKeyName, std::string& theString)
{
	JNIEnv* env = Android::Util::GetJNIEnv();
	if (env)
	{
		jstring key = env->NewStringUTF(theKeyName.c_str());
		jobject gameObject = Android::Util::GetGameObject(env);
		jstring str = (jstring)env->CallObjectMethod(gameObject, gJavaConfig->mReadStringEx, key);
		bool ret = false;
		if (str)
		{
			if (!Android::Util::StringFromJString(env, theString, str))
				theString = "";
			ret = true;
			env->DeleteLocalRef(str);
		}
		env->DeleteLocalRef(key);
		return ret;
	}
	return false;
}

bool Android::Config::ConfigReadWideString(std::string const& theKeyName, std::wstring& theString)
{
	JNIEnv* env = Android::Util::GetJNIEnv();
	if (!env)
		return false;
	jstring key = env->NewStringUTF(theKeyName.c_str());
	jobject gameObject = Android::Util::GetGameObject(env);
	jstring str = (jstring)env->CallObjectMethod(gameObject, gJavaConfig->mReadString, key);
	bool ret = false;
	if (str)
	{
		ret = true;
		Android::Util::WStringFromJString(env, theString, str);
		env->DeleteLocalRef(str);
	}
	env->DeleteLocalRef(key);
	return ret;
}

bool Android::Config::ConfigReadInteger(std::string const& theKeyName, int32& theValue)
{
	JNIEnv* env = Android::Util::GetJNIEnv();
	if (env)
	{
		bool ret = false;
		jstring key = env->NewStringUTF(theKeyName.c_str());
		jobject gameObject = Android::Util::GetGameObject(env);
		if (env->CallBooleanMethod(gameObject, gJavaConfig->mKeyExists, key))
		{
			ret = true;
			gameObject = Android::Util::GetGameObject(env);
			theValue = env->CallIntMethod(gameObject, gJavaConfig->mReadInteger, key);
		}
		env->DeleteLocalRef(key);
		return ret;
	}
	return false;
}

bool Android::Config::ConfigReadBoolean(std::string const& theKeyName, bool& theValue)
{
	JNIEnv* env = Android::Util::GetJNIEnv();
	if (env)
	{
		jstring key = env->NewStringUTF(theKeyName.c_str());
		jobject gameObject = Android::Util::GetGameObject(env);
		bool ret = false;
		if (env->CallBooleanMethod(gameObject, gJavaConfig->mKeyExists, key))
		{
			theValue = env->CallBooleanMethod(gameObject, gJavaConfig->mReadBoolean, key);
			ret = true;
		}
		env->DeleteLocalRef(key);
		return ret;
	}
	return false;
}

bool Android::Config::ConfigWriteUTF8String(std::string const& theKeyName, std::string const& theString)
{
	JNIEnv* env = Android::Util::GetJNIEnv();
	if (env)
	{
		jstring key = env->NewStringUTF(theKeyName.c_str());
		jstring str = env->NewStringUTF(theString.c_str());
		jobject gameObject = Android::Util::GetGameObject(env);
		bool ok = env->CallBooleanMethod(gameObject, gJavaConfig->mWriteString, key, str);
		env->DeleteLocalRef(str);
		env->DeleteLocalRef(key);
		return ok;
	}
	return false;
}

bool Android::Config::ConfigWriteWideString(std::string const& theKeyName, std::wstring const& theString)
{
	JNIEnv* env = Android::Util::GetJNIEnv();
	if (env)
	{
		jstring key = env->NewStringUTF(theKeyName.c_str());
		jstring str = env->NewString((const jchar*)theString.c_str(), theString.size());
		jobject gameObject = Android::Util::GetGameObject(env);
		bool ok = env->CallBooleanMethod(gameObject, gJavaConfig->mWriteString, key, str);
		env->DeleteLocalRef(str);
		env->DeleteLocalRef(key);
		return ok;
	}
	return false;
}

bool Android::Config::ConfigWriteInteger(std::string const& theKeyName, int32 theValue)
{
	JNIEnv* env = Android::Util::GetJNIEnv();
	if (!env)
		return false;
	jstring key = env->NewStringUTF(theKeyName.c_str());
	jobject gameObject = Android::Util::GetGameObject(env);
	bool ok = env->CallBooleanMethod(gameObject, gJavaConfig->mWriteInteger, key, theValue) != 0;
	env->DeleteLocalRef(key);
	return ok;
}

bool Android::Config::ConfigWriteBoolean(std::string const& theKeyName, bool theValue)
{
	JNIEnv* env = Android::Util::GetJNIEnv();
	if (!env)
		return false;
	jstring key = env->NewStringUTF(theKeyName.c_str());
	jobject gameObject = Android::Util::GetGameObject(env);
	bool ok = env->CallBooleanMethod(gameObject, gJavaConfig->mWriteBoolean, key, theValue) != 0;
	env->DeleteLocalRef(key);
	return ok;
}

void Android::Config::ConfigEraseKey(std::string const& theKeyName)
{
	JNIEnv* env = Android::Util::GetJNIEnv();
	if (env)
	{
		jstring key = env->NewStringUTF(theKeyName.c_str());
		jobject gameObject = Android::Util::GetGameObject(env);
		env->CallVoidMethod(gameObject, gJavaConfig->mEraseKey, key);
		env->DeleteLocalRef(key);
	}
}

void Android::Config::ConfigEraseKey(std::wstring const& theKeyName)
{
	JNIEnv* env = Android::Util::GetJNIEnv();
	if (env)
	{
		jstring key = env->NewString((const jchar*)theKeyName.c_str(), theKeyName.size());
		jobject gameObject = Android::Util::GetGameObject(env);
		env->CallVoidMethod(gameObject, gJavaConfig->mEraseKey, key);
		env->DeleteLocalRef(key);
	}
}
