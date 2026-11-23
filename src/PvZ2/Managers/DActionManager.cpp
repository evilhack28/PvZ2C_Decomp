//
//  DActionManager.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-23.
//

#include "SexyAppFramework/Common.h"

#include "DNode/DAction.h"

/////////////// Update ///////////////

void DActionManager::update(float dt)
{
	m_isInLoop = true;
	if (m_actionMap.size() != 0)
	{
		for (auto it = m_actionMap.begin(); it != m_actionMap.end();)
		{
			DArray<DAction*>& actionList = (*it).second.actionList;
			for (auto actionIt = actionList.begin(); actionIt != actionList.end(); ++actionIt)
			{
				DAction* action = *actionIt;
				action->update(dt);
				if (action->isDone())
					m_actionDelayList.push_back(DActionDelay(action, NULL, DActionDelay::REMOVE_BY_ACTION));
			}
			if (actionList.size() == 0)
				m_actionMap.erase(it++);
			else
				++it;
		}
	}
	m_isInLoop = false;
	auto delayIt = m_actionDelayList.begin();
	auto delayEnd = m_actionDelayList.end();
	for (; delayIt != delayEnd; ++delayIt)
	{
		if ((*delayIt).type == DActionDelay::ADD_ACTION)
			addAction((*delayIt).action, (*delayIt).target);
		else if ((*delayIt).type == DActionDelay::REMOVE_BY_ACTION)
			removeAction((*delayIt).action);
		else if ((*delayIt).type == DActionDelay::REMOVE_BY_TARGET)
			removeAllActionFromTarget((*delayIt).target);
	}
	m_actionDelayList.clear();
}
