//
//  GameInputListenerInfo.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-05.
//

#include "SexyAppFramework/Common.h"

#include "GameInputHandler.h"

/////////////// Lifecycle ///////////////

GameInputListenerInfo::GameInputListenerInfo(GameInputDelegate i_touchDelegate, const int i_priority, BoardEntityPtr i_boardEntity, CancelInputDelegate i_cancelDelegate)
{
	DBG_ASSERT(i_touchDelegate != GameInputDelegate());
	DBG_ASSERT(i_priority >= 0);

	m_touchDelegate = i_touchDelegate;
	m_cancelDelegate = i_cancelDelegate;
	m_priority = i_priority;
	m_boardEntity = i_boardEntity;
	m_renderOrder = 0;
}

GameInputListenerInfo::GameInputListenerInfo(const GameInputListenerInfo&) = default;

GameInputListenerInfo::GameInputListenerInfo(GameInputListenerInfo&&) = default;

GameInputListenerInfo::~GameInputListenerInfo() = default;

GameInputListenerInfo& GameInputListenerInfo::operator=(GameInputListenerInfo&&) = default;

/////////////// Logic ///////////////

bool GameInputListenerInfo::operator<(const GameInputListenerInfo& i_rhs) const
{
	if (m_priority == i_rhs.m_priority && m_boardEntity.IsValid())
		return m_renderOrder > i_rhs.m_renderOrder;
	return m_priority > i_rhs.m_priority;
}

bool GameInputListenerInfo::operator==(const GameInputListenerInfo& i_rhs) const
{
	return m_priority == i_rhs.m_priority && m_renderOrder == i_rhs.m_renderOrder;
}
