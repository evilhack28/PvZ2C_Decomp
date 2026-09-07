//
//  WidgetContainer.cpp
//
//  SexyAppFramework, PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-07.
//

#include "WidgetContainer.h"
#include "Widget.h"
#include "WidgetManager.h"
#include "ReflectionBuilder.h"

using namespace Sexy;

static int gSysColorChangedCount;

RT_CLASS_IMPLEMENT(WidgetContainer);
void WidgetContainer::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WidgetContainer);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(RtObject);

	REFLECTION_CLASSBUILDER_END(WidgetContainer);
}

//////////////// empty virtual overrides ////////////////

void WidgetContainer::DisableWidget(Widget* theWidget) {}
void WidgetContainer::SetFocus(Widget* theWidget) {}
void WidgetContainer::Draw(Graphics* g) {}
void WidgetContainer::UpdateF(float theFrac) {}
void WidgetContainer::SysColorChanged() {}

void WidgetContainer::SysColorChangedAll()
{
	SysColorChanged();

	if (mWidgets.size() != 0)
		++gSysColorChangedCount;

	for (WidgetList::iterator anItr = mWidgets.begin(); anItr != mWidgets.end(); ++anItr)
		(*anItr)->SysColorChangedAll();
}

//////////////// ctor / dtor ////////////////

WidgetContainer::WidgetContainer()
{
	mX = 0;
	mY = 0;
	mWidth = 0;
	mHeight = 0;
	mParent = NULL;
	mWidgetManager = NULL;
	mUpdateIteratorModified = false;
	mLastWMUpdateCount = 0;
	mUpdateIterator = mWidgets.end();
	mUpdateCnt = 0;
	mDirty = false;
	mHasAlpha = false;
	mClip = true;
	mPriority = 0;
	mZOrder = 0;
}

WidgetContainer::~WidgetContainer()
{
}

//////////////// small accessors ////////////////

void WidgetContainer::Update()
{
	mUpdateCnt++;
}

int WidgetContainer::GetChildCount()
{
	return mWidgets.size();
}

void WidgetContainer::SetIgnoreMouseInput(bool ignore)
{
	if (ignore)
		mWidgetFlagsMod.mRemoveFlags |= WIDGETFLAGS_ALLOW_MOUSE;
	else
		mWidgetFlagsMod.mRemoveFlags &= ~WIDGETFLAGS_ALLOW_MOUSE;
}

Rect WidgetContainer::GetRect()
{
	return Rect(mX, mY, mWidth, mHeight);
}

Rect WidgetContainer::GetClipRect() const
{
	return Rect(0, 0, mWidth, mHeight);
}

bool WidgetContainer::Intersects(WidgetContainer* theWidget)
{
	return GetRect().Intersects(theWidget->GetRect());
}

Point WidgetContainer::GetAbsPos()
{
	if (mParent != NULL)
		return Point(mX, mY) + mParent->GetAbsPos();

	return Point(mX, mY);
}

//////////////// dirty ////////////////

void WidgetContainer::MarkDirty()
{
	if (mParent != NULL)
		mParent->MarkDirty(this);
	else
		mDirty = true;
}

void WidgetContainer::MarkDirtyFull()
{
	if (mParent != NULL)
		mParent->MarkDirtyFull(this);
	else
		mDirty = true;
}

void WidgetContainer::MarkDirtyFull(WidgetContainer* theWidget)
{
	MarkDirtyFull();
	theWidget->mDirty = true;

	if (mParent != NULL)
		return;

	WidgetList::iterator anItr = std::find(mWidgets.begin(), mWidgets.end(), theWidget);
	if (anItr == mWidgets.end())
		return;

	if (anItr != mWidgets.begin())
	{
		WidgetList::iterator aScan = anItr;
		--aScan;

		while (true)
		{
			Widget* aWidget = *aScan;
			if (aWidget->mVisible)
			{
				if (!aWidget->mHasTransparencies && !aWidget->mHasAlpha)
				{
					Rect aRect1(theWidget->mX, theWidget->mY, theWidget->mWidth, theWidget->mHeight);
					Rect aRect2(0, 0, mWidth, mHeight);
					Rect aRect = aRect1.Intersection(aRect2);
					if (aWidget->Contains(aRect.mX, aRect.mY) &&
					    aWidget->Contains(aRect.mX + aRect.mWidth - 1, aRect.mY + aRect.mHeight - 1))
					{
						aWidget->MarkDirty();
						break;
					}
				}

				if (aWidget->Intersects(theWidget))
					MarkDirty(aWidget);
			}

			if (aScan == mWidgets.begin())
				break;
			--aScan;
		}
	}

	for (WidgetList::iterator aFwd = anItr; aFwd != mWidgets.end(); ++aFwd)
	{
		Widget* aWidget = *aFwd;
		if (aWidget->mVisible && aWidget->Intersects(theWidget))
			MarkDirty(aWidget);
	}
}

