//
//  AlarmSagittifoliaAvatarSkill.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-18.
//

#include "SexyAppFramework/Common.h"

#include "GridSquareAlarmSagittifoliaFencePiece.h"
#include "Board.h"
#include "BoardTransforms.h"
#include "Effect_PopAnim.h"
#include "EntityFinder.h"
#include "LawnApp.h"
#include "Renderable.h"
#include "Zombie.h"

AlarmSagittifoliaAvatarSkill::AlarmSagittifoliaAvatarSkill()
    : m_endTime(0.0f)
    , m_damageInfo(0.0f, DAMAGE_NONE, (BoardEntity*)NULL)
{
}

AlarmSagittifoliaAvatarSkill::AlarmSagittifoliaAvatarSkill(const AlarmSagittifoliaAvatarSkill&) = default;

AlarmSagittifoliaAvatarSkill& AlarmSagittifoliaAvatarSkill::operator=(const AlarmSagittifoliaAvatarSkill&) = default;

void AlarmSagittifoliaAvatarSkill::onDestroy()
{
	if (m_effect.IsValid())
		m_effect->Destroy();
	m_effect.ClearId();
}

void AlarmSagittifoliaAvatarSkill::setInfo(pvztime_t i_endTime, const Point& i_point, const DamageInfo& i_damageInfo)
{
	m_gridLocation = i_point;
	m_endTime = i_endTime;
	m_damageInfo = i_damageInfo;

	Sexy::Rect rect = BoardTransforms::GridToBoardSpaceRect(m_gridLocation);
	Sexy::Point center = rect.GetCenter();
	SexyVector3 position((float)center.mX, (float)center.mY, 0);
	position.z = !(__builtin_expect(gLawnApp->m_board->m_roofStage, 0)) ? position.z : gLawnApp->m_board->calculateRoofOffsetZ(position.x);

	Effect_PopAnim* effect;
	effect = gLawnApp->m_board->AddEffect<Effect_PopAnim>();
	effect->CreatePopAnimRig(GetPAMByName("POPANIM_EFFECTS_ALARMSAGITTIFOLIA_ELECTRIC_FIELD").Get(), NULL);
	effect->SetScale(1.0f);
	effect->PlayLoopingAnimation("animation1", m_endTime - PVZ_T(), SELECT_RANDOM_INDEX);
	effect->SetBoardSpaceOrigin(position, -1);
	effect->SetCentered(true);
	effect->SetRenderLayerOverride(Board::MakeRenderOrder(RENDER_LAYER_ELECTRIC_FENCE, m_gridLocation.mY, 0));
	m_effect = effect->GetPtr();
}

void AlarmSagittifoliaAvatarSkill::takeEffect()
{
	std::vector<BoardEntity*> entities;
	Sexy::Rect area(m_gridLocation.mX - 1, m_gridLocation.mY - 1, 3, 3);
	EntityFinder::GetEntitiesInGridSquares(entities, ENTITYTYPE_ZOMBIE, area);
	std::vector<BoardEntity*>::iterator it = entities.begin();
	std::vector<BoardEntity*>::iterator end = entities.end();
	for (; it != end; ++it)
	{
		BoardEntity*& entity = *it;
		if (entity->IsA<Zombie>())
			entity->TakeDamage(m_damageInfo);
	}
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(AlarmSagittifoliaAvatarSkill);

void AlarmSagittifoliaAvatarSkill::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(AlarmSagittifoliaAvatarSkill);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(BoardEntity);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_endTime);
		REFLECTION_CLASSBUILDER_FIELD(Point, m_gridLocation);
	REFLECTION_CLASSBUILDER_END(AlarmSagittifoliaAvatarSkill);
}
