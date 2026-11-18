//
//  ScrollWidget.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-18.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/drivers/misc/iphoneos/ScrollWidget.h"
#include "SexyAppFramework/drivers/misc/iphoneos/PageControl.h"
#include "SexyAppFramework/WidgetManager.h"
#include "ReflectionBuilder.h"

namespace Sexy
{

/////////////// Accessors ///////////////

void ScrollWidget::SetScrollSnapper(ScrollSnapper *scrollSnapper)
{
	mScrollSnapper = scrollSnapper;
}

void ScrollWidget::SetPageControl(PageControl *pageControl)
{
	mPageControl = pageControl;
	if (mPagingEnabled)
		mPageControl->SetNumberOfPages(mPageCountHorizontal);
}

void ScrollWidget::SetAlignment(Alignment alignX, Alignment alignY)
{
	mAlignX = alignX;
	mAlignY = alignY;
	CacheDerivedValues();
}

void ScrollWidget::SetScrollMode(ScrollMode mode)
{
	mScrollMode = mode;
	CacheDerivedValues();
}

void ScrollWidget::SetScrollInsets(const Insets &insets)
{
	mScrollInsets = insets;
	CacheDerivedValues();
}

void ScrollWidget::SetIndicatorsInsets(const Insets &insets)
{
	mIndicatorsInsets = insets;
}

void ScrollWidget::EnablePaging(bool enable)
{
	mPagingEnabled = enable;
}

void ScrollWidget::EnableBackgroundFill(bool enable)
{
	mFillBackground = enable;
}

void ScrollWidget::EnableOverlays(bool enable)
{
	mDrawOverlays = enable;
}

void ScrollWidget::SetBackgroundImage(Image *image)
{
	mBackgroundImage = image;
}

int ScrollWidget::GetPageVertical()
{
	return mCurrentPageVertical;
}

void ScrollWidget::EnableBounce(bool enable)
{
	mBounceEnabled = enable;
}

void ScrollWidget::EnableIndicators(Image *indicatorsImage, Image *indicatorsBackgroundImage)
{
	mIndicatorsImage = indicatorsImage;
	mIndicatorsBackgroundImage = indicatorsBackgroundImage;
}

void ScrollWidget::SetPermanentIndicators(bool permanent)
{
	if (permanent)
	{
		mIndicatorsFlashTimer = 0x7fffffff;
		mIndicatorsOpacity = 1.0f;
	}
	else
	{
		mIndicatorsFlashTimer = 0;
		mIndicatorsOpacity = 0.0f;
	}
}

void ScrollWidget::SetPageHorizontal(int page, bool animated)
{
	SetPage(page, mCurrentPageVertical, animated);
}

void ScrollWidget::SetPageVertical(int page, bool animated)
{
	SetPage(mCurrentPageHorizontal, page, animated);
}

int ScrollWidget::GetPageHorizontal()
{
	return mCurrentPageHorizontal;
}

bool ScrollWidget::GetNeedsScroller() const
{
	return mScrollPractical != SCROLL_DISABLED;
}

FPoint ScrollWidget::GetScrollOffset() const
{
	return mScrollOffset;
}

FPoint ScrollWidget::GetScrollMin() const
{
	return mScrollMin;
}

FPoint ScrollWidget::GetScrollMax() const
{
	return mScrollMax;
}

Widget *ScrollWidget::GetClientWidget()
{
	return mClient;
}

bool ScrollWidget::GetIsTrackingTouch()
{
	return mScrollTracking;
}

void ScrollWidget::SetTimeDTForScrolling(const float dt)
{
	mTimeDTForScrolling = dt;
}

void ScrollWidget::ClientSizeChanged()
{
	if (mClient)
		CacheDerivedValues();
}

void ScrollWidget::CancelCurrentScroll()
{
	if (mScrollTouchID != 0)
		mScrollForcePassThrough = true;
}

void ScrollWidget::RemoveWidget(Widget *theWidget)
{
	if (mClient == theWidget)
		mClient = NULL;
	super::RemoveWidget(theWidget);
}

/////////////// Lifecycle ///////////////

ScrollWidget::ScrollWidget(ScrollWidgetListener *listener)
{
	mScrollSnapper = &DefaultScrollSnapper::GetInstance();
	Init(listener);
}

ScrollWidget::ScrollWidget()
{
	mScrollSnapper = &DefaultScrollSnapper::GetInstance();
	Init(NULL);
}

ScrollWidget::~ScrollWidget()
{
	RemoveAllWidgets(true, true);
}

void ScrollWidget::Init(ScrollWidgetListener *listener)
{
	mListener = listener;
	mScrollMode = SCROLL_VERTICAL;
	mClient = NULL;
	mClientLastDown = NULL;
	mPageControl = NULL;
	mIndicatorsProxy = NULL;
	mIndicatorsImage = NULL;
	mIndicatorsBackgroundImage = NULL;
	mAlignX = ALIGN_MIN;
	mAlignY = ALIGN_MIN;
	mScrollInsets = Insets(0, 0, 0, 0);
	mScrollTracking = false;
	mScrollForcePassThrough = false;
	mSeekScrollTarget = false;
	mBounceEnabled = true;
	mPagingEnabled = false;
	mCheckClientWidget = false;
	mClientWidgetChecked = false;
	mIndicatorsInsets = Insets(0, 0, 0, 0);
	mIndicatorsFlashTimer = 0;
	mBackgroundImage = NULL;
	mFillBackground = false;
	mDrawOverlays = false;
	mScrollTouchID = 0;
	mIndicatorsOpacity = 0.0f;
	mTimeDTForScrolling = 0.01f;
	mScrollDragThreshold = FPoint(6.0f, 6.0f);
	mWasPreviouslyScrollingToTarget = false;
	mCircleScroll = false;
	mCircleAdditionWidth = 0;
	mThresholdScale = 1.0f;
	mScrollOffset = FPoint(0.0f, 0.0f);
	mScrollVelocity = FPoint(0.0f, 0.0f);
	mClip = true;
	mIndicatorsProxy = new ProxyWidget(this);
	mIndicatorsProxy->mZOrder = 0x7fffffff;
	mIndicatorsProxy->mMouseVisible = false;
	mIndicatorsProxy->Resize(0, 0, mWidth, mHeight);
	super::AddWidget(mIndicatorsProxy);
}

/////////////// Layout ///////////////

/////////////// Scrolling ///////////////

void ScrollWidget::Resize(int x, int y, int width, int height)
{
	super::Resize(x, y, width, height);
	if (mIndicatorsProxy)
		mIndicatorsProxy->Resize(0, 0, width, height);
	CacheDerivedValues();
}

void ScrollWidget::AddWidget(Widget *theWidget)
{
	if (!mClient)
	{
		mClient = theWidget;
		theWidget->mWidgetFlagsMod.mRemoveFlags |= WIDGETFLAGS_ALLOW_MOUSE;
		theWidget->Move((int)mScrollOffset.mX, (int)mScrollOffset.mY);
		super::AddWidget(mClient);
		CacheDerivedValues();
	}
}

void ScrollWidget::SetScrollOffset(FPoint anOffset, bool animated)
{
	if (animated)
	{
		mScrollTarget = anOffset;
		mSeekScrollTarget = true;
	}
	else
	{
		mScrollOffset = anOffset;
		mScrollVelocity = FPoint(0.0f, 0.0f);
		if (mClient)
			mClient->Move((int)mScrollOffset.mX, (int)mScrollOffset.mY);
	}
	CircleSetScrollOffset(anOffset, animated);
}

void ScrollWidget::ScrollToMin(bool animated)
{
	SetScrollOffset(mScrollMax, animated);
}

void ScrollWidget::ScrollToPoint(const Point &point, bool animated)
{
	if (!mIsDown)
	{
		FPoint offset;
		offset.mX = -point.mX;
		offset.mY = -point.mY;
		SetScrollOffset(offset, animated);
	}
}

void ScrollWidget::SetPage(int hpage, int vpage, bool animated)
{
	if (mPagingEnabled)
	{
		mCurrentPageHorizontal = std::max(0, std::min(hpage, mPageCountHorizontal - 1));
		mCurrentPageVertical = std::max(0, std::min(vpage, mPageCountVertical - 1));
		FPoint offset;
		offset.mX = mScrollInsets.mLeft - mCurrentPageHorizontal * mPageSize.mX;
		offset.mY = mScrollInsets.mTop - mCurrentPageVertical * mPageSize.mY;
		SetScrollOffset(offset, animated);
	}
}

void ScrollWidget::AddOverlayImage(Image *image, const Point &offset)
{
	mDrawOverlays = true;
	Overlays::iterator it;
	for (it = mOverlays.begin(); it != mOverlays.end(); ++it)
	{
		if (it->image == image)
		{
			it->offset = offset;
			return;
		}
	}
	Overlay overlay;
	overlay.image = image;
	overlay.offset = offset;
	mOverlays.push_back(overlay);
}

/////////////// Drawing ///////////////

void ScrollWidget::Draw(Graphics *g)
{
	super::Draw(g);
	if (mBackgroundImage)
		g->DrawImage(mBackgroundImage, 0, 0);
	else if (mFillBackground)
	{
		g->SetColor(GetColor(COLOR_BACKGROUND));
		g->FillRect(0, 0, mWidth, mHeight);
	}
}

/////////////// Touch ///////////////

void ScrollWidget::SnapToPage()
{
	FPoint center;
	center.mX = mScrollInsets.mLeft + mPageSize.mX * 0.5f;
	center.mY = mScrollInsets.mTop + mPageSize.mY * 0.5f;
	FPoint rel(center - mScrollOffset);
	int hpage = (int)floorf(rel.mX / mPageSize.mX);
	int vpage = (int)floorf(rel.mY / mPageSize.mY);
	hpage = std::max(0, std::min(hpage, mPageCountHorizontal - 1));
	vpage = std::max(0, std::min(vpage, mPageCountVertical - 1));
	FPoint target;
	target.mX = mScrollInsets.mLeft - hpage * mPageSize.mX;
	target.mY = mScrollInsets.mTop - vpage * mPageSize.mY;
	if (mScrollVelocity.mX > mThresholdScale * 60.0f && target.mX < mScrollOffset.mX)
		hpage--;
	else if (mScrollVelocity.mX < -mThresholdScale * 60.0f && target.mX > mScrollOffset.mX)
		hpage++;
	if (mThresholdScale * 60.0f < mScrollVelocity.mY && target.mY < mScrollOffset.mY)
		vpage--;
	else if (mScrollVelocity.mY < -mThresholdScale * 60.0f && target.mY > mScrollOffset.mY)
		vpage++;
	SetPage(hpage, vpage, true);
}

void ScrollWidget::TouchesCanceled()
{
	if (mClient && mClientLastDown && !mScrollTracking)
	{
		mClientLastDown->TouchesCanceled();
		mClientLastDown->mIsDown = false;
		mClientLastDown = NULL;
	}
	if (mScrollTracking)
		mScrollSnapper->DoSnap(this);
	mScrollTracking = false;
	mScrollTouchID = 0;
	MarkDirty();
}

void ScrollWidget::TouchBegan(const Touch &touch)
{
	if (mClient && mScrollTouchID == 0)
	{
		mScrollVelocity = FPoint(0.0f, 0.0f);
		mWasPreviouslyScrollingToTarget = false;
		if (mSeekScrollTarget)
		{
			mWasPreviouslyScrollingToTarget = true;
			if (mListener)
				mListener->ScrollTargetInterrupted(this);
			if (mPagingEnabled && mPageControl)
				mPageControl->SetCurrentPage(mCurrentPageHorizontal);
		}
		mScrollTouchReference = FPoint(touch.location.mX, touch.location.mY);
		mScrollOffset = mScrollOffsetReference = FPoint(mClient->mX, mClient->mY);
		mScrollTouchID = touch.ident;
		mScrollTracking = false;
		mSeekScrollTarget = false;
		mScrollForcePassThrough = false;
		mScrollLastTimestamp = touch.timestamp;
		Touch transformedTouch;
		mClientLastDown = GetClientWidgetAt(touch, transformedTouch);
		if (mClientLastDown->WantsFocus())
			mWidgetManager->SetFocus(mClientLastDown);
		mClientLastDown->mIsDown = true;
		mClientLastDown->mIsOver = true;
		mClientLastDown->TouchBegan(transformedTouch);
		if (mCheckClientWidget)
			mClientWidgetChecked = false;
	}
	MarkDirty();
}

void ScrollWidget::TouchEnded(const Touch &touch)
{
	if (mScrollTouchID == (int32)touch.ident)
	{
		if (mScrollTracking)
		{
			TouchMotion(touch);
			mScrollTracking = false;
			mWasPreviouslyScrollingToTarget = false;
			mScrollSnapper->DoSnap(this);
			if (mPagingEnabled)
				SnapToPage();
		}
		else if (mClientLastDown)
		{
			Point delta(GetAbsPos() - mClientLastDown->GetAbsPos());
			Point touchPoint(touch.location.mX, touch.location.mY);
			Point location(touchPoint + delta);
			Touch transformedTouch(touch);
			transformedTouch.location.mX += delta.mX;
			transformedTouch.location.mY += delta.mY;
			transformedTouch.previousLocation.mX += delta.mX;
			transformedTouch.previousLocation.mY += delta.mY;
			mClientLastDown->TouchEnded(transformedTouch);
			mClientLastDown->mIsDown = false;
			mClientLastDown = NULL;
		}
		if (mWasPreviouslyScrollingToTarget)
		{
			mWasPreviouslyScrollingToTarget = false;
			mScrollSnapper->DoSnap(this);
		}
		mScrollTouchID = 0;
		if (mListener)
			mListener->ScrollTouchEnd(touch);
		MarkDirty();
	}
}

void ScrollWidget::CheckClientWidget()
{
	for (WidgetList::iterator it = mClient->mWidgets.begin(); it != mClient->mWidgets.end(); ++it)
	{
		Widget *widget = *it;
		if (widget)
		{
			bool visible = widget->mVisible;
			int x = widget->mX + mClient->mX;
			if ((double)(x + widget->mWidth) + (double)mWidth * 0.5 < 0.0 || (double)x > (double)mWidth * 1.5)
			{
				if (visible)
					widget->SetVisible(false);
			}
			else if (!visible)
				widget->SetVisible(true);
		}
	}
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(ScrollWidget);

void ScrollWidget::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ScrollWidget);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;
	REFLECTION_CLASSBUILDER_END(ScrollWidget);
}
}
