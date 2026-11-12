//
//  S2C_CurrencyInfo.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "LawnApp.h"
#include "PVPManager.h"
#include "ProfileMgr.h"
#include "PlayerInfo.h"
#include "GameCommon.h"

/////////////// Logic ///////////////

void S2C_CurrencyInfo::SetToPlayerInfo()
{
	PlayerInfo* profile = Sexy::LazySingleton<ProfileMgr>::GetInstance().GetCurrentProfile();
	if (m_gemValid)
	{
		profile->SetGems(eastl::max_alt(m_gem, 0));
		m_gemValid = false;
	}
	if (m_coinValid)
	{
		if (m_coin < 0)
		{
			profile->SubtractCoins(-m_coin);
			m_coinValid = false;
		}
		else
		{
			profile->AddCoins(m_coin);
			m_coinValid = false;
		}
	}
	if (m_pvpCoin >= 0)
	{
		PVPManager::GetInstancePtr()->SetPVPCoin(m_pvpCoin);
		m_pvpCoin = -1;
	}
	if (m_pvpMedal >= 0)
	{
		PVPManager::GetInstancePtr()->SetPVPMedal(m_pvpMedal);
		m_pvpMedal = -1;
	}
	int i = 0;
	while (i < m_rewardList.size())
	{
		S2C_ItemInfo& item = m_rewardList[i];
		ProfileChangeItemAmount(item.m_id, item.m_num, false);
		i++;
	}
}
