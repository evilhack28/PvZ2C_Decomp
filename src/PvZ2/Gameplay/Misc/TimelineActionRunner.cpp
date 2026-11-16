//
//  TimelineActionRunner.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "TimelineActionRunner.h"

/////////////// Lifecycle ///////////////

TimelineActionRunner::TimelineActionRunner()
{
	m_startTime = PVZ_EOT();
}

TimelineActionRunner::~TimelineActionRunner()
{
	EndAllActions();
	for (TimelineActionRunnerEvent& event : m_events)
		delete event.Action;
}

/////////////// Accessors ///////////////

bool TimelineActionRunner::IsEmpty() const
{
	return m_events.empty();
}

/////////////// Logic ///////////////

RunnableAction* TimelineActionRunner::Add(RunnableAction* i_action)
{
	return Add(i_action, 0.0f);
}

RunnableAction* TimelineActionRunner::Add(RunnableAction* i_action, pvztime_t i_startDelaySeconds)
{
	m_events.push_back(TimelineActionRunnerEvent(i_action, i_startDelaySeconds));
	return i_action;
}

void TimelineActionRunner::EndAllActions()
{
	for (TimelineActionRunnerEvent& event : m_events)
	{
		if (!event.Action->IsFinished())
			event.Action->End();
	}
}

int TimelineActionRunner::Size() const
{
	return (int)m_events.size();
}

void TimelineActionRunner::onBegin()
{
	m_startTime = PVZ_T();
}

void TimelineActionRunner::onUpdate()
{
	pvztime_t elapsed = PVZ_T() - m_startTime;
	for (TimelineActionRunnerEvent& event : m_events)
	{
		RunnableAction* action = event.Action;
		unsigned started = action->IsStarted();
		pvztime_t start = event.StartTimeSeconds;
		unsigned due = elapsed >= start;
		if (started < due)
			action->Begin();
		if (action->IsRunning())
			action->Update();
	}
	if (IsRunning() && allActionsAreFinished())
		End();
}

void TimelineActionRunner::onEnd()
{
	EndAllActions();
}

bool TimelineActionRunner::allActionsAreFinished()
{
	for (TimelineActionRunnerEvent& event : m_events)
	{
		if (!event.Action->IsFinished())
			return false;
	}
	return true;
}
