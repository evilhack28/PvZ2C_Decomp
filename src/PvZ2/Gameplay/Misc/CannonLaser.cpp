//
//  CannonLaser.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "CannonLaser.h"

#include "Board.h"
#include "LawnApp.h"
#include "PopAnim.h"
#include "Effect_PopAnim.h"
#include "EntityFinder.h"
#include "ScaledApp.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

CannonLaser::~CannonLaser()
{
}

CannonLaser::CannonLaser()
	: m_laserOriginRig(nullptr)
	, m_laserRig(nullptr)
	, m_timerDestroy(PVZ_EOT())
	, m_timerAttack(0)
	, m_bCanCollision(false)
	, m_laserState(0)
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(CannonLaser);

void CannonLaser::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CannonLaser);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Projectile);

		REFLECTION_CLASSBUILDER_FIELD(int, m_laserState);
	REFLECTION_CLASSBUILDER_END(CannonLaser);
}

/////////////// Accessors ///////////////

void CannonLaser::SetTarget(const SexyVector3& from, const SexyVector3& to)
{
	getProps();
	m_laserFrom = from;
	m_laserTo = to;
}

float CannonLaser::GetCross(const SexyVector3& p)
{
	SexyVector3 a = p - m_laserFrom;
	SexyVector3 b = p - m_laserTo;
	return b.y * a.x - b.x * a.y;
}

/////////////// Logic ///////////////

using namespace Sexy;

SexyVector2 boardToScreenSpace(const SexyVector3& i_vector);

SexyVector2 artPointToScreenPoint(const Point& i_artPoint);

float getAngleForVector(const SexyVector2& i_vector);

void CannonLaser::onDestroy()
{
}

bool CannonLaser::ShouldDrawShadow() const
{
	return false;
}

void CannonLaser::onUpdate(pvztime_t i_dt)
{
	m_bCanCollision = false;
	SetPosition(m_laserFrom);
	if (m_timerDestroy < PVZ_T())
	{
		onAnimationDone(std::string(""));
	}
	else if (m_timerAttack < PVZ_T() && m_laserState == 1)
	{
		float t = PVZ_T();
		m_bCanCollision = true;
		m_timerAttack = t + 0.5f;
	}
}

RtWeakPtr<GameObject> CannonLaser::LoadPopanimEffect(std::string i_name, int i_renderLayer)
{
	Effect_PopAnim* effect = gLawnApp->m_board->AddEffect<Effect_PopAnim>();
	effect->CreatePopAnimRig(GetPAMByName(i_name), NULL);
	effect->SetBoardSpaceOrigin(SexyVector3(0, 0, 0), -1);
	effect->SetRenderLayerOverride(i_renderLayer);
	effect->SetIsScreenSpaceEffect(false);
	effect->SetVisibility(false);
	return effect->GetPtr();
}

bool CannonLaser::Accept(BoardEntity* i_entity)
{
	Rect r = i_entity->GetCollisionRect();
	float c1 = GetCross(SexyVector3(r.mX, r.mY, 0));
	if (c1 == 0)
		return true;
	float c2 = GetCross(SexyVector3(r.mX, r.mY + r.mHeight, 0));
	if (c2 == 0 || (c1 > 0) != (c2 > 0))
		return true;
	float c3 = GetCross(SexyVector3(r.mX + r.mWidth, r.mY, 0));
	if (c3 == 0 || (c2 > 0) != (c3 > 0))
		return true;
	float c4 = GetCross(SexyVector3(r.mX + r.mWidth, r.mY + r.mHeight, 0));
	if (c4 == 0)
		return true;
	return (c3 > 0) != (c4 > 0);
}

