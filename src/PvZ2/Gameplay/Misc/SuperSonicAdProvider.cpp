//
//  SuperSonicAdProvider.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "SexyAppFramework/Common.h"

#include "SuperSonicAdProvider.h"
#include "SuperSonicAdProviderAndroid.h"

/////////////// SuperSonicAdProvider ///////////////

SuperSonicAdProvider::SuperSonicAdProvider()
{
}

SuperSonicAdProvider::~SuperSonicAdProvider()
{
}

AdProvider& SuperSonicAdProvider::PlatformSpecificInstance()
{
	return SuperSonicAdProviderAndroid::GetInstance();
}

const std::string SuperSonicAdProvider::getEnabledOverrideKey()
{
	return SUPERSONIC_ENABLED_OVERRIDE_KEY;
}

const std::string SuperSonicAdProvider::getUseDemoCampaignsKey()
{
	return SUPERSONIC_USE_DEMO_CAMPAIGNS_KEY;
}
