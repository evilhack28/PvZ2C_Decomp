//
//  RunnableAction.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "SexyAppFramework/Common.h"

#include "RunnableAction.h"

/////////////// RunnableAction ///////////////

RunnableAction::RunnableAction()
	: m_runnableActionState(NotStarted)
{
}

void RunnableAction::Begin()
{
	DBG_ASSERT(NotStarted == m_runnableActionState);
	m_runnableActionState = Running;
	onBegin();
}

void RunnableAction::Update()
{
	DBG_ASSERT(Running == m_runnableActionState);
	onUpdate();
}

void RunnableAction::End()
{
	DBG_ASSERT(Finished != m_runnableActionState);
	onEnd();
	m_runnableActionState = Finished;
}

void RunnableAction::onBegin()
{
}

void RunnableAction::onUpdate()
{
}

void RunnableAction::onEnd()
{
}
