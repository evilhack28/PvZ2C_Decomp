//
//  BusyAnimationManager.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-07.
//

#include "SexyAppFramework/Common.h"

#include "RtObject.h"
#include "BusyAnimationManager.h"
#include "LawnApp.h"
#include "ActivityConfig.h"
#include "TipsManager.h"
#include "PopAnimRig.h"

/////////////// Lifecycle ///////////////

BusyAnimationManager::BusyAnimationManager()
{
	mWidgetFlagsMod.mRemoveFlags = Sexy::WIDGETFLAGS_ALLOW_MOUSE | Sexy::WIDGETFLAGS_ALLOW_FOCUS;
	Resize(0, 0, gLawnApp->mWidth, gLawnApp->mHeight);
	m_isDataInitialized = false;
	m_active = false;
	m_removeBusyIcon = false;
	m_transitionCount = 0;
	m_stateChangeStartTime = PVZ_EOT();
	m_bTransform = false;
	m_loadIconFront = nullptr;
	m_loadIconBack = nullptr;
}

BusyAnimationManager::~BusyAnimationManager()
{
	if (m_isDataInitialized)
	{
		if (m_loadIconFront)
		{
			delete m_loadIconFront;
			m_loadIconFront = nullptr;
		}
		if (m_loadIconBack)
		{
			delete m_loadIconBack;
			m_loadIconBack = nullptr;
		}
	}
}

/////////////// Accessors ///////////////

bool BusyAnimationManager::OnBackButtonPressed()
{
	return m_transitionCount != 0;
}

/////////////// Logic ///////////////

void BusyAnimationManager::StopBusyIcon()
{
	if (m_transitionCount == 0)
		return;
	m_transitionCount--;
	if (m_transitionCount == 0)
	{
		m_removeBusyIcon = true;
		TipsManager::GetInstance().StopTip();
	}
}

void BusyAnimationManager::Draw(Graphics* i_g)
{
	if (m_stateChangeStartTime != PVZ_EOT())
		DeferOverlay(99);
}

void BusyAnimationManager::generateBounceTracks()
{
	generateBounceTrack(m_bounceInAnim[0]);
	generateBounceTrack(m_bounceInAnim[1]);
}

void BusyAnimationManager::generateBounceTrack(TimeLineTrack<float>& i_intoTrack)
{
	float duration = (Sexy::Rand(0.4f) + 1.0f) * 0.6f;
	float peakTime = duration * 0.618034f;
	float settleTime = peakTime + 0.618034f * (duration - peakTime);
	float peak = Sexy::Rand(0.12000000476837158f) + 1.1400001049041748f;
	float settle = Sexy::Rand(0.08999999612569809f) + 0.8549999594688416f;
	i_intoTrack.Initialize(0.0f);
	float value = 0.0f;
	i_intoTrack.AddKeyFrame(0.0f, value, CURVE_EASE_IN_OUT_WEAK);
	i_intoTrack.AddKeyFrame(peakTime, peak, CURVE_EASE_IN_OUT_WEAK);
	i_intoTrack.AddKeyFrame(settleTime, settle, CURVE_EASE_IN_OUT_WEAK);
	value = 1.0f;
	i_intoTrack.AddKeyFrame(duration, value, CURVE_CONSTANT);
}

static CachedResourcePtr<Sexy::PopAnim> s_loadIconBack("POPANIM_EFFECTS_LOAD_ICON_BACK");
static CachedResourcePtr<Sexy::PopAnim> s_loadIconFront("POPANIM_EFFECTS_LOAD_ICON_FRONT");

void BusyAnimationManager::InitializeData()
{
	if (!m_isDataInitialized)
	{
		m_isDataInitialized = true;
		Sexy::RtWeakPtr<Sexy::PopAnim> frontAnim = s_loadIconFront;
		Sexy::PopAnim* front = frontAnim.Get();
		Sexy::RtWeakPtr<Sexy::PopAnim> backAnim = s_loadIconBack;
		Sexy::PopAnim* back = backAnim.Get();
		m_loadIconFront = PopAnimRig::CreateRigOutsideTable(front, PopAnimRig::StaticGetClass());
		m_loadIconBack = PopAnimRig::CreateRigOutsideTable(back, PopAnimRig::StaticGetClass());
		Sexy::SexyTransform2D transform;
		int offset = S<int>(140);
		transform.Translate((float)(mWidth / 2 - offset), (float)(mHeight / 2 - offset));
		m_loadIconFront->SetRenderTransform(transform);
		m_loadIconBack->SetRenderTransform(transform);
		m_bounceInAnim[0].Initialize(0.0f);
		m_bounceInAnim[1].Initialize(0.0f);
	}
}

static bool IsTipsActivated(bool i_activated)
{
	return i_activated;
}

