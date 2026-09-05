//
//  AdProvider.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "SexyAppFramework/Common.h"

#include "AdProvider.h"
#include "EASquaredMessageTypes.h"
#include "GameEventMgr.h"

/////////////// AdProvider ///////////////

AdProvider::AdProvider()
	: mAdsAreAvailable(false)
	, mInventoryCountAvailble(0)
{
}

AdProvider::~AdProvider()
{
}

bool AdProvider::HasAdvertisements() const
{
	return mAdsAreAvailable;
}

int AdProvider::GetNumAdvertisementsAvailable() const
{
	return mAdsAreAvailable ? mInventoryCountAvailble : 0;
}

void AdProvider::ShowAdvertisements(const ::Sexy::Delegate2<int, int>& i_coinsAwardedCallback, const ::Sexy::Delegate0& i_onAdsClosedCallback)
{
	mCoinsAwardedCallback = i_coinsAwardedCallback;
	mAdsClosedCallback = i_onAdsClosedCallback;
	doShowAdvertisements();
}

void AdProvider::awardRewards(int i_rewardQuantity, int i_videosWatched)
{
	mCoinsAwardedCallback(i_rewardQuantity, i_videosWatched);
}

void AdProvider::onClose()
{
	if (mAdsClosedCallback)
	{
		mAdsClosedCallback();
		mAdsClosedCallback = ::Sexy::Delegate0();
	}
}

void AdProvider::setAdsAreAvailable(bool i_adsAreAvailable, int adInventory)
{
	mAdsAreAvailable = i_adsAreAvailable;
	mInventoryCountAvailble = adInventory;
	BroadcastMessage(Message::EASquaredAdsAvailableChanged);
}
