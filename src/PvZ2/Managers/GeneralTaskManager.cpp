//
//  GeneralTaskManager.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-05.
//

#include "SexyAppFramework/Common.h"

#include "GeneralTaskMgr.h"
#include "GeneralTask.h"

/////////////// Lifecycle ///////////////

GeneralTaskManager::GeneralTaskManager()
{
	m_Tasks.clear();
}

GeneralTaskManager::~GeneralTaskManager()
{
	ClearAllTasks();
}

void GeneralTaskManager::Initialize()
{
	LoadConfig();
	FilterTask();
	CreatTask();
}

/////////////// Tasks ///////////////

GeneralTask* GeneralTaskManager::GetTaskByID(int i_id)
{
	for (std::vector<GeneralTask*>::iterator it = m_Tasks.begin(); it != m_Tasks.end(); ++it)
	{
		if ((*it)->TaskConfig->ID == i_id)
			return *it;
	}
	return NULL;
}

std::vector<GeneralTask*>& GeneralTaskManager::GetAllTasks()
{
	return m_Tasks;
}

void GeneralTaskManager::ClearAllTasks()
{
	std::vector<GeneralTask*>::iterator it = m_Tasks.begin();
	while (it != m_Tasks.end())
	{
		GeneralTask* task = *it;
		if (task)
		{
			it = m_Tasks.erase(it);
			delete task;
		}
		else
			++it;
	}
}

bool GeneralTaskManager::HaveCompletedTask()
{
	for (size_t i = 0; i < m_Tasks.size(); i++)
	{
		if (m_Tasks[i]->CurrentState == 2)
			return true;
	}
	return false;
}
