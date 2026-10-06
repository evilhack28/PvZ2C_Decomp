//
//  NetWorkEvent.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-04.
//

#include "gameNetWork/events/NetWorkEvent.h"

#include "gameNetWork/NetworkMgr.h"

NetWorkEvent::NetWorkEvent()
{
}

NetWorkEvent::~NetWorkEvent()
{
}

void NetWorkEvent::Update(long ms)
{
}

void NetWorkEvent::Init()
{
}

bool NetWorkEvent::IsTimeOut(long ms)
{
	m_nowGap += ms;

	if (NetworkMgr::Instance()->GetNetWorkProcess()->IsLogined())
	{
		if (m_nowGap > m_TimeGap)
		{
			m_nowGap = 0;
			return true;
		}
	}

	return false;
}
