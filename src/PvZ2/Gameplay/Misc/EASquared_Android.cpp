//
//  EASquared_Android.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "EASquared_Android.h"

EASquared_Android::~EASquared_Android()
{
}

bool EASquared_Android::IsShowingAds()
{
	return false;
}

bool EASquared_Android::IsAwardingAds()
{
	return false;
}

bool EASquared_Android::IsEnabledForUser()
{
	return false;
}

void EASquared_Android::showAdvertisement(const EASquaredAdCompletedCallback & i_postFlowCallback, bool i_suppressRewardScreen)
{
}

void EASquared_Android::OfferToShowAdvertisements(const std::string& i_placementOrigin, const EASquaredAdCompletedCallback& i_postFlowCallback)
{
}

void EASquared_Android::CancelAdvertisementCallback()
{
}

void EASquared_Android::Update()
{
}
