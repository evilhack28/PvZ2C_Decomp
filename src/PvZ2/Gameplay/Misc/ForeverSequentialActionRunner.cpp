//
//  ForeverSequentialActionRunner.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-21.
//

#include "SexyAppFramework/Common.h"

#include "SequentialActionRunner.h"

/////////////// Lifecycle ///////////////

ForeverSequentialActionRunner::ForeverSequentialActionRunner()
{
}

ForeverSequentialActionRunner::~ForeverSequentialActionRunner()
{
}

/////////////// Logic ///////////////

void ForeverSequentialActionRunner::onUpdate()
{
	processActions();
	deleteCompletedActions();
}

void ForeverSequentialActionRunner::deleteCompletedActions()
{
	while (!m_actions.empty() && m_actions.front()->IsFinished())
	{
		delete m_actions.front();
		m_actions.erase(m_actions.begin());
	}
}
