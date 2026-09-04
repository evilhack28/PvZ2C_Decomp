//
//  Ultra.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-04.
//

#include "SexyAppFramework/Common.h"

#include <algorithm>

#include "AdProvider.h"
#include "AdProviderFactory.h"
#include "EASquaredPropertySheet.h"
#include "EASquaredMessageTypes.h"
#include "GameEventMgr.h"
#include "PVZDB.h"
#include "SuperSonicAdProvider.h"
#include "Ultra.h"

/////////////// Ultra ///////////////

Ultra::Ultra()
	: mSuperSonic(NULL)
	, m_useSuperSonicV6(false)
{
}

void Ultra::Initialize(const std::string& i_obfuscatedUserId, Delegate2<int, int>& i_addCoinsToBeAwarded, Delegate0& i_onAdvertisementsClosed)
{
	mAddCoinsToBeAwarded = i_addCoinsToBeAwarded;
	mOnAdvertisementsClosed = i_onAdvertisementsClosed;

	const EASquaredPropertySheet* config = (const EASquaredPropertySheet*)PVZDB::GetInstance().FindObjectByAlias<EASquaredPropertySheet>(PVZDB::TABLE_EASQUAREDCONFIG, RtName(L"EASquaredConfig")).GetObject();

	mSuperSonic = SuperSonicAdProvider::GetInstance().InitializeAndGet(config->EnableSuperSonic);
	mAdProviders.push_back(mSuperSonic);
	m_useSuperSonicV6 = SuperSonicAdProvider::GetInstance().IsEnabled();

	onInitialize(i_obfuscatedUserId);

	for (std::vector<AdProvider*>::iterator it = mAdProviders.begin(); it != mAdProviders.end(); ++it)
	{
		(*it)->Initialize(i_obfuscatedUserId);
	}
}

bool Ultra::HasAdvertisements()
{
	return std::any_of(mAdProviders.begin(), mAdProviders.end(), [](AdProvider* i_adProvider) { return i_adProvider->HasAdvertisements(); });
}

int Ultra::GetNumAdvertisementsAvailable()
{
	int numAvailable = 0;
	for (std::vector<AdProvider*>::iterator it = mAdProviders.begin(); it != mAdProviders.end(); ++it)
	{
		int numFromProvider = (*it)->GetNumAdvertisementsAvailable();
		if (numFromProvider > 0)
		{
			numAvailable += numFromProvider;
		}
	}
	return numAvailable;
}

bool Ultra::SuperSonicHasAdvertisements() const
{
	return mSuperSonic ? mSuperSonic->HasAdvertisements() : false;
}

bool Ultra::showSuperSonic()
{
	return showAdProvider(mSuperSonic);
}

bool Ultra::showAdProvider(AdProvider* i_adProvider)
{
	bool hasAds = i_adProvider->HasAdvertisements();
	if (hasAds)
	{
		gMessageRouter->Broadcast(Message::EASquaredAdvertisementsWillOpen);
		i_adProvider->ShowAdvertisements(mAddCoinsToBeAwarded, mOnAdvertisementsClosed);
	}
	return hasAds;
}
