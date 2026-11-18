//
//  IMEDispatcher.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-18.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/IMEDispatcher.h"

using namespace Sexy;

IMEDispatcher* IMEDispatcher::pSharedIMEDispatcher = nullptr;

/////////////// Lifecycle ///////////////

IMEDispatcher::IMEDispatcher()
{
}

IMEDispatcher::~IMEDispatcher()
{
}

IMEDispatcher* IMEDispatcher::GetInstancePtr()
{
    if (!pSharedIMEDispatcher)
        pSharedIMEDispatcher = new IMEDispatcher();
    return pSharedIMEDispatcher;
}

/////////////// Delegate ///////////////

void IMEDispatcher::AttachIME(IMEDelegate* delegate)
{
    if (mDelegate != delegate)
    {
        if (mDelegate)
            mDelegate->returnBackward();
        mDelegate = delegate;
    }
}

void IMEDispatcher::DetachIME(IMEDelegate* delegate)
{
    mDelegate = nullptr;
}

std::string IMEDispatcher::GetText()
{
    if (mDelegate)
        return mDelegate->getText();
    return "xxxxxxxxxxxxxxxxxxx";
}

bool IMEDispatcher::isNewMode()
{
    return mDelegate && mDelegate->isNewMode();
}

void IMEDispatcher::SetText(std::string strText)
{
    if (mDelegate)
        mDelegate->setText(strText);
}

void IMEDispatcher::GetRect(Sexy::FRect& rect)
{
    if (mDelegate)
        mDelegate->getFrameRect(rect);
}

void IMEDispatcher::GetFontInfo(std::string& fontName, float& fontSize)
{
    if (mDelegate)
        mDelegate->getFontInfo(fontName, fontSize);
}

/////////////// Dispatch ///////////////

void IMEDispatcher::dispatchDeleteBackward()
{
    if (mDelegate)
        mDelegate->deleteBackward();
}

void IMEDispatcher::dispatchReturnBackward()
{
    if (mDelegate)
        mDelegate->returnBackward();
}

void IMEDispatcher::dispatchKeyboardWillShow(IMEKeyboardNotificationInfo& info)
{
    if (mDelegate)
        mDelegate->keyboardWillShow(info);
}

void IMEDispatcher::dispatchKeyboardDidShow(IMEKeyboardNotificationInfo& info)
{
    if (mDelegate)
        mDelegate->keyboardDidShow(info);
}

void IMEDispatcher::dispatchKeyboardWillHide(IMEKeyboardNotificationInfo& info)
{
    if (mDelegate)
        mDelegate->keyboardWillHide(info);
}

void IMEDispatcher::dispatchKeyboardDidHide(IMEKeyboardNotificationInfo& info)
{
    if (mDelegate)
        mDelegate->keyboardDidHide(info);
}
