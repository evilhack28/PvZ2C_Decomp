// ScrollbarWidget.cpp
//
// Source: PopCap Games Framework (SexyAppFramework), open source release.
// https://github.com/LolHacksRule/sexy/blob/master/source/SexyAppFramework/ScrollbarWidget.cpp
// Functions that differ in the game build are rewritten from the game's code; the rest is the original.

#include "ScrollbarWidget.h"
#include "WidgetManager.h"
#include "ScrollListener.h"
#include "ScrollbuttonWidget.h"

using namespace Sexy;

ScrollbarWidget::~ScrollbarWidget()
{
    if (mUpButton)
        RemoveWidget(mUpButton);
    delete mUpButton;
    if (mDownButton)
        RemoveWidget(mDownButton);
    delete mDownButton;
}

void ScrollbarWidget::SetInvisIfNoScroll(bool invisIfNoScroll)
{
	mInvisIfNoScroll = invisIfNoScroll;

	if (mInvisIfNoScroll) 
	{
		SetVisible(false);
		mDownButton->SetVisible(false);
		mUpButton->SetVisible(false);
	}
}

void ScrollbarWidget::SetHorizontal(bool isHorizontal)
{
	mHorizontal = isHorizontal;
	mDownButton->mHorizontal = mHorizontal;
	mUpButton->mHorizontal = mHorizontal;
}

void ScrollbarWidget::ResizeScrollbar(int theX, int theY, int theWidth, int theHeight)
{
    Resize(theX, theY, theWidth, theHeight);
    if (mHorizontal)
    {
        int aButtonLength = mButtonLength > 0 ? mButtonLength : theHeight;
        mUpButton->Resize(0, 0, aButtonLength, theHeight);
        mDownButton->Resize(theWidth - aButtonLength, 0, aButtonLength, theHeight);
    }
    else
    {
        int aButtonLength = mButtonLength > 0 ? mButtonLength : theWidth;
        mUpButton->Resize(0, 0, theWidth, aButtonLength);
        mDownButton->Resize(0, theHeight - aButtonLength, theWidth, aButtonLength);
    }
}

void ScrollbarWidget::SetMaxValue(double theNewMaxValue) 
{
	mMaxValue = theNewMaxValue;
	ClampValue();
	MarkDirty();
}

void ScrollbarWidget::SetPageSize(double theNewPageSize) 
{
	mPageSize = theNewPageSize;
	ClampValue();
	MarkDirty();
}

void ScrollbarWidget::SetValue(double theNewValue) 
{
	mValue = theNewValue;		
	ClampValue();
	mScrollListener->ScrollPosition(mId, mValue);
	MarkDirty();
}

bool ScrollbarWidget::AtBottom() 
{
	return mMaxValue - mPageSize - mValue <= 1.0;
}

void ScrollbarWidget::GoToBottom() 
{
	mValue = mMaxValue - mPageSize;
	ClampValue();
	SetValue(mValue);
}

int ScrollbarWidget::GetTrackSize()
{
    if (mButtonLength > 0)
    {
        if (mHorizontal)
            return mWidth - 2 * mButtonLength;
        else
            return mHeight - 2 * mButtonLength;
    }

    if (mHorizontal)
        return mWidth - 2 * mUpButton->mWidth;
    else
        return mHeight - 2 * mUpButton->mHeight;
}

int ScrollbarWidget::GetThumbSize() 
{
	if (mPageSize > mMaxValue)
		return 0;
		
	int aThumbSize = (int) ((double) ((GetTrackSize() * mPageSize / mMaxValue)) + 0.5);
	return max(8, aThumbSize);
}

int ScrollbarWidget::GetThumbPosition()
{
    if (mPageSize > mMaxValue)
    {
        if (mHorizontal)
            return mUpButton->mWidth;
        return mUpButton->mHeight;
    }
    double aValue = mValue;
    return (int) (((GetTrackSize() - GetThumbSize()) * aValue / (mMaxValue - mPageSize)) + 0.5);
}

void ScrollbarWidget::ClampValue() 
{
	double anOldValue = mValue;
		
	if (mValue > mMaxValue - mPageSize)
		mValue = mMaxValue - mPageSize;
	if (mValue < 0.0)
		mValue = 0.0;
		
	bool canScroll = mPageSize < mMaxValue;
		
	SetDisabled(!canScroll);
	mUpButton->SetDisabled(!canScroll);
	mDownButton->SetDisabled(!canScroll);
				
	if (mInvisIfNoScroll) 
	{
		SetVisible(canScroll);
		mDownButton->SetVisible(canScroll);
		mUpButton->SetVisible(canScroll);
	}
		
	if (mValue != anOldValue) mScrollListener->ScrollPosition(mId, mValue);
}

void ScrollbarWidget::SetThumbPosition(int thePosition) 
{
	SetValue(((thePosition-mUpButton->mWidth) * (mMaxValue - mPageSize)) / (GetTrackSize() - GetThumbSize()));				
}

void ScrollbarWidget::ButtonPress(int theId) 
{
	mButtonAcc = 0;
		
	if (theId == 0) 
		SetValue(mValue-1);
	else 
		SetValue(mValue+1);
}