void BusyAnimationManager::StartBusyIcon()
{
	InitializeData();
	if (m_transitionCount == 0 && !m_removeBusyIcon)
	{
		m_loadIconBack->Play("ANIMATION", PLAY_CONTINUOUS, SELECT_EXACT);
		m_loadIconFront->Play("ANIMATION", PLAY_CONTINUOUS, SELECT_EXACT);
		mWidgetFlagsMod.mRemoveFlags = 0;
		m_active = true;
		m_stateChangeStartTime = PVZ_RealT();
		generateBounceTracks();
		TipsManager::GetInstance().StartNewTipFromAcitvityConfig();
	}
	m_transitionCount++;
	m_removeBusyIcon = false;
	if (gLawnApp->GetActivityConfig() && gLawnApp->GetActivityConfig()->IsActivityDays() && IsTipsActivated(gLawnApp->GetActivityConfig()->m_strTips.bIsActivated))
		m_bTransform = true;
	else
		m_bTransform = false;
}

void BusyAnimationManager::Update()
{
	TipsManager::GetInstance().Update();
	pvztime_t endOfTime;
	pvztime_t startTime;
	if (!m_removeBusyIcon)
	{
		endOfTime = PVZ_EOT();
		startTime = m_stateChangeStartTime;
		if (endOfTime == startTime)
			return;
	}
	else
	{
		startTime = m_stateChangeStartTime;
		m_removeBusyIcon = false;
		endOfTime = PVZ_EOT();
		if (startTime < endOfTime)
		{
			pvztime_t elapsed = PVZ_RealT() - m_stateChangeStartTime;
			pvztime_t now = PVZ_RealT();
			pvztime_t delay = std::max(0.6f - elapsed, 0.0f);
			m_active = false;
			mWidgetFlagsMod.mRemoveFlags = Sexy::WIDGETFLAGS_ALLOW_MOUSE | Sexy::WIDGETFLAGS_ALLOW_FOCUS;
			startTime = now - delay;
			m_stateChangeStartTime = startTime;
		}
		else
		{
			m_active = false;
			mWidgetFlagsMod.mRemoveFlags = Sexy::WIDGETFLAGS_ALLOW_MOUSE | Sexy::WIDGETFLAGS_ALLOW_FOCUS;
		}
		if (endOfTime == startTime)
			return;
	}
	if (!m_active && PVZ_RealT() - m_stateChangeStartTime > 1.2f)
	{
		m_stateChangeStartTime = endOfTime;
		return;
	}
	m_loadIconBack->UpdateAnim(PVZ_T(), PVZ_Dt());
	m_loadIconFront->UpdateAnim(PVZ_T(), PVZ_Dt());
}

void BusyAnimationManager::DrawOverlay(Graphics* i_g)
{
	TipsManager::GetInstance().Draw(i_g);
	Sexy::SexyVector2 backScale(0.0f, 0.0f);
	Sexy::SexyVector2 frontScale(0.0f, 0.0f);
	if (m_active)
	{
		pvztime_t elapsed = PVZ_RealT() - m_stateChangeStartTime;
		backScale.x = m_bounceInAnim[0].GetValueAt(elapsed);
		frontScale.y = backScale.x;
		backScale.y = m_bounceInAnim[1].GetValueAt(elapsed);
		frontScale.x = backScale.y;
	}
	else
	{
		pvztime_t remaining = 0.6f - (PVZ_RealT() - m_stateChangeStartTime);
		pvztime_t ahead = remaining + 0.06000000238418579f;
		backScale.x = m_bounceInAnim[0].GetValueAt(ahead);
		backScale.y = m_bounceInAnim[1].GetValueAt(ahead);
		frontScale.y = m_bounceInAnim[0].GetValueAt(remaining);
		frontScale.x = m_bounceInAnim[1].GetValueAt(remaining);
	}
	{
		Sexy::SexyTransform2D transform;
		transform.Scale(backScale.x, backScale.y);
		const Sexy::PopAnim* pam = m_loadIconBack->GetPAM();
		Sexy::SexyVector2 size((float)pam->mAnimRect.mWidth, (float)pam->mAnimRect.mHeight);
		size.x = pam->mDrawScale * size.x * backScale.x;
		size.y = pam->mDrawScale * size.y * backScale.y;
		if (m_bTransform)
			transform.Translate((float)gLawnApp->mWidth - size.x, (float)gLawnApp->mHeight - size.y);
		else
			transform.Translate(((float)gLawnApp->mWidth - size.x) * 0.5f, ((float)gLawnApp->mHeight - size.y) * 0.5f);
		m_loadIconBack->SetRenderTransform(transform);
		m_loadIconBack->Draw(i_g);
	}
	{
		Sexy::SexyTransform2D transform;
		m_loadIconFront->SetRenderTransform(transform);
		transform.Scale(frontScale.x, frontScale.y);
		const Sexy::PopAnim* pam = m_loadIconBack->GetPAM();
		Sexy::SexyVector2 size((float)pam->mAnimRect.mWidth, (float)pam->mAnimRect.mHeight);
		size.x = pam->mDrawScale * size.x * frontScale.x;
		size.y = pam->mDrawScale * size.y * frontScale.y;
		if (m_bTransform)
			transform.Translate((float)gLawnApp->mWidth - size.x, (float)gLawnApp->mHeight - size.y);
		else
			transform.Translate(((float)gLawnApp->mWidth - size.x) * 0.5f, ((float)gLawnApp->mHeight - size.y) * 0.5f);
		m_loadIconFront->SetRenderTransform(transform);
		m_loadIconFront->Draw(i_g);
	}
}
