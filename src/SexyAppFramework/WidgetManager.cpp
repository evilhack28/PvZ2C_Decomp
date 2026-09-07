//
//  WidgetManager.cpp
//
//  SexyAppFramework, PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-06.
//

#include "WidgetManager.h"
#include "Widget.h"

using namespace Sexy;

void WidgetManager::FreeResources() {}

void WidgetManager::AddBaseModal(Widget* theWidget)
{
	AddBaseModal(theWidget, mDefaultBelowModalFlagsMod);
}

bool WidgetManager::IsLeftButtonDown()
{
	return (mActualDownButtons & 1) != 0;
}

bool WidgetManager::IsMiddleButtonDown()
{
	return (mActualDownButtons & 4) != 0;
}

bool WidgetManager::IsRightButtonDown()
{
	return (mActualDownButtons & 2) != 0;
}

int WidgetManager::GetWidgetFlags()
{
	if (mHasFocus)
		return mWidgetFlags;

	return GetModFlags(mWidgetFlags, mLostFocusFlagsMod);
}

void WidgetManager::SetPopupCommandWidget(Widget* theList)
{
	mPopupCommandWidget = theList;
	AddWidget(theList);
}

void WidgetManager::RemovePopupCommandWidget()
{
	if (mPopupCommandWidget != NULL)
	{
		Widget* aWidget = mPopupCommandWidget;
		mPopupCommandWidget = NULL;
		RemoveWidget(aWidget);
	}
}

Widget* WidgetManager::GetAnyWidgetAt(int x, int y, int* theWidgetX, int* theWidgetY)
{
	bool aFound;
	return GetWidgetAtHelper(x, y, GetWidgetFlags(), &aFound, theWidgetX, theWidgetY);
}

Widget* WidgetManager::GetWidgetAt(int x, int y, int* theWidgetX, int* theWidgetY)
{
	Widget* aWidget = GetAnyWidgetAt(x, y, theWidgetX, theWidgetY);
	if (aWidget != NULL && aWidget->mDisabled)
		aWidget = NULL;

	return aWidget;
}

void WidgetManager::TouchesCanceled()
{
	mTouches = 0;

	if (mLastDownWidget != NULL)
	{
		mLastDownWidget->mIsDown = false;
		mLastDownWidget->TouchesCanceled();
		mLastDownWidget = NULL;
	}
}

void WidgetManager::TouchBegan(const Touch& theTouch)
{
	mActualDownButtons |= 1;
	mLastInputUpdateCnt = mUpdateCnt;

	MousePosition(theTouch.location.mX, theTouch.location.mY);

	Widget* aWidget = GetWidgetAt(theTouch.location.mX, theTouch.location.mY, NULL, NULL);
	Widget* aDownWidget = mLastDownWidget != NULL ? mLastDownWidget : aWidget;

	Touch aTouch = theTouch;

	if (aDownWidget != NULL)
	{
		Point aPos = aDownWidget->GetAbsPos();
		aTouch.location.mX -= aPos.mX;
		aTouch.previousLocation.mX -= aPos.mX;
		aTouch.location.mY -= aPos.mY;
		aTouch.previousLocation.mY -= aPos.mY;

		mLastDownWidget = aDownWidget;
		mLastDownButtonId = 1;
		mDownButtons |= 1;
		mTouches++;

		if (aDownWidget->WantsFocus())
			SetFocus(aDownWidget);

		aDownWidget->mIsDown = true;
		aDownWidget->TouchBegan(aTouch);
	}
	else
	{
		mLastDownButtonId = 1;
		mDownButtons |= 1;
		mTouches++;
		mLastDownWidget = aWidget;
	}
}