void ScrollbarWidget::ButtonDepress(int theId)
{
}

void ScrollbarWidget::ButtonDownTick(int theId)
{
	if (theId == 0) 
	{
		if (++mButtonAcc >= 25)	
		{
			SetValue(mValue-1);
			mButtonAcc = 24;	
		}
	}
	else 
	{
		if (++mButtonAcc >= 25)	
		{
			SetValue(mValue+1);
			mButtonAcc = 24;
		}
	}
}

void ScrollbarWidget::Update()
{
    Widget::Update();

    switch (mUpdateMode)
    {
    case UPDATE_MODE_PGUP:
        if (ThumbCompare(mLastMouseX, mLastMouseY) != -1)
        {
            mUpdateMode = UPDATE_MODE_IDLE;
            MarkDirty();
        }
        else if (++mUpdateAcc >= 25)
        {
            SetValue(mValue - mPageSize);
            mUpdateAcc = 20;
        }
        break;
    case UPDATE_MODE_PGDN:
        if (ThumbCompare(mLastMouseX, mLastMouseY) != 1)
        {
            mUpdateMode = UPDATE_MODE_IDLE;
            MarkDirty();
        }
        else if (++mUpdateAcc >= 25)
        {
            SetValue(mPageSize + mValue);
            mUpdateAcc = 20;
        }
        break;
    }
}

int ScrollbarWidget::ThumbCompare(int x, int y)
{
    int aTrackPosition;

    if (mHorizontal)
        aTrackPosition = x - mUpButton->mWidth;
    else
        aTrackPosition = y - mUpButton->mHeight;

    if (aTrackPosition < GetThumbPosition())
        return -1;

    if (aTrackPosition >= GetThumbPosition() + GetThumbSize())
        return 1;

    return 0;
}

void ScrollbarWidget::MouseDown(int x, int y, int theBtnNum, int theClickCount)
{
    Widget::MouseDown(x, y, theBtnNum, theClickCount);

    if (!mDisabled)
    {
        switch (ThumbCompare(x, y))
        {
        case -1:
            SetValue(mValue - mPageSize);
            mUpdateMode = UPDATE_MODE_PGUP;
            mUpdateAcc = 0;
            break;
        case 0:
            mPressedOnThumb = true;
            mMouseDownThumbPos = GetThumbPosition();
            mMouseDownX = x;
            mMouseDownY = y;
            break;
        case 1:
            SetValue(mPageSize + mValue);
            mUpdateMode = UPDATE_MODE_PGDN;
            mUpdateAcc = 0;
            break;
        }
    }

    mLastMouseX = x;
    mLastMouseY = y;
}

void ScrollbarWidget::MouseUp(int x, int y, int theBtnNum, int theClickCount) 
{
	Widget::MouseUp(x, y, theBtnNum, theClickCount);

	mUpdateMode = 0;
	mPressedOnThumb = false;
	MarkDirty();
}

void ScrollbarWidget::MouseDrag(int x, int y)
{
    Widget::MouseDrag(x, y);

    if (mPressedOnThumb)
    {
        if (mHorizontal)
            SetThumbPosition(x + mMouseDownThumbPos + mUpButton->mWidth - mMouseDownX);
        else
            SetThumbPosition(y + mMouseDownThumbPos + mUpButton->mHeight - mMouseDownY);
    }

    mLastMouseX = x;
    mLastMouseY = y;
}

void ScrollbarWidget::SetButtonImages(Image* button, Image* down, Image* disabled)
{
    mUpButton->mButtonImage = button;
    mUpButton->mDownImage = down;
    mUpButton->mDisabledImage = disabled;
    mDownButton->mButtonImage = button;
    mDownButton->mDownImage = down;
    mDownButton->mDisabledImage = disabled;
}

void ScrollbarWidget::SetThumbImage(Image* img)
{
    mThumbImage = img;
}

void ScrollbarWidget::SetBarImages(Image* theBarImage, Image* thePagingImage)
{
    mBarImage = theBarImage;
    mPagingImage = thePagingImage;
}

void ScrollbarWidget::SetButtonColors(int theColors[][3], int theNumColors)
{
    mUpButton->SetColors(theColors, theNumColors);
    mDownButton->SetColors(theColors, theNumColors);
}

void ScrollbarWidget::SetButtonColors(int theColors[][4], int theNumColors)
{
    mUpButton->SetColors(theColors, theNumColors);
    mDownButton->SetColors(theColors, theNumColors);
}

void ScrollbarWidget::SetButtonColor(int theIdx, const Color& theColor)
{
    mUpButton->SetColor(theIdx, theColor);
    mDownButton->SetColor(theIdx, theColor);
}

void ScrollbarWidget::RemoveAllWidgets(bool doDelete, bool recursive)
{
    WidgetContainer::RemoveAllWidgets(doDelete, recursive);
    if (doDelete)
    {
        mUpButton = NULL;
        mDownButton = NULL;
    }
}

void ScrollbarWidget::DrawThumb(Graphics* g, Rect theRect)
{
    DrawThumb(g, theRect.mX, theRect.mY, theRect.mWidth, theRect.mHeight);
}

