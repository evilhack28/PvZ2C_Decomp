//
//  UserInfo.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-03.
//

#include "SexyAppFramework/Common.h"

#include <functional>
#include "UserInfo.h"
#include "PlayerInfo.h"
#include "ProfileMgr.h"
#include "ProfileUtils.h"

/////////////// Accessors ///////////////

const std::string& UserInfo::getName() const { return m_Name; }
void UserInfo::setName(const std::string& v) { m_Name = v; }
const std::string& UserInfo::getPhone() const { return m_Phone; }
void UserInfo::setPhone(const std::string& v) { m_Phone = v; }
const std::string& UserInfo::getEmail() const { return m_Email; }
void UserInfo::setEmail(const std::string& v) { m_Email = v; }

/////////////// Lifecycle ///////////////

UserInfo::UserInfo()
{
	PlayerInfo* profile = ProfileUtils::Profile();
	if (profile != nullptr)
	{
		setName(Sexy::WStringToUTF8String(profile->AM_GetName()));
		setHeadShotId(profile->getHeadshotId());
	}
}

UserInfo::~UserInfo()
{
}

/////////////// Headshots ///////////////

void UserInfo::setHeadShotId(int a)
{
	HeadShotId = a;
	PlayerInfo* profile = ProfileUtils::Profile();
	if (profile != nullptr)
	{
		profile->setHeadshotId(a);
		bool unlocked = profile->isUnlockHeadshotId(a);
		if (!unlocked)
		{
			profile->setUnlockHeadshotId(a);
			profile->SAVE_PROFILE();
			ProfileMgr::GetInstance().Save(unlocked);
		}
	}
}

void UserInfo::unlockHeadShotId(int a)
{
	PlayerInfo* profile = ProfileUtils::Profile();
	if (profile != nullptr)
	{
		bool unlocked = profile->isUnlockHeadshotId(a);
		if (!unlocked)
		{
			profile->setUnlockHeadshotId(a);
			profile->SAVE_PROFILE();
			ProfileMgr::GetInstance().Save(unlocked);
		}
	}
}
