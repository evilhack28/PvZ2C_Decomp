//
//  Diag.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-09.
//

#include "SexyAppFramework/Common.h"

#include "drivers/app/android/JavaInterface.h"

struct JavaDiagMethods
{
	char pad[0x230];
	jmethodID mPrimaryMACAddress;
	jmethodID mOSVersion;
	jmethodID mHardwareModel;
	jmethodID mDeviceID;
	jmethodID mUniqueCharacterID;
	jmethodID mAvailMemory;
	jmethodID mUsedMemory;
	jmethodID mNetworkType;
	jmethodID mMobileCardType;
	jmethodID mSimProvince;
	jmethodID mDeviceIMSI;
	jmethodID mDeviceIMEI;
	jmethodID mDeviceMODEL;
	jmethodID mDeviceBRAND;
	jmethodID mHasNotchInScreen;
	jmethodID mNotchHeight;
	jmethodID mSwitchOpen;
};

static JavaDiagMethods* volatile gJavaDiag;

namespace Android
{
	namespace Diag
	{
		/////////////// Lifecycle ///////////////

		bool Register(JNIEnv* InEnv, jclass InGameClass)
		{
			JavaDiagMethods* aMethods;
			jmethodID aMethod;

			aMethods = gJavaDiag;
			aMethod = InEnv->GetMethodID(InGameClass, "Diag_GetPrimaryMACAddress", "()Ljava/lang/String;");
			aMethods->mPrimaryMACAddress = aMethod;
			if (aMethod != NULL)
			{
				aMethods = gJavaDiag;
				aMethod = InEnv->GetMethodID(InGameClass, "Diag_GetOSVersion", "()Ljava/lang/String;");
				aMethods->mOSVersion = aMethod;
				if (aMethod != NULL)
				{
					aMethods = gJavaDiag;
					aMethod = InEnv->GetMethodID(InGameClass, "Diag_GetHardwareModel", "()Ljava/lang/String;");
					aMethods->mHardwareModel = aMethod;
					if (aMethod != NULL)
					{
						aMethods = gJavaDiag;
						aMethod = InEnv->GetMethodID(InGameClass, "Diag_GetDeviceID", "()Ljava/lang/String;");
						aMethods->mDeviceID = aMethod;
						if (aMethod != NULL)
						{
							aMethods = gJavaDiag;
							aMethod = InEnv->GetMethodID(InGameClass, "Diag_GetUniqueCharacterID", "()Ljava/lang/String;");
							aMethods->mUniqueCharacterID = aMethod;
							if (aMethod != NULL)
							{
								aMethods = gJavaDiag;
								aMethod = InEnv->GetMethodID(InGameClass, "Diag_GetAvailMemory", "()J");
								aMethods->mAvailMemory = aMethod;
								if (aMethod != NULL)
								{
									aMethods = gJavaDiag;
									aMethod = InEnv->GetMethodID(InGameClass, "Diag_GetUsedMemory", "()J");
									aMethods->mUsedMemory = aMethod;
									if (aMethod != NULL)
									{
										aMethods = gJavaDiag;
										aMethod = InEnv->GetMethodID(InGameClass, "Diag_GetNetworkType", "()Ljava/lang/String;");
										aMethods->mNetworkType = aMethod;
										if (aMethod != NULL)
										{
											aMethods = gJavaDiag;
											aMethod = InEnv->GetMethodID(InGameClass, "Diag_GetMobileCardType", "()I");
											aMethods->mMobileCardType = aMethod;
											if (aMethod != NULL)
											{
												aMethods = gJavaDiag;
												aMethod = InEnv->GetMethodID(InGameClass, "Diag_GetSimProvince", "()I");
												aMethods->mSimProvince = aMethod;
												if (aMethod != NULL)
												{
													aMethods = gJavaDiag;
													aMethod = InEnv->GetMethodID(InGameClass, "Diag_GetDeviceIMSI", "()Ljava/lang/String;");
													aMethods->mDeviceIMSI = aMethod;
													if (aMethod != NULL)
													{
														aMethods = gJavaDiag;
														aMethod = InEnv->GetMethodID(InGameClass, "Diag_GetDeviceIMEI", "()Ljava/lang/String;");
														aMethods->mDeviceIMEI = aMethod;
														if (aMethod != NULL)
														{
															aMethods = gJavaDiag;
															aMethod = InEnv->GetMethodID(InGameClass, "Diag_GetDeviceMODEL", "()Ljava/lang/String;");
															aMethods->mDeviceMODEL = aMethod;
															if (aMethod != NULL)
															{
																aMethods = gJavaDiag;
																aMethod = InEnv->GetMethodID(InGameClass, "Diag_GetDeviceBRAND", "()Ljava/lang/String;");
																aMethods->mDeviceBRAND = aMethod;
																if (aMethod != NULL)
																{
																	aMethods = gJavaDiag;
																	aMethod = InEnv->GetMethodID(InGameClass, "Diag_HasNotchInScreen", "(I)Z");
																	aMethods->mHasNotchInScreen = aMethod;
																	if (aMethod != NULL)
																	{
																		aMethods = gJavaDiag;
																		aMethod = InEnv->GetMethodID(InGameClass, "Diag_GetNotchHeight", "(I)I");
																		aMethods->mNotchHeight = aMethod;
																		if (aMethod != NULL)
																		{
																			aMethods = gJavaDiag;
																			aMethod = InEnv->GetMethodID(InGameClass, "Diag_GetSwitchOpen", "()I");
																			aMethods->mSwitchOpen = aMethod;
																			return aMethod != NULL;
																		}
																	}
																}
															}
														}
													}
												}
											}
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

		/////////////// Accessors ///////////////

		void GetPrimaryMACAddress(std::string& outString)
		{
			JNIEnv* env = Util::GetJNIEnv();
			if (env)
			{
				jstring str = (jstring)env->CallObjectMethod(Util::GetGameObject(env), gJavaDiag->mPrimaryMACAddress);
				if (str)
				{
					Util::StringFromJString(env, outString, str);
					env->DeleteLocalRef(str);
				}
			}
		}

		void GetOSVersion(std::string& outString)
		{
			JNIEnv* env = Util::GetJNIEnv();
			if (env)
			{
				jstring str = (jstring)env->CallObjectMethod(Util::GetGameObject(env), gJavaDiag->mOSVersion);
				if (str)
				{
					Util::StringFromJString(env, outString, str);
					env->DeleteLocalRef(str);
				}
			}
		}

		void GetHardwareModel(std::string& outString)
		{
			JNIEnv* env = Util::GetJNIEnv();
			if (env)
			{
				jstring str = (jstring)env->CallObjectMethod(Util::GetGameObject(env), gJavaDiag->mHardwareModel);
				if (str)
				{
					Util::StringFromJString(env, outString, str);
					env->DeleteLocalRef(str);
				}
			}
		}

		void GetDeviceID(std::string& outString)
		{
			JNIEnv* env = Util::GetJNIEnv();
			if (env)
			{
				jstring str = (jstring)env->CallObjectMethod(Util::GetGameObject(env), gJavaDiag->mDeviceID);
				if (str)
				{
					Util::StringFromJString(env, outString, str);
					env->DeleteLocalRef(str);
				}
			}
		}

		void GetUniqueCharacterID(std::string& outString)
		{
			JNIEnv* env = Util::GetJNIEnv();
			if (env)
			{
				jstring str = (jstring)env->CallObjectMethod(Util::GetGameObject(env), gJavaDiag->mUniqueCharacterID);
				if (str)
				{
					Util::StringFromJString(env, outString, str);
					env->DeleteLocalRef(str);
				}
			}
		}

		void GetDeviceIMSI(std::string& outString)
		{
			JNIEnv* env = Util::GetJNIEnv();
			if (env)
			{
				jstring str = (jstring)env->CallObjectMethod(Util::GetGameObject(env), gJavaDiag->mDeviceIMSI);
				if (str)
				{
					Util::StringFromJString(env, outString, str);
					env->DeleteLocalRef(str);
				}
			}
		}

		void GetDeviceIMEI(std::string& outString)
		{
			JNIEnv* env = Util::GetJNIEnv();
			if (env)
			{
				jstring str = (jstring)env->CallObjectMethod(Util::GetGameObject(env), gJavaDiag->mDeviceIMEI);
				if (str)
				{
					Util::StringFromJString(env, outString, str);
					env->DeleteLocalRef(str);
				}
			}
		}

		void GetDeviceMODEL(std::string& outString)
		{
			JNIEnv* env = Util::GetJNIEnv();
			if (env)
			{
				jstring str = (jstring)env->CallObjectMethod(Util::GetGameObject(env), gJavaDiag->mDeviceMODEL);
				if (str)
				{
					Util::StringFromJString(env, outString, str);
					env->DeleteLocalRef(str);
				}
			}
		}

		void GetDeviceBRAND(std::string& outString)
		{
			JNIEnv* env = Util::GetJNIEnv();
			if (env)
			{
				jstring str = (jstring)env->CallObjectMethod(Util::GetGameObject(env), gJavaDiag->mDeviceBRAND);
				if (str)
				{
					Util::StringFromJString(env, outString, str);
					env->DeleteLocalRef(str);
				}
			}
		}

		long GetAvailMemory()
		{
			JNIEnv* env = Util::GetJNIEnv();
			if (env)
				return env->CallLongMethod(Util::GetGameObject(env), gJavaDiag->mAvailMemory);
			return 0;
		}

		long GetUsedMemory()
		{
			JNIEnv* env = Util::GetJNIEnv();
			if (env)
				return env->CallLongMethod(Util::GetGameObject(env), gJavaDiag->mUsedMemory);
			return 0;
		}

		int GetMobileCardType()
		{
			JNIEnv* env = Util::GetJNIEnv();
			if (env)
				return env->CallIntMethod(Util::GetGameObject(env), gJavaDiag->mMobileCardType);
			return 0;
		}

		int GetSimProvince()
		{
			JNIEnv* env = Util::GetJNIEnv();
			if (env)
				return env->CallIntMethod(Util::GetGameObject(env), gJavaDiag->mSimProvince);
			return 0;
		}

		int GetSwitchOpen()
		{
			JNIEnv* env = Util::GetJNIEnv();
			if (env)
				return env->CallIntMethod(Util::GetGameObject(env), gJavaDiag->mSwitchOpen);
			return 0;
		}

		int GetNotchHeight(int i_type)
		{
			JNIEnv* env = Util::GetJNIEnv();
			if (env)
				return env->CallIntMethod(Util::GetGameObject(env), gJavaDiag->mNotchHeight, i_type);
			return 0;
		}

		bool HasNotchInScreen(int i_type)
		{
			JNIEnv* env = Util::GetJNIEnv();
			if (env && env->CallBooleanMethod(Util::GetGameObject(env), gJavaDiag->mHasNotchInScreen, i_type))
				return GetSwitchOpen() != 1;
			return false;
		}

		std::string GetNetworkType()
		{
			std::string result = "";
			JNIEnv* env = Util::GetJNIEnv();
			if (env)
			{
				jstring str = (jstring)env->CallObjectMethod(Util::GetGameObject(env), gJavaDiag->mNetworkType);
				if (str)
				{
					if (!Util::StringFromJString(env, result, str))
						result = "";
					env->DeleteLocalRef(str);
				}
			}
			return result;
		}

		void GetLocal(std::string& outString)
		{
			outString = "zh-cn";
		}

		bool IsMobileCardType(MobileCardType i_type)
		{
			return (GetMobileCardType() & i_type) != 0;
		}
	}
}
