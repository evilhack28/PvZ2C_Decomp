//
//  Widget.cpp
//
//  SexyAppFramework, PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "Widget.h"
#include "WidgetManager.h"
#include "ReflectionBuilder.h"

using namespace Sexy;

RT_CLASS_IMPLEMENT(Widget);
void Widget::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(Widget);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(WidgetContainer);

	REFLECTION_CLASSBUILDER_END(Widget);
}

Widget::Widget()
{
	mWidgetManager = NULL;
	mDisabled = false;
	mVisible = true;
	mMouseVisible = true;
	mIsDown = false;
	mIsOver = false;
	mDoFinger = false;
	mHasFocus = false;
	mHasTransparencies = false;
	mWantsFocus = false;
	mTabPrev = NULL;
	mTabNext = NULL;
	mDataMenuId = -1;
	mReceiveAllOverTouchEvents = false;
}

Widget::~Widget()
{
	mColors.clear();
}

//////////////// empty virtual overrides ////////////////

void Widget::MouseEnter() {}
void Widget::MouseLeave() {}
void Widget::MouseWheel(int theDelta) {}
void Widget::DrawOverlay(Graphics* g) {}
void Widget::OnGestureFlick(GestureFlickDirection theDirection, Point theStartingLocation) {}
void Widget::OnGesturePinch(Point theCenterPoint, int theDistanceBetweenFingersSquared, float theScaleDelta) {}
void Widget::TouchesCanceled() {}
void Widget::OnGestureLongPress(Point theStartingLocation) {}
void Widget::OrderInManagerChanged() {}
void Widget::Draw(Graphics* g) {}
void Widget::KeyUp(KeyCode theKey) {}
void Widget::Update()
{
	WidgetContainer::Update();
}

void Widget::UpdateF(float theFrac) {}
void Widget::KeyChar(SexyChar theChar) {}

void Widget::KeyDown(KeyCode theKey)
{
	if (theKey == KEYCODE_TAB)
	{
		if (mWidgetManager->mKeyDown[KEYCODE_SHIFT])
		{
			if (mTabPrev != NULL)
				mWidgetManager->SetFocus(mTabPrev);
		}
		else
		{
			if (mTabNext != NULL)
				mWidgetManager->SetFocus(mTabNext);
		}
	}
}
void Widget::MouseUp(int x, int y) {}
void Widget::MouseUp(int x, int y, int theBtnNum, int theClickCount) {}
void Widget::MouseDown(int x, int y, int theBtnNum, int theClickCount) {}
void Widget::MouseDrag(int x, int y) {}
void Widget::MouseMove(int x, int y) {}

//////////////// small accessors ////////////////

bool Widget::WantsFocus()
{
	return mWantsFocus;
}

bool Widget::IsPointVisible(int x, int y)
{
	return true;
}

void Widget::LostFocus()
{
	mHasFocus = false;
}

void Widget::GotFocus()
{
	mHasFocus = true;
}

bool Widget::Contains(int theX, int theY)
{
	return theX >= mX && theX < mX + mWidth &&
		theY >= mY && theY < mY + mHeight;
}

Rect Widget::GetInsetRect()
{
	return Rect(mX + mMouseInsets.mLeft, mY + mMouseInsets.mTop,
		mWidth - mMouseInsets.mLeft - mMouseInsets.mRight,
		mHeight - mMouseInsets.mTop - mMouseInsets.mBottom);
}

//////////////// resize / move ////////////////

void Widget::Move(int theNewX, int theNewY)
{
	Resize(theNewX, theNewY, mWidth, mHeight);
}

void Widget::Translate(int theX, int theY)
{
	Resize(mX + theX, mY + theY, mWidth, mHeight);
}

void Widget::Resize(const Rect& theRect)
{
	Resize(theRect.mX, theRect.mY, theRect.mWidth, theRect.mHeight);
}

//////////////// touch forwarding ////////////////

void Widget::TouchMoved(const Touch& theTouch)
{
	MouseDrag(theTouch.location.mX, theTouch.location.mY);
}

void Widget::TouchBegan(const Touch& theTouch)
{
	MouseDown(theTouch.location.mX, theTouch.location.mY, 1);
}

void Widget::TouchEnded(const Touch& theTouch)
{
	MouseUp(theTouch.location.mX, theTouch.location.mY, 1);
}

