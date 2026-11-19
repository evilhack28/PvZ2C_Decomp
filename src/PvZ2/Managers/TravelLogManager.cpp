//
//  TravelLogManager.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include "TravelLogMgr.h"

/////////////// Accessors ///////////////

std::vector<TravelLogTask*>& TravelLogManager::GetAllTasks()
{
	return m_TravelLogTasks;
}

void TravelLogManager::SetChipLock(bool i_flag)
{
	m_TaskChipLock = i_flag;
}

bool TravelLogManager::GetChipLock()
{
	return m_TaskChipLock;
}
