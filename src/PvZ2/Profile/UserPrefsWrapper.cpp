//
//  UserPrefsWrapper.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-03.
//

#include "UserPrefsWrapper.h"
#include "iosExtras.h"
#include "Utils.h"
#include "SexyAppFramework/Common.h"

__asm__(".local __dso_handle\n.comm __dso_handle,8,8");

/////////////// Lifecycle ///////////////

inline UserPrefsWrapper::~UserPrefsWrapper() {}

/////////////// Prefs ///////////////

const std::string UserPrefsWrapper::GetString(const std::string& i_key, std::string i_defaultValue) { return UserPrefs::GetString(i_key, i_defaultValue); }
const std::string UserPrefsWrapper::GetStringEx(const std::string& i_key, std::string i_defaultValue) { return UserPrefs::GetStringEx(i_key, i_defaultValue); }
void UserPrefsWrapper::SetString(const std::string& i_key, std::string i_value) { UserPrefs::SetString(i_key, i_value); UserPrefs::Synchronize(); }
void UserPrefsWrapper::SetBool(const std::string& i_key, bool i_value) { UserPrefs::SetBool(i_key, i_value); UserPrefs::Synchronize(); }
const bool UserPrefsWrapper::GetBool(const std::string& i_key) { return UserPrefs::GetBool(i_key); }
const int UserPrefsWrapper::GetInt(const std::string& i_key, int i_defaultValue) { return UserPrefs::GetInt(i_key, i_defaultValue); }
void UserPrefsWrapper::SetInt(const std::string& i_key, int i_value) { UserPrefs::SetInt(i_key, i_value); UserPrefs::Synchronize(); }

/////////////// Age / PCPID ///////////////

std::string UserPrefsWrapper::GetAge() { return GetString(age_key, ""); }
void UserPrefsWrapper::SetAge(const std::string& i_value) { SetString(age_key, i_value); }
std::string UserPrefsWrapper::GetPCPID() { return GetString(pcpid_key, ""); }

void UserPrefsWrapper::SetPCPIDStrings(const std::string& i_value)
{
	if (i_value.size())
	{
		std::vector<std::string> parts = SplitString(i_value, '-');
		for (int i = 0; (size_t)i < parts.size(); i++)
		{
			std::string key = Sexy::StrFormat("pcpid_%d", i + 1);
			std::string value = parts[i];
			UserPrefs::SetString(key, value);
		}
	}
	SetString(pcpid_key, i_value);
}
