//
//  PuzzleTipUtil.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/Rect.h"
#include "SexyAppFramework/Graphics.h"
#include "SexyAppFramework/Image.h"
#include "SexyAppFramework/Widget.h"
#include "PrimeText/PrimeTypeface.h"
#include "TodLib/TodCommon.h"

using namespace Sexy;

#include "PuzzleTip.h"
#include "PuzzleTipUtil.h"
#include "LawnApp.h"
#include "ScaledApp.h"

/////////////// PuzzleTipUtil ///////////////

PuzzleTip* PuzzleTipUtil::PopTip(SexyString tip, Rect rect)
{
	PuzzleTip* tipPtr = new PuzzleTip();
	tipPtr->mWidgetFlagsMod.mAddFlags |= 0x10;
	tipPtr->SetTip(tip);
	tipPtr->Resize(rect);
	gLawnApp->mWidgetManager->AddWidget(tipPtr);
	gLawnApp->mWidgetManager->BringToFront(tipPtr);
	return tipPtr;
}

void PuzzleTipUtil::DeleteTip(PuzzleTip* tipPtr)
{
	if (tipPtr != NULL)
	{
		gLawnApp->mWidgetManager->RemoveWidget(tipPtr);
		gLawnApp->SafeDeleteWidget(tipPtr);
	}
}

Rect PuzzleTipUtil::CreateTipRect(Point pos, int buttonWidth)
{
	return Rect(pos.mX + (buttonWidth - 468) / 2, pos.mY - 123 + UI_S(5), 468, 123);
}
