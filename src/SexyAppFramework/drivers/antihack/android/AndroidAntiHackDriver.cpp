//
//  AndroidAntiHackDriver.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-31.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/drivers/antihack/android/AndroidAntiHackDriver.h"
#include "SexyAppFramework/drivers/app/android/JavaInterface.h"
#include <android/log.h>

using namespace Sexy;

/////////////// Lifecycle ///////////////

AndroidAntiHackDriver::AndroidAntiHackDriver()
{
}

AndroidAntiHackDriver::~AndroidAntiHackDriver()
{
}

/////////////// Signature ///////////////

long AndroidAntiHackDriver::GetDigitalSignature()
{
	long hash = 0;
	std::string packageName = Android::Util::GetPackageName();
	JNIEnv* env = Android::Util::GetJNIEnv();
	std::string signature("");

	jobject packageManager = Android::Util::GetPackageManagerObject(env);
	if (!packageManager)
		return hash;
	jclass packageManagerClass = env->GetObjectClass(packageManager);
	if (!packageManagerClass)
		return hash;
	jmethodID getPackageInfo = env->GetMethodID(packageManagerClass, "getPackageInfo", "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
	if (!getPackageInfo)
		return hash;

	std::string name = packageName;
	jobject packageInfo = env->CallObjectMethod(packageManager, getPackageInfo, env->NewStringUTF(name.c_str()), 64);
	if (!packageInfo)
		return hash;
	jclass packageInfoClass = env->GetObjectClass(packageInfo);
	if (!packageInfoClass)
		return hash;
	jfieldID signaturesField = env->GetFieldID(packageInfoClass, "signatures", "[Landroid/content/pm/Signature;");
	if (!signaturesField)
		return hash;
	jobjectArray signatures = (jobjectArray)env->GetObjectField(packageInfo, signaturesField);
	if (!signatures)
		return hash;
	jobject firstSignature = env->GetObjectArrayElement(signatures, 0);
	if (!firstSignature)
		return hash;
	jclass signatureClass = env->GetObjectClass(firstSignature);
	if (!signatureClass)
		return hash;
	jmethodID hashCode = env->GetMethodID(signatureClass, "hashCode", "()I");
	if (!hashCode)
		return hash;

	hash = env->CallIntMethod(firstSignature, hashCode);
	env->DeleteLocalRef(packageInfo);
	env->DeleteLocalRef(signatures);
	env->DeleteLocalRef(firstSignature);
	return hash;
}

bool AndroidAntiHackDriver::IsPackageHacked()
{
	static const unsigned int validSignatures[] =
	{
		0xcc6ecb51, 0x0cd8155e, 0x8fdec6da, 0x5d525fb6,
		0xbdcaffab, 0x1dd1d232, 0xc1129970, 0x8923cbb8,
		0x3eddd200, 0x70213926, 0x09d1c4fd, 0xdbd513c1
	};
	int i_size = sizeof(validSignatures) / sizeof(validSignatures[0]);

	unsigned int signature = GetDigitalSignature();
	__android_log_print(ANDROID_LOG_VERBOSE, "CheckHacked", "Sign( %d )", signature);
	OutputDebugStrF("=============siginatuee: %d, i_size: %d", signature, i_size);

	for (int i = 0; i < i_size; i++)
	{
		if (signature == validSignatures[i])
			return false;
	}
	return true;
}
