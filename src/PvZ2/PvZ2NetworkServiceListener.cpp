//
//  PvZ2NetworkServiceListener.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "SexyAppFramework/Common.h"

#include "PvZ2NetworkServiceListener.h"
#include "TimeMgr.h"

/////////////// PvZ2NetworkServiceListener ///////////////

PvZ2NetworkServiceListener::PvZ2NetworkServiceListener()
{
	m_lastSet = TimeMgr::GetInstancePtr()->m_realT;
	m_blocked = false;
}

void PvZ2NetworkServiceListener::SetBlocked()
{
	if (!m_blocked)
	{
		m_lastSet = TimeMgr::GetInstancePtr()->m_realT;
	}
	m_blocked = true;
}

bool PvZ2NetworkServiceListener::IsBlocked()
{
	if (m_blocked && TimeMgr::GetInstancePtr()->m_realT >= m_lastSet + 5.0f)
	{
		SetBlocked();
	}
	return m_blocked;
}

bool PvZ2NetworkServiceListener::isMyRequest(const void* context)
{
	return context == this;
}

void PvZ2NetworkServiceListener::logFailMessage(const std::string& requestType, const Sexy::StructuredData* response)
{
	m_blocked = false;
}

void PvZ2NetworkServiceListener::logSuccessMessage(const std::string& requestType, const Sexy::StructuredData* response)
{
	m_blocked = false;
}