void WidgetContainer::MarkDirty(WidgetContainer* theWidget)
{
	if (theWidget->mDirty)
		return;

	MarkDirty();
	theWidget->mDirty = true;

	if (mParent != NULL)
		return;

	if (theWidget->mHasAlpha)
	{
		MarkDirtyFull(theWidget);
		return;
	}

	bool aFound = false;
	for (WidgetList::iterator anItr = mWidgets.begin(); anItr != mWidgets.end(); ++anItr)
	{
		Widget* aWidget = *anItr;
		if (aWidget == theWidget)
		{
			aFound = true;
			continue;
		}

		if (aFound && aWidget->mVisible && aWidget->Intersects(theWidget))
			MarkDirty(aWidget);
	}
}

//////////////// z-order queries ////////////////

bool WidgetContainer::IsBelow(Widget* theWidget1, Widget* theWidget2)
{
	bool aFound = false;
	return IsBelowHelper(theWidget1, theWidget2, &aFound);
}

Widget* WidgetContainer::GetWidgetAtHelper(int theX, int theY, int theFlags, bool* found, int* theWidgetX, int* theWidgetY)
{
	int aFlags = theFlags;
	ModFlags(aFlags, mWidgetFlagsMod);

	bool aFoundModal = false;

	for (WidgetList::reverse_iterator anItr = mWidgets.rbegin(); anItr != mWidgets.rend(); ++anItr)
	{
		Widget* aWidget = *anItr;

		int aWidgetFlags = aFlags;
		ModFlags(aWidgetFlags, aWidget->mWidgetFlagsMod);
		if (aFoundModal)
			ModFlags(aWidgetFlags, mWidgetManager->mBelowModalFlagsMod);

		if ((aWidgetFlags & WIDGETFLAGS_ALLOW_MOUSE) && aWidget->mVisible)
		{
			bool aChildFound = false;
			Widget* aResult = aWidget->GetWidgetAtHelper(theX - aWidget->mX, theY - aWidget->mY, aWidgetFlags, &aChildFound, theWidgetX, theWidgetY);
			if (aResult != NULL || aChildFound)
			{
				*found = true;
				return aResult;
			}

			if (aWidget->mMouseVisible)
			{
				if (aWidget->GetInsetRect().Contains(theX, theY))
				{
					*found = true;
					if (aWidget->IsPointVisible(theX - aWidget->mX, theY - aWidget->mY))
					{
						if (theWidgetX != NULL)
							*theWidgetX = theX - aWidget->mX;
						if (theWidgetY != NULL)
							*theWidgetY = theY - aWidget->mY;

						return aWidget;
					}
				}
			}
		}

		if (mWidgetManager->mBaseModalWidget == aWidget && aWidget->mVisible)
			aFoundModal = true;
	}

	*found = false;
	return NULL;
}

bool WidgetContainer::IsBelowHelper(Widget* theWidget1, Widget* theWidget2, bool* found)
{
	for (WidgetList::iterator anItr = mWidgets.begin(); anItr != mWidgets.end(); ++anItr)
	{
		Widget* aWidget = *anItr;
		if (aWidget == theWidget1)
		{
			*found = true;
			return true;
		}

		if (aWidget == theWidget2)
		{
			*found = true;
			return false;
		}

		bool aResult = aWidget->IsBelowHelper(theWidget1, theWidget2, found);
		if (*found)
			return aResult;
	}

	return false;
}

bool WidgetContainer::HasWidget(Widget* theWidget)
{
	return std::find(mWidgets.begin(), mWidgets.end(), theWidget) != mWidgets.end();
}

void WidgetContainer::DisableAllWidgets(bool disable)
{
	for (WidgetList::iterator anItr = mWidgets.begin(); anItr != mWidgets.end(); ++anItr)
		(*anItr)->SetDisabled(disable);
}

void WidgetContainer::MarkAllDirty()
{
	MarkDirty();

	for (WidgetList::iterator anItr = mWidgets.begin(); anItr != mWidgets.end(); ++anItr)
	{
		(*anItr)->mDirty = true;
		(*anItr)->MarkAllDirty();
	}
}

void WidgetContainer::AddedToManager(WidgetManager* theWidgetManager)
{
	for (WidgetList::iterator anItr = mWidgets.begin(); anItr != mWidgets.end(); ++anItr)
	{
		Widget* aWidget = *anItr;
		aWidget->mWidgetManager = theWidgetManager;
		aWidget->AddedToManager(theWidgetManager);
		MarkDirty();
	}
}

