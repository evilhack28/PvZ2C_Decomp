//
//  PowerupTouchBased.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "BasePowerup.h"
#include "LawnApp.h"
#include "Board.h"

PowerupTouchBased::~PowerupTouchBased()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PowerupTouchBased);

void PowerupTouchBased::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PowerupTouchBased);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(BasePowerup);

	REFLECTION_CLASSBUILDER_END(PowerupTouchBased);
}

/////////////// Touch ///////////////

PowerupTouchBased::PowerupTouchBased()
	: m_touchIdent(0)
{
}

const Sexy::Touch& PowerupTouchBased::getLastTouchEvent() const
{
	return m_lastTouchEvent;
}

const Sexy::TouchID& PowerupTouchBased::getActiveTouchIdent() const
{
	return m_touchIdent;
}

void PowerupTouchBased::registerForEvents()
{
	gLawnApp->m_board->RegisterTouchGameplayObject(Sexy::MakeDelegate(*this, &PowerupTouchBased::handleTouch), 4, BoardEntityPtr(), Sexy::MakeDelegate(*this, &PowerupTouchBased::cancelTouch));
}

void PowerupTouchBased::unregisterForEvents()
{
	gLawnApp->UnregisterBoardTouchGameplayObject(this);
}

void PowerupTouchBased::cancelTouch()
{
	m_touchIdent = 0;
	onTouchCanceled();
}

bool PowerupTouchBased::handleTouch(const Sexy::Touch& i_touch)
{
	bool began;
	bool ret;
	if (isInState(0))
		return false;

	if (m_touchIdent == 0 && i_touch.phase == 0)
	{
begin:
		began = onTouchBegin(i_touch);
		ret = true;
		if (!began)
			return ret;

		m_touchIdent = i_touch.ident;
		m_lastTouchEvent = i_touch;
		return ret;
	}

	if (m_touchIdent != i_touch.ident)
		return false;

	switch (i_touch.phase)
	{
	case 1:
		onTouchMoved(i_touch);
		m_lastTouchEvent = i_touch;
		return false;
	case 0:
		goto begin;
	case 3:
		onTouchEnd(i_touch);
		m_lastTouchEvent = i_touch;
		cancelTouch();
		return true;
	default:
		return true;
	}
}