void WidgetManager::TouchMoved(const Touch& theTouch)
{
	mLastInputUpdateCnt = mUpdateCnt;
	mLastMouseX = theTouch.location.mX;
	mMouseIn = true;
	mLastMouseY = theTouch.location.mY;

	if (mLastDownWidget == NULL)
		return;

	Widget* aWidget = GetWidgetAt(theTouch.location.mX, theTouch.location.mY, NULL, NULL);

	if (aWidget != NULL && mLastDownWidget != aWidget)
	{
		if (aWidget->ShouldReceiveAllOverTouchEvents())
		{
			Touch aTouch = theTouch;
			Point aPos = aWidget->GetAbsPos();
			aTouch.location.mX -= aPos.mX;
			aTouch.location.mY -= aPos.mY;
			aTouch.previousLocation.mX -= aPos.mX;
			aTouch.previousLocation.mY -= aPos.mY;
			aWidget->TouchMoved(aTouch);
		}
	}

	Touch aTouch = theTouch;
	Point aPos = mLastDownWidget->GetAbsPos();
	aTouch.location.mX -= aPos.mX;
	aTouch.location.mY -= aPos.mY;
	aTouch.previousLocation.mX -= aPos.mX;
	aTouch.previousLocation.mY -= aPos.mY;
	mLastDownWidget->TouchMoved(aTouch);

	if (aWidget == mLastDownWidget && aWidget != NULL)
	{
		if (mOverWidget == NULL)
		{
			mOverWidget = mLastDownWidget;
			MouseEnter(mLastDownWidget);
		}
	}
	else if (mOverWidget != NULL)
	{
		Widget* anOldOver = mOverWidget;
		mOverWidget = NULL;
		MouseLeave(anOldOver);
	}
}

bool WidgetManager::MouseExit(int x, int y)
{
	mLastInputUpdateCnt = mUpdateCnt;
	mMouseIn = false;

	if (mOverWidget != NULL)
	{
		MouseLeave(mOverWidget);
		mOverWidget = NULL;
	}

	return true;
}

void WidgetManager::Resize(const Rect& theMouseDestRect, const Rect& theMouseSourceRect)
{
	mWidth = theMouseDestRect.mWidth + theMouseDestRect.mX * 2;
	mHeight = theMouseDestRect.mHeight + theMouseDestRect.mY * 2;
	mMouseDestRect = theMouseDestRect;
	mMouseSourceRect = theMouseSourceRect;
}

void WidgetManager::DoMouseUps()
{
	if (mLastDownWidget != NULL && mDownButtons != 0)
	{
		DoMouseUps(mLastDownWidget, mDownButtons);
		mDownButtons = 0;
		mLastDownWidget = NULL;
	}
}

void WidgetManager::InitModalFlags(ModalFlags* theModalFlags)
{
	theModalFlags->mIsOver = (mBaseModalWidget == NULL);

	int aFlags = GetWidgetFlags();
	theModalFlags->mOverFlags = aFlags;
	theModalFlags->mUnderFlags = GetModFlags(aFlags, mBelowModalFlagsMod);
}

void WidgetManager::MouseLeave(Widget* theWidget)
{
	theWidget->mIsOver = false;
	theWidget->MouseLeave();

	if (theWidget->mDoFinger)
		theWidget->ShowFinger(false);
}

void WidgetManager::MouseEnter(Widget* theWidget)
{
	theWidget->mIsOver = true;
	theWidget->MouseEnter();

	if (theWidget->mDoFinger)
		theWidget->ShowFinger(true);
}

bool WidgetManager::KeyDown(KeyCode key)
{
	mLastInputUpdateCnt = mUpdateCnt;

	if ((uint)key <= 0xFE)
		mKeyDown[key] = true;

	if (mFocusWidget != NULL)
		mFocusWidget->KeyDown(key);

	return true;
}

bool WidgetManager::KeyUp(KeyCode key)
{
	mLastInputUpdateCnt = mUpdateCnt;

	if ((uint)key <= 0xFE)
	{
		mKeyDown[key] = false;

		if (key == KEYCODE_TAB && mKeyDown[KEYCODE_CONTROL])
			return true;
	}

	if (mFocusWidget != NULL)
		mFocusWidget->KeyUp(key);

	return true;
}

void WidgetManager::RemapMouse(int& theX, int& theY)
{
	if (mMouseSourceRect.mWidth == 0)
		return;
	if (mMouseSourceRect.mHeight == 0)
		return;

	theX = (theX - mMouseSourceRect.mX) * mMouseDestRect.mWidth / mMouseSourceRect.mWidth + mMouseDestRect.mX;
	theY = (theY - mMouseSourceRect.mY) * mMouseDestRect.mHeight / mMouseSourceRect.mHeight + mMouseDestRect.mY;
}