void WidgetContainer::RemovedFromManager(WidgetManager* theWidgetManager)
{
	for (WidgetList::iterator anItr = mWidgets.begin(); anItr != mWidgets.end(); ++anItr)
	{
		Widget* aWidget = *anItr;
		theWidgetManager->DisableWidget(aWidget);
		aWidget->RemovedFromManager(theWidgetManager);
		aWidget->mWidgetManager = NULL;
	}

	if (theWidgetManager->mPopupCommandWidget == this)
		theWidgetManager->mPopupCommandWidget = NULL;
}

//////////////// add / remove ////////////////

void WidgetContainer::AddWidget(Widget* theWidget)
{
	if (std::find(mWidgets.begin(), mWidgets.end(), theWidget) == mWidgets.end())
	{
		InsertWidgetHelper(mWidgets.end(), theWidget);

		theWidget->mWidgetManager = mWidgetManager;
		theWidget->mParent = this;

		if (mWidgetManager != NULL)
		{
			theWidget->AddedToManager(mWidgetManager);
			theWidget->MarkDirtyFull();
			mWidgetManager->RehupMouse();
		}

		MarkDirty();
	}
}

void WidgetContainer::RemoveWidget(Widget* theWidget)
{
	WidgetList::iterator anItr = std::find(mWidgets.begin(), mWidgets.end(), theWidget);
	if (anItr != mWidgets.end())
	{
		theWidget->WidgetRemovedHelper();
		theWidget->mParent = NULL;

		bool anUpdate = (anItr == mUpdateIterator);
		anItr = mWidgets.erase(anItr);
		if (anUpdate)
		{
			mUpdateIterator = anItr;
			mUpdateIteratorModified = true;
		}
	}
}

void WidgetContainer::RemoveAllWidgets(bool doDelete, bool recursive)
{
	if (!recursive)
	{
		while (!mWidgets.empty())
		{
			Widget* aWidget = mWidgets.front();
			RemoveWidget(aWidget);

			if (aWidget != NULL && doDelete)
				delete aWidget;
		}
	}
	else
	{
		if (doDelete)
		{
			while (!mWidgets.empty())
			{
				Widget* aWidget = mWidgets.front();
				RemoveWidget(aWidget);
				aWidget->RemoveAllWidgets(doDelete, true);
				delete aWidget;
			}
		}
		else
		{
			while (!mWidgets.empty())
			{
				Widget* aWidget = mWidgets.front();
				RemoveWidget(aWidget);
				aWidget->RemoveAllWidgets(doDelete, true);
			}
		}
	}
}

//////////////// z-order ////////////////

void WidgetContainer::InsertWidgetHelper(const WidgetList::iterator& where, Widget* theWidget)
{
	WidgetList::iterator anItr = where;

	while (anItr != mWidgets.end() && (*anItr)->mZOrder < theWidget->mZOrder)
		++anItr;

	if (anItr != mWidgets.end())
	{
		if (anItr != mWidgets.begin())
		{
			WidgetList::iterator aPrevItr = anItr;
			--aPrevItr;

			if ((*anItr)->mZOrder > theWidget->mZOrder)
				goto scanBack;
		}

		mWidgets.insert(anItr, theWidget);
		return;
	}

scanBack:
	while (anItr != mWidgets.begin())
	{
		--anItr;
		if ((*anItr)->mZOrder <= theWidget->mZOrder)
		{
			++anItr;
			mWidgets.insert(anItr, theWidget);
			return;
		}
	}

	mWidgets.push_front(theWidget);
}

void WidgetContainer::BringToFront(Widget* theWidget)
{
	WidgetList::iterator anItr = std::find(mWidgets.begin(), mWidgets.end(), theWidget);
	if (anItr != mWidgets.end())
	{
		if (anItr == mUpdateIterator)
		{
			++mUpdateIterator;
			mUpdateIteratorModified = true;
		}

		mWidgets.erase(anItr);
		InsertWidgetHelper(mWidgets.begin(), theWidget);
		theWidget->OrderInManagerChanged();
	}
}

void WidgetContainer::BringToBack(Widget* theWidget)
{
	WidgetList::iterator anItr = std::find(mWidgets.begin(), mWidgets.end(), theWidget);
	if (anItr != mWidgets.end())
	{
		if (anItr == mUpdateIterator)
		{
			++mUpdateIterator;
			mUpdateIteratorModified = true;
		}

		mWidgets.erase(anItr);
		InsertWidgetHelper(mWidgets.end(), theWidget);
		theWidget->OrderInManagerChanged();
	}
}

void WidgetContainer::PutBehind(Widget* theWidget, Widget* theRefWidget)
{
	if (theRefWidget != NULL)
		theWidget->mZOrder = theRefWidget->mZOrder;

	WidgetList::iterator anItr = std::find(mWidgets.begin(), mWidgets.end(), theWidget);
	if (anItr != mWidgets.end())
	{
		if (anItr == mUpdateIterator)
		{
			++mUpdateIterator;
			mUpdateIteratorModified = true;
		}

		mWidgets.erase(anItr);

		anItr = std::find(mWidgets.begin(), mWidgets.end(), theRefWidget);
		InsertWidgetHelper(anItr, theWidget);
		theWidget->OrderInManagerChanged();
	}
}