//////////////// visibility / enable ////////////////

void Widget::SetVisible(bool isVisible)
{
	if (mVisible == isVisible)
		return;

	mVisible = isVisible;

	if (isVisible)
		MarkDirty();
	else
		MarkDirtyFull();

	if (mWidgetManager)
		mWidgetManager->RehupMouse();
}

void Widget::SetDisabled(bool isDisabled)
{
	if (mDisabled == isDisabled)
		return;

	mDisabled = isDisabled;

	if (isDisabled)
	{
		if (mWidgetManager)
			mWidgetManager->DisableWidget(this);

		MarkDirty();
	}
	else
	{
		MarkDirty();

		if (mWidgetManager && Contains(mWidgetManager->mLastMouseX, mWidgetManager->mLastMouseY))
			mWidgetManager->MousePosition(mWidgetManager->mLastMouseX, mWidgetManager->mLastMouseY);
	}
}

void Widget::DeferOverlay(int thePriority)
{
	mWidgetManager->DeferOverlay(this, thePriority);
}

void Widget::Resize(int theX, int theY, int theWidth, int theHeight)
{
	if (mX == theX && mY == theY && mWidth == theWidth && mHeight == theHeight)
		return;

	MarkDirtyFull();

	mX = theX;
	mY = theY;
	mWidth = theWidth;
	mHeight = theHeight;

	MarkDirty();

	if (mWidgetManager)
		mWidgetManager->RehupMouse();
}

void Widget::MouseDown(int x, int y, int theClickCount)
{
	if (theClickCount == 3)
		MouseDown(x, y, 2, 1);
	else if (theClickCount >= 0)
		MouseDown(x, y, 0, theClickCount);
	else
		MouseDown(x, y, 1, -theClickCount);
}

void Widget::MouseUp(int x, int y, int theLastDownButtonId)
{
	MouseUp(x, y);

	if (theLastDownButtonId == 3)
		MouseUp(x, y, 2, 1);
	else if (theLastDownButtonId >= 0)
		MouseUp(x, y, 0, theLastDownButtonId);
	else
		MouseUp(x, y, 1, -theLastDownButtonId);
}

void Widget::DrawOverlay(Graphics* g, int thePriority)
{
	DrawOverlay(g);
}

void Widget::SetColors(int theColors[][3], int theNumColors)
{
	mColors.clear();
	for (int i = 0; i < theNumColors; i++)
		SetColor(i, Color(theColors[i][0], theColors[i][1], theColors[i][2]));
	MarkDirty();
}

void Widget::SetColors(int theColors[][4], int theNumColors)
{
	mColors.clear();
	for (int i = 0; i < theNumColors; i++)
		SetColor(i, Color(theColors[i][0], theColors[i][1], theColors[i][2], theColors[i][3]));
	MarkDirty();
}

void Widget::SetColor(int theIdx, const Color& theColor)
{
	if (theIdx >= (int)mColors.size())
		mColors.resize(theIdx + 1);

	mColors[theIdx] = theColor;

	MarkDirty();
}

const Color& Widget::GetColor(int theIdx)
{
	static Color sDefaultColor;
	if (theIdx < (int)mColors.size())
		return mColors[theIdx];
	return sDefaultColor;
}

Color Widget::GetColor(int theIdx, const Color& theDefaultColor)
{
	if (theIdx < (int)mColors.size())
		return mColors[theIdx];
	return theDefaultColor;
}

int Widget::GetWordWrappedHeight(Graphics* g, int theWidth, const SexyString& theLine, int aLineSpacing)
{
	return g->GetWordWrappedHeight(theWidth, theLine, aLineSpacing, NULL, NULL);
}

int Widget::GetNumDigits(int theNumber)
{
	int aNumDigits = 1;
	if (theNumber > 9)
	{
		int aPow = 10;
		do
		{
			aPow *= 10;
			aNumDigits++;
		} while (theNumber >= aPow);
	}
	return aNumDigits;
}

void Widget::ShowFinger(bool on)
{
	if (mWidgetManager == NULL)
		return;

	if (on)
		mWidgetManager->mApp->SetCursor(CURSOR_HAND);
	else
		mWidgetManager->mApp->SetCursor(CURSOR_POINTER);
}
