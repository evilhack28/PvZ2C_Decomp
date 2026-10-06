//
//  Timer.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-04.
//

#include "SexyAppFramework/Common.h"

#include "Timer.h"

/////////////// PvZ2::Utilities::Timer ///////////////

namespace PvZ2 { namespace Utilities
{

Timer::Timer()
{
}

Timer::Timer(pvztime_t i_timerLength, const TimeoutCallback& callback)
{
	SetCallback(callback);
	Reset(i_timerLength);
}

void Timer::Update()
{
	if (m_endTime > 0 && PVZ_IS_IT(m_endTime))
	{
		triggerCallback();
	}
}

void Timer::Reset()
{
	if (m_timerLength > 0)
	{
		m_endTime = PVZ_T() + m_timerLength;
	}
	else
	{
		m_endTime = -1;
	}
}

void Timer::Reset(pvztime_t i_newTimerLength)
{
	m_timerLength = i_newTimerLength;
	Reset();
}

void Timer::Clear()
{
	m_endTime = -1;
}

void Timer::SetCallback(const TimeoutCallback& callback)
{
	m_callback = callback;
}

void Timer::triggerCallback()
{
	if (m_callback)
	{
		m_callback();
	}
	Clear();
}

}}