bool WidgetManager::KeyChar(SexyChar theChar)
{
	mLastInputUpdateCnt = mUpdateCnt;

	if (theChar == KEYCODE_TAB && mKeyDown[KEYCODE_CONTROL])
	{
		if (mDefaultTab != NULL)
			mDefaultTab->KeyChar(theChar);
	}
	else if (mFocusWidget != NULL)
	{
		mFocusWidget->KeyChar(theChar);
	}

	return true;
}

void WidgetManager::MouseWheel(int theDelta)
{
	mLastInputUpdateCnt = mUpdateCnt;

	if (mFocusWidget != NULL)
		mFocusWidget->MouseWheel(theDelta);
}

void WidgetManager::GotFocus()
{
	if (!mHasFocus)
	{
		Widget* aWidget = mFocusWidget;
		mHasFocus = true;
		if (aWidget != NULL)
			aWidget->GotFocus();
	}
}

void WidgetManager::LostFocus()
{
	if (mHasFocus)
	{
		mActualDownButtons = 0;

		for (int i = 0; i < 0xFF; i++)
			if (mKeyDown[i])
				KeyUp((KeyCode)i);

		mHasFocus = false;
		if (mFocusWidget != NULL)
			mFocusWidget->LostFocus();
	}
}

void WidgetManager::SetFocus(Widget* aWidget)
{
	Widget* anOldFocus = mFocusWidget;
	if (anOldFocus == aWidget)
		return;

	if (anOldFocus != NULL)
		anOldFocus->LostFocus();

	if (aWidget == NULL || aWidget->mWidgetManager != this)
	{
		mFocusWidget = NULL;
	}
	else
	{
		mFocusWidget = aWidget;
		if (mHasFocus)
			aWidget->GotFocus();
	}
}

void WidgetManager::RehupMouse()
{
	if (mLastDownWidget != NULL)
	{
		if (mOverWidget != NULL &&
			GetWidgetAt(mLastMouseX, mLastMouseY, NULL, NULL) != mLastDownWidget)
		{
			Widget* anOldOver = mOverWidget;
			mOverWidget = NULL;
			MouseLeave(anOldOver);
		}
	}
	else if (mMouseIn)
	{
		MousePosition(mLastMouseX, mLastMouseY);
	}
}

void WidgetManager::DeferOverlay(Widget* theWidget, int thePriority)
{
	mDeferredOverlayWidgets.push_back(std::pair<Widget*, int>(theWidget, thePriority));

	if (thePriority < mMinDeferredOverlayPriority)
		mMinDeferredOverlayPriority = thePriority;
}

bool WidgetManager::UpdateFrame()
{
	ModalFlags aModalFlags;
	InitModalFlags(&aModalFlags);

	mUpdateCnt++;
	mLastWMUpdateCount = mUpdateCnt;

	UpdateAll(&aModalFlags);

	return mDirty;
}

bool WidgetManager::UpdateFrameF(float theFrac)
{
	ModalFlags aModalFlags;
	InitModalFlags(&aModalFlags);

	UpdateFAll(&aModalFlags, theFrac);

	return mDirty;
}

void WidgetManager::OnGestureLongPress(Point i_startingLocation)
{
	Widget* aWidget = GetWidgetAt(i_startingLocation.mX, i_startingLocation.mY, NULL, NULL);
	if (aWidget != NULL)
		aWidget->OnGestureLongPress(i_startingLocation);
}

void WidgetManager::OnGestureFlick(GestureFlickDirection i_direction, Point i_startingLocation)
{
	Widget* aWidget = GetWidgetAt(i_startingLocation.mX, i_startingLocation.mY, NULL, NULL);
	if (aWidget != NULL)
		aWidget->OnGestureFlick(i_direction, i_startingLocation);
}