void CannonLaser::getCollisionEntities(std::vector<BoardEntity*> &o_entities, const Rect& i_projectileRect) const
{
	if (m_bCanCollision)
	{
		BoardEntityTypeFlag types = BoardEntityTypeFlag(0);
		if (CollidesWithType(CollisionTypeFlags(8)))
			types |= BoardEntityTypeFlag(4);
		if (CollidesWithType(CollisionTypeFlags(7)))
			types |= BoardEntityTypeFlag(2);
		if (CollidesWithType(CollisionTypeFlags(0xf0)))
			types |= BoardEntityTypeFlag(1);
		EntityFinder::EntitySearchAcceptEventType acceptEvent;
		acceptEvent += MakeDelegate(const_cast<CannonLaser&>(*this), &CannonLaser::Accept);
		EntityFinder::GetEntities(o_entities, types, acceptEvent);
	}
}

void CannonLaser::Initialise()
{
	const CannonLaserProjectileProps* props = getProps()->CastChecked<CannonLaserProjectileProps>();
	m_laserRig = LoadPopanimEffect(props->AttachedPAM, GetRenderOrder());
	m_laserOriginRig = LoadPopanimEffect(props->LaserOrginEffect, GetRenderOrder() + 1);
	m_laserOriginRig->GetPopAnimRig()->PlayAndStop("idle", SELECT_EXACT, PopAnimRig::AnimStoppedReflectionDelegate(GetPtr(), "onAnimationDone"));
	m_laserState = 0;
	float attackTime = props->AttackTime;
	m_timerDestroy = PVZ_T() + attackTime;
	m_timerAttack = 0;
}

void CannonLaser::onAnimationDone(const std::string& i_animName)
{
	switch (m_laserState)
	{
	case 0:
		m_laserOriginRig->GetPopAnimRig()->PlayAndContinue("keep", SELECT_EXACT);
		m_laserRig->PlayLoopingAnimation("idle", PVZ_EOT(), SELECT_EXACT);
		m_laserState = 1;
		m_timerDestroy = PVZ_T() + 1.6f;
		break;
	case 1:
		m_laserState = 2;
		m_laserOriginRig->GetPopAnimRig()->PlayAndStop("end", SELECT_EXACT, PopAnimRig::AnimStoppedReflectionDelegate(GetPtr(), "onAnimationDone"));
		break;
	case 2:
		Destroy();
		break;
	}
}

void CannonLaser::Draw(Graphics* i_g)
{
	const CannonLaserProjectileProps* props = getProps()->CastChecked<CannonLaserProjectileProps>();
	SexyVector2 from = boardToScreenSpace(m_laserFrom);
	SexyVector2 to = boardToScreenSpace(m_laserTo);
	SexyVector2 artStart = artPointToScreenPoint(props->LaserStartArtOffset);
	SexyVector2 artEnd = artPointToScreenPoint(props->LaserEndArtOffset);
	SexyVector2 dir = to - from;
	if (m_laserState == 1)
	{
		float length = dir.Magnitude();
		float artLength = (artEnd - artStart).Magnitude();
		float ratio = length / artLength;
		float angle = getAngleForVector(dir);
		SexyVector2 scale(ratio, 1.0f);
		SexyTransform2D transform = SexyTransform2D::CreateTransformWithPivot(from, angle, scale, artStart, true);
		m_laserRig->GetPopAnimRig()->SetRenderTransform(transform);
		m_laserRig->SetVisibility(true);
		m_laserRig->Draw(i_g);
		m_laserRig->SetVisibility(false);
	}
	SexyVector2 pivot(100.0f, 96.0f);
	float angle2 = getAngleForVector(dir);
	SexyVector2 pivot2 = pivot * S(1.0f);
	SexyTransform2D transform2 = SexyTransform2D::CreateTransformWithPivot(from, angle2, 1.0f, pivot2, true);
	m_laserOriginRig->GetPopAnimRig()->SetRenderTransform(transform2);
	m_laserOriginRig->SetVisibility(true);
	m_laserOriginRig->Draw(i_g);
	m_laserOriginRig->SetVisibility(false);
}
