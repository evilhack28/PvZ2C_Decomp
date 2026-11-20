//
//  MessageRouter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-20.
//

#include "SexyAppFramework/Common.h"

#include "GameEventMgr.h"

/////////////// Subscription ///////////////

void MessageRouter::Subscribe(void (*message)(void), const Sexy::Delegate0 &listener)
{
	queueInsert((void*)message, listener);
}

void MessageRouter::Unsubscribe(void (*message)(void), const Sexy::Delegate0 &listener)
{
	queueRemove((void*)message, listener);
}

void MessageRouter::Unsubscribe(void *listener)
{
	queueRemove(listener);
}

int MessageRouter::SubscriberCount(void *message)
{
	return m_routingTable[message].size();
}

/////////////// Queueing ///////////////

void MessageRouter::queueInsert(void *message, const Sexy::Delegate0 &listener)
{
	if (m_postCount == 0)
		insert(message, listener);
	else
		m_queuedRequests.push_back(AddRemoveRequest(AddRemoveRequest::Add, message, listener));
}

void MessageRouter::queueRemove(void *message, const Sexy::Delegate0 &listener)
{
	if (m_postCount == 0)
		remove(message, listener);
	else
		m_queuedRequests.push_back(AddRemoveRequest(AddRemoveRequest::RemoveDelegate, message, listener));
}

void MessageRouter::queueRemove(void *listener)
{
	if (m_postCount == 0)
		remove(listener);
	else
		m_queuedRequests.push_back(AddRemoveRequest(AddRemoveRequest::RemoveObject, listener));
}

/////////////// Dispatch ///////////////

void MessageRouter::Broadcast(void (*message)(void))
{
	dispatch(getTable((void*)message));
}

void MessageRouter::SendTo(RtWeakPtr<RtObject> object, void (*message)(void))
{
	dispatch(getTableForTarget(object, (void*)message));
}

void MessageRouter::dispatch(const std::vector<Sexy::Delegate0> &table)
{
	++m_postCount;
	for (const auto &target : table)
	{
		if (isDelegateValid(target))
			target();
	}
	--m_postCount;

	if (m_postCount == 0)
		addAndRemoveSubscribers();
}

void MessageRouter::addAndRemoveSubscribers()
{
	for (const auto &request : m_queuedRequests)
	{
		switch (request.Action)
		{
		case AddRemoveRequest::Add:
			insert(request.Message, request.ObserverDelegate);
			break;
		case AddRemoveRequest::RemoveDelegate:
			remove(request.Message, request.ObserverDelegate);
			break;
		case AddRemoveRequest::RemoveObject:
			remove(request.ObserverObject);
			break;
		}
	}

	m_queuedRequests.clear();
}

bool MessageRouter::isDelegateValid(const Sexy::Delegate0& rDelegate) const
{
	for (const auto &request : m_queuedRequests)
	{
		switch (request.Action)
		{
		case AddRemoveRequest::RemoveDelegate:
			if (request.ObserverDelegate == rDelegate)
				return false;
			break;
		case AddRemoveRequest::RemoveObject:
			if (request.ObserverObject == rDelegate.GetInstanceContext())
				return false;
			break;
		}
	}

	return true;
}

void MessageRouter::insert(void *message, const Sexy::Delegate0 &listener)
{
	std::vector<Sexy::Delegate0> &aTable = m_routingTable[message];
	if (std::find(aTable.begin(), aTable.end(), listener) == aTable.end())
	{
		aTable.reserve(aTable.size() + 1);
		aTable.push_back(listener);

		if (listener.GetInstanceContext() != nullptr)
			m_targettedRoutingTables[listener.GetInstanceContext()][message].push_back(listener);
	}
}

void MessageRouter::remove(void *message, const Sexy::Delegate0 &listener)
{
	std::vector<Sexy::Delegate0> &aTable = m_routingTable[message];
	std::vector<Sexy::Delegate0>::iterator anIt = std::find(aTable.begin(), aTable.end(), listener);
	if (anIt != aTable.end())
		aTable.erase(anIt);

	if (listener.GetInstanceContext() != nullptr)
	{
		std::vector<Sexy::Delegate0> &aTargetTable = m_targettedRoutingTables[listener.GetInstanceContext()][(void*)message];
		anIt = std::find(aTargetTable.begin(), aTargetTable.end(), listener);
		if (anIt != aTargetTable.end())
			aTargetTable.erase(anIt);
	}
}

void MessageRouter::remove(void *message, void *listener)
{
	std::vector<Sexy::Delegate0> &aTable = m_routingTable[message];
	aTable.erase(std::remove_if(std::begin(aTable), std::end(aTable), [listener](const Sexy::Delegate0 &d) { return d.GetInstanceContext() == listener; }), std::end(aTable));
}
