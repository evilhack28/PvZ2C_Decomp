//
//  AlarmSagittifoliaAvatarSkillSystem.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-18.
//

#include "SexyAppFramework/Common.h"

#include "GridSquareAlarmSagittifoliaFencePiece.h"

AlarmSagittifoliaAvatarSkillSystem::AlarmSagittifoliaAvatarSkillSystem()
    : m_timeUpdate(PVZ_T())
{
	m_pieces.clear();
}

AlarmSagittifoliaAvatarSkillSystem::~AlarmSagittifoliaAvatarSkillSystem()
{
	m_pieces.clear();
}

void AlarmSagittifoliaAvatarSkillSystem::CreateEffect(pvztime_t i_endTime, const Point& i_point, const DamageInfo& i_damageInfo)
{
	AlarmSagittifoliaAvatarSkill skill;
	skill.setInfo(i_endTime, i_point, i_damageInfo);
	m_pieces.push_back(skill);
}

void AlarmSagittifoliaAvatarSkillSystem::Update()
{
	if (PVZ_T() > m_timeUpdate)
	{
		std::vector<AlarmSagittifoliaAvatarSkill>::iterator it = m_pieces.begin();
		while (it != m_pieces.end())
		{
			(*it).takeEffect();
			pvztime_t now = PVZ_T();
			AlarmSagittifoliaAvatarSkill& skill = *it;
			if (now > skill.getEndTime())
			{
				skill.Destroy();
				it = m_pieces.erase(it);
			}
			else
			{
				++it;
			}
		}
		m_timeUpdate = PVZ_T() + 1.0f;
	}
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(AlarmSagittifoliaAvatarSkillSystem);

void AlarmSagittifoliaAvatarSkillSystem::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(AlarmSagittifoliaAvatarSkillSystem);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GameSubSystem);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_timeUpdate);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<AlarmSagittifoliaAvatarSkill>, m_pieces);
	REFLECTION_CLASSBUILDER_END(AlarmSagittifoliaAvatarSkillSystem);
}
