//
//  DTimerManager.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-20.
//

#include "SexyAppFramework/Common.h"

#include <sys/time.h>
#include <cmath>
#include <algorithm>

#include "DNode/DTimer.h"
#include "DNode/DAction.h"
#include "TimeMgr.h"

/////////////// Lifecycle ///////////////

DTimerManager::DTimerManager() : m_nextDeltaTimeZero(false), m_bPause(false)
{
	m_pActionManager = new DActionManager();
	m_lastUpdate = (struct timeval*)operator new(sizeof(struct timeval));
}

DTimerManager::~DTimerManager()
{
	delete m_pActionManager;
	if (m_lastUpdate)
		operator delete(m_lastUpdate);
}

DTimerManager* DTimerManager::getInstane()
{
	if (s_pTimeManager)
		return s_pTimeManager;

	s_pTimeManager = new DTimerManager();
	return s_pTimeManager;
}

void DTimerManager::purge()
{
	if (s_pTimeManager)
	{
		delete s_pTimeManager;
		s_pTimeManager = nullptr;
	}
}

/////////////// Update ///////////////

void DTimerManager::update()
{
	if (isPause())
		return;

	updateTimer(PVZ_RealDt());
	m_pActionManager->update(PVZ_Dt());
}

void DTimerManager::setPause(bool pause)
{
	if (m_bPause != pause)
	{
		m_bPause = pause;
		if (!pause)
		{
			m_nextDeltaTimeZero = true;
			m_deltaTime = 0.0f;
		}
	}
}

/////////////// Timers ///////////////

void DTimerManager::addTimer(const std::string& name, const std::function<void(float dt)>& fun, float time, size_t repeatTime)
{
	DTimerElement element;
	element.endTime = time;
	element.callback = fun;
	element.repeatTime = repeatTime;
	m_schedule[name] = element;
}

void DTimerManager::setTimer(const std::string& name, float time, size_t repeatTime)
{
	std::map<std::string, DTimerElement>::iterator it = m_schedule.find(name);
	if (it != m_schedule.end())
	{
		if (m_currentTimer == name)
		{
			(*it).second.needChanged = true;
			(*it).second.newEndTime = time;
			(*it).second.newRepeatTime = repeatTime;
		}
		else
		{
			(*it).second.needChanged = false;
			(*it).second.startTime = 0;
			(*it).second.endTime = time;
			(*it).second.repeatTime = repeatTime;
		}
	}
}

void DTimerManager::removeTimer(const std::string& name)
{
	std::map<std::string, DTimerElement>::iterator it = m_schedule.find(name);
	if (it != m_schedule.end())
	{
		if (m_currentTimer == name)
			m_currentTimerIsDead = true;
		else
			m_schedule.erase(it);
	}
}
