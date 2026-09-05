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

	Widget* aWidget = mFocusWidget;
	if (theChar == KEYCODE_TAB && mKeyDown[KEYCODE_CONTROL])
		aWidget = mDefaultTab;

	if (aWidget != NULL)
		aWidget->KeyChar(theChar);

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
	volatile int aClickCounts[3] = {1, -1, 3};

	if (theDownCode & 1)
	{
		theWidget->mIsDown = false;
		theWidget->MouseUp(mLastMouseX - theWidget->mX, mLastMouseY - theWidget->mY, aClickCounts[0]);
	}

	if (theDownCode & 2)
	{
		theWidget->mIsDown = false;
		theWidget->MouseUp(mLastMouseX - theWidget->mX, mLastMouseY - theWidget->mY, aClickCounts[1]);
	}

	if (theDownCode & 4)
	{
		theWidget->mIsDown = false;
		theWidget->MouseUp(mLastMouseX - theWidget->mX, mLastMouseY - theWidget->mY, aClickCounts[2]);
	}
}

void WidgetManager::AddBaseModal(Widget* theWidget, const FlagsMod& theBelowFlagsMod)
{
	if (mBaseModalWidget != theWidget)
	{
		PreModalInfo aPreModalInfo;
		aPreModalInfo.mBaseModalWidget = theWidget;
		aPreModalInfo.mPrevBaseModalWidget = mBaseModalWidget;
		aPreModalInfo.mPrevFocusWidget = mFocusWidget;
		aPreModalInfo.mPrevBelowModalFlagsMod = mBelowModalFlagsMod;
		mPreModalInfoList.push_back(aPreModalInfo);

		SetBaseModal(theWidget, theBelowFlagsMod);
	}
}

void WidgetManager::SetBaseModal(Widget* theWidget, const FlagsMod& theBelowFlagsMod)
{
	mBaseModalWidget = theWidget;
	mBelowModalFlagsMod = theBelowFlagsMod;

	if (mOverWidget != NULL)
	{
		if (mBelowModalFlagsMod.mRemoveFlags & WIDGETFLAGS_ALLOW_MOUSE)
		{
			if (IsBelow(mOverWidget, mBaseModalWidget))
			{
				Widget* anOldOverWidget = mOverWidget;
				mOverWidget = NULL;
				MouseLeave(anOldOverWidget);
			}
		}
	}

	if (mLastDownWidget != NULL)
	{
		if (mBelowModalFlagsMod.mRemoveFlags & WIDGETFLAGS_ALLOW_MOUSE)
		{
			if (IsBelow(mLastDownWidget, mBaseModalWidget))
			{
				Widget* anOldLastDownWidget = mLastDownWidget;
				int anOldDownButtons = mDownButtons;
				mDownButtons = 0;
				mLastDownWidget = NULL;
				DoMouseUps(anOldLastDownWidget, anOldDownButtons);
			}
		}
	}

	if (mFocusWidget != NULL)
	{
		if (mBelowModalFlagsMod.mRemoveFlags & WIDGETFLAGS_ALLOW_FOCUS)
		{
			if (IsBelow(mFocusWidget, mBaseModalWidget))
			{
				Widget* anOldFocusWidget = mFocusWidget;
				mFocusWidget = NULL;
				anOldFocusWidget->LostFocus();
			}
		}
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
	mDefaultBelowModalFlagsMod.mRemoveFlags = WIDGETFLAGS_ALLOW_MOUSE | WIDGETFLAGS_ALLOW_FOCUS;
	mDefaultTab = NULL;
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
	for (int i = 0; i < 0xFF; i++)
		mKeyDown[i] = false;
	mWidgetFlags = WIDGETFLAGS_UPDATE | WIDGETFLAGS_DRAW | WIDGETFLAGS_CLIP |
		WIDGETFLAGS_ALLOW_MOUSE | WIDGETFLAGS_ALLOW_FOCUS;
}
