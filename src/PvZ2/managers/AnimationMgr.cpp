//
//  AnimationMgr.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-07.
//

#include "SexyAppFramework/Common.h"

#include "AnimationMgr.h"
#include "TimeMgr.h"
#include "ObjectTypeDescriptor.h"

/////////////// RemovePredicate ///////////////

struct RemovePredicate
{
	RemovePredicate(pvztime_t i_time) : m_time(i_time) {}

	bool operator()(AnimationController* i_controller);

	pvztime_t m_time;
};

bool RemovePredicate::operator()(AnimationController* i_controller)
{
	bool done = i_controller->IsAnimDone(m_time);
	if (done && i_controller->DeleteWhenDone())
		i_controller->Destroy();
	return done;
}

static bool DeleteController(AnimationController* i_controller)
{
	if (i_controller->DeleteWhenDone())
		i_controller->Destroy();
	return true;
}

static void DeleteAll(std::vector<AnimationControllerWkPtr>::iterator i_begin, std::vector<AnimationControllerWkPtr>::iterator i_end)
{
	for (; i_begin != i_end; ++i_begin)
		DeleteController(*i_begin);
}

/////////////// AnimationMgr ///////////////

RT_CLASS_IMPLEMENT(AnimationMgr);

AnimationMgr::AnimationMgr()
	: m_time(0.f)
	, m_pause(false)
	, m_removing(false)
{
}

AnimationMgr::~AnimationMgr()
{
}

AnimationMgr* AnimationMgr::Create()
{
	return GameObject::Create<AnimationMgr>(PVZDB::TABLE_GAMEOBJECTS);
}

void AnimationMgr::onInitialized()
{
	m_time = 0.f;
	m_pause = false;
	m_removing = false;
}

bool AnimationMgr::Serialize(const RtSerializeContext& inContext)
{
	return GameObject::Serialize(inContext);
}

AnimationMgr* AnimationMgr::Add(AnimationController* i_motion)
{
	return Add(i_motion, m_time);
}

AnimationMgr* AnimationMgr::Add(AnimationController* i_motion, pvztime_t i_startTime)
{
	pvztime_t notUsed;
	return Add(i_motion, i_startTime, notUsed);
}

AnimationMgr* AnimationMgr::Add(AnimationController* i_motion, pvztime_t i_startTime, pvztime_t& o_endTime)
{
	Add(AnimationControllerWkPtr(i_motion->GetPtr()), i_startTime, o_endTime);
	return this;
}

void AnimationMgr::Add(AnimationControllerWkPtr i_motion)
{
	Add(i_motion, m_time);
}

void AnimationMgr::Add(AnimationControllerWkPtr i_motion, pvztime_t i_startTime)
{
	pvztime_t notUsed;
	Add(i_motion, i_startTime, notUsed);
}

void AnimationMgr::Update()
{
	if (m_pause)
		return;

	for (AnimationControllerIterator it = m_animationControllers.begin(); it != m_animationControllers.end(); ++it)
	{
		AnimationController* controller = *it;
		if (controller && controller->ShouldUpdate(m_time))
			controller->Update(m_time);
	}

	if (m_animationControllers.size() != 0)
	{
		m_removing = true;
		AnimationControllerIterator newEnd = std::remove_if(m_animationControllers.begin(), m_animationControllers.end(), RemovePredicate(m_time));
		if (newEnd != m_animationControllers.end())
			m_animationControllers.erase(newEnd, m_animationControllers.end());
		m_removing = false;
	}

	m_time += TimeMgr::GetInstancePtr()->Dt();
}

void AnimationMgr::AddToRenderQueue(RenderQueue* i_queue)
{
	if (m_pause)
		return;

	for (AnimationControllerIterator it = m_animationControllers.begin(); it != m_animationControllers.end(); ++it)
	{
		AnimationController* controller = *it;
		if (controller->ShouldUpdate(m_time))
			controller->AddToRenderQueue(i_queue);
	}
}

void AnimationMgr::InnerDraw(Graphics* i_g)
{
	if (m_pause)
		return;

	for (AnimationControllerIterator it = m_animationControllers.begin(); it != m_animationControllers.end(); ++it)
	{
		AnimationController* controller = *it;
		if (controller->ShouldUpdate(m_time))
			controller->InnerDraw(i_g);
	}
}

void AnimationMgr::Add(AnimationControllerWkPtr i_motion, pvztime_t i_startTime, pvztime_t& o_endTime)
{
	if (std::find(m_animationControllers.begin(), m_animationControllers.end(), i_motion) != m_animationControllers.end())
		return;

	i_motion->SetStartTime(i_startTime);
	o_endTime = i_motion->GetEndTime();
	m_animationControllers.push_back(i_motion);
}

void AnimationMgr::Clear()
{
	AnimationControllerIterator it = m_animationControllers.begin();
	AnimationControllerIterator end = m_animationControllers.end();
	DeleteAll(it, end);
	m_animationControllers.clear();
}

void AnimationMgr::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(AnimationMgr);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GameObject);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_time);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_pause);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_removing);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<AnimationControllerWkPtr>, m_animationControllers);
	REFLECTION_CLASSBUILDER_END(AnimationMgr);
}
