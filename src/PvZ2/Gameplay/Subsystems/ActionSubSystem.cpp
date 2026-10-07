//
//  ActionSubSystem.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ActionSubSystem.h"
#include "GameCommon.h"
#include "ReflectionBuilder.h"
#include "PopAnimRig.h"
#include "Zombie.h"
#include "Plant.h"

/////////////// ActionSubSystem ///////////////

void ActionSubSystem::registerForEvents()
{
}

ActionSubSystem::ActionSubSystem()
{
}

RT_CLASS_IMPLEMENT(ActionSubSystem);

void ActionSubSystem::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ActionSubSystem);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GameSubSystem);

	REFLECTION_CLASSBUILDER_END(ActionSubSystem);
}

void ActionSubSystem::onInitialized()
{
}

ActionSubSystem::~ActionSubSystem()
{
	std::for_each(m_Actions.begin(), m_Actions.end(), [](ActionBase* action){ delete action; });
	std::for_each(m_newActions.begin(), m_newActions.end(), [](ActionBase* action){ delete action; });
	m_Actions.clear();
	m_newActions.clear();
}

void ActionSubSystem::Update()
{
	SuperClass::Update();

	const pvztime_t dt = PVZ_Dt();

	m_Actions.insert(m_Actions.end(), m_newActions.begin(), m_newActions.end());
	m_newActions.clear();

	for (int i = static_cast<int>(m_Actions.size()) - 1; i >= 0; --i)
	{
		ActionBase* action = m_Actions[i];
		if (action)
		{
			action->step(dt);
			if (action->isDone())
			{
				action->stop();
				if (action->_callback)
					action->_callback.GetDelegate()(action->_target);
				m_Actions.erase(m_Actions.begin() + i);
				delete action;
				action = nullptr;
			}
		}
	}
}

void ActionSubSystem::AddActionMoveTo(RealObjectPtr target, float duration, const SexyVector3& position, ActionSubSystemCallback i_callback)
{
	ActionMoveTo* newAction = new ActionMoveTo();
	newAction->InitWithTarget(target, duration, position);
	newAction->_callback = i_callback;
	m_newActions.push_back(newAction);
}

void ActionSubSystem::AddActionBezierBy(RealObjectPtr target, float duration, const ccBezierConfig& i_config, ActionSubSystemCallback i_callback)
{
	ActionBezierBy* newAction = new ActionBezierBy();
	newAction->InitWithTarget(target, duration, i_config);
	newAction->_callback = i_callback;
	m_newActions.push_back(newAction);
}

void ActionSubSystem::AddActionBezierTo(RealObjectPtr target, float duration, const ccBezierConfig& i_config, ActionSubSystemCallback i_callback)
{
	ActionBezierTo* newAction = new ActionBezierTo();
	newAction->InitWithTarget(target, duration, i_config);
	newAction->_callback = i_callback;
	m_newActions.push_back(newAction);
}

void ActionSubSystem::AddActionEntityFade(RealObjectPtr target, float duration, bool bFadeOut, ActionSubSystemCallback i_callback)
{
	ActionEntityFade* newAction = new ActionEntityFade();
	newAction->InitWithTarget(target, duration, bFadeOut);
	newAction->_callback = i_callback;
	m_newActions.push_back(newAction);
}

bool ActionSubSystem::Serialize(const Sexy::RtSerializeContext& i_serializeContext)
{
	SuperClass::Serialize(i_serializeContext);
	if (i_serializeContext.GetSync()->SyncBeginObject("actions"))
	{
		SerializeArrayDataPoint("m_Actions", m_Actions, i_serializeContext);
		SerializeArrayDataPoint("m_newActions", m_newActions, i_serializeContext);
		i_serializeContext.GetSync()->SyncEndObject();
	}
	return true;
}

/////////////// ActionBase ///////////////

RT_CLASS_IMPLEMENT(ActionBase);

void ActionBase::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ActionBase);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_FIELD_UNSAFE(RtReflectionDelegateBase, _callback);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<RealObject>, _target);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, _duration);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, _elapsed);
		REFLECTION_CLASSBUILDER_FIELD(bool, _firstTick);
	REFLECTION_CLASSBUILDER_END(ActionBase);
}

ActionBase::ActionBase()
{
	_duration = 0;
	_elapsed = 0;
	_firstTick = true;
}

void ActionBase::InitWithTarget(RealObjectPtr target, float duration)
{
	_target = target;
	_duration = duration;
	// prevent division by 0
	if (_duration == 0)
		_duration = FLT_EPSILON;
	_elapsed = 0;
	_firstTick = true;
}

void ActionBase::step(float dt)
{
	if (_firstTick)
	{
		_firstTick = false;
		_elapsed = 0;
	}
	else
		_elapsed += dt;

	this->update(fmaxf(0, fminf(1, _elapsed / _duration)));
}

/////////////// ActionEntityFade ///////////////

RT_CLASS_IMPLEMENT(ActionEntityFade);

