//
//  PlayerIdentityService.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PlayerIdentityService.h"

#include "PlayerIdentityService.h"
void PlayerIdentityService::iCloudDataInitialSyncChange()
{
	 PlayerIdentityService::accountStoredInKvStore();
}

#include "PlayerIdentityService.h"
void PlayerIdentityService::iCloudDidFinishInitialization()
{
	 PlayerIdentityService::accountStoredInKvStore();
}

#include "PlayerIdentityService.h"
void PlayerIdentityService::iCloudAccountDidSignInFirstTime()
{
	 PlayerIdentityService::accountStoredInKvStore();
}

#include "PlayerIdentityService.h"
void PlayerIdentityService::iCloudDataServerChangeWithChangedKeys(const char** keys)
{
	 PlayerIdentityService::accountStoredInKvStore();
}
