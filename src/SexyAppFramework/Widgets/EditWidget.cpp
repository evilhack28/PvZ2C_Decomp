//
//  EditWidget.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-17.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/EditWidget.h"
#include "SexyAppFramework/EditListener.h"
#include "SexyAppFramework/WidgetManager.h"
#include "SexyAppFramework/SexyAppBase.h"
#include "SexyAppFramework/Font.h"

using namespace Sexy;

/////////////// Accessors ///////////////

bool EditWidget::WantsFocus()
{
    return true;
}

bool EditWidget::IsPartOfWord(SexyChar theChar)
{
    return (((theChar >= _S('A')) && (theChar <= _S('Z'))) ||
            ((theChar >= _S('a')) && (theChar <= _S('z'))) ||
            ((theChar >= _S('0')) && (theChar <= _S('9'))) ||
            (((unsigned int)theChar >= 0xbf) && ((unsigned int)theChar <= 0x2c7)) ||
            (theChar == _S('_')));
}

void EditWidget::UpdateCaretPos()
{
}

/////////////// Layout ///////////////

void EditWidget::Resize(int theX, int theY, int theWidth, int theHeight)
{
    Widget::Resize(theX, theY, theWidth, theHeight);

    FocusCursor(false);
}

/////////////// Input ///////////////

void EditWidget::GotFocus()
{
    Widget::GotFocus();
    AttachIME();

    mShowingCursor = false;
    mBlinkAcc = 0;
    MarkDirty();
}

void EditWidget::LostFocus()
{
    Widget::LostFocus();
    DetachIME();

    mIsEditWidgetActive = false;
    mShowingCursor = false;
    MarkDirty();
}

void EditWidget::TouchBegan(const Touch& i_touch)
{
    GotFocus();
}

void EditWidget::KeyChar(SexyChar theChar)
{
    ProcessKey(KEYCODE_UNKNOWN, theChar);

    Widget::KeyChar(theChar);
}

void EditWidget::MouseEnter()
{
    Widget::MouseEnter();

    mWidgetManager->mApp->SetCursor(CURSOR_TEXT);
}

void EditWidget::MouseLeave()
{
    Widget::MouseLeave();

    mWidgetManager->mApp->SetCursor(CURSOR_POINTER);
}

/////////////// Fonts ///////////////

void EditWidget::SetFont(Font* theFont, Font* theWidthCheckFont)
{
    delete mFont;
    mFont = theFont->Duplicate();

    ClearWidthCheckFonts();
    if (theWidthCheckFont != NULL)
        AddWidthCheckFont(theWidthCheckFont);
}

void EditWidget::SetFont(PrimeTypeface* theFont, PrimeTypeface* theWidthCheckFont)
{
	mPrimeFont = theFont;
	ClearWidthCheckFonts();
	if (theWidthCheckFont)
		AddWidthCheckFont(theWidthCheckFont);
}

void EditWidget::ClearWidthCheckFonts()
{
	for (WidthCheckList::iterator anItr = mWidthCheckList.begin(); anItr != mWidthCheckList.end(); ++anItr)
		delete anItr->mFont;

	mWidthCheckList.clear();
}
