//
//  TimeLine.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-03.
//

#include "SexyAppFramework/Common.h"

#include "RtObject.h"
#include "TimeLine.h"

/////////////// Lifecycle ///////////////

TimeLine::TimeLine()
: m_currTime(0.0)
, m_needSort(false)
{}

TimeLine::~TimeLine() {}

TimeLine::TimeLine(const TimeLine& i_other)
: m_currTime(i_other.m_currTime)
, m_events(i_other.m_events)
, m_needSort(i_other.m_needSort)
{}

/////////////// Events ///////////////

void TimeLine::Initialize(pvztime_t i_startTime)
{
	m_currTime = i_startTime;
	m_events.clear();
}

void TimeLine::AddEvent(pvztime_t i_atTime, TimeLineEventCallback i_eventCallback)
{
	TimeLineEvent newEvent(i_atTime, i_eventCallback);
	AddEvent(newEvent);
}

void TimeLine::AddEvent(const TimeLineEvent& i_event)
{
	if (m_events.size() > 0 && i_event.Time < m_events.back().Time)
		m_needSort = true;

	m_events.push_back(i_event);
}

void TimeLine::Update(pvztime_t i_dt)
{
	if (m_needSort)
	{
		auto sortEarliestToLatest = [](const TimeLineEvent& a, const TimeLineEvent& b) { return a.Time < b.Time; };
		std::sort(m_events.begin(), m_events.end(), sortEarliestToLatest);
		m_needSort = false;
	}

	Updater updater(*this, i_dt);
	while (!updater.IsDone())
	{
		updater.Progress();
		updater.FireEvent(*(volatile bool*)&updater.m_stoppedAtEvent);
	}
}


/////////////// Updater ///////////////

void TimeLine::Updater::Progress()
{
	if (m_stoppedAtEvent)
	{
		m_timeLine.m_events.pop_front();
		m_stoppedAtEvent = false;
	}
	const int numEvents = (int)m_timeLine.m_events.size();
	if (numEvents == 0)
	{
		float rem = m_remainingDt;
		m_lastStep = rem;
		m_timeLine.m_currTime = m_timeLine.m_currTime + rem;
		m_remainingDt = 0.0f;
		return;
	}
	const TimeLineEvent& nextEvent = m_timeLine.m_events.front();
	float curr = m_timeLine.m_currTime;
	float rem = m_remainingDt;
	float sum = curr + rem;
	if (sum >= nextEvent.Time)
	{
		float step = nextEvent.Time - curr;
		m_stoppedAtEvent = true;
		m_lastStep = step;
		m_timeLine.m_currTime = step + curr;
		m_remainingDt = rem - step;
		return;
	}
	m_lastStep = rem;
	m_timeLine.m_currTime = sum;
	m_remainingDt = 0.0f;
}