void WidgetManager::OnGesturePinch(Point i_centerPoint, int i_distanceBetweenFingersSquared, float i_scaleDelta)
{
	Widget* aWidget = GetWidgetAt(i_centerPoint.mX, i_centerPoint.mY, NULL, NULL);
	if (aWidget != NULL)
		aWidget->OnGesturePinch(i_centerPoint, i_distanceBetweenFingersSquared, i_scaleDelta);
}

bool WidgetManager::MouseUp(int x, int y, int theClickCount)
{
	mLastInputUpdateCnt = mUpdateCnt;

	int aDownCode;
	if (theClickCount < 0)
		aDownCode = 2;
	else if (theClickCount == 3)
		aDownCode = 4;
	else
		aDownCode = 1;

	Widget* aLastDownWidget = mLastDownWidget;
	int anOldDownButtons = mDownButtons;

	mActualDownButtons &= ~aDownCode;
	mDownButtons &= ~aDownCode;

	if (aLastDownWidget != NULL && (anOldDownButtons & aDownCode) != 0)
	{
		if (mDownButtons == 0)
			mLastDownWidget = NULL;

		aLastDownWidget->mIsDown = false;
		Point aPos = aLastDownWidget->GetAbsPos();
		aLastDownWidget->MouseUp(x - aPos.mX, y - aPos.mY, theClickCount);
	}

	MousePosition(x, y);
	return true;
}

bool WidgetManager::MouseDown(int x, int y, int theClickCount)
{
	mLastInputUpdateCnt = mUpdateCnt;

	if (theClickCount < 0)
		mActualDownButtons |= 2;
	else if (theClickCount == 3)
		mActualDownButtons |= 4;
	else
		mActualDownButtons |= 1;

	MousePosition(x, y);

	if (mPopupCommandWidget != NULL && !mPopupCommandWidget->Contains(x, y))
		RemovePopupCommandWidget();

	int aWidgetX, aWidgetY;
	Widget* aWidget = GetWidgetAt(x, y, &aWidgetX, &aWidgetY);
	Widget* aDownWidget = mLastDownWidget != NULL ? mLastDownWidget : aWidget;

	if (theClickCount < 0)
	{
		mLastDownButtonId = -1;
		mDownButtons |= 2;
	}
	else if (theClickCount == 3)
	{
		mLastDownButtonId = 2;
		mDownButtons |= 4;
	}
	else
	{
		mLastDownButtonId = 1;
		mDownButtons |= 1;
	}

	mLastDownWidget = aDownWidget;
	if (aDownWidget != NULL)
	{
		if (aDownWidget->WantsFocus())
			SetFocus(aDownWidget);

		aDownWidget->mIsDown = true;
		aDownWidget->MouseDown(aWidgetX, aWidgetY, theClickCount);
	}

	return true;
}

bool WidgetManager::MouseMove(int x, int y)
{
	mLastInputUpdateCnt = mUpdateCnt;

	if (mDownButtons != 0)
		return MouseDrag(x, y);

	mMouseIn = true;
	MousePosition(x, y);
	return true;
}

bool WidgetManager::MouseDrag(int x, int y)
{
	Widget* anOverWidget = mOverWidget;

	mLastInputUpdateCnt = mUpdateCnt;
	mLastMouseX = x;
	mMouseIn = true;
	mLastMouseY = y;

	if (anOverWidget != NULL && anOverWidget != mLastDownWidget)
	{
		mOverWidget = NULL;
		MouseLeave(anOverWidget);
	}

	if (mLastDownWidget != NULL)
	{
		Point aPos = mLastDownWidget->GetAbsPos();
		mLastDownWidget->MouseDrag(x - aPos.mX, y - aPos.mY);

		Widget* aWidget = GetWidgetAt(x, y, NULL, NULL);
		if (aWidget == mLastDownWidget && aWidget != NULL)
		{
			if (mOverWidget == NULL)
			{
				mOverWidget = mLastDownWidget;
				MouseEnter(mLastDownWidget);
			}
		}
		else if (mOverWidget != NULL)
		{
			Widget* anOldOver = mOverWidget;
			mOverWidget = NULL;
			MouseLeave(anOldOver);
		}
	}

	return true;
}

static Point gTouchEndedMousePos;

