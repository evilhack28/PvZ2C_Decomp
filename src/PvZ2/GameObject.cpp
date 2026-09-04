//
//  GameObject.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-04.
//

#include "SexyAppFramework/Common.h"

#include "SexyAppFramework/ReflectionBuilder.h"

#include "GameObject.h"
#include "RtReflectionDelegate.h"
#include "GameEventMgr.h"

/////////////// GameObject ///////////////

RT_CLASS_IMPLEMENT(GameObject);

void GameObject::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(RtReflectionDelegateBase);
		REFLECTION_CLASSBUILDER_FIELD(RtId, m_objectId);
		REFLECTION_CLASSBUILDER_FIELD(std::string, m_methodName);
	REFLECTION_CLASSBUILDER_END(RtReflectionDelegateBase);

	REFLECTION_CLASSBUILDER_BEGIN(GameObject);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_FIELD_UNSAFE(RtWeakPtr<RtObject>, m_thisPtr);
	REFLECTION_CLASSBUILDER_END(GameObject);
}

GameObject::~GameObject()
{
}

bool GameObject::IsDestroyed() const
{
	return !m_thisPtr.IsValid();
}

void GameObject::registerForEvents()
{
}

void GameObject::onInitialized()
{
}

void GameObject::unregisterForEvents()
{
}

void GameObject::onPostLoad()
{
}

void GameObject::onDestroy()
{
}

void GameObject::initialize(RtId i_id)
{
	m_thisPtr = i_id;
	registerForEvents();
	onInitialized();
}

void GameObject::CallInitialize(RtId i_id)
{
	m_thisPtr = i_id;
}

void GameObject::Destroy()
{
	if (m_thisPtr.IsValid())
	{
		onDestroy();
		gMessageRouter->Unsubscribe(this);
		unregisterForEvents();

		RtWeakPtr<GameObject> thisPtr = m_thisPtr;
		m_thisPtr.ClearId();
		RtDb::GetDb()->ReleaseId(thisPtr);
	}
}

void GameObject::PostLoad()
{
	RtDb::GetDb()->SetObjectDeletionMode(m_thisPtr, RtDbTable::ODM_Deferred);
	registerForEvents();
	onPostLoad();
}

GameObject* GameObject::Create(RtClass* i_class, PVZDB::TableIndex i_inTable)
{
	GameObject* newObject = i_class->New()->CastChecked<GameObject>();

	RtId id;
	if (i_inTable != PVZDB::TABLE_INVALID)
	{
		id = PVZDB::GetInstance().GetTable(i_inTable)->AllocId(newObject, RtDbTable::ODM_Deferred, true, NULL);
	}

	newObject->initialize(id);
	return newObject;
}

bool GameObject::Serialize(const RtSerializeContext& inContext)
{
	{
		RtSerialRtonSync* sync = inContext.GetSync();
		RtSerialRtonKey key("objdata");
		RtSerializeContext objContext(sync, key);
		RtObject::Serialize(objContext);
	}

	if (inContext.GetSync()->IsReading())
	{
		gMessageRouter->Broadcast(Message::GameObjectSerializedIn, this);
	}

	return true;
}

namespace Message
{
	void GameObjectSerializedIn(GameObject* i_object)
	{
	}
}
