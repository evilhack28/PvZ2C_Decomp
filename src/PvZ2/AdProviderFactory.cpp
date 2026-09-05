//
//  AdProviderFactory.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "SexyAppFramework/Common.h"

#include "AdProviderFactory.h"
#include "AdProvider.h"
#include "UserPrefsWrapper.h"

/////////////// AdProviderFactory ///////////////

AdProviderFactory::AdProviderFactory()
	: EnabledValueFromConfig(false)
	, EnabledOverrideValue(NO_OVERRIDE)
	, UsingDemoCampaigns(false)
{
}

AdProviderFactory::~AdProviderFactory()
{
}

AdProvider* AdProviderFactory::InitializeAndGet(bool i_enableProvider)
{
	EnabledValueFromConfig = i_enableProvider;
	EnabledOverrideValue = (AdProviderEnabledOverrideState)UserPrefsWrapper::GetInstance().GetInt(getEnabledOverrideKey(), 0);
	UsingDemoCampaigns = UserPrefsWrapper::GetInstance().GetBool(getUseDemoCampaignsKey());

	if (IsEnabled())
		return &PlatformSpecificInstance();

	return &AdProviderNullImpl::GetInstance();
}

bool AdProviderFactory::IsEnabled()
{
	switch (EnabledOverrideValue)
	{
	case FORCE_DISABLE_AD_PROVIDER:
		return false;
	case FORCE_ENABLE_AD_PROVIDER:
		return true;
	default:
		return EnabledValueFromConfig;
	}
}