void WidgetManager::TouchEnded(const Touch& theTouch)
{
	int aTouches = mTouches - 1;
	if (aTouches < 0)
		aTouches = 0;

	Widget* aDownWidget = mLastDownWidget;

	mActualDownButtons &= ~1;
	mLastInputUpdateCnt = mUpdateCnt;
	mTouches = aTouches;

	if (aDownWidget == NULL || (mDownButtons & 1) == 0)
	{
		mDownButtons &= ~1;
	}
	else
	{
		if (aTouches == 0)
			mDownButtons &= ~1;

		Widget* aWidget = GetWidgetAt(theTouch.location.mX, theTouch.location.mY, NULL, NULL);
		if (aWidget != NULL && mLastDownWidget != aWidget)
		{
			if (aWidget->ShouldReceiveAllOverTouchEvents())
			{
				Touch aTouch = theTouch;
				Point aPos = aWidget->GetAbsPos();
				aTouch.location.mX -= aPos.mX;
				aTouch.previousLocation.mX -= aPos.mX;
				aTouch.location.mY -= aPos.mY;
				aTouch.previousLocation.mY -= aPos.mY;
				aWidget->TouchEnded(aTouch);
			}
		}

		if (mDownButtons == 0)
			mLastDownWidget = NULL;

		Touch aTouch = theTouch;
		Point aPos = aDownWidget->GetAbsPos();
		aTouch.location.mX -= aPos.mX;
		aTouch.previousLocation.mX -= aPos.mX;
		aTouch.location.mY -= aPos.mY;
		aTouch.previousLocation.mY -= aPos.mY;
		aDownWidget->mIsDown = false;
		aDownWidget->TouchEnded(aTouch);
	}

	MousePosition(gTouchEndedMousePos.mX, gTouchEndedMousePos.mY);
}

void WidgetManager::DisableWidget(Widget* theWidget)
{
	if (mOverWidget == theWidget)
	{
		mOverWidget = NULL;
		MouseLeave(theWidget);
	}

	if (mLastDownWidget == theWidget)
	{
		mLastDownWidget = NULL;
		DoMouseUps(theWidget, mDownButtons);
		mDownButtons = 0;
	}

	if (mFocusWidget == theWidget)
	{
		mFocusWidget = NULL;
		theWidget->LostFocus();
	}

	if (mBaseModalWidget == theWidget)
	{
		mBaseModalWidget = NULL;
	}
}

void WidgetManager::MousePosition(int x, int y)
{
	int anOldMouseX = mLastMouseX;
	int anOldMouseY = mLastMouseY;
	mLastMouseX = x;
	mLastMouseY = y;

	int aWidgetX, aWidgetY;
	Widget* aNewOver = GetWidgetAt(x, y, &aWidgetX, &aWidgetY);
	Widget* anOldOver = mOverWidget;

	if (anOldOver != aNewOver)
	{
		mOverWidget = NULL;
		if (anOldOver != NULL)
			MouseLeave(anOldOver);

		mOverWidget = aNewOver;
		if (aNewOver != NULL)
		{
			MouseEnter(aNewOver);
			aNewOver->MouseMove(aWidgetX, aWidgetY);
		}
	}
	else if (anOldMouseX != x || anOldMouseY != y)
	{
		if (anOldOver != NULL)
			anOldOver->MouseMove(aWidgetX, aWidgetY);
	}
}

void WidgetManager::DoMouseUps(Widget* theWidget, ulong theDownCode)
{
	int aClickCounts[3] = {1, -1, 3};

	for (int i = 0; i < 3; i++)
	{
		if (theDownCode & (1 << i))
		{
			theWidget->mIsDown = false;
			theWidget->MouseUp(mLastMouseX - theWidget->mX, mLastMouseY - theWidget->mY, aClickCounts[i]);
		}
	}
}

void WidgetManager::AddBaseModal(Widget* theWidget, const FlagsMod& theBelowFlagsMod)
{
	if (mBaseModalWidget != theWidget)
	{
		PreModalInfo aPreModalInfo;
		aPreModalInfo.mPrevBaseModalWidget = mBaseModalWidget;
		aPreModalInfo.mPrevFocusWidget = mFocusWidget;
		aPreModalInfo.mPrevBelowModalFlagsMod = mBelowModalFlagsMod;
		aPreModalInfo.mBaseModalWidget = theWidget;
		mPreModalInfoList.push_back(aPreModalInfo);

		SetBaseModal(theWidget, theBelowFlagsMod);
	}
}