void WidgetContainer::PutInfront(Widget* theWidget, Widget* theRefWidget)
{
	if (theRefWidget != NULL)
		theWidget->mZOrder = theRefWidget->mZOrder;

	WidgetList::iterator anItr = std::find(mWidgets.begin(), mWidgets.end(), theWidget);
	if (anItr != mWidgets.end())
	{
		if (anItr == mUpdateIterator)
		{
			++mUpdateIterator;
			mUpdateIteratorModified = true;
		}

		mWidgets.erase(anItr);

		anItr = std::find(mWidgets.begin(), mWidgets.end(), theRefWidget);
		if (anItr != mWidgets.end())
			++anItr;

		InsertWidgetHelper(anItr, theWidget);
		theWidget->OrderInManagerChanged();
	}
}

//////////////// update / draw recursion ////////////////

void WidgetContainer::UpdateAll(ModalFlags* theFlags)
{
	AutoModalFlags anAutoFlags(theFlags, mWidgetFlagsMod);

	if (theFlags->GetFlags() & WIDGETFLAGS_MARK_DIRTY)
		MarkDirty();

	WidgetManager* aWidgetManager = mWidgetManager;
	if (aWidgetManager == NULL)
		return;

	if (theFlags->GetFlags() & WIDGETFLAGS_UPDATE)
	{
		if (mLastWMUpdateCount != (ulong)aWidgetManager->mUpdateCnt)
		{
			mLastWMUpdateCount = aWidgetManager->mUpdateCnt;
			Update();
		}
	}

	for (mUpdateIterator = mWidgets.begin(); mUpdateIterator != mWidgets.end(); )
	{
		mUpdateIteratorModified = false;
		Widget* aWidget = *mUpdateIterator;

		if (aWidget == aWidgetManager->mBaseModalWidget)
			theFlags->mIsOver = true;

		aWidget->UpdateAll(theFlags);

		if (!mUpdateIteratorModified)
			++mUpdateIterator;
	}

	mUpdateIteratorModified = true;
}

void WidgetContainer::UpdateFAll(ModalFlags* theFlags, float theFrac)
{
	AutoModalFlags anAutoFlags(theFlags, mWidgetFlagsMod);

	WidgetManager* aWidgetManager = mWidgetManager;
	if (aWidgetManager == NULL)
		return;

	if (theFlags->GetFlags() & WIDGETFLAGS_UPDATE)
		UpdateF(theFrac);

	for (mUpdateIterator = mWidgets.begin(); mUpdateIterator != mWidgets.end(); )
	{
		mUpdateIteratorModified = false;
		Widget* aWidget = *mUpdateIterator;

		if (aWidget == aWidgetManager->mBaseModalWidget)
			theFlags->mIsOver = true;

		aWidget->UpdateFAll(theFlags, theFrac);

		if (!mUpdateIteratorModified)
			++mUpdateIterator;
	}

	mUpdateIteratorModified = true;
}

void WidgetContainer::DrawAll(ModalFlags* theFlags, Graphics* g)
{
	if (mWidgetManager != NULL && mPriority > mWidgetManager->mMinDeferredOverlayPriority)
		mWidgetManager->FlushDeferredOverlayWidgets(mPriority);

	AutoModalFlags anAutoFlags(theFlags, mWidgetFlagsMod);

	if (mClip && (theFlags->GetFlags() & WIDGETFLAGS_CLIP))
		g->ClipRect(GetClipRect());

	if (mWidgets.size() == 0)
	{
		if (theFlags->GetFlags() & WIDGETFLAGS_DRAW)
			Draw(g);

		return;
	}

	if (theFlags->GetFlags() & WIDGETFLAGS_DRAW)
	{
		g->PushState();
		Draw(g);
		g->PopState();
	}

	for (WidgetList::iterator anItr = mWidgets.begin(); anItr != mWidgets.end(); ++anItr)
	{
		Widget* aWidget = *anItr;
		if (!aWidget->mVisible)
			continue;

		if (mWidgetManager != NULL && aWidget == mWidgetManager->mBaseModalWidget)
			theFlags->mIsOver = true;

		g->PushState();
		g->Translate(aWidget->mX, aWidget->mY);
		aWidget->DrawAll(theFlags, g);
		aWidget->mDirty = false;
		g->PopState();
	}
}

bool WidgetContainer::OnBackButtonPressed()
{
	for (WidgetList::reverse_iterator anItr = mWidgets.rbegin(); anItr != mWidgets.rend(); ++anItr)
	{
		if ((*anItr)->OnBackButtonPressed())
			return true;
	}

	return false;
}