void ActionEntityFade::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ActionEntityFade);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ActionBase);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_bFadeOut);
	REFLECTION_CLASSBUILDER_END(ActionEntityFade);
}

void ActionEntityFade::InitWithTarget(RealObjectPtr target, float duration, bool bFadeOut)
{
	ActionBase::InitWithTarget(target, duration);
	m_bFadeOut = bFadeOut;
}

bool ActionEntityFade::isDone() const
{
	return _elapsed >= _duration;
}

void ActionEntityFade::update(float time)
{
	if (_target.IsValid())
	{
		if (_target->IsA<Zombie>())
		{
			PopAnimRig* pPopAnimRig = _target->Cast<Zombie>()->GetAnimRig();
			if (pPopAnimRig)
			{
				Color fadeColor = Color::White;
				fadeColor.mAlpha = (m_bFadeOut ? (1 - time) : time) * 255;
				pPopAnimRig->SetPAMColor(fadeColor);
			}
		}
		else if (_target->IsA<Plant>())
			((RealObject*)NULL)->Cast<Plant>()->GetAnimRig();
	}
}

/////////////// ActionMoveTo ///////////////

RT_CLASS_IMPLEMENT(ActionMoveTo);

void ActionMoveTo::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ActionMoveTo);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ActionBase);

		REFLECTION_CLASSBUILDER_FIELD(SexyVector3, _positionDelta);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector3, _startPosition);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector3, _previousPosition);
	REFLECTION_CLASSBUILDER_END(ActionMoveTo);
}

ActionMoveTo::ActionMoveTo()
{
}

void ActionMoveTo::InitWithTarget(RealObjectPtr target, float duration, const SexyVector3& position)
{
	ActionBase::InitWithTarget(target, duration);
	_positionDelta = position - _target->GetPosition();
}

bool ActionMoveTo::isDone() const
{
	return _elapsed >= _duration;
}

void ActionMoveTo::update(float time)
{
	if (_target)
	{
		SexyVector3 currentPos = _target->GetPosition();
		SexyVector3 diff = currentPos - _previousPosition;
		_startPosition = _startPosition + diff;
		SexyVector3 newPos = _startPosition + (_positionDelta * time);
		_target->SetPosition(newPos);
		_previousPosition = newPos;
	}
}

/////////////// ActionBezierBy ///////////////

static inline float bezierat(float a, float b, float c, float d, float t)
{
	return (powf(1 - t, 3) * a +
			3 * t * (powf(1 - t, 2)) * b +
			3 * powf(t, 2) * (1 - t) * c +
			powf(t, 3) * d);
}

RT_CLASS_IMPLEMENT(ActionBezierBy);

void ActionBezierBy::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ccBezierConfig);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector2, endPosition);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector2, controlPoint_1);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector2, controlPoint_2);
	REFLECTION_CLASSBUILDER_END(ccBezierConfig);

	REFLECTION_CLASSBUILDER_BEGIN(ActionBezierBy);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ActionBase);

		REFLECTION_CLASSBUILDER_FIELD(ccBezierConfig, _config);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector3, _startPosition);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector3, _previousPosition);
	REFLECTION_CLASSBUILDER_END(ActionBezierBy);
}

void ActionBezierBy::InitWithTarget(RealObjectPtr target, float duration, const ccBezierConfig& i_config)
{
	ActionBase::InitWithTarget(target, duration);
	_config = i_config;
	_previousPosition = _startPosition = target->GetPosition();
}

bool ActionBezierBy::isDone() const
{
	return _elapsed >= _duration;
}

void ActionBezierBy::update(float time)
{
	if (_target)
	{
		float xa = 0;
		float xb = _config.controlPoint_1.x;
		float xc = _config.controlPoint_2.x;
		float xd = _config.endPosition.x;

		float ya = 0;
		float yb = _config.controlPoint_1.y;
		float yc = _config.controlPoint_2.y;
		float yd = _config.endPosition.y;

		float x = bezierat(xa, xb, xc, xd, time);
		float y = bezierat(ya, yb, yc, yd, time);

		_target->SetPosition(_startPosition + SexyVector3(x, y, 0));
	}
}

/////////////// ActionBezierTo ///////////////

RT_CLASS_IMPLEMENT(ActionBezierTo);

void ActionBezierTo::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ActionBezierTo);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ActionBezierBy);

		REFLECTION_CLASSBUILDER_FIELD(ccBezierConfig, _toConfig);
	REFLECTION_CLASSBUILDER_END(ActionBezierTo);
}

void ActionBezierTo::InitWithTarget(RealObjectPtr target, float duration, const ccBezierConfig& i_config)
{
	_toConfig = i_config;
	ActionBezierBy::InitWithTarget(target, duration, i_config);

	SexyVector2 start_pos = SexyVector2(_startPosition.x, _startPosition.y);
	_config.controlPoint_1 = _toConfig.controlPoint_1 - start_pos;
	_config.controlPoint_2 = _toConfig.controlPoint_2 - start_pos;
	_config.endPosition = _toConfig.endPosition - start_pos;
}