void WidgetManager::RemoveBaseModal(Widget* theWidget)
{
	bool aCheckWidget = true;

	while (mPreModalInfoList.size() != 0)
	{
		PreModalInfo& aPreModalInfo = mPreModalInfoList.back();

		if (aCheckWidget && aPreModalInfo.mBaseModalWidget != theWidget)
			return;

		bool aDone = aPreModalInfo.mPrevBaseModalWidget != NULL || mPreModalInfoList.size() == 1;

		SetBaseModal(aPreModalInfo.mPrevBaseModalWidget, aPreModalInfo.mPrevBelowModalFlagsMod);

		if (mFocusWidget == NULL)
		{
			mFocusWidget = aPreModalInfo.mPrevFocusWidget;
			if (mFocusWidget != NULL)
				mFocusWidget->GotFocus();
		}

		mPreModalInfoList.pop_back();

		if (aDone)
			return;

		aCheckWidget = false;
	}
}

void WidgetManager::SetBaseModal(Widget* theWidget, const FlagsMod& theBelowFlagsMod)
{
	mBaseModalWidget = theWidget;
	mBelowModalFlagsMod = theBelowFlagsMod;

	if (mOverWidget != NULL && (mBelowModalFlagsMod.mRemoveFlags & WIDGETFLAGS_ALLOW_MOUSE) &&
		IsBelow(mOverWidget, mBaseModalWidget))
	{
		Widget* anOldOverWidget = mOverWidget;
		mOverWidget = NULL;
		MouseLeave(anOldOverWidget);
	}

	if (mLastDownWidget != NULL && (mBelowModalFlagsMod.mRemoveFlags & WIDGETFLAGS_ALLOW_MOUSE) &&
		IsBelow(mLastDownWidget, mBaseModalWidget))
	{
		int anOldDownButtons = mDownButtons;
		Widget* anOldLastDownWidget = mLastDownWidget;
		mDownButtons = 0;
		mLastDownWidget = NULL;
		DoMouseUps(anOldLastDownWidget, anOldDownButtons);
	}

	if (mFocusWidget != NULL && (mBelowModalFlagsMod.mRemoveFlags & WIDGETFLAGS_ALLOW_FOCUS) &&
		IsBelow(mFocusWidget, mBaseModalWidget))
	{
		Widget* anOldFocusWidget = mFocusWidget;
		mFocusWidget = NULL;
		anOldFocusWidget->LostFocus();
	}
}

WidgetManager::~WidgetManager()
{
	FreeResources();
}

WidgetManager::WidgetManager(SexyAppBase* theApplet)
{
	mWidgetManager = this;
	mMinDeferredOverlayPriority = 0x7FFFFFFF;
	mApp = theApplet;
	mHasFocus = true;
	mDefaultTab = NULL;
	mDefaultBelowModalFlagsMod.mRemoveFlags = WIDGETFLAGS_ALLOW_MOUSE | WIDGETFLAGS_ALLOW_FOCUS;
	mImage = NULL;
	mLastHadTransients = false;
	mPopupCommandWidget = NULL;
	mFocusWidget = NULL;
	mLastDownWidget = NULL;
	mOverWidget = NULL;
	mBaseModalWidget = NULL;
	mGamepadSelectionWidget = NULL;
	mWidth = 0;
	mHeight = 0;
	mUpdateCnt = 0;
	mMouseIn = false;
	mLastDownButtonId = 0;
	mDownButtons = 0;
	mActualDownButtons = 0;
	mTouches = 0;
	mWidgetFlags = WIDGETFLAGS_UPDATE | WIDGETFLAGS_DRAW | WIDGETFLAGS_CLIP |
		WIDGETFLAGS_ALLOW_MOUSE | WIDGETFLAGS_ALLOW_FOCUS;
	for (int i = 0; i < 0xFF; i++)
		mKeyDown[i] = false;
}
