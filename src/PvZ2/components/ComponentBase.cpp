//
//  ComponentBase.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-02.
//

#include "ComponentBase.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ComponentBase);
void ComponentBase::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ComponentBase);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GameObject);

	REFLECTION_CLASSBUILDER_END(ComponentBase);
}

ComponentBase::ComponentBase()
	: m_state(COMPONENTSTATE_NotStarted)
	, m_initialized(false)
	, m_owner(nullptr)
{
}

ComponentBase::~ComponentBase()
{
}

void ComponentBase::onBegin()
{
}

void ComponentBase::onUpdate()
{
}

void ComponentBase::onDraw(Sexy::Graphics* i_g)
{
}

void ComponentBase::onEnd()
{
}

void ComponentBase::SetOwner(BoardEntityPtr i_owner)
{
	m_owner = i_owner;
}

BoardEntityPtr ComponentBase::GetOwner()
{
	return m_owner;
}

void ComponentBase::SetName(const std::string& i_name)
{
	m_name = i_name;
}

void ComponentBase::Initialize()
{
	if (m_initialized)
	{
		return;
	}

	registerForEvents();

	m_initialized = true;
}

void ComponentBase::Uninitialize()
{
	if (m_initialized == false)
	{
		return;
	}

	unregisterForEvents();

	m_initialized = false;
}

void ComponentBase::Begin()
{
	DBG_ASSERT(COMPONENTSTATE_NotStarted == m_state);
	Initialize();
	onBegin();
	m_state = COMPONENTSTATE_Running;
}

void ComponentBase::Update()
{
	//DBG_ASSERT(COMPONENTSTATE_Running == m_state);
	onUpdate();
}

void ComponentBase::Draw(Sexy::Graphics* i_g)
{
	//DBG_ASSERT(COMPONENTSTATE_Running == m_state);
	onDraw(i_g);
}

void ComponentBase::End()
{
	DBG_ASSERT(COMPONENTSTATE_Finished != m_state);
	onEnd();
	Uninitialize();
	m_state = COMPONENTSTATE_Finished;
}
