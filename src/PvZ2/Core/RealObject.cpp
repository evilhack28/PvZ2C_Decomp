//
//  RealObject.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-02.
//

#include "RealObject.h"

#include "AudioMgr.h"
#include "Board.h"
#include "BoardTransforms.h"
#include "BoardPropertySheet.h"
#include "BoardRegion.h"
#include "LawnApp.h"
#include "RenderQueue.h"
#include "ScaledApp.h"

RT_CLASS_IMPLEMENT(RealObject);
void RealObject::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(RealObject);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GameObject);

	REFLECTION_CLASSBUILDER_END(RealObject);
}

RealObject::RealObject()
	: m_teamFlags(TEAM_None)
	, m_realObjectFlags(ROFLAG_None)
	, m_bSpecialSplitRect(false)
{
	// wwise needs to know about every object that can emit positional audio
	gAudioMgr->RegisterForAudio(this);
}

RealObject::RealObject(const RealObject& i_other) = default;

RealObject& RealObject::operator=(const RealObject& i_other) = default;

RealObject::~RealObject()
{
	gAudioMgr->UnregisterForAudio(this);
}

void RealObject::SetPosition(const SexyVector3& i_newPosition)
{
	m_position = i_newPosition;
}

/////////////// Team ///////////////

void RealObject::JoinTeam(TeamFlags i_team)
{
	TeamFlags oldTeams = m_teamFlags;

	// plants and zombies are mutually exclusive - joining one leaves the other
	if (TestFlag(i_team, TEAM_PLANTS))
		SetFlag(m_teamFlags, TEAM_ZOMBIES, false);
	if (TestFlag(i_team, TEAM_ZOMBIES))
		SetFlag(m_teamFlags, TEAM_PLANTS, false);

	SetFlag(m_teamFlags, i_team, true);
	onChangeTeams(oldTeams, m_teamFlags);
}

void RealObject::LeaveTeam(TeamFlags i_team)
{
	TeamFlags oldTeams = m_teamFlags;
	SetFlag(m_teamFlags, i_team, false);
	onChangeTeams(oldTeams, m_teamFlags);
}

bool RealObject::IsOnTeam(TeamFlags i_team) const
{
	return TestFlag(m_teamFlags, i_team);
}

bool RealObject::IsOnOpposingTeam(TeamFlags i_teams) const
{
	return TeamsAreOpposing(m_teamFlags, i_teams);
}

bool RealObject::IsOnOpposingTeam(const RealObject* i_entity) const
{
	return IsOnOpposingTeam(i_entity->m_teamFlags);
}

/////////////// Ground and water ///////////////

bool RealObject::ShouldClipWithWater() const
{
	return false;
}

bool RealObject::ShouldDrawShadow() const
{
	// no shadow when hidden, or when floating over open sky (there is no ground
	// to cast onto)
	if (IsHidden())
		return false;
	return !gLawnApp->m_board->IsSky(GetPosition());
}

bool RealObject::IsOnWaterTile(const SexyVector3& i_position) const
{
	return gLawnApp->m_board->IsShallowWater(i_position);
}

void RealObject::SnapToGround(bool i_snapOnlyUnderGround)
{
	if (TestFlag(m_realObjectFlags, ROFLAG_DisableSnapToGround))
		return;

	float groundZ = CalcGroundZHeight(GetPosition());

	// when i_snapOnlyUnderGround is set we only lift the object up to ground
	// level, never push it down
	if (!i_snapOnlyUnderGround || groundZ > GetPosition().z)
		m_position.z = groundZ;
}

float RealObject::CalcGroundZHeight(const Sexy::SexyVector3 &i_position)
{
	float z = 0.f;
	if (gLawnApp->m_board->m_roofStage)
		z = gLawnApp->m_board->calculateRoofOffsetZ(i_position.x);

	// over a water tile the "ground" is the tide surface
	if (ShouldClipWithWater() && IsOnWaterTile(i_position))
		z = calcTideDepth(i_position, 0.f);
	return z;
}

float RealObject::calcTideDepth(const SexyVector3& i_position, float i_additionalWaterDepth)
{
	BoardRegion* region = gLawnApp->m_board->FindRegionWithFlags(i_position, BOARDREGION_ShallowWater);
	if (!region)
		return 0.f;

	// how far the object sinks scales with its height and the region's depth
	// fraction at this point
	float frac = region->GetGroundHeightOffsetFraction(i_position);
	return (getTideDepthHeightMaxPct() * calcCollisionRect().mHeight - i_additionalWaterDepth) * frac;
}

float RealObject::getTideDepthHeightMaxPct()
{
	return gLawnApp->m_board->GetBoardProperties()->DefaultTideMaxHeightPct;
}

Sexy::Point RealObject::CalcGridPosition() const
{
	return Sexy::Point(BoardTransforms::BoardSpaceToGridXUnbounded(m_position.x),
	                   BoardTransforms::BoardSpaceToGridYUnbounded(m_position.y));
}

Sexy::Rect RealObject::calcCollisionRect()
{
	// default footprint is a single point at the object's 2.5D position
	SexyVector2 pos = GetPosition2D();
	return Sexy::Rect((int)pos.x, (int)pos.y, 1, 1);
}

/////////////// Sound ///////////////

void RealObject::PlayPositionalSound(const std::string& i_eventName, float i_throttleTime)
{
	if (gLawnApp->GetSfxVolume() <= 0.0)
		return;

	SendPositionalAudioValue();

	if (i_throttleTime > 0.f)
		gAudioMgr->SendEventThrottled(i_eventName, i_throttleTime, this);
	else
		gAudioMgr->SendEvent(i_eventName, this);
}

void RealObject::SendPositionalAudioValue()
{
	gAudioMgr->SendPositionalAudioValue(this, GetPosition());
}

/////////////// Drawing ///////////////

void RealObject::AddToRenderQueue(RenderQueue* i_queue)
{
	if (!IsHidden())
		i_queue->Add(CalcRenderOrder(), Sexy::MakeDelegate(*this, &RealObject::Draw));

	if (ShouldDrawShadow())
		i_queue->Add(RENDER_LAYER_SHADOWS, Sexy::MakeDelegate(*this, &RealObject::DrawShadow));
}

Sexy::Rect RealObject::GetDrawClipRect(bool& o_needsClipRect)
{
	o_needsClipRect = false;
	if (!TestFlag(m_realObjectFlags, ROFLAG_UseGroundClipRect))
		return Sexy::Rect();

	// a fixed box around the object, scaled into screen space; the split-rect
	// variant starts higher so tall objects are not clipped at the waist
	const SexyVector3& pos = GetPosition();
	int x = (int)(pos.x - 400.f);
	int y = (int)(pos.y - (m_bSpecialSplitRect ? 60.f : 395.f));

	Sexy::Rect clipRect(x, y, 800, 400);
	float scale = S(1.f);
	clipRect.Scale(scale, scale);

	o_needsClipRect = true;
	return clipRect;
}

void RealObject::onApplyDrawClipRect(Sexy::Graphics* i_g)
{
	bool needsClipRect;
	Sexy::Rect clipRect = GetDrawClipRect(needsClipRect);
	if (needsClipRect)
		i_g->SetClipRect(clipRect);
}

void RealObject::Draw(Sexy::Graphics* i_g)
{
	onDraw(i_g);
}

void RealObject::DrawShadow(Sexy::Graphics* i_g)
{
	onDrawShadow(i_g);
}
