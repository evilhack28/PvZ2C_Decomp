//
//  DaveTaskManager.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include "DaveTaskMgr.h"

/////////////// Accessors ///////////////

std::vector<DaveTask*>& DaveTaskManager::GetAllTasks()
{
	return m_daveTaskTasks;
}

void DaveTaskManager::SetIsEndLevelWin(bool i_isWin)
{
	m_isEndLevelWin = i_isWin;
}

bool DaveTaskManager::GetIsEndLevelWin()
{
	return m_isEndLevelWin;
}
