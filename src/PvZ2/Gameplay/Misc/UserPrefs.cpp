//
//  UserPrefs.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"
#include "iosExtras.h"
#include "SexyAppFramework/SexyAppBase.h"
#include "SexyAppFramework/IDiagDriver.h"
#include "SexyAppFramework/drivers/app/android/JavaInterface.h"

/////////////// Prefs ///////////////

void UserPrefs::SetString(const std::string& i_key, std::string i_value)
{
	Android::Config::ConfigWriteUTF8String(i_key, i_value);
}

void UserPrefs::Synchronize()
{
}

void UserPrefs::SetBool(const std::string& i_key, bool i_value)
{
	Android::Config::ConfigWriteBoolean(i_key, i_value);
}

void UserPrefs::SetInt(const std::string& i_key, int i_value)
{
	Android::Config::ConfigWriteInteger(i_key, i_value);
}

bool UserPrefs::GetBool(const std::string& i_key, bool defaultValue)
{
	bool value;
	if (Android::Config::ConfigReadBoolean(i_key, value))
		return value;
	return defaultValue;
}

int UserPrefs::GetInt(const std::string& i_key, int defaultValue)
{
	int value;
	if (Android::Config::ConfigReadInteger(i_key, value))
		return value;
	return defaultValue;
}

const std::string UserPrefs::GetString(const std::string& i_key, std::string i_defaultValue)
{
	std::string value;
	if (Android::Config::ConfigReadUTF8String(i_key, value))
		return value;
	return i_defaultValue;
}

const std::string UserPrefs::GetStringEx(const std::string& i_key, std::string i_defaultValue)
{
	std::string value;
	if (Android::Config::ConfigReadUTF8StringEx(i_key, value))
		return value;
	return i_defaultValue;
}

std::string UserPrefs::GetDeviceType()
{
	return gSexyAppBase->mDiagDriver->GetInfoStringSafe(IDiagDriver::INFO_HardwareModel);
}
