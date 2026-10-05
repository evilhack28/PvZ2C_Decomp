//
//  PowerupWizardFinger.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-05.
//

#include "SexyAppFramework/Common.h"

#include "PowerupWizardFinger.h"
#include "LawnApp.h"
#include "Board.h"
#include "AudioMgr.h"
#include "BoardEntity.h"

#include "ReflectionBuilder.h"

/////////////// PowerupWizardFinger ///////////////

RT_CLASS_IMPLEMENT(PowerupWizardFinger);

void PowerupWizardFinger::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PowerupWizardFinger);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(BasePowerup);

	REFLECTION_CLASSBUILDER_END(PowerupWizardFinger);
}

static int ScreenScaleNum(int i_num)
{
	return ((ScaledApp*)gSexyApp)->ScreenScaleNum(i_num);
}

void PowerupWizardFinger::onEnterState_Selected(PowerupState i_fromState)
{
	BasePowerup::onEnterState_Selected(i_fromState);
}

bool PowerupWizardFinger::isTouching()
{
	return m_touchIdent != 0;
}

void PowerupWizardFinger::cancelTouch()
{
	m_touchIdent = Sexy::InvalidTouchID;
	if (m_WFGameObject.IsValid())
		m_WFGameObject->SetActive(false);
}

void PowerupWizardFinger::onEnterState_Idle(PowerupState i_fromState)
{
	BasePowerup::onEnterState_Idle(i_fromState);
	if (i_fromState != -1)
		cancelTouch();
}

void PowerupWizardFinger::onExitState_Activated(PowerupState)
{
	m_WFGameObject->Destroy();
}

void PowerupWizardFinger::updateState_Activated()
{
	m_WFGameObject->Update();
	BasePowerup::updateState_Activated();
}

void PowerupWizardFinger::unregisterForEvents()
{
	gLawnApp->UnregisterBoardTouchGameplayObject(this);
}

void PowerupWizardFinger::registerForEvents()
{
	gLawnApp->m_board->RegisterTouchGameplayObject(Sexy::MakeDelegate(*this, &PowerupWizardFinger::handleTouch), 4, BoardEntityPtr(), Sexy::MakeDelegate(*this, &PowerupWizardFinger::cancelTouch));
}

bool PowerupWizardFinger::shouldActivate(const Sexy::Touch& i_touch)
{
	bool result = isInState(1);
	if (result)
	{
		SexyVector2 location((float)ScreenScaleNum(i_touch.location.mX), (float)ScreenScaleNum(i_touch.location.mY));
		Sexy::Point point((int)location.x, (int)location.y);
		result = gLawnApp->m_board->GetGridBoundingRect().Contains(point);
		if (result)
			result = m_WFGameObject->GetClosestEntity(location) != NULL;
	}
	return result;
}

void PowerupWizardFinger::activate(const Sexy::Touch& i_touch)
{
	m_touchIdent = i_touch.ident;
	m_WFGameObject = GameObject::Create(WizardFingerGameObject::StaticGetClass(), PVZDB::TABLE_GAMEOBJECTS)->GetPtr();
	m_WFGameObject->SetActive(true);
	m_WFGameObject->SetLocation(SexyVector2((float)ScreenScaleNum(i_touch.location.mX), (float)ScreenScaleNum(i_touch.location.mY)));
	gAudioMgr->SendEvent("Play_UI_PowerUp_WizardFinger");
	BasePowerup::Activate();
}

bool PowerupWizardFinger::handleTouch(const Sexy::Touch& i_touch)
{
	bool result;
	if (!isInState(1) && !isInState(2))
		return false;
	switch (i_touch.phase)
	{
	case 0:
		if (m_touchIdent != 0)
			break;
		result = shouldActivate(i_touch);
		if (__builtin_expect(result, 0))
			goto doActivate;
		if (!isInState(2))
			break;
		m_touchIdent = i_touch.ident;
		m_WFGameObject->SetActive(true);
		m_WFGameObject->SetLocation(SexyVector2((float)ScreenScaleNum(i_touch.location.mX), (float)ScreenScaleNum(i_touch.location.mY)));
		gAudioMgr->SendEvent("Play_UI_PowerUp_WizardFinger");
		return true;
	case 1:
		if (m_touchIdent == 0 && shouldActivate(i_touch))
		{
			result = false;
			goto doActivate;
		}
		if (i_touch.ident == m_touchIdent)
		{
			m_WFGameObject->SetLocation(SexyVector2((float)ScreenScaleNum(i_touch.location.mX), (float)ScreenScaleNum(i_touch.location.mY)));
			return false;
		}
		break;
	case 3:
		result = i_touch.ident == m_touchIdent;
		goto doCancel;
	case 4:
		result = false;
	doCancel:
		cancelTouch();
		return result;
	}
	return false;
doActivate:
	activate(i_touch);
	return result;
}
