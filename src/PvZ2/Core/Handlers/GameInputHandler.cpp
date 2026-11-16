//
//  GameInputHandler.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-11.
//

#include "GameInputHandler.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

GameInputHandler::GameInputHandler()
{
}

GameInputHandler::~GameInputHandler()
{
}

/////////////// Touch ///////////////

void GameInputHandler::RegisterTouchGameplayObject(GameInputDelegate i_touchDelegate, const int i_priority, BoardEntityPtr i_boardEntity, CancelInputDelegate i_cancelDelegate)
{
	m_gameInputListeners.push_back(GameInputListenerInfo(i_touchDelegate, i_priority, i_boardEntity, i_cancelDelegate));
}

void GameInputHandler::UnregisterTouchGameplayObject(void* i_touchOwner)
{
	for (int i = 0; i < m_gameInputListeners.size(); i++)
	{
		if (m_gameInputListeners[i].m_touchDelegate.GetInstanceContext() == i_touchOwner)
		{
			m_gameInputListeners.erase(m_gameInputListeners.begin() + i);
			return;
		}
	}
}

void GameInputHandler::ChangePriority(void* i_touchOwner, const int i_priority)
{
	for (size_t i = 0; i < m_gameInputListeners.size(); i++)
	{
		GameInputListenerInfo& info = m_gameInputListeners[i];
		if (info.m_touchDelegate.GetInstanceContext() == i_touchOwner)
		{
			info.m_priority = i_priority;
			return;
		}
	}
}

bool GameInputHandler::OnGameplayTouchEvent(const Touch& i_touch)
{
	for (size_t i = 0; i < m_gameInputListeners.size(); i++)
	{
		if (m_gameInputListeners[i].m_boardEntity.IsValid())
		{
			m_gameInputListeners[i].m_renderOrder = m_gameInputListeners[i].m_boardEntity.Get()->CalcRenderOrder();
		}
	}

	std::sort(m_gameInputListeners.begin(), m_gameInputListeners.end());

	Touch touch = i_touch;
	bool handled = false;
	for (size_t i = 0; i < m_gameInputListeners.size(); i++)
	{
		if (m_gameInputListeners[i].m_touchDelegate(touch))
		{
			handled = true;
			if (touch.phase == TOUCH_ENDED)
			{
				touch.phase = TOUCH_CANCELED;
			}
			else if (touch.phase != TOUCH_CANCELED)
			{
				break;
			}
		}
	}
	return handled;
}

void GameInputHandler::CancelTouch(const Touch& i_touch, void* i_ignoredDelegateOwner)
{
	Touch touch = i_touch;
	touch.phase = TOUCH_CANCELED;
	for (size_t i = 0; i < m_gameInputListeners.size(); i++)
	{
		if (m_gameInputListeners[i].m_touchDelegate.GetInstanceContext() != i_ignoredDelegateOwner)
		{
			m_gameInputListeners[i].m_touchDelegate(touch);
		}
	}
}

void GameInputHandler::SendCancelDelegate()
{
	for (size_t i = 0; i < m_gameInputListeners.size(); i++)
	{
		if (m_gameInputListeners[i].m_cancelDelegate)
		{
			m_gameInputListeners[i].m_cancelDelegate();
		}
	}
}

/////////////// Gesture ///////////////

void GameInputHandler::RegisterGesture(GestureDelegate i_gestureDelegate)
{
	m_gestureListeners.push_back(i_gestureDelegate);
}

void GameInputHandler::UnregisterGesture(void* i_gestureOwner)
{
	for (int i = 0; i < m_gestureListeners.size(); i++)
	{
		if (m_gestureListeners[i].GetInstanceContext() == i_gestureOwner)
		{
			m_gestureListeners.erase(m_gestureListeners.begin() + i);
			return;
		}
	}
}

void GameInputHandler::OnGestureEvent(Point i_gestureLocation, int i_distanceBetweenFingersSquared, float i_scaleDelta)
{
	for (int i = 0; i < m_gestureListeners.size(); i++)
	{
		m_gestureListeners[i](i_gestureLocation, i_distanceBetweenFingersSquared, i_scaleDelta);
	}
}

/////////////// Long press ///////////////

void GameInputHandler::RegisterLongPress(LongPressDelegate i_longPressDelegate)
{
	m_longPressListeners.push_back(i_longPressDelegate);
}

void GameInputHandler::UnregisterLongPress(void* i_longPressOwner)
{
	for (int i = 0; i < m_longPressListeners.size(); i++)
	{
		if (m_longPressListeners[i].GetInstanceContext() == i_longPressOwner)
		{
			m_longPressListeners.erase(m_longPressListeners.begin() + i);
			return;
		}
	}
}

void GameInputHandler::OnLongPress(Point i_location)
{
	for (int i = 0; i < m_longPressListeners.size(); i++)
	{
		m_longPressListeners[i](i_location);
	}
}
