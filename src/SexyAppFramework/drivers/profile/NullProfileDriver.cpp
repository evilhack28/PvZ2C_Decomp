//
//  NullProfileDriver.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-18.
//
/////////////// Lifecycle ///////////////

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/drivers/profile/NullProfileDriver.h"
#include "SexyAppFramework/ProfileManager.h"
#include "SexyAppFramework/SexyAppBase.h"

namespace Sexy
{

NullProfileDriver::NullProfileDriver()
{
}

bool NullProfileDriver::Init()
{
	return true;
}

bool NullProfileDriver::HasError()
{
	return false;
}

void NullProfileDriver::Update()
{
}

/////////////// Profiles ///////////////

uint32 NullProfileDriver::GetNumProfiles()
{
	return mProfileMap.size();
}

UserProfile* NullProfileDriver::GetProfile(int index)
{
	ProfileMap::iterator anItr = mProfileMap.begin();
	for (int i = 0; i < index && anItr != mProfileMap.end(); i++)
		++anItr;

	if (anItr != mProfileMap.end())
		return anItr->second;

	return NULL;
}

UserProfile* NullProfileDriver::GetProfile(const SexyString &theName)
{
	ProfileMap::iterator anItr = mProfileMap.find(theName);
	if (anItr != mProfileMap.end())
		return anItr->second;

	return NULL;
}

UserProfile* NullProfileDriver::GetAnyProfile()
{
	if (!mProfileMap.empty())
		return mProfileMap.begin()->second;

	return NULL;
}

UserProfile* NullProfileDriver::AddProfile(const SexyString &theName)
{
	std::pair<ProfileMap::iterator, bool> aRet;
	UserProfile *aProfile = gSexyAppBase->mProfileManager->CreateUserProfile();
	aRet = mProfileMap.insert(ProfileMap::value_type(theName, aProfile));
	if (aRet.second)
		return aRet.first->second;

	return NULL;
}

bool NullProfileDriver::DeleteProfile(const SexyString &theName)
{
	return false;
}

bool NullProfileDriver::RenameProfile(const SexyString &theOldName, const SexyString &theNewName)
{
	return false;
}

void NullProfileDriver::ClearProfiles()
{
}

}
