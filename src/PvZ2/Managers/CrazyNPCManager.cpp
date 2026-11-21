//
//  CrazyNPCManager.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "CrazyNPCManager.h"
#include "CrazyNPC.h"

void CrazyNPCManager::initLoadingResourcesGroupList()
{
}

void CrazyNPCManager::stopSound()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CrazyNPCManager);

#include "CrazyNPCManager.h"
void CrazyNPCManager::ForceEndNarrative()
{
	 CrazyNPCManager::finishNarrative();
}

void CrazyNPCManager::addToLoadingResourcesGroupList(const std::string& i_groupName)
{
}

void CrazyNPCManager::FinisAllTalking()
{
	stopAllTalking();
	finishNarrative();
}

void CrazyNPCManager::setStateHelper(const StateDefinition<CrazyNPCManagerState>& i_newStateDefinition)
{
	if (m_stateMachine.SetState(i_newStateDefinition))
	{
		m_stateEnterTime = PVZ_T();
	}
}

void CrazyNPCManager::stopAllTalking()
{
	for (size_t i = 0; i < m_activeNPCs.size(); i++)
	{
		m_activeNPCs[i]->StopTalking();
	}
}

void CrazyNPCManager::finishNarrative()
{
	for (size_t i = 0; i < m_activeNPCs.size(); i++)
	{
		if (!m_activeNPCs[i]->IsLeaving())
		{
			m_activeNPCs[i]->Leave();
		}
	}
}
