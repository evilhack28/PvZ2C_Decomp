//
//  TimeMgr.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "TimeMgr.h"
#include "GameEventMgr.h"

TimeMgr::TimeMgr()
{
}

TimeMgr::~TimeMgr()
{
}

void TimeMgr::Init()
{
    m_timeScale = 1.0f;
    m_timeCurrent = m_timeStart = Sexy::SexyTime();
    m_paused = false;
    m_pauseAfterUpdateCount = 0;
    m_virtualizedT = 0.0f;
    m_gameOnlyPause = false;
    m_realT = 0.0f;
    m_overrideDelta = 0;
    m_cinematicT = 0.0f;
    m_frames = 0;
    m_cinematicDt = 0.0f;
    m_accumDT = 0.0f;
    m_fixedSPF = -1.0f;
    m_maxInterval = 15.0f;
}

void TimeMgr::SetT(pvztime_t i_newTime)
{
    m_virtualizedT = i_newTime;
}

void TimeMgr::PauseGameOnly(bool i_pause)
{
    m_gameOnlyPause = i_pause;
}

bool TimeMgr::GameIsPause()
{
    return m_gameOnlyPause;
}

void TimeMgr::SetFixedSPF(pvztime_t fVal)
{
    m_fixedSPF = fVal;
}

time_t TimeMgr::GetDate()
{
    return time(NULL) + m_overrideDelta;
}

void TimeMgr::SetDateOverride(time_t i_date)
{
    m_overrideDelta = i_date - time(NULL);
}

void TimeMgr::ClearDateOverride()
{
    SetDateOverride(0);
}

void TimeMgr::Update()
{
    if (m_pauseAfterUpdateCount != 0)
    {
        if (m_pauseAfterUpdateCount == 1)
        {
            m_pauseAfterUpdateCount = 2;
        }
        else if (m_pauseAfterUpdateCount == 2)
        {
            m_pauseAfterUpdateCount = 0;
            Pause(true);
        }
    }

    m_realDt = (float)(Sexy::SexyTime() - m_timeCurrent) * 0.001f;
    m_timeCurrent = Sexy::SexyTime();
    m_frames++;
    m_accumDT += m_realDt;
    if (m_accumDT > 0.1)
    {
        m_currentFPS = (float)m_frames / m_accumDT;
        m_frames = 0;
        m_accumDT = 0.0f;
    }

    if (m_realDt > m_maxInterval)
    {
        gMessageRouter->Post(&Message::NotifyReachMaxInterval);
    }
    if (m_realDt > 0.04f)
    {
        m_realDt = 0.04f;
    }

    if (IsPaused())
    {
        m_virtualizedDt = 0.0f;
        m_cinematicDt = 0.0f;
        m_realT += m_realDt;
        return;
    }

    float dt;
    float cinematicDt = m_realDt * m_timeScale;
    if (m_gameOnlyPause)
    {
        dt = 0.0f;
    }
    else if (m_fixedSPF > 0.0f)
    {
        if (m_realDt < m_fixedSPF)
        {
            float ms = (m_fixedSPF - m_realDt) * 1000.0f;
            if (ms > 1.0f)
            {
                Sexy::SexySleep((uint32)ms);
            }
        }
        dt = m_fixedSPF * m_timeScale;
        cinematicDt = m_realDt * m_timeScale;
    }
    else
    {
        dt = cinematicDt;
    }
    m_virtualizedDt = dt;
    m_cinematicDt = cinematicDt;
    m_virtualizedT += dt;
    m_realT += m_realDt;
    m_cinematicT += cinematicDt;
    if (dt != 0.0f)
    {
        m_virtualizedInvDt = 1.0f / dt;
    }
}
