//
//  WorldMapActivityBtnTurnChangeManager.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include "LuaCUIDialog.h"
#include "WorldMapActivityBtnTurnChangeManager.h"
#include "ActivityManager.h"
#include "ProfileUtils.h"
#include "ProfileMgr.h"

/////////////// Accessors ///////////////

void WorldMapActivityBtnTurnChangeManager::setIsInit(bool isInit)
{
	m_bIsInit = isInit;
}

void WorldMapActivityBtnTurnChangeManager::update()
{
	if (m_bIsInit)
	{
		if (!ActivityManager::GetInstancePtr()->IsInit())
		{
			setIsInit(false);
		}
		else
		{
			bool hasCompleted = ProfileUtils::HasCompletedLevel("egypt3", false, ProfileMgr::GetInstance().GetCurrentProfile());
			if (hasCompleted && m_bIsAlreadyLoadData && !CheckUniverseMap() && !CheckGame())
			{
				if (!m_bIsFirstInit)
				{
					m_bIsFirstInit = true;
					initButtonTurn();
				}
				if (!m_bIsPause)
				{
					Update_NewIcon();
				}
			}
		}
	}
}
