//
//  SequentialActionRunner.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "SequentialActionRunner.h"

/////////////// Lifecycle ///////////////

SequentialActionRunner::SequentialActionRunner()
{
}

SequentialActionRunner::~SequentialActionRunner()
{
	EndAllActions();
	for (std::vector<RunnableAction*>::iterator it = m_actions.begin(), end = m_actions.end(); it != end; ++it)
	{
		delete *it;
	}
	m_actions.clear();
}

/////////////// Accessors ///////////////

bool SequentialActionRunner::IsEmpty() const
{
	return m_actions.empty();
}

/////////////// Logic ///////////////

void SequentialActionRunner::onBegin()
{
}

RunnableAction* SequentialActionRunner::Add(RunnableAction* i_action)
{
	m_actions.push_back(i_action);
	return i_action;
}

void SequentialActionRunner::EndAllActions()
{
	for (std::vector<RunnableAction*>::iterator it = m_actions.begin(), end = m_actions.end(); it != end; ++it)
	{
		RunnableAction* action = *it;
		if (!action->IsFinished())
		{
			action->End();
		}
	}
}

int SequentialActionRunner::Size() const
{
	return m_actions.size();
}

void SequentialActionRunner::onUpdate()
{
	processActions();
	if (!IsRunning())
	{
		return;
	}
	if (m_actions.empty() || m_actions.back()->IsFinished())
	{
		End();
	}
}

void SequentialActionRunner::onEnd()
{
	EndAllActions();
}

void SequentialActionRunner::processActions()
{
	for (std::vector<RunnableAction*>::iterator it = m_actions.begin(), end = m_actions.end(); it != end; ++it)
	{
		RunnableAction* action = *it;
		if (!action->IsStarted())
		{
			action->Begin();
		}
		if (action->IsRunning())
		{
			action->Update();
		}
		if (!action->IsFinished())
		{
			break;
		}
	}
}
